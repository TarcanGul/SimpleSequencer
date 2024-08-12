#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_events/juce_events.h>

class BeatMarker : public juce::Component {
public:
    BeatMarker(int initNumOfBeats);
    ~BeatMarker() override;

    void resized() override;
    void paint(juce::Graphics& g) override;
    void updateMarkedBeat(int newBeat);
private:
    const int MARGIN_TOP = 20;
    int num_beats_;
    int marked_beat_ = -1;
    juce::FlexBox container;
    std::vector<bool> beatBitmap;
    juce::RectangleList<float> rectangles;
};