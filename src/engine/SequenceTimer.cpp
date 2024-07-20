#include "SequenceTimer.h"

SequenceTimer::SequenceTimer(int bpm, std::function<void()> timer_callback)
{
    bpm_ = bpm;
    timer_callback_ = timer_callback;
    beats_per_measure_ = 4;
}

SequenceTimer::~SequenceTimer()
{
    stopTimer();
    timer_callback_ = nullptr;    
}


void SequenceTimer::hiResTimerCallback()
{
    timer_callback_();
}

void SequenceTimer::start()
{
    double timerInterval = 60000.0 / (bpm_ * beats_per_measure_);
    startTimer(timerInterval);
}

void SequenceTimer::stop()
{
    stopTimer();
}

void SequenceTimer::setBpm(double bpm)
{
    bpm_ = bpm;

    // The interval has to be recalculated.
    stop();
    start();
}

void SequenceTimer::setBeatsPerMeasure(int beats_per_measure)
{
    beats_per_measure_ = beats_per_measure;
}
