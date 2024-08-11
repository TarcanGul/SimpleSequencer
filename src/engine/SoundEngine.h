#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <stdexcept>
#include "../components/SoundLine.h"
#include "SequenceTimer.h"
#include "../types/AudioTypes.h"

// Event handler function for subscribing to events. Currently provides int value, can change in the future.
typedef std::function<void(int)> Handler;

enum class SoundEngineEvent {
    BEAT_ADVANCE
};

class SoundEngine {
public:
    SoundEngine(juce::MixerAudioSource& mixerAudioSource, 
        juce::AudioFormatManager& audioFormatManager,
        juce::AudioSourcePlayer& audioSourcePlayer,
        juce::AudioDeviceManager& deviceManager,
        double defaultBpm = 120);
    virtual ~SoundEngine();

    void playAll(std::vector<AudioFileData *> sounds);
    void pauseAll();
    void setBpm(double bpm);
    void subscribe(SoundEngineEvent event, Handler onEvent);
private:

    juce::MixerAudioSource& mixerAudioSource_;
    juce::AudioFormatManager& audioFormatManager_;
    juce::AudioSourcePlayer& audioSourcePlayer_;
    juce::AudioDeviceManager& deviceManager_;

    std::vector<AudioFileData *> allSounds;
    std::map<SoundEngineEvent, Handler> subscriptonMap;
    SequenceTimer timer;
    int numBeats = 8;
    int beatCounter = 0;

    void onBeatHit();
    void fireEvent(SoundEngineEvent event, int data);

    static const int SAMPLE_BLOCK_SIZE = 128;
    static const int SAMPLE_RATE = 44100;
    static const int INIT_NUM_OF_SOUNDS = 6;
};