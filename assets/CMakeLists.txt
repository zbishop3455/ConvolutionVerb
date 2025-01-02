
cmake_minimum_required(VERSION 3.31)

# Version is needed by JUCE.
project(ConvolutionVerb VERSION 0.1.0)

# Use juce to embed the impulse response data into the binary
# This is the same as the Projucer setting "Binary Resources"
# This lets us ship the entire plugin as a single VST file
juce_add_binary_data( ConvolutionVerbBinaryData SOURCES
    ir/ir_reverb_1.wav
    images/background.jpg
    images/knob_1.jpg

)