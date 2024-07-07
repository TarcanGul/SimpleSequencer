#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include "../components/SoundLine.h"
#include "SequenceTimer.h"
#include "../types/AudioTypes.h"


class SoundEngine {
public:
    SoundEngine();
    virtual ~SoundEngine();

    void playAll(std::vector<AudioFileData *> sounds);
    void pauseAll();
private:
    juce::MixerAudioSource mixerAudioSource;
    juce::AudioFormatManager audioFormatManager;
    juce::AudioSourcePlayer audioSourcePlayer;
    juce::AudioDeviceManager deviceManager;

    std::vector<AudioFileData *> allSounds;
    SequenceTimer timer;
    int beatCounter = 0;

    void onBeatHit();

    static const int SAMPLE_BLOCK_SIZE = 128;
    static const int SAMPLE_RATE = 44100;

};