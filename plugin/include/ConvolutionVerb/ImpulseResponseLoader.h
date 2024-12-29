#pragma once

#include <juce_gui_basics/juce_gui_basics.h>


class ImpulseResponseLoader  : public juce::Component {
public:
  ImpulseResponseLoader();
  ~ImpulseResponseLoader() override;

  void paint (juce::Graphics&) override;
  void resized() override;

private:

  juce::TextButton loadButton;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ImpulseResponseLoader)
};
