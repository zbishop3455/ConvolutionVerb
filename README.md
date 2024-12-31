# ConvolutionVerb 

ConvolutionVerb is a VST audio plugin built using the JUCE framework that creates a reverberation effect using convolution. This DSP technique uses an impulse response (sample) and "applies" it to incoming audio. In this application, we use impulse responses (IRs) from different rooms and apply it to audio to make it sound as if it was in the room. This application is mostly a self study project for learning JUCE before I start a larger convolution reverb project that will model the sound of underground caves!

## Installation

This project can be built using CMake or by using the ProJucer application to launch in your favorite IDE.

### CMake

1. Install CMake
2. Run `cmake --build build` to build standalone and VST version
3. Use the built application found in `build/plugin/ConvolutionVerb_artefacts`

### ProJucer

TBD...

## Scope & Roadmap

ConvolutionVerb aims to contribute to the audio plugin community by providing a simple example of a convolution reverb plugin. While this type of plugin is nothing new, this project will help others get started with convolution faster!

Roadmap:

**Convolution**
Basic convolution processing (complete)

**IR Management**
User can load and select different impulse responses

**Reverb Parameters**
Add decay, predelay, output, mix, etc

**UI Overhaul**
Build out custom knobs and sliders. Add a background image. Add a visualization of some sort.

**IR Blending**
Experiment with blending over 2 different IRs