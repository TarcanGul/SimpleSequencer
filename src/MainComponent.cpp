#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 600);

    // Set palette.
    lookAndFeel.setColour(ColorPalette::Background, juce::Colour::fromRGBA(100, 13, 107, 255));
    lookAndFeel.setColour(ColorPalette::Primary, juce::Colour::fromRGBA(181, 27, 117, 255));
    lookAndFeel.setColour(ColorPalette::Secondary, juce::Colour::fromRGBA(230, 92, 25, 255));
    lookAndFeel.setColour(ColorPalette::Light, juce::Colour::fromRGBA(248, 208, 130, 255));

    backgroundRectangle.setFill(lookAndFeel.findColour(ColorPalette::Background));
    backgroundRectangle.setCornerSize(juce::Point<float>(10.0f, 10.0f));

    appSection.alignContent = juce::FlexBox::AlignContent::center;
    appSection.flexDirection = juce::FlexBox::Direction::column;

    appSection.items = {
        juce::FlexItem(buttonSection).withFlex(0.2),
        juce::FlexItem().withFlex(0.8)
    };

    buttonSection.alignContent = juce::FlexBox::AlignContent::center;
    buttonSection.items = { 
        juce::FlexItem(addSoundButton).withFlex(1.0).withMinWidth(10.0), 
        juce::FlexItem(changeTimeSignatureButton).withFlex(1.0).withMinWidth(10.0), 
        juce::FlexItem(bpmSlider).withFlex(1.0).withMinWidth(10.0) 
    };

    addAndMakeVisible(backgroundRectangle, 0);
    addAndMakeVisible(addSoundButton);
    addAndMakeVisible(changeTimeSignatureButton);
    addAndMakeVisible(bpmSlider);

    appSection.performLayout(backgroundRectangle.getBounds());
    buttonSection.performLayout(appSection.items.getFirst().currentBounds);
}

void MainComponent::resized()
{
    juce::Rectangle<int> background = getLocalBounds().reduced(BACKGROUND_RECT_MARGIN);
    int backgroundWidth = background.getWidth();
    int backgroundHeight = background.getHeight();

    backgroundRectangle.setRectangle(juce::Rectangle<float>(BACKGROUND_RECT_MARGIN, BACKGROUND_RECT_MARGIN, backgroundWidth, backgroundHeight));

    appSection.performLayout(backgroundRectangle.getBounds());
    buttonSection.performLayout(appSection.items.getFirst().currentBounds);
}
