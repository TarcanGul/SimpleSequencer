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
        juce::FlexItem(sequencerViewport).withFlex(0.9f)
    };

    addRowButton.setButtonText("Add row");
    addRowButton.setColour(addRowButton.buttonColourId, lookAndFeel.findColour(ColorPalette::Primary));
    addRowButton.setColour(addRowButton.textColourOffId, lookAndFeel.findColour(ColorPalette::Light));
    addRowButton.setColour(addRowButton.textColourOnId, juce::Colours::white);
    addRowButton.addListener(this);
    
    bpmSlider.setSliderStyle(juce::Slider::SliderStyle::IncDecButtons);
    bpmSlider.setIncDecButtonsMode(juce::Slider::IncDecButtonMode::incDecButtonsDraggable_Vertical);
    bpmSlider.setColour(bpmSlider.backgroundColourId, lookAndFeel.findColour(ColorPalette::Primary));
    bpmSlider.setColour(bpmSlider.trackColourId, lookAndFeel.findColour(ColorPalette::Primary));
    bpmSlider.setRange(MIN_BPM, MAX_BPM, 0.5);
    bpmSlider.setValue(DEFAULT_BPM);
    bpmSlider.setHelpText("BPM");

    try {
        soundEngine = std::make_unique<SoundEngine>(
            mixerAudioSource, 
            audioFormatManager, 
            audioSourcePlayer, 
            deviceManager, 
            bpmSlider.getValue());
    }
    catch (const std::exception& ex) {
        // Do nothing for now.
        std::cout << ex.what() << '\n';
    }

    bpmSlider.onValueChange = std::bind(&MainComponent::onBpmSliderChange, this);

    std::unique_ptr<juce::Drawable> playIcon = juce::Drawable::createFromImageFile(PLAY_ICON);
    std::unique_ptr<juce::Drawable> pauseIcon = juce::Drawable::createFromImageFile(PAUSE_ICON);
    std::unique_ptr<juce::Drawable> stopIcon = juce::Drawable::createFromImageFile(STOP_ICON);

    playButton = std::make_unique<juce::DrawableButton>("playButton", juce::DrawableButton::ImageOnButtonBackground);
    playButton->setToggleable(true);
    playButton->setColour(juce::TextButton::ColourIds::buttonColourId, lookAndFeel.findColour(ColorPalette::Primary));
    playButton->setColour(juce::TextButton::ColourIds::buttonOnColourId, lookAndFeel.findColour(ColorPalette::Secondary));
    playButton->setImages(playIcon.get(), nullptr, nullptr, nullptr, pauseIcon.get(), nullptr, nullptr, nullptr);
    playButton->addListener(this);
    
    resetButton = std::make_unique<juce::DrawableButton>("resetButton", juce::DrawableButton::ImageOnButtonBackground);
    resetButton->setImages(stopIcon.get());
    resetButton->setColour(juce::TextButton::ColourIds::buttonColourId, lookAndFeel.findColour(ColorPalette::Primary));
    resetButton->addListener(this);

    buttonSection.alignContent = juce::FlexBox::AlignContent::center;
    buttonSection.items = { 
        juce::FlexItem(addRowButton).withFlex(2.0).withMargin(juce::FlexItem::Margin(10)), 
        juce::FlexItem(bpmSlider).withFlex(1.0).withMargin(juce::FlexItem::Margin(10)),
        juce::FlexItem(*playButton).withFlex(0.5).withMargin(juce::FlexItem::Margin(5)),
        juce::FlexItem(*resetButton).withFlex(0.5).withMargin(juce::FlexItem::Margin(5))
    };
    buttonSection.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;

    addAndMakeVisible(backgroundRectangle, 0);
    addAndMakeVisible(addRowButton);
    addAndMakeVisible(bpmSlider);
    addAndMakeVisible(playButton.get());
    addAndMakeVisible(resetButton.get());
    addAndMakeVisible(sequencerViewport);
    
    // Letting the sequencer subscribe when the beat updates.
    soundEngine.get()->subscribe(SoundEngineEvent::BEAT_ADVANCE, [this](int updatedBeatValue) {
        this->sequencer.updateBeat(updatedBeatValue);
    });

    appSection.performLayout(backgroundRectangle.getBounds());
    buttonSection.performLayout(appSection.items.getFirst().currentBounds);
}

void MainComponent::resized()
{
    if(sequencerViewport.getViewedComponent() != nullptr) {
        sequencerViewport.getViewedComponent()->setSize(sequencerViewport.getWidth(), sequencer.getHeight());
    }
    else {
        sequencerViewport.setViewedComponent(&sequencer, false);
        sequencer.setSize(getWidth(), getHeight() * 0.9);
    }

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
    else if(button == &addRowButton) {
        sequencer.addRow();
    }
    else if(button == resetButton.get()) {
        soundEngine->reset();
    }
}

void MainComponent::onBpmSliderChange()
{
    double updatedValue = bpmSlider.getValue();
    soundEngine->setBpm(updatedValue);
}
