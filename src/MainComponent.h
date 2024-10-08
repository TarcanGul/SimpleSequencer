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
    const int BACKGROUND_RECT_MARGIN = 5;
    const int DEFAULT_BPM = 120;
    const int MIN_BPM = 80;
    const int MAX_BPM = 200;

    const juce::File ASSETS_DIR = juce::File(__FILE__).getParentDirectory().getChildFile("assets");
    const juce::File PLAY_ICON = ASSETS_DIR.getChildFile("play.png");
    const juce::File PAUSE_ICON = ASSETS_DIR.getChildFile("pause.png");
    const juce::File STOP_ICON = ASSETS_DIR.getChildFile("stop.png");

    juce::LookAndFeel_V4 lookAndFeel;
    juce::DrawableRectangle backgroundRectangle;

    juce::FlexBox appSection;

    juce::FlexBox buttonSection;
    juce::TextButton addRowButton;
    std::unique_ptr<juce::DrawableButton> playButton;
    std::unique_ptr<juce::DrawableButton> resetButton;
    juce::Slider bpmSlider;

    Sequencer sequencer;
    juce::Viewport sequencerViewport;

    juce::MixerAudioSource mixerAudioSource;
    juce::AudioFormatManager audioFormatManager;
    juce::AudioSourcePlayer audioSourcePlayer;
    juce::AudioDeviceManager deviceManager;
    std::unique_ptr<SoundEngine> soundEngine;

    enum ColorPalette {
        Background, 
        Primary, 
        Secondary,
        Light
    };

    void buttonClicked(juce::Button * button) override;
    void onBpmSliderChange();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
