#include "SoundEngine.h"

SoundEngine::SoundEngine() {
    audioFormatManager.registerBasicFormats();
    audioPlaySource.setPosition(0.0);
    deviceManager.initialise(0, 2, nullptr, true);
    deviceManager.addAudioCallback(&audioSourcePlayer);
    audioSourcePlayer.setSource(&audioPlaySource);
}

SoundEngine::~SoundEngine()
{
    audioPlaySource.releaseResources();
    audioSourcePlayer.setSource(nullptr);
    deviceManager.removeAudioCallback(&audioSourcePlayer);
    deviceManager.closeAudioDevice();
}

void SoundEngine::playAll(std::vector<SoundLine *> sounds)
{
    SoundLine * firstSound = sounds[0];
    juce::File lineFile = firstSound->getCurrentFile();
    std::cout << "File about to played is " << lineFile.getFileName() << std::endl;

    juce::AudioFormatReader * reader = audioFormatManager.createReaderFor (lineFile);
    readerSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
    audioPlaySource.setSource(readerSource.get(), 0, nullptr, reader->sampleRate);
    audioPlaySource.prepareToPlay(SAMPLE_BLOCK_SIZE, reader->sampleRate);

    audioPlaySource.start();
}

void SoundEngine::pauseAll()
{
    if(audioPlaySource.isPlaying()) {
        audioPlaySource.stop();
        audioPlaySource.setPosition(0.0);
    }
}

