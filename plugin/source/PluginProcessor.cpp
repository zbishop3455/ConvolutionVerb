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
                        apvts(*this, nullptr, "Parameters", createParameterLayout()),
                        convolution(),
                        dryWetMixer()


#endif
{

    dryWetMixer.setMixingRule(juce::dsp::DryWetMixingRule::linear);

}

ConvolutionVerbAudioProcessor::~ConvolutionVerbAudioProcessor()
{

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


//==============================================================================
void ConvolutionVerbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = 2;

    convolution.reset();
    auto dir = juce::File::getCurrentWorkingDirectory();
    juce::File fileImpulseResponse = dir.getChildFile("assets").getChildFile("ir_reverb_1.wav");
    convolution.loadImpulseResponse(fileImpulseResponse, juce::dsp::Convolution::Stereo::yes, juce::dsp::Convolution::Trim::no, 0, juce::dsp::Convolution::Normalise::yes);
    convolution.prepare(spec);

}


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

    //float mix = apvts.getRawParameterValue("MIX")->load();
    // mix = 0.0f;
    // dryWetMixer.setWetMixProportion(mix);
    // dryWetMixer.pushDrySamples(buffer);

    // Wrap the buffer in an AudioBlock
    juce::dsp::AudioBlock<float> block(buffer);

    // Extract left and right channels
    // juce::dsp::AudioBlock<float> leftBlock = block.getSingleChannelBlock(0);
    // juce::dsp::AudioBlock<float> rightBlock = block.getSingleChannelBlock(1);

    // Wrap the blocks in a ProcessContextReplacing
    // juce::dsp::ProcessContextReplacing<float> contextLeft(leftBlock);
    // juce::dsp::ProcessContextReplacing<float> contextRight(rightBlock);
    
    juce::dsp::ProcessContextReplacing<float> context(block);

    // Process the convolution
    // convolution.process(contextLeft);
    // convolution.process(contextRight);

    // if (convolution.getCurrentIRSize() > 0) {
    //     convolution.process(context);
    // }

    convolution.process(context);

    // dryWetMixer.mixWetSamples(buffer);
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

    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());

    if (xml == nullptr) {
        throw new std::runtime_error("Failed to create XML from state");
    }

    copyXmlToBinary(*xml, destData);
    
}

void ConvolutionVerbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
    
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ConvolutionVerbAudioProcessor();
}

// Defines parameters for the plugin
juce::AudioProcessorValueTreeState::ParameterLayout ConvolutionVerbAudioProcessor::createParameterLayout()
{

    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

    // Dry / Wet
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("MIX", "Dry / Wet", 0.0f, 1.0f, 0.5f));

    return { parameters.begin(), parameters.end() };
}
