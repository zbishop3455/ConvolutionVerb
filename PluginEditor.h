/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "components/ImpulseResponseLoader.h"


//==============================================================================
/**
*/
class ConvolutionVerbAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    
    ConvolutionVerbAudioProcessorEditor (ConvolutionVerbAudioProcessor&);
    ~ConvolutionVerbAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ConvolutionVerbAudioProcessor& audioProcessor;

	juce::Slider dryWetSlider;
	juce::Label dryWetLabel;

	ImpulseResponseLoader impulseResponseLoader;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConvolutionVerbAudioProcessorEditor)
};
