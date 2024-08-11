#include "BeatMarker.h"

BeatMarker::BeatMarker(int initNumOfBeats) : num_beats_(initNumOfBeats)
{
    // Left padding to move the marker to the right.
    // int currentX = getX() + 320;
    // int currentY = getY();

    // for(int i = 0; i < initNumOfBeats; ++i) {
    //     juce::Rectangle<float> border(currentX, currentY, 60, 20);
    //     currentX += 60;
    //     rectangles.add(border);
    // }

}

BeatMarker::~BeatMarker()
{
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
    repaint();
}

void BeatMarker::resized() {

    rectangles.clear();

    int currentX = getX() + (getWidth() / 3);
    int currentY = getY();

    for(int i = 0; i < num_beats_; ++i) {
        juce::Rectangle<float> border(currentX, currentY, 20, 20);
        currentX += getWidth() / 12;
        rectangles.add(border);
    }
}
