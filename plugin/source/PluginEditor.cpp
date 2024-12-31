
#include "ConvolutionVerb/PluginProcessor.h"
#include "ConvolutionVerb/PluginEditor.h"
#include "ConvolutionVerb/ImpulseResponseLoader.h"

//==============================================================================
ConvolutionVerbAudioProcessorEditor::ConvolutionVerbAudioProcessorEditor (ConvolutionVerbAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{

    setSize(800, 400);

	// Add the impulse response loader
	//addAndMakeVisible(impulseResponseLoader);

	// Setup the dry / wet slider
    addAndMakeVisible(mixSlider);
    mixSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    mixSlider.setRange(0.0, 1.0, 0.01);

    // Attach the slider to the processor
    mixSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "MIX", mixSlider);

	addAndMakeVisible(mixSliderLabel);
	mixSliderLabel.setText("Dry / Wet", juce::dontSendNotification);
	mixSliderLabel.attachToComponent(&mixSlider, false);

}

ConvolutionVerbAudioProcessorEditor::~ConvolutionVerbAudioProcessorEditor()
{
}


void ConvolutionVerbAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}


void ConvolutionVerbAudioProcessorEditor::resized()
{

    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	mixSlider.setBounds(10, 300, 100, 100);
	//impulseResponseLoader.setBounds(0, 0, getWidth(), (getHeight() / 2) );

}
