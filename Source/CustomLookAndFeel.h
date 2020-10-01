/*
  ==============================================================================

    CustomLookAndFeel.h
    Created: 29 Sep 2020 12:27:51pm
    Author:  ktzor

  ==============================================================================
*/

#pragma once

class CustomLookAndFeel : public juce::LookAndFeel_V4 {
public:

    CustomLookAndFeel() {
        setColour(juce::TextButton::buttonColourId, juce::Colour::fromString("002DE1FC"));
        setColour(juce::TextButton::textColourOffId, juce::Colour::fromString("FF2DE1FC"));
        setColour(juce::Slider::textBoxOutlineColourId, juce::Colour::fromString("002DE1FC"));
        setColour(juce::Slider::textBoxTextColourId, juce::Colour::fromString("FF2DE1FC"));

    }
    ~CustomLookAndFeel() {

    }

    juce::Font getTextButtonFont(juce::TextButton&, int) override {
        return juce::Font("Verdana Pro", 16, juce::Font::plain);
    }


    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override
    {
        auto radius = (float)juce::jmin(width / 2, height / 2) - 4.0f;
        auto centreX = (float)x + (float)width * 0.5f;
        auto centreY = (float)y + (float)height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

        // fill
        g.setColour(juce::Colour::fromString("002DE1FC"));
        g.fillEllipse(rx, ry, rw, rw);

        // outline
        g.setColour(juce::Colour::fromString("FF2DE1FC"));
        g.drawEllipse(rx, ry, rw, rw, 3.0f);

        juce::Path p;
        auto pointerLength = radius * 0.33f;
        auto pointerThickness = 8.0f;
        p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

        // pointer
        g.setColour(juce::Colour::fromString("FF2DE1FC"));
        g.fillPath(p);
    }

    //GlowEffect fx;

};