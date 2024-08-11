cmake_minimum_required(VERSION 3.29)

project(SimpleSequencer VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

enable_testing()

find_package(JUCE CONFIG REQUIRED)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)


juce_add_gui_app(${CMAKE_PROJECT_NAME}
COMPANY_NAME "TarcanGul"
PRODUCT_NAME "Simple Sequencer"
)

target_sources(${CMAKE_PROJECT_NAME}
    PRIVATE
        src/main.cpp 
        src/MainComponent.cpp

        src/components/Sequencer.cpp
        src/components/SoundLine.cpp
        src/components/BeatButton.cpp
        src/components/BeatMarker.cpp

        src/engine/SoundEngine.cpp
        src/engine/SequenceTimer.cpp
)

target_compile_definitions(${CMAKE_PROJECT_NAME}
    PRIVATE
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_gui_app` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_gui_app` call
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:SimpleSequencer,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:SimpleSequencer,JUCE_VERSION>")

target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE 
        juce::juce_core
        juce::juce_gui_basics
        juce::juce_gui_extra
        juce::juce_audio_basics
        juce::juce_audio_formats
        juce::juce_audio_devices
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

include_directories(${Boost_INCLUDE_DIRS})

file(GLOB_RECURSE TEST_SRCS test/*.cpp)

foreach(testSrc ${TEST_SRCS})
    get_filename_component(testName ${testSrc} NAME_WE)
    add_executable(${testName} ${testSrc} src/engine/SoundEngine.cpp src/engine/SequenceTimer.cpp)
    target_link_libraries(${testName} 
    PRIVATE 
        ${Boost_LIBRARIES}
        juce::juce_core
        juce::juce_gui_basics
        juce::juce_gui_extra
        juce::juce_audio_basics
        juce::juce_audio_formats
        juce::juce_audio_devices
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
    )
    add_test(NAME ${testName} COMMAND ${testName})
endforeach()