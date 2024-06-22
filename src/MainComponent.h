#pragma once

// CMake builds don't use an AppConfig.h, so it's safe to include juce module headers
// directly. If you need to remain compatible with Projucer-generated builds, and
// have called `juce_generate_juce_header(<thisTarget>)` in your CMakeLists.txt,
// you could `#include <JuceHeader.h>` here instead, to make all your module headers visible.
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include "./components/Sequencer.h"
#include "./engine/SoundEngine.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent final : public juce::Component,
                            public juce::Button::Listener
{
public:
    //==============================================================================
    MainComponent();

    //==============================================================================
    void resized() override;


private:
    //==============================================================================
    // Your private member variables go here...
    const int BACKGROUND_RECT_MARGIN = 5;
    juce::LookAndFeel_V4 lookAndFeel;
    juce::DrawableRectangle backgroundRectangle;

    juce::FlexBox appSection;

    juce::FlexBox buttonSection;
    juce::TextButton addRowButton;
    std::unique_ptr<juce::DrawableButton> playButton;
    std::unique_ptr<juce::DrawableButton> resetButton;
    juce::TextButton changeTimeSignatureButton;
    juce::Slider bpmSlider;

    Sequencer sequencer;
    SoundEngine soundEngine;

    enum ColorPalette {
        Background, 
        Primary, 
        Secondary,
        Light
    };

    void buttonClicked(juce::Button * button) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
