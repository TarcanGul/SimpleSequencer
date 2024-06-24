
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include "../components/SoundLine.h"
#include "SequenceTimer.h";


class SoundEngine {
public:
    SoundEngine();
    ~SoundEngine();

    void playAll(std::vector<SoundLine *> sounds);
    void pauseAll();
private:
    void prepareFileToPlay(juce::File& file);

    // std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    // juce::AudioTransportSource audioPlaySource;
    juce::MixerAudioSource mixerAudioSource;
    juce::AudioFormatManager audioFormatManager;
    juce::AudioSourcePlayer audioSourcePlayer;
    juce::AudioDeviceManager deviceManager;

    std::vector<int> currentSoundSequence;
    std::vector<std::vector<int>> allSequences;
    std::vector<juce::AudioFormatReaderSource *> allReaderSources;
    std::vector<juce::AudioTransportSource *> allTransportSources;
    SequenceTimer timer;
    int beatCounter = 0;

    void onBeatHit();

    static const int SAMPLE_BLOCK_SIZE = 128;

};