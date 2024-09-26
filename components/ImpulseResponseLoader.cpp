/*
  ==============================================================================

    ImpulseResponseLoader.cpp
    Created: 25 Sep 2024 11:22:44pm
    Author:  Zachary

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ImpulseResponseLoader.h"

//==============================================================================
ImpulseResponseLoader::ImpulseResponseLoader()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

	addAndMakeVisible(loadButton);
	loadButton.setButtonText("Load Impulse Response");

}

ImpulseResponseLoader::~ImpulseResponseLoader()
{
}

void ImpulseResponseLoader::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (14.0f));
    g.drawText ("ImpulseResponseLoader", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void ImpulseResponseLoader::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

	loadButton.setBounds(100, 100, 200, 50);

}
