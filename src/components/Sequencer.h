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
private:
    std::vector<SoundLine *> soundList;
    static const int NUM_SOUNDS = 6;
    static const int LINE_HEIGHT = 50;
    static const int LINE_VERTICAL_GAP = 20;
    static const int LINE_SIDE_MARGIN = 20;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Sequencer)
};