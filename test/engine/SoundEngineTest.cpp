#define BOOST_TEST_MODULE SoundEngineTest
#include <boost/test/included/unit_test.hpp>
#include "../../external/FakeIt/boost/fakeit.hpp"
#include "../../src/engine/SoundEngine.h"

using namespace fakeit;

BOOST_AUTO_TEST_CASE(playAllTest) 
{
    Mock<juce::MixerAudioSource> mixerAudioSourceMock;

    // Cannot mock this since it is not polymorphic.
    juce::AudioFormatManager formatManagerMock;
    Mock<juce::AudioSourcePlayer> audioSourcePlayerMock;
    Mock<juce::AudioDeviceManager> deviceManagerMock;

    When(Method(deviceManagerMock, initialise)).Return(juce::String(""));
    When(Method(deviceManagerMock, addAudioCallback)).Return();
    When(Method(audioSourcePlayerMock, setSource)).Return();

    SoundEngine soundEngine(mixerAudioSourceMock.get(), formatManagerMock, audioSourcePlayerMock.get(), deviceManagerMock.get());

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