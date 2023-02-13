#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class DigiDelayAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                        public juce::Slider::Listener
{
public:
    DigiDelayAudioProcessorEditor (DigiDelayAudioProcessor&);
    ~DigiDelayAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged (juce::Slider*) override;

private:
    DigiDelayAudioProcessor& processor;
    juce::Slider delayTimeSlider;
    juce::Slider feedbackSlider;
    juce::Slider gainSlider;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DigiDelayAudioProcessorEditor)
};
