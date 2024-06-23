#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <vector>

class SoundLine : public juce::Component, 
                  public juce::Button::Listener
{
public:
    SoundLine();
    ~SoundLine() override;

    juce::File getCurrentFile();

    void resized() override;

private:
    juce::FlexBox container;
    juce::TextButton labelButton;
    std::vector<juce::Button *> beatButtons;
    std::unique_ptr<juce::FileChooser> fileChooser;

    juce::File audioFile;
    std::vector<int> currentSequence;

    static const int NUM_BEATS = 8;
    static const int LINE_VERTICAL_GAP = 20;
    static const int LINE_SIDE_MARGIN = 20;
    static const int LINE_HEIGHT = 50;

    int findIndex(std::vector<juce::Button *> buttons, juce::Button * inputButton);

    // debug functions
    void printSequence(std::vector<int> sequence);

    void buttonClicked(juce::Button * button) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundLine)
};