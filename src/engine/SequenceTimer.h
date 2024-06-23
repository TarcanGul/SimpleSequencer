#include <juce_core/juce_core.h>
#include <functional>

class SequenceTimer : public juce::HighResolutionTimer {
    public:
        SequenceTimer(unsigned int bpm, std::function<void()> timerCallback);
        ~SequenceTimer();
        void hiResTimerCallback () override;
        void start();
        void stop();
    private:
        unsigned int bpm;
        std::function<void()> timerCallback;

};