#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <stdexcept>
#include "../components/SoundLine.h"
#include "SequenceTimer.h"
#include "../types/AudioTypes.h"


class SoundEngine {
public:
    SoundEngine(juce::MixerAudioSource& mixerAudioSource, 
        juce::AudioFormatManager& audioFormatManager,
        juce::AudioSourcePlayer& audioSourcePlayer,
        juce::AudioDeviceManager& deviceManager);
    virtual ~SoundEngine();

    void playAll(std::vector<AudioFileData *> sounds);
    void pauseAll();
private:
    juce::MixerAudioSource& mixerAudioSource_;
    juce::AudioFormatManager& audioFormatManager_;
    juce::AudioSourcePlayer& audioSourcePlayer_;
    juce::AudioDeviceManager& deviceManager_;

    std::vector<AudioFileData *> allSounds;
    SequenceTimer timer;
    int numBeats = 8;
    int beatCounter = 0;

    void onBeatHit();

    static const int SAMPLE_BLOCK_SIZE = 128;
    static const int SAMPLE_RATE = 44100;
    static const int INIT_NUM_OF_SOUNDS = 6;

};