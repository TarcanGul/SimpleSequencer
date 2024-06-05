#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <vector>

class Sequencer : public juce::Component {
public:
    Sequencer();
    ~Sequencer();

    void resized() override;
private:
    std::vector<juce::FlexBox *> soundList;
    static const int NUM_SOUNDS = 4;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Sequencer)
};