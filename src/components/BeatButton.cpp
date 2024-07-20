#include "BeatButton.h"

BeatButton::BeatButton(const juce::String& buttonName) : juce::Button(buttonName)
{
    buttonName_ = buttonName;
    setClickingTogglesState(true);
}

void BeatButton::resized()
{
}

void BeatButton::paintButton(juce::Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    int markerAreaWidth = 10;
    int markerAreaHeight = 7;

    juce::Rectangle<float> buttonArea(xPos_, yPos_, 20, 28);
    juce::Rectangle<float> markerArea(xPos_ + markerAreaWidth / 2, yPos_ + 5, markerAreaWidth, markerAreaHeight);

    if(shouldDrawButtonAsHighlighted) {
        g.setColour(juce::Colours::whitesmoke);
        g.fillRoundedRectangle(markerArea, 10.0);
    }
    else if(getToggleState()) {
        g.setColour(juce::Colour::fromRGBA(230, 92, 25, 255));
        g.fillRoundedRectangle(markerArea, 10.0);
    }
    else {
        g.setColour(juce::Colour::fromRGBA(230, 92, 25, 255));
        g.drawRoundedRectangle(markerArea, 10.0, 1.0);
    }

    g.setColour(juce::Colour::fromRGBA(230, 92, 25, 255));
    g.drawRoundedRectangle(buttonArea, 10.0, 1.0);

    g.setColour(juce::Colours::black);
    g.drawEllipse(markerArea, 1.5);

}

void BeatButton::setPosition(int x, int y)
{
    xPos_ = x;
    yPos_ = y;
}