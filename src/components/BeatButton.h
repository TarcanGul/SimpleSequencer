#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>

class BeatButton : public juce::Button {
public:
    BeatButton(const juce::String& buttonName);

    void resized() override;
    void paintButton (juce::Graphics& g,
                            bool shouldDrawButtonAsHighlighted,
                            bool shouldDrawButtonAsDown) override;
    void setPosition(int x, int y);
private:
    juce::String buttonName_;
    int xPos_ = 0;
    int yPos_ = 0;
};