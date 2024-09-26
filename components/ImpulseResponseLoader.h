/*
  ==============================================================================

    ImpulseResponseLoader.h
    Created: 25 Sep 2024 11:22:44pm
    Author:  Zachary

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ImpulseResponseLoader  : public juce::Component
{
public:
    ImpulseResponseLoader();
    ~ImpulseResponseLoader() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

	juce::TextButton loadButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ImpulseResponseLoader)
};
