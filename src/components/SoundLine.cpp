#include "SoundLine.h"

SoundLine::SoundLine() {
    container.alignContent = juce::FlexBox::AlignContent::center;

    fileChooser = std::make_unique<juce::FileChooser>(
        "Please select the sound file you want to load.",
        juce::File(),
        "*.wav,*.aiff"
    );

    labelButton.setButtonText("<no sound>");

    audioFileData = std::make_shared<AudioFileData>();

    // Setup sequencer state
    for(int i = 0; i < NUM_BEATS; i++) {
        audioFileData->sequence.push_back(0);
    }

    container.items.addArray({
        juce::FlexItem(labelButton).withFlex(3.0).withMargin(1.0).withMinWidth(20.0),
        juce::FlexItem().withFlex(0.5), // gap
    });

    labelButton.addListener(this);
    addAndMakeVisible(labelButton);

    for(int i = 0; i < NUM_BEATS; i++) {
        juce::Button * button = new juce::ToggleButton();
        beatButtons.push_back(button);
        button->addListener(this);
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

std::shared_ptr<AudioFileData> SoundLine::getCurrentFileData() {
    if(hasFile) {
        return audioFileData;
    }
    else {
        return nullptr;
    }
}

void SoundLine::resized() {
    container.performLayout(getLocalBounds());
}

int SoundLine::findIndex(std::vector<juce::Button *> buttons, juce::Button *inputButton)
{
    for(int i = 0; i < buttons.size(); i++) {
        if(buttons.at(i) == inputButton) {
            return i;
        }
    }

    return -1;
}

void SoundLine::buttonClicked(juce::Button *button)
{
    if(button == &labelButton) {
        int fileChooserFlags = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles;
        fileChooser->launchAsync(fileChooserFlags, [this] (const juce::FileChooser& chooser) {
            if(chooser.getResult() != juce::File()) {
                juce::File selectedFile (chooser.getResult());
                this->audioFileData->file = std::make_shared<juce::File>(selectedFile);
                this->audioFileData->sourcesNeedUpdate = true;
                this->hasFile = true;
                labelButton.setButtonText(selectedFile.getFileName());
            }
        });
        return;
    }
    
    int beatButtonIndex = findIndex(beatButtons, button);

    if(beatButtonIndex != -1) {
        audioFileData->sequence[beatButtonIndex] = button->getToggleState();
    }
}

void SoundLine::printSequence(std::vector<int> sequence) {
    std::cout << "Sequence is ";
    for(int i = 0; i < sequence.size(); i++) {
        std::cout << sequence[i];
    }

    std::cout << std::endl;
}

