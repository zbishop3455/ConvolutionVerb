/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/


#include "ConvolutionVerb/PluginProcessor.h"
#include "ConvolutionVerb/PluginEditor.h"


//==============================================================================
ConvolutionVerbAudioProcessor::ConvolutionVerbAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
                       apvts(*this, nullptr, "Parameters", createParameterLayout())
#endif
{

}

ConvolutionVerbAudioProcessor::~ConvolutionVerbAudioProcessor()
{
    // delete parameters;
}

//==============================================================================
const juce::String ConvolutionVerbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ConvolutionVerbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ConvolutionVerbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ConvolutionVerbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ConvolutionVerbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ConvolutionVerbAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ConvolutionVerbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ConvolutionVerbAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ConvolutionVerbAudioProcessor::getProgramName (int index)
{
    return {};
}

void ConvolutionVerbAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ConvolutionVerbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void ConvolutionVerbAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ConvolutionVerbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif


void ConvolutionVerbAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    
    float mix = apvts.getRawParameterValue("MIX")->load(); 

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {

        // Copy the dry signal
        juce::AudioBuffer<float> dryBuffer;
        dryBuffer.makeCopyOf(buffer);

        auto* channelData = buffer.getWritePointer(channel);
        auto* dryChannelData = dryBuffer.getWritePointer(channel);

        // Temp wet signal - not sure what this will do 
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
            channelData[sample] = sinf(2.0 * 3.14f * 440.0 * sample / 44100.0);
        }

        // Mix Dry and Wet (linear interpolation)
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
            channelData[sample] = 
            (1.0f - mix) * dryChannelData[sample] + 
            mix * channelData[sample];
        }
        
        // Done :D 
    }


}

//==============================================================================
bool ConvolutionVerbAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* ConvolutionVerbAudioProcessor::createEditor()
{
    return new ConvolutionVerbAudioProcessorEditor (*this);
}

//==============================================================================
void ConvolutionVerbAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    // juce::MemoryOutputStream (destData, true).writeFloat (*mix);
}

void ConvolutionVerbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    // *mix = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
}

juce::AudioProcessorValueTreeState::ParameterLayout ConvolutionVerbAudioProcessor::createParameterLayout()
{

    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

    // Dry / Wet
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("MIX", "Dry / Wet", 0.0f, 1.0f, 0.5f));

    return { parameters.begin(), parameters.end() };
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ConvolutionVerbAudioProcessor();
}
