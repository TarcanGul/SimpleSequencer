#include "SoundEngine.h"

SoundEngine::SoundEngine() : 
timer(120, std::bind(&SoundEngine::onBeatHit, this)), allSounds(6) {
    audioFormatManager.registerBasicFormats();
    deviceManager.initialise(0, 2, nullptr, true);
    deviceManager.addAudioCallback(&audioSourcePlayer);
    audioSourcePlayer.setSource(&mixerAudioSource);
}

SoundEngine::~SoundEngine()
{
    for(const auto& sound : allSounds) {
        if(sound->file != nullptr) {
            sound->formatReaderSource->releaseResources();
        }
    }

    audioSourcePlayer.setSource(nullptr);
    deviceManager.removeAudioCallback(&audioSourcePlayer);
    deviceManager.closeAudioDevice();
}

void SoundEngine::playAll(std::vector<AudioFileData *> sounds)
{
    int sampleRate = 44100;
    for(int i = 0; i < sounds.size(); ++i) {
        auto * currentAudioData = sounds[i];
        if(currentAudioData == nullptr) {
            continue;
        }
        this->allSounds[i] = currentAudioData;
        std::shared_ptr<juce::File> lineFile = currentAudioData->file;
        if(lineFile == nullptr) {
            this->allSounds[i]->file = nullptr;
            this->allSounds[i]->sequence = {};
            this->allSounds[i]->formatReaderSource = nullptr;
            this->allSounds[i]->transportSource = nullptr;
            continue;
        }
        
        this->allSounds[i]->file = lineFile;
        this->allSounds[i]->sequence = sounds.at(i)->sequence;
        juce::AudioFormatReader * reader = audioFormatManager.createReaderFor (*lineFile);
        if(reader != nullptr) {
            //sounds[i]->formatReaderSource = std::make_shared<juce::AudioFormatReaderSource>(reader, true);
            this->allSounds[i]->formatReaderSource = std::make_shared<juce::AudioFormatReaderSource>(reader, true);
            //sounds[i] -> transportSource = std::make_shared<juce::AudioTransportSource>();
            this->allSounds[i]->transportSource = std::make_shared<juce::AudioTransportSource>();
            this->allSounds[i]->transportSource->setSource(this->allSounds[i]->formatReaderSource.get(), 0, nullptr, reader->sampleRate);
            mixerAudioSource.addInputSource(this->allSounds[i]->transportSource.get(), false);
            sampleRate = reader->sampleRate;
        }
    }
    mixerAudioSource.prepareToPlay(SAMPLE_BLOCK_SIZE, sampleRate);
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
            sound->transportSource->setSource(nullptr);
        }
        mixerAudioSource.removeAllInputs();
        timer.stop();
        beatCounter = 0;
    }
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
    beatCounter %= 8;
}
