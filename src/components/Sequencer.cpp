#include "Sequencer.h"

Sequencer::Sequencer() : beatMarker(8) {

    setSize(600, NUM_SOUNDS * (LINE_VERTICAL_GAP + LINE_HEIGHT));

    for(int i = 0; i < NUM_SOUNDS; i++) {
        SoundLine * soundLine = new SoundLine();
        soundList.push_back(soundLine);
    }

    beatMarker.setBounds(0, 0, getWidth() - LINE_SIDE_MARGIN, LINE_HEIGHT);
    addAndMakeVisible(beatMarker);

    // Relative to parent 
    int startingX = 50;
    int startingY = 0;

    int currentX = startingX;
    int currentY = startingY;

    for(auto * soundLine : soundList) {
        soundLine->setBounds(currentX, currentY, getWidth() - LINE_SIDE_MARGIN, LINE_HEIGHT);
        addAndMakeVisible(soundLine);
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

    beatMarker.setBounds(0, 0, getWidth() - LINE_SIDE_MARGIN, LINE_HEIGHT);
    addAndMakeVisible(beatMarker);

    // Relative to parent 
    int startingX = 0;
    int startingY = 50;

    int currentX = startingX;

    // Center from y-axis.
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
    setSize(getWidth(), soundList.size() * (LINE_VERTICAL_GAP + LINE_HEIGHT));
    addAndMakeVisible(soundLine);
}

void Sequencer::updateBeat(int updatedBeatValue)
{
    beatMarker.updateMarkedBeat(updatedBeatValue);
}