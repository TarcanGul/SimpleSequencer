#include "SoundEngine.h"

SoundEngine::SoundEngine() : 
timer(120, std::bind(&SoundEngine::onBeatHit, this)), 
allSequences(6),
allReaderSources(6), 
allTransportSources(6) {
    audioFormatManager.registerBasicFormats();
    // audioPlaySource.setPosition(0.0);
    deviceManager.initialise(0, 2, nullptr, true);
    deviceManager.addAudioCallback(&audioSourcePlayer);
   //audioSourcePlayer.setSource(&audioPlaySource);
   audioSourcePlayer.setSource(&mixerAudioSource);


}

SoundEngine::~SoundEngine()
{
    allReaderSources.clear();
    allTransportSources.clear();
    // audioPlaySource.releaseResources();
    audioSourcePlayer.setSource(nullptr);
    deviceManager.removeAudioCallback(&audioSourcePlayer);
    deviceManager.closeAudioDevice();
}

void SoundEngine::playAll(std::vector<SoundLine *> sounds)
{
    int sampleRate = 44100;
    for(int i = 0; i < sounds.size(); ++i) {
        juce::File * lineFile = sounds.at(i)->getCurrentFile();
        if(lineFile == nullptr) {
            this->allSequences[i] = {};
            this->allReaderSources[i] = nullptr;
            this->allTransportSources[i] = nullptr;
            continue;
        }
        std::vector<int> seq = sounds.at(i)->getCurrentSequence();
        this->allSequences[i] = seq;
        juce::AudioFormatReader * reader = audioFormatManager.createReaderFor (*lineFile);
        if(reader != nullptr) {
            auto * currentFileReaderSource = new juce::AudioFormatReaderSource(reader, true);
            auto * currentTransportSource = new juce::AudioTransportSource();
            allReaderSources.at(i) = currentFileReaderSource;
            allTransportSources.at(i) = currentTransportSource;
            currentTransportSource->setSource(currentFileReaderSource, 0, nullptr, reader->sampleRate);
            mixerAudioSource.addInputSource(currentTransportSource, true);
            sampleRate = reader->sampleRate;
        }
    }
    mixerAudioSource.prepareToPlay(SAMPLE_BLOCK_SIZE, sampleRate);
    timer.start();
}

void SoundEngine::pauseAll()
{
    if(timer.isTimerRunning()) {
        for(const auto& playSource : allTransportSources) {
            if(playSource == nullptr) {
                continue;
            }

            playSource->stop();
            playSource->setPosition(0.0);
            playSource->setSource(nullptr);
        }
        mixerAudioSource.removeAllInputs();
        timer.stop();
        beatCounter = 0;
    }
}

void SoundEngine::prepareFileToPlay(juce::File &file)
{

}

void SoundEngine::onBeatHit()
{
    for(const auto& playSource : allTransportSources) {
        if(playSource == nullptr) {
            continue;
        }
        if(playSource->isPlaying() || playSource->hasStreamFinished()) {
            playSource->stop();
            playSource->setPosition(0.0);
        }
    }

    for(int i = 0; i < allSequences.size(); i++) {
        if(allSequences.at(i).empty()) {
            continue;
        }
        if(allSequences.at(i)[beatCounter] > 0) {
            allTransportSources.at(i)->start();
        }
    }

    beatCounter++;
    beatCounter %= 8;
}
