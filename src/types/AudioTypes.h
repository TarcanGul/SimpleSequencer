#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_audio_devices/juce_audio_devices.h>

struct AudioFileData {
    std::shared_ptr<juce::File> file;
    std::vector<int> sequence;
    bool sourcesNeedUpdate = false;
    std::shared_ptr<juce::AudioFormatReaderSource> formatReaderSource;
    std::shared_ptr<juce::AudioTransportSource> transportSource;

    AudioFileData() {
        file = nullptr;
        sequence = {};
        formatReaderSource = nullptr;
        transportSource = nullptr;
    }
    AudioFileData(AudioFileData& other);
};