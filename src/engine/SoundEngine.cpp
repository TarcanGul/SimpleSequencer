#include "SoundEngine.h"

SoundEngine::SoundEngine(juce::MixerAudioSource& mixerAudioSource, juce::AudioFormatManager& audioFormatManager, juce::AudioSourcePlayer& audioSourcePlayer, juce::AudioDeviceManager& deviceManager) :
mixerAudioSource_(mixerAudioSource),
audioFormatManager_(audioFormatManager),
audioSourcePlayer_(audioSourcePlayer),
deviceManager_(deviceManager),
timer(120, std::bind(&SoundEngine::onBeatHit, this)), 
allSounds(INIT_NUM_OF_SOUNDS) {
    audioFormatManager_.registerBasicFormats();
    deviceManager_.initialise(0, 2, nullptr, true);
    deviceManager_.addAudioCallback(&audioSourcePlayer_);
    audioSourcePlayer_.setSource(&mixerAudioSource_);
}

SoundEngine::~SoundEngine() {
    for(const auto& sound : allSounds) {
        if(sound != nullptr && sound->file != nullptr) {
            sound->formatReaderSource->releaseResources();
        }
    }

    audioSourcePlayer_.setSource(nullptr);
    deviceManager_.removeAudioCallback(&audioSourcePlayer_);
    deviceManager_.closeAudioDevice();
}

void SoundEngine::playAll(std::vector<AudioFileData *> sounds)
{
    // Prepare sounds by making sure the vector is updated with the sounds in the argument.
    for(int i = 0; i < sounds.size(); ++i) {
        this->allSounds[i] = sounds[i];
    }

    // Play files
    for(int i = 0; i < this->allSounds.size(); ++i) {
        auto * currentAudioFileData = this->allSounds.at(i);
        if(currentAudioFileData == nullptr) {
            continue;
        }
        if(currentAudioFileData->sourcesNeedUpdate) {
            if(currentAudioFileData->transportSource != nullptr) {
                currentAudioFileData->transportSource->setSource(nullptr);
            }

            juce::AudioFormatReader * reader = audioFormatManager_.createReaderFor (*currentAudioFileData->file);
            if(reader != nullptr) {
                currentAudioFileData->formatReaderSource = std::make_shared<juce::AudioFormatReaderSource>(reader, true);
                currentAudioFileData->transportSource = std::make_shared<juce::AudioTransportSource>();
                currentAudioFileData->transportSource->setSource(currentAudioFileData->formatReaderSource.get(), 0, nullptr, SAMPLE_RATE);
            }
            currentAudioFileData->sourcesNeedUpdate = false;
        }

        mixerAudioSource_.addInputSource(currentAudioFileData->transportSource.get(), false);
    }
    mixerAudioSource_.prepareToPlay(SAMPLE_BLOCK_SIZE, SAMPLE_RATE);
    timer.start();
}

void SoundEngine::pauseAll()
{
    if(timer.isTimerRunning()) {
        for(const auto& sound : allSounds) {
            if(sound == nullptr || sound->transportSource == nullptr) {
                continue;
            }
            sound->transportSource->stop();
            sound->transportSource->setPosition(0.0);
        }
        mixerAudioSource_.removeAllInputs();
        timer.stop();
        beatCounter = 0;
    }
}

void SoundEngine::setBpm(double bpm)
{
    timer.setBpm(bpm);
}

void SoundEngine::onBeatHit()
{
    for(int i = 0 ; i < allSounds.size(); i++) {
        auto sound = allSounds[i];
        if(sound == nullptr || sound->transportSource == nullptr) {
            continue;
        }
        if(sound->transportSource->isPlaying() || sound->transportSource->hasStreamFinished()) {
            sound->transportSource->stop();
            sound->transportSource->setPosition(0.0);
        }

        if(sound->sequence.empty()) {
            continue;
        }

        if(sound->sequence[beatCounter] > 0) {
            sound->transportSource->start();
        }
    }

    beatCounter++;
    beatCounter %= numBeats;
}
