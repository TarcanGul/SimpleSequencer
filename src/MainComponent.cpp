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
    bpmSlider.setRange(MIN_BPM, MAX_BPM, 0.5);
    bpmSlider.setValue(DEFAULT_BPM);
    bpmSlider.setHelpText("BPM");

    try {
        soundEngine = std::make_unique<SoundEngine>(mixerAudioSource, audioFormatManager, audioSourcePlayer, deviceManager);
        soundEngine.get()->setBpm((double) bpmSlider.getValue());
    }
    catch (const std::exception& ex) {
        // Do nothing for now.
        std::cout << ex.what() << '\n';
    }

    bpmSlider.onValueChange = std::bind(&MainComponent::onBpmSliderChange, this);
    // bpmSlider.onValueChange = [this] {onBpmSliderChange(); };

    std::unique_ptr<juce::Drawable> playIcon = juce::Drawable::createFromImageFile(juce::File("/Users/tarcangul/projects/simple-sequencer/src/assets/play.png"));
    std::unique_ptr<juce::Drawable> pauseIcon = juce::Drawable::createFromImageFile(juce::File("/Users/tarcangul/projects/simple-sequencer/src/assets/pause.png"));
    std::unique_ptr<juce::Drawable> stopIcon = juce::Drawable::createFromImageFile(juce::File("/Users/tarcangul/projects/simple-sequencer/src/assets/stop.png"));

    playButton = std::make_unique<juce::DrawableButton>("playButton", juce::DrawableButton::ImageOnButtonBackground);
    playButton->setToggleable(true);
    playButton->setColour(juce::TextButton::ColourIds::buttonColourId, lookAndFeel.findColour(ColorPalette::Primary));
    playButton->setColour(juce::TextButton::ColourIds::buttonOnColourId, lookAndFeel.findColour(ColorPalette::Secondary));
    playButton->setImages(playIcon.get(), nullptr, nullptr, nullptr, pauseIcon.get(), nullptr, nullptr, nullptr);
    playButton->addListener(this);
    
    resetButton = std::make_unique<juce::DrawableButton>("resetButton", juce::DrawableButton::ImageOnButtonBackground);
    resetButton->setImages(stopIcon.get());
    resetButton->setColour(juce::TextButton::ColourIds::buttonColourId, lookAndFeel.findColour(ColorPalette::Primary));

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

void MainComponent::buttonClicked(juce::Button *button)
{
    if(button == playButton.get()) {
        bool isPlaying = playButton -> getToggleState();
        if(!isPlaying) {
            // Should get everything from sequencer and be able to play it.
            auto allSounds = sequencer.getSounds();
            soundEngine->playAll(allSounds);
        }
        else {
            soundEngine->pauseAll();
        }

        playButton -> setToggleState(!isPlaying, juce::NotificationType::dontSendNotification);
    }
}

void MainComponent::onBpmSliderChange()
{
    double updated_value = bpmSlider.getValue();
    soundEngine->setBpm(updated_value);
}
