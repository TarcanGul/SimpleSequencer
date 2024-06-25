
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include "../components/SoundLine.h"
#include "SequenceTimer.h"

struct AudioFileData {
    juce::File * file;
    std::vector<int> sequence;
    juce::AudioFormatReaderSource * formatReaderSource;
    juce::AudioTransportSource * transportSource;
};

class SoundEngine {
public:
    SoundEngine();
    ~SoundEngine();

    void playAll(std::vector<SoundLine *> sounds);
    void pauseAll();
private:
    juce::MixerAudioSource mixerAudioSource;
    juce::AudioFormatManager audioFormatManager;
    juce::AudioSourcePlayer audioSourcePlayer;
    juce::AudioDeviceManager deviceManager;

    std::vector<AudioFileData> allSounds;
    SequenceTimer timer;
    int beatCounter = 0;

    void onBeatHit();

    static const int SAMPLE_BLOCK_SIZE = 128;

};