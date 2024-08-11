#include "BeatMarker.h"

BeatMarker::BeatMarker(int initNumOfBeats) : num_beats_(initNumOfBeats)
{
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
    int currentWidth = getWidth();
    int unit = currentWidth / 12;

    int currentX = getX() + (4 * unit);
    int currentY = getY() + 10;

    for(int i = 0; i < num_beats_; ++i) {
        juce::Rectangle<float> border(currentX, currentY, 15, 5);
        currentX += unit;
        rectangles.add(border);
    }
}
