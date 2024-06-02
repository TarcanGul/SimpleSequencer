#include "MainComponent.h"

void MainComponent::getLayout() {
    box.flexDirection = juce::FlexBox::Direction::row;

    box.items.addArray({
        juce::FlexItem(label1).withFlex(1.0).withMinWidth(50.0),
        juce::FlexItem(label2).withFlex(1.0).withMinWidth(50.0)
    });
}

//==============================================================================
MainComponent::MainComponent()
{
    setSize (1000, 1000);
    setOpaque(true);

    label1.setText("Left side", juce::NotificationType::dontSendNotification);
    label1.setBounds(getLocalBounds());
    label1.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label1);

    label2.setText("Changed text.", juce::NotificationType::dontSendNotification);
    label2.setBounds(getLocalBounds());
    label2.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label2);

    box.flexDirection = juce::FlexBox::Direction::row;

    box.items.addArray({
        juce::FlexItem(label1).withFlex(1.0).withMinWidth(50.0),
        juce::FlexItem(label2).withFlex(1.0).withMinWidth(50.0)
    });
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

    box.performLayout(getLocalBounds());
}

void MainComponent::resized()
{

}
