#include "SequenceTimer.h"

SequenceTimer::SequenceTimer(unsigned int bpm, std::function<void()> timerCallback)
{
    this->bpm = bpm;
    this->timerCallback = timerCallback;
}

SequenceTimer::~SequenceTimer()
{
    
}

void SequenceTimer::hiResTimerCallback()
{
    this->timerCallback();
}

void SequenceTimer::start()
{
    double timerInterval = 60000.0 / (this->bpm) / 4;
    startTimer(timerInterval);
}

void SequenceTimer::stop()
{
    stopTimer();
}
