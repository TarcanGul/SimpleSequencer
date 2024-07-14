#define BOOST_TEST_MODULE SoundEngineTest
#include <boost/test/included/unit_test.hpp>
#include "../../external/FakeIt/boost/fakeit.hpp"
#include "../../src/engine/SoundEngine.h"

BOOST_AUTO_TEST_CASE(playAllTest) 
{
    fakeit::Mock<juce::MixerAudioSource> mixerAudioSourceMock;
    juce::AudioFormatManager formatManagerMock;
    fakeit::Mock<juce::AudioSourcePlayer> audioSourcePlayerMock;
    juce::AudioDeviceManager deviceManagerMock;

    SoundEngine soundEngine(mixerAudioSourceMock.get(), formatManagerMock, audioSourcePlayerMock.get(), deviceManagerMock);

    std::vector<AudioFileData *> testAudioData(8);

    soundEngine.playAll(testAudioData);
}

// BOOST_AUTO_TEST_CASE(playAllTestEmptyVector) 
// {
//     fakeit::Mock<juce::MixerAudioSource> mixerAudioSourceMock;
//     juce::AudioFormatManager formatManagerMock;
//     fakeit::Mock<juce::AudioSourcePlayer> audioSourcePlayerMock;
//     fakeit::Mock<juce::AudioDeviceManager> deviceManagerMock;

//     SoundEngine soundEngine(mixerAudioSourceMock.get(), formatManagerMock, audioSourcePlayerMock.get(), deviceManagerMock.get());

//     soundEngine.playAll(std::vector<AudioFileData *>());

// }