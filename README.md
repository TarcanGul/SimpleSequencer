# Simple Sequencer

This is a sequencer that you can make simple music.

![Simple Sequencer Demo](/images/SimpleSequencerDemo.gif)

## Technologies

This sequencer is built using the [JUCE Framework](https://juce.com/).

Features:
- You can load any `mp3` or `wav` format sound.
- You can add rows to add even more sounds.
- Currently 8 beats is supported in 4/4 time signature.
- You can use between 80-200 BPM (inclusive)
- Includes an interactive beat marker.

Feel free to fork and operate under the MIT license.

## Build the Project

### Prerequisites
- Make sure that you have clone [JUCE](https://github.com/juce-framework/JUCE) in a directory you can specify.

### Steps
- Clone the repository.
- Create a `build/` folder and navigate to it.
- Run `cmake .. -DCMAKE_PREFIX_PATH=<DIRECTORY WHERE YOU CLONED JUCE>`
- After build files are generated, run `make`
- For MacOS, the executable will be in `simple-sequencer/build/SimpleSequencer_artefacts/Debug/"Simple Sequencer.app"/Contents/MacOS/"Simple Sequencer"`. Just run this as a command and voila!