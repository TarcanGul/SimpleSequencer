#include "Sequencer.h"

Sequencer::Sequencer() {

    setSize(1200, 1200);

    for(int i = 0; i < NUM_SOUNDS; i++) {
        SoundLine * soundLine = new SoundLine();
        soundList.push_back(soundLine);
        addAndMakeVisible(soundLine);
    }

    int startingX = getX();
    int startingY = getY();

    int currentX = startingX;
    int currentY = startingY;
    for(auto * soundLine : soundList) {
        soundLine->setBounds(currentX, currentY, getWidth() - LINE_SIDE_MARGIN, LINE_HEIGHT);
        currentY += LINE_HEIGHT + LINE_VERTICAL_GAP;
    }

    lastX = currentX;
    lastY = currentY;
}

Sequencer::~Sequencer()
{
    for(auto * soundLine : soundList) {
        delete soundLine;
    }
}

void Sequencer::resized() {
    int startingX = getX();
    int startingY = getY();

    int currentX = startingX;
    int currentY = startingY;
    for(auto * soundLine : soundList) {
        soundLine->setBounds(currentX, currentY, getWidth() - LINE_SIDE_MARGIN, LINE_HEIGHT);
        currentY += LINE_HEIGHT + LINE_VERTICAL_GAP;
    }

    lastX = currentX;
    lastY = currentY;
}

std::vector<AudioFileData *> Sequencer::getSounds()
{
    std::vector<AudioFileData *> output;
    auto mapper = [] (SoundLine * line) {
        return line->getCurrentFileData().get();
    };
    std::transform(soundList.begin(), soundList.end(), std::back_inserter(output), mapper);
    return output;
}

void Sequencer::addRow()
{
    SoundLine * soundLine = new SoundLine();
    soundList.push_back(soundLine);
    soundLine->setBounds(lastX, lastY, getWidth() - LINE_SIDE_MARGIN, LINE_HEIGHT);
    lastY += LINE_HEIGHT + LINE_VERTICAL_GAP;
    addAndMakeVisible(soundLine);
}
