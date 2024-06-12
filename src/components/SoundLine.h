#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <vector>

class SoundLine : public juce::Component {
public:
    SoundLine();
    ~SoundLine() override;

    void resized() override;

private:
    juce::FlexBox container;
    juce::TextButton labelButton;
    std::vector<juce::TextButton *> beatButtons;

    static unsigned const int NUM_BEATS = 8;
    static const int LINE_VERTICAL_GAP = 20;
    static const int LINE_SIDE_MARGIN = 20;
    static const int LINE_HEIGHT = 50;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundLine)
};