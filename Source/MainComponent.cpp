#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{

    
    addAndMakeVisible(frequencyKnob);
    addAndMakeVisible(amplitudeKnob);
    addAndMakeVisible(fmatrix);

    frequencyKnob.onValueChange = [this]() {
        toneGenerator.setFrequency(frequencyKnob.getValue());
    };
    amplitudeKnob.onValueChange = [this]() {
        toneGenerator.setAmplitude(juce::Decibels::decibelsToGain(amplitudeKnob.getValue()));
    };

    // Make sure you set the size of the component after
    // you add any child components.
    setLookAndFeel(&laf);
    setSize (650, 350);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    setLookAndFeel(nullptr);
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    toneGenerator.setFrequency(0);
    toneGenerator.setAmplitude(0);
    toneGenerator.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();
    toneGenerator.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    toneGenerator.releaseResources();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll(juce::Colours::darkgrey);

}

void MainComponent::resized()
{
    auto area = getLocalBounds();
    auto top = area.removeFromBottom(getHeight() - 10);
    auto bottom = top.removeFromBottom(getHeight() - 180);
    auto footer = bottom.removeFromBottom(30);

    frequencyKnob.setBounds(top.removeFromLeft(getWidth() / 2));
    amplitudeKnob.setBounds(top.removeFromLeft(getWidth() / 2));
    fmatrix.setBounds(bottom);
}
