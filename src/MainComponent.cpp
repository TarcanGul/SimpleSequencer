#include "MainComponent.h"

juce::FlexBox * MainComponent::getLayout() {
    juce::Label * label1 = new juce::Label();
    label1->setText("Left side", juce::NotificationType::dontSendNotification);
    label1->setBounds(getLocalBounds());
    label1->setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label1);

    juce::Label * label2 = new juce::Label();
    label2->setText("Right side", juce::NotificationType::dontSendNotification);
    label2->setBounds(getLocalBounds());
    label2->setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label2);

    juce::FlexBox * box = new juce::FlexBox();
    box->flexDirection = juce::FlexBox::Direction::row;

    box->items.addArray({
        juce::FlexItem(* label1).withFlex(1.0).withMinWidth(50.0),
        juce::FlexItem(* label2).withFlex(1.0).withMinWidth(50.0)
    });

    return box;
}

//==============================================================================
MainComponent::MainComponent()
{
    setSize (1000, 1000);
    setOpaque(true);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // Clear background
    g.fillAll(juce::Colours::white);

    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::white);
    juce::FlexBox * box = getLayout();
    box->performLayout(getLocalBounds());
    //g.drawText ("Hello yo!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    repaint();
}
