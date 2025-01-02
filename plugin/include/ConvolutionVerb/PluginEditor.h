/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "PluginProcessor.h"
#include "ImpulseResponseLoader.h"
#include "CustomLookAndFeel.h"

class ConvolutionVerbAudioProcessorEditor  : public juce::AudioProcessorEditor {

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

    juce::Slider mixSlider;
    juce::Label mixSliderLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixSliderAttachment;
    CustomLookAndFeel lookAndFeel;

    // ImpulseResponseLoader impulseResponseLoader;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConvolutionVerbAudioProcessorEditor)
};
