


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
        
        int imageWidth = slider.getBounds().getWidth();
        int imageHeight = slider.getBounds().getHeight();

        juce::Image rotaryImage = juce::ImageCache::getFromMemory(BinaryData::knob_1_png, BinaryData::knob_1_pngSize)
        .rescaled(imageWidth, imageHeight, juce::Graphics::ResamplingQuality::highResamplingQuality);

        int centerX = rotaryImage.getWidth() / 2;
        int centerY = rotaryImage.getHeight() / 2;

        // rotate the image
        float rotation = (rotaryEndAngle - rotaryStartAngle) * sliderPosProportional + rotaryStartAngle;
        
        juce::AffineTransform transform = juce::AffineTransform::rotation(rotation, centerX, centerY);
        
        g.drawImageTransformed(rotaryImage, transform, false);
    }

private:
    /* data */
    
};
