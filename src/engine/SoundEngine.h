
#include <juce_audio_basics/juce_audio_basics.h>
#include "../components/SoundLine.h"


class SoundEngine {
public:
    void playAll(std::vector<SoundLine *> sounds);
    void pauseAll();
private:
};