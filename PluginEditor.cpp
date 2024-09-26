/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "components/ImpulseResponseLoader.h"

//==============================================================================
ConvolutionVerbAudioProcessorEditor::ConvolutionVerbAudioProcessorEditor (ConvolutionVerbAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{

    setSize (854, 480);

	// Add the impulse response loader
	addAndMakeVisible(impulseResponseLoader);

	// Setup the dry / wet slider
    addAndMakeVisible(dryWetSlider);
    dryWetSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
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

}

void ConvolutionVerbAudioProcessorEditor::resized()
{

	dryWetSlider.setBounds(100, 300, 100, 100);
	impulseResponseLoader.setBounds(0, 0, getWidth(), (getHeight() / 2) );


    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
