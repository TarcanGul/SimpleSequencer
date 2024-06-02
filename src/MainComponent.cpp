#include "MainComponent.h"

// void setLayout() {
//     juce::Label * label1 = new juce::Label();
//     label1->setText("Left side", juce::NotificationType::dontSendNotification);

//     juce::Label * label2 = new juce::Label();
//     label2->setText("Right side", juce::NotificationType::dontSendNotification);

//     juce::FlexBox box;

//     juce::FlexItem item1;
//     item1.withWidth(50.0);
//     item1.associatedComponent = label1;

//     juce::FlexItem item2;
//     item2.withWidth(50.0);
//     item2.associatedComponent = label2;

//     box.items.add(item1, item2);
// }

//==============================================================================
MainComponent::MainComponent()
{
    setSize (1000, 1000);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::white);
    // setLayout();
    g.drawText ("Hello World!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
