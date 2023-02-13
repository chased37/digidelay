#include "PluginProcessor.h"
#include "PluginEditor.h"

DigiDelayAudioProcessor::DigiDelayAudioProcessor()
    : AudioProcessor (BusesProperties().withInput  ("Input",  juce::AudioChannelSet::stereo())
                                         .withOutput ("Output", juce::AudioChannelSet::stereo())),
      parameters (*this, nullptr, "PARAMETERS",
                  {
                      std::make_unique<juce::AudioParameterFloat>("delayTimeMs", "Delay Time", juce::NormalisableRange<float>(0.0f, 2000.0f), 500.0f),
                      std::make_unique<juce::AudioParameterFloat>("feedback", "Feedback", juce::NormalisableRange<float>(0.0f, 1.0f), 0.5f),
                      std::make_unique<juce::AudioParameterFloat>("gain", "Gain", juce::NormalisableRange<float>(0.0f, 1.0f), 0.5f)
                  })
{
    delayTimeMs = parameters.getRawParameterValue("delayTimeMs")->load();
    feedback = parameters.getRawParameterValue("feedback")->load();
    gain = parameters.getRawParameterValue("gain")->load();

    delayBuffer.setSize(getTotalNumInputChannels(), getSampleRate() * delayTimeMs / 1000.0f);
    delayBuffer.clear();
    delayWritePosition = 0;
}

DigiDelayAudioProcessor::~DigiDelayAudioProcessor()
{
}

void DigiDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

void DigiDelayAudioProcessor::releaseResources()
{
}

void DigiDelayAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    const int numSamples = buffer.getNumSamples();
    const int delayWritePos = (delayWritePosition - (int) (delayTimeMs / 1000.0f * getSampleRate()) + delayBuffer.getNumSamples()) % delayBuffer.getNumSamples();
    const int delayReadPos = (delayWritePosition - delayBuffer.getNumSamples() + delayBuffer.getNumSamples()) % delayBuffer.getNumSamples();

    for (int channel = 0; channel < getTotalNumInputChannels(); ++channel)
    {
        float* const channelData = buffer.getWritePointer(channel);
        float* const delayData = delayBuffer.getWritePointer(channel);
        const float* const channelReadData = buffer.getReadPointer(channel);

        for (int sample = 0; sample < numSamples; ++sample)
        {
            // apply delay effect
            const float in = channelReadData[sample];
            const float delay = delayData[delayReadPos];
            channelData[sample] = in + gain * delay;
            delayData[delayWritePos] = in + delay * feedback;
            delayWritePosition = (delayWritePosition + 1) % delayBuffer.getNumSamples();
        }
    }
}

juce::AudioProcessorEditor* DigiDelayAudioProcessor::createEditor()
{
    return new DigiDelayAudioProcessorEditor (*this);
}

bool DigiDelayAudioProcessor::hasEditor() const
{
    return true;
}

const juce::String DigiDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int DigiDelayAudioProcessor::getNumPrograms()
{
    return 1;
}

int DigiDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DigiDelayAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DigiDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void DigiDelayAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

bool DigiDelayAudioProcessor::producesMidi() const
{
    return false;
}

bool DigiDelayAudioProcessor::acceptsMidi() const { return false; }

double DigiDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.5; // or the tail length of your plugin's processing, in seconds
}


void DigiDelayAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
}

void DigiDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DigiDelayAudioProcessor();
}
