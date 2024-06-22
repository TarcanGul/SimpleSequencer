
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include "../components/SoundLine.h"


class SoundEngine {
public:
    SoundEngine();
    ~SoundEngine();

    void playAll(std::vector<SoundLine *> sounds);
    void pauseAll();
private:
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource audioPlaySource;
    juce::AudioFormatManager audioFormatManager;
    juce::AudioSourcePlayer audioSourcePlayer;
    juce::AudioDeviceManager deviceManager;

};