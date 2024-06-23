#include "SoundEngine.h"

SoundEngine::SoundEngine() : timer(120, std::bind(&SoundEngine::onBeatHit, this)) {
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
    this->currentSoundSequence = firstSound->getCurrentSequence();
    std::cout << "File about to played is " << lineFile.getFileName() << std::endl;

    juce::AudioFormatReader * reader = audioFormatManager.createReaderFor (lineFile);
    if(reader != nullptr) {
        readerSource.reset(new juce::AudioFormatReaderSource(reader, true));
        // In here, we have the timer start, the callback would be the start and maybe the sequence.
        audioPlaySource.setSource(readerSource.get(), 0, nullptr, reader->sampleRate);
        audioPlaySource.prepareToPlay(SAMPLE_BLOCK_SIZE, reader->sampleRate);
        timer.start();
    }
}

void SoundEngine::pauseAll()
{
    if(timer.isTimerRunning()) {
        audioPlaySource.stop();
        audioPlaySource.setPosition(0.0);
        audioPlaySource.setSource(nullptr);
        timer.stop();
    }
}

void SoundEngine::prepareFileToPlay(juce::File &file)
{

}

void SoundEngine::onBeatHit()
{
    if(audioPlaySource.isPlaying() || audioPlaySource.hasStreamFinished()) {
        audioPlaySource.stop();
        audioPlaySource.setPosition(0.0);
    }
    // stop sound

    if(currentSoundSequence[beatCounter] > 0) {
        audioPlaySource.start();
    }
    beatCounter++;
    beatCounter %= currentSoundSequence.size();
}
