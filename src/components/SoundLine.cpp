#include "SoundLine.h"

SoundLine::SoundLine() {
    container.alignContent = juce::FlexBox::AlignContent::center;

    labelButton.setButtonText("<no sound>");

    container.items.addArray({
        juce::FlexItem(labelButton).withFlex(3.0).withMargin(1.0).withMinWidth(20.0),
        juce::FlexItem().withFlex(0.5), // gap
    });

    addAndMakeVisible(labelButton);

    for(int i = 0; i < NUM_BEATS; i++) {
        juce::TextButton * button = new juce::TextButton();
        beatButtons.push_back(button);
        addAndMakeVisible(button);
        container.items.add(juce::FlexItem(* button).withFlex(1.0).withMargin(4.0).withMinWidth(10.0));
    }

    container.performLayout(getLocalBounds());
}

SoundLine::~SoundLine()
{
    for(auto button : beatButtons) {
        delete button;
    }
}

void SoundLine::resized() {
    container.performLayout(getLocalBounds());
}
