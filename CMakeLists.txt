cmake_minimum_required(VERSION 3.29)

project(SimpleSequencer VERSION 1.0)

find_package(JUCE CONFIG REQUIRED)

juce_add_gui_app(${CMAKE_PROJECT_NAME}
COMPANY_NAME "TarcanGul"
PRODUCT_NAME "Simple Sequencer"
)

target_sources(${CMAKE_PROJECT_NAME}
    PRIVATE
        src/main.cpp 
        src/MainComponent.cpp
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
        juce::juce_gui_basics
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)