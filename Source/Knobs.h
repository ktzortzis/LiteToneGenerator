/*
  ==============================================================================

    Knobs.h
    Created: 29 Sep 2020 12:29:04pm
    Author:  ktzor

  ==============================================================================
*/

#pragma once

class FrequencyKnob : public juce::Slider
{
public:
    FrequencyKnob(double frequency=440)
    {
        setRange(frequencyRange, 1);
        setValue(frequency);
        setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        setTextBoxStyle(Slider::TextBoxBelow, false, 140, 20);
        setTextValueSuffix(" Hz");
        setSkewFactor(0.4);
        //setColour(Slider::textBoxOutlineColourId, {});
    }


private:
    juce::Range<double> frequencyRange{ 16,20000 };

};

//===============================================================================

class AmplitudeKnob : public juce::Slider
{
public:
    AmplitudeKnob(double value=-96) {
        setRange(-96, 0);
        setValue(value);
        setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        setTextBoxStyle(Slider::TextBoxBelow, false, 140, 20);
        setTextBoxIsEditable(true);
        //setLookAndFeel(&decibelSliderLookAndFeel);
        //getLookAndFeel().setColour(Slider::thumbColourId, Colours::darkgreen);
        //getLookAndFeel().setColour(Slider::trackColourId, Colours::darkgreen);
        //setSize(100, 100);
    }

    ~AmplitudeKnob() {
        //setLookAndFeel(nullptr);
    }

    juce::String getTextFromValue(double value) override {
        return juce::Decibels::toString(value);
    }

    double getValueFromText(const juce::String& text) override {
        auto decibelText = text.upToFirstOccurrenceOf("dB", false, false).trim();
        auto minusInfinitydB = -100.0;
        return decibelText.equalsIgnoreCase("-INF") ? minusInfinitydB : decibelText.getDoubleValue() * -1;
    }
private:
    //LookAndFeel_V4 decibelSliderLookAndFeel;
    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DecibelSlider)
};