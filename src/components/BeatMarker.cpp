#include "BeatMarker.h"

BeatMarker::BeatMarker(int initNumOfBeats) : num_beats_(initNumOfBeats)
{
    container.alignContent = juce::FlexBox::AlignContent::center;
    // gap aligned with the sound lines.
    container.items.add(juce::FlexItem().withFlex(4.0).withMargin(1.0).withMinWidth(10.0));
    for(int i = 0; i < num_beats_; ++i) {
        juce::FlexItem flexItemWrapper;
        flexItemWrapper = flexItemWrapper.withFlex(1.0).withMargin(1.0).withMinWidth(2.0);
        container.items.add(flexItemWrapper);
    }

    container.performLayout(getLocalBounds());
}

BeatMarker::~BeatMarker()
{
    rectangles.clear();
}

void BeatMarker::paint(juce::Graphics &g)
{
    // Paint the rectangles
    g.setColour(juce::Colours::black);

    g.fillRectList(rectangles);

    if(marked_beat_ != -1) {
        juce::Rectangle<float> markedRectangle = rectangles.getRectangle(marked_beat_);
        g.setColour(juce::Colours::white);
        g.fillRect(markedRectangle);
    }
}

void BeatMarker::updateMarkedBeat(int newBeat)
{
    marked_beat_ = newBeat;
    const juce::MessageManagerLock mmLock;
    repaint();
}

void BeatMarker::resized() {

    rectangles.clear();
    container.performLayout(getLocalBounds());

    for(int i = 0; i < num_beats_; ++i) {
        juce::Rectangle<float> border(container.items[i + 1].currentBounds.getX(),container.items[i + 1].currentBounds.getY() + MARGIN_TOP, 20, 5);
        rectangles.add(border);
    }
}
