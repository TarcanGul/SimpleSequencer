#include "Sequencer.h"

Sequencer::Sequencer() {
    // The sound list have to be dynamically created.

    const int NUM_BEATS  = 8;

    int startingX = getX();
    int startingY = getY();

    int lineHeight = 50;

    int currentX = startingX;
    int currentY = startingY;

    for(int i = 0; i < NUM_SOUNDS; i++) {
        juce::FlexBox * soundLine = new juce::FlexBox();

        juce::Label * label = new juce::Label();
        label->setText("Sound " + std::to_string(i), juce::NotificationType::dontSendNotification);

        // How not to leak the memory?
        std::vector<juce::TextButton> * buttons = new std::vector<juce::TextButton>(NUM_BEATS);

        addAndMakeVisible(label);

        soundLine->items.add(juce::FlexItem(*label).withFlex(3.0).withMargin(1.0).withMinWidth(20.0));
 
        for(int j = 0; j < NUM_BEATS; j++) {
            addAndMakeVisible(buttons->at(j));
            soundLine->items.add(juce::FlexItem(buttons->at(j)).withFlex(1.0).withMargin(1.0).withMinWidth(10.0));
        }
        soundLine->performLayout(juce::Rectangle<int>(currentX, currentY, getWidth(), lineHeight));
        currentY += lineHeight;
        soundList.push_back(soundLine);
    }
}

Sequencer::~Sequencer()
{
    for(auto soundLine : soundList) {
        for(auto it = soundLine->items.begin(); it != soundLine->items.end(); ++it) {
            delete it->associatedComponent;
        }
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
        (**it).performLayout(juce::Rectangle<int>(currentX, currentY, getWidth(), lineHeight));
        currentY += lineHeight;
    }
}
