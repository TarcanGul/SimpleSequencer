#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <vector>
#include <memory>
#include "SoundLine.h"

class Sequencer : public juce::Component {
public:
    Sequencer();
    ~Sequencer() override;

    void resized() override;

    std::vector<AudioFileData *> getSounds();
    void addRow();

private:
    static const int NUM_SOUNDS = 6;
    static const int LINE_HEIGHT = 50;
    static const int LINE_VERTICAL_GAP = 20;
    static const int LINE_SIDE_MARGIN = 20;

    std::vector<SoundLine *> soundList;
    int lastX = 0;
    int lastY = 0;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Sequencer)
};