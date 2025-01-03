
#include "ConvolutionVerb/PluginProcessor.h"
#include "ConvolutionVerb/PluginEditor.h"
#include "ConvolutionVerb/ImpulseResponseLoader.h"
#include "BinaryData.h"

//==============================================================================
ConvolutionVerbAudioProcessorEditor::ConvolutionVerbAudioProcessorEditor (ConvolutionVerbAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{

    setSize(800, 400);
    setLookAndFeel(&lookAndFeel);

    // Input knob
    addAndMakeVisible(predelayKnob);
    predelayKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    predelayKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    predelayKnob.setRange(-12.0, 12.0, 0.0);
    predelayKnobAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "PREDELAY", predelayKnob);
    addAndMakeVisible(predelayKnobLabel);
    predelayKnobLabel.setText("PreDelay", juce::dontSendNotification);
    predelayKnobLabel.attachToComponent(&predelayKnob, false);

    // Decay knob
    addAndMakeVisible(decayKnob);
    decayKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    decayKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    decayKnob.setRange(0.0, 1.0, 0.01);
    decayKnobAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DECAY", decayKnob);
    addAndMakeVisible(decayKnobLabel);
    decayKnobLabel.setText("Decay", juce::dontSendNotification);
    decayKnobLabel.attachToComponent(&decayKnob, false);

	// Mix knob
    addAndMakeVisible(mixKnob);
    mixKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mixKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    mixKnob.setRange(0.0, 1.0, 0.01);
    mixKnobAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "MIX", mixKnob);
	addAndMakeVisible(mixKnobLabel);
	mixKnobLabel.setText("Mix", juce::dontSendNotification);
	mixKnobLabel.attachToComponent(&mixKnob, false);

    // Output Knob
    addAndMakeVisible(outputKnob);
    outputKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    outputKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    outputKnob.setRange(-12.0, 12.0, 1.0);
    outputKnobAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "OUTPUT", outputKnob);
    addAndMakeVisible(outputKnobLabel);
    outputKnobLabel.setText("Output", juce::dontSendNotification);
    outputKnobLabel.attachToComponent(&outputKnob, false);
    
}

ConvolutionVerbAudioProcessorEditor::~ConvolutionVerbAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}


void ConvolutionVerbAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.drawImage(juce::ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize), getLocalBounds().toFloat());

}


void ConvolutionVerbAudioProcessorEditor::resized()
{

    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    predelayKnob.setBounds(158, 255, 75, 75);
    decayKnob.setBounds(275, 255, 75, 75);
	mixKnob.setBounds(450, 255, 75, 75);
    outputKnob.setBounds(570, 255, 75, 75);
	//impulseResponseLoader.setBounds(0, 0, getWidth(), (getHeight() / 2) );

}
