#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (1000, 1000);

    int backgroundWidth = getLocalBounds().reduced(10).getWidth();
    int backgroundHeight = getLocalBounds().reduced(10).getHeight();

    int x = (getWidth() - static_cast<int>(backgroundWidth)) / 2;
    int y = (getHeight() - static_cast<int>(backgroundHeight)) / 2;

    backgroundRectangle.setFill(juce::Colours::red);
    backgroundRectangle.setRectangle(juce::Rectangle<float>(x, y, backgroundWidth, backgroundHeight));
    backgroundRectangle.setCornerSize(juce::Point<float>(10.0f, 10.0f));

    addAndMakeVisible(backgroundRectangle, 0);
}

void MainComponent::resized()
{
    int backgroundWidth = getLocalBounds().reduced(10).getWidth();
    int backgroundHeight = getLocalBounds().reduced(10).getHeight();

    int x = (getWidth() - static_cast<int>(backgroundWidth)) / 2;
    int y = (getHeight() - static_cast<int>(backgroundHeight)) / 2;

    backgroundRectangle.setRectangle(juce::Rectangle<float>(x, y, backgroundWidth, backgroundHeight));
}
