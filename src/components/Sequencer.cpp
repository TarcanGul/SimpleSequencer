#include "Sequencer.h"

Sequencer::Sequencer() {
    int startingX = getX();
    int startingY = getY();

    int currentX = startingX;
    int currentY = startingY;

    for(int i = 0; i < NUM_SOUNDS; i++) {
        juce::FlexBox * soundLine = new juce::FlexBox();
        soundList.push_back(soundLine);
        soundLine->alignContent = juce::FlexBox::AlignContent::center;

        juce::TextButton * soundLabelButton = new juce::TextButton();
        allButtons.push_back(soundLabelButton);
        soundLabelButton->setButtonText("Sound " + std::to_string(i + 1));

        addAndMakeVisible(soundLabelButton);

        soundLine->items.add(juce::FlexItem(* soundLabelButton).withFlex(3.0).withMargin(1.0).withMinWidth(20.0));

        // Add gap
        soundLine->items.add(juce::FlexItem().withFlex(0.5));
 
        for(int j = 0; j < NUM_BEATS; j++) {
            juce::TextButton * button = new juce::TextButton();
            allButtons.push_back(button);
            addAndMakeVisible(button);
            soundLine->items.add(juce::FlexItem(* button).withFlex(1.0).withMargin(4.0).withMinWidth(10.0));
        }
        soundLine->performLayout(juce::Rectangle<int>(currentX, currentY, getWidth() - LINE_SIDE_MARGIN, LINE_HEIGHT));
        currentY += LINE_HEIGHT + LINE_VERTICAL_GAP;
    }
}

Sequencer::~Sequencer()
{
    // Clear the buttons
    for(auto button : allButtons) {
        delete button;
    }

    for(auto soundLine : soundList) {
        soundLine->items.clear();
        delete soundLine;
    }
}

void Sequencer::resized() {
    int startingX = getX();
    int startingY = getY();

    int lineHeight = 50;

    int currentX = startingX;
    int currentY = startingY;

    for(auto it = soundList.begin(); it != soundList.end(); ++it) {
        (**it).performLayout(juce::Rectangle<int>(currentX, currentY, getWidth()-20, lineHeight));
        currentY += lineHeight + 20;
    }
}
