


#include <juce_gui_basics/juce_gui_basics.h>
#include "BinaryData.h"

class CustomLookAndFeel : public juce::LookAndFeel_V4
{


public:

    CustomLookAndFeel() {

    }


    ~CustomLookAndFeel() override {

    }

    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override {
        
        
        juce::Image rotaryImage = juce::ImageCache::getFromMemory(BinaryData::knob_1_png, BinaryData::knob_1_pngSize)
        .rescaled(width, height, juce::Graphics::highResamplingQuality);

        //  rotate the image
        float rotation = (rotaryEndAngle - rotaryStartAngle) * sliderPosProportional + rotaryStartAngle;
        float centreX = width * 0.5f;
        float centreY = height * 0.5f;
        
        juce::AffineTransform transform = juce::AffineTransform::rotation(rotation, centreX, centreY);
        

        g.drawImageTransformed(rotaryImage, transform, false);

    }

private:
    /* data */
    
};
