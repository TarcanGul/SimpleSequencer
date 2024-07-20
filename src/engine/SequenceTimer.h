#include <juce_core/juce_core.h>
#include <functional>

class SequenceTimer : public juce::HighResolutionTimer {
    public:
        SequenceTimer(int bpm, std::function<void()> timer_callback);
        ~SequenceTimer() override;
        void hiResTimerCallback () override;
        void start();
        void stop();
        void setBpm(double bpm);
        void setBeatsPerMeasure(int beats_per_measure);
    private:
        const int DEFAULT_BEATS_PER_MEASURE = 4;

        double bpm_;
        int beats_per_measure_ = DEFAULT_BEATS_PER_MEASURE;
        std::function<void()> timer_callback_;

};