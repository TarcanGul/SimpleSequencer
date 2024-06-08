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
        juce::FlexItem(buttonSection).withFlex(0.1f),
        juce::FlexItem(sequencer).withFlex(0.9f)
    };

    addRowButton.setButtonText("Add row");
    addRowButton.setColour(addRowButton.buttonColourId, lookAndFeel.findColour(ColorPalette::Primary));
    addRowButton.setColour(addRowButton.textColourOffId, lookAndFeel.findColour(ColorPalette::Light));
    addRowButton.setColour(addRowButton.textColourOnId, juce::Colours::white);

    changeTimeSignatureButton.setButtonText("Set time signature");
    changeTimeSignatureButton.setColour(changeTimeSignatureButton.buttonColourId, lookAndFeel.findColour(ColorPalette::Primary));
    changeTimeSignatureButton.setColour(changeTimeSignatureButton.textColourOffId, lookAndFeel.findColour(ColorPalette::Light));
    changeTimeSignatureButton.setColour(changeTimeSignatureButton.textColourOnId, juce::Colours::white);
    
    bpmSlider.setSliderStyle(juce::Slider::SliderStyle::IncDecButtons);
    bpmSlider.setIncDecButtonsMode(juce::Slider::IncDecButtonMode::incDecButtonsDraggable_Vertical);
    bpmSlider.setColour(bpmSlider.backgroundColourId, lookAndFeel.findColour(ColorPalette::Primary));
    bpmSlider.setColour(bpmSlider.trackColourId, lookAndFeel.findColour(ColorPalette::Primary));
    bpmSlider.setRange(80, 250, 0.5);
    bpmSlider.setHelpText("BPM");

    juce::Path playButtonShape;
    juce::Path resetButtonShape;

    juce::Path playButtonTop;
    juce::Path resetButtonTop;

    playButtonShape.addRectangle(0, 0, 100.0, 100.0);
    playButtonTop.addTriangle(30, 30, 30, 100, 50, 50);

    playButtonShape.addPath(playButtonTop);

    resetButtonShape.addRectangle(0, 0, 100.0, 100.0);
    resetButtonTop.addRectangle(0, 0, 50.0, 50.0);

    resetButtonShape.addPath(resetButtonTop);

    playButton = std::make_unique<juce::ShapeButton>("playButton", juce::Colours::azure, juce::Colours::black, juce::Colours::blue);
    playButton->setOutline(juce::Colours::black, 1.0f);

    resetButton = std::make_unique<juce::ShapeButton>("resetButton", lookAndFeel.findColour(ColorPalette::Primary), lookAndFeel.findColour(ColorPalette::Secondary), lookAndFeel.findColour(ColorPalette::Light));

    playButton->setShape(playButtonShape, true, true, false);
    resetButton->setShape(resetButtonShape, true, true, false);

    buttonSection.alignContent = juce::FlexBox::AlignContent::center;
    buttonSection.items = { 
        juce::FlexItem(addRowButton).withFlex(1.0).withMargin(juce::FlexItem::Margin(10)), 
        juce::FlexItem(changeTimeSignatureButton).withFlex(1.0).withMargin(juce::FlexItem::Margin(10)), 
        juce::FlexItem(bpmSlider).withFlex(1.0).withMargin(juce::FlexItem::Margin(10)),
        juce::FlexItem(*playButton).withFlex(0.5).withMargin(juce::FlexItem::Margin(5)),
        juce::FlexItem(*resetButton).withFlex(0.5).withMargin(juce::FlexItem::Margin(5))
    };
    buttonSection.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;

    addAndMakeVisible(backgroundRectangle, 0);
    addAndMakeVisible(addRowButton);
    addAndMakeVisible(changeTimeSignatureButton);
    addAndMakeVisible(bpmSlider);
    addAndMakeVisible(playButton.get());
    addAndMakeVisible(resetButton.get());
    addAndMakeVisible(sequencer);

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
