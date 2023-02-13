#include "PluginEditor.h"

DigiDelayAudioProcessorEditor::DigiDelayAudioProcessorEditor (DigiDelayAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    delayTimeSlider.setSliderStyle (juce::Slider::LinearHorizontal);
    delayTimeSlider.setRange (0.0f, 2000.0f, 1.0f);
    delayTimeSlider.setValue (processor.delayTimeMs);
    delayTimeSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 80, 20);
    delayTimeSlider.addListener (this);
    addAndMakeVisible (delayTimeSlider);

    feedbackSlider.setSliderStyle (juce::Slider::LinearHorizontal);
    feedbackSlider.setRange (0.0f, 1.0f, 0.01f);
    feedbackSlider.setValue (processor.feedback);
    feedbackSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 80, 20);
    feedbackSlider.addListener (this);
    addAndMakeVisible (feedbackSlider);

    gainSlider.setSliderStyle (juce::Slider::LinearHorizontal);
    gainSlider.setRange (0.0f, 1.0f, 0.01f);
    gainSlider.setValue (processor.gain);
    gainSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 80, 20);
    gainSlider.addListener (this);
    addAndMakeVisible (gainSlider);

    setSize (400, 300);
}

DigiDelayAudioProcessorEditor::~DigiDelayAudioProcessorEditor()
{
}

void DigiDelayAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawText ("Delay Plugin", getLocalBounds(),
                juce::Justification::centred, true);
}

void DigiDelayAudioProcessorEditor::resized()
{
    const int sliderLeft = 20;
    const int sliderWidth = getWidth() - 2 * sliderLeft;
    const int sliderTop = 20;
    const int sliderHeight = 40;

    delayTimeSlider.setBounds (sliderLeft, sliderTop, sliderWidth, sliderHeight);
    feedbackSlider.setBounds (sliderLeft, sliderTop + 50, sliderWidth, sliderHeight);
    gainSlider.setBounds (sliderLeft, sliderTop + 100, sliderWidth, sliderHeight);
}

void DigiDelayAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    if (slider == &delayTimeSlider)
    {
        processor.delayTimeMs = delayTimeSlider.getValue();
    }
    else if (slider == &feedbackSlider)
    {
        processor.feedback = feedbackSlider.getValue();
    }
    else if (slider == &gainSlider)
    {
        processor.gain = gainSlider.getValue();
    }
}

