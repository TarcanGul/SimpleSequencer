#include "SoundEngine.h"

SoundEngine::SoundEngine() {
    audioFormatManager.registerBasicFormats();
    audioPlaySource.setPosition(0.0);
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
    // For each sound, play the selected file if there is any in the given sequence.
    // for(auto it = sounds.begin(); it != sounds.end(); ++it) {
    //     juce::File lineFile = (*it)->getCurrentFile();
    //     std::unique_ptr<juce::AudioFormatReader> reader (audioFormatManager.createReaderFor (lineFile));
    //     if(reader.get() != nullptr) {
    //         auto duration = reader->lengthInSamples / reader->sampleRate;
    //         buffer.setSize(reader->numChannels, reader->lengthInSamples);
    //         reader->read(&buffer, 0, reader->lengthInSamples, 0, true, true);
    //     }
    // }
    // Proof of concept with one sound.
    SoundLine * firstSound = sounds[0];
    juce::File lineFile = firstSound->getCurrentFile();
    std::cout << "File about to played is " << lineFile.getFileName() << std::endl;

    juce::AudioFormatReader * reader = audioFormatManager.createReaderFor (lineFile);
    readerSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
    audioPlaySource.setSource(readerSource.get(), 0, nullptr, reader->sampleRate);
    audioPlaySource.prepareToPlay(128, reader->sampleRate);

    deviceManager.initialise(0, 2, nullptr, true);
    deviceManager.addAudioCallback(&audioSourcePlayer);

    audioSourcePlayer.setSource(&audioPlaySource);
    audioPlaySource.start();
}

void SoundEngine::pauseAll()
{
    if(audioPlaySource.isPlaying()) {
        audioPlaySource.stop();
    }
}

