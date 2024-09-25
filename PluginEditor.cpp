/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ConvolutionVerbAudioProcessorEditor::ConvolutionVerbAudioProcessorEditor (ConvolutionVerbAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{

    setSize (400, 300);

	// Setup the dry / wet slider
    addAndMakeVisible(dryWetSlider);
    dryWetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    dryWetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    dryWetSlider.setRange(0.0, 1.0, 0.01);

	addAndMakeVisible(dryWetLabel);
	dryWetLabel.setText("Dry / Wet", juce::dontSendNotification);
	dryWetLabel.attachToComponent(&dryWetSlider, false);

}

ConvolutionVerbAudioProcessorEditor::~ConvolutionVerbAudioProcessorEditor()
{
}

//==============================================================================
void ConvolutionVerbAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Convolution Reverb!", getLocalBounds(), juce::Justification::centred, 1);


}

void ConvolutionVerbAudioProcessorEditor::resized()
{

	dryWetSlider.setBounds(10, 10, 100, 100);
	dryWetLabel.setBounds(10, 110, 100, 20);


    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
