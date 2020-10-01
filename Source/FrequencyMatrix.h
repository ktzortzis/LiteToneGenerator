/*
  ==============================================================================

    FrequencyMatrix.h
    Created: 29 Sep 2020 12:30:58pm
    Author:  Konstantinos Tzortzis

  ==============================================================================
*/

#pragma once

const std::initializer_list<double> init
{
    1.6e1, 2e1, 2.5e1, 3.15e1, 4e1, 5e1, 6.3e1, 8e1, 1e2,
    1.25e2, 1.6e2, 2e2, 2.5e2, 3.15e2, 4e2, 5e2, 6.3e2,
    8e2, 1e3, 1.25e3, 1.6e3, 2e3, 2.5e3, 3.15e3, 4e3,
    5e3, 6.3e3, 8e3, 1e4, 1.25e4, 1.6e4, 2e4
};

struct FrequencyButton : public juce::TextButton
{
public:
    double frequency;

    FrequencyButton() {}
    FrequencyButton(double value) : frequency{ value } {}
    FrequencyButton(juce::String text, double value)
        :  frequency(value)
    {
        setButtonText(text);
    }
    
    void createButton(juce::String text, double value) 
    {
        setButtonText(text);
        frequency = value ;
    }
};

class  FrequencyMatrix : public juce::Component
{
public:
	 FrequencyMatrix();
     FrequencyMatrix(FrequencyKnob* knob);
     ~FrequencyMatrix();

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    unsigned int border{ 20 };
    unsigned int buttonHeight{ 30 };
    

    juce::OwnedArray<FrequencyButton> buttons;

    std::string double2string(double value, int precision);
    void updateBtnColour(FrequencyButton* btn, FrequencyButton* temp);

    FrequencyButton* temp{};

};

//=================================================================================

inline FrequencyMatrix::FrequencyMatrix(FrequencyKnob* knob)
{
    
    FrequencyButton* btn {};
    
    for (auto value : init) {
        if (value < 1000) {
            btn = new FrequencyButton(double2string(value, 2) + " Hz", value);

        }
        else {
            btn = new FrequencyButton(double2string(value / 1000, 2) + " KHz", value);
        }
        btn->onClick = [this, knob, btn]() {
            knob->setValue(btn->frequency);
            //btn->setColour(juce::TextButton::buttonColourId, juce::Colours::green);
            //updateBtnColour(btn, temp);
        };
        buttons.add(btn);
        addAndMakeVisible(btn);
    }
    
    setSize(getParentWidth()-border, getParentHeight()-border);
}

inline FrequencyMatrix::~ FrequencyMatrix()
{

}

 inline void FrequencyMatrix::paint(juce::Graphics& g)
 {

 }

 inline void FrequencyMatrix::resized()
 {
     auto totalItems = buttons.size();
     //int n_rows = std::sqrt(totalItems);
     int n_rows = (int)getHeight() / buttonHeight;
     int n_colums{};
     while ((n_rows > 1) && (totalItems % n_rows) != 0) {
         n_rows -= 1;
     }
     n_rows > 0 ? n_colums = totalItems / n_rows : n_colums = totalItems;

     double buttonWidth = getWidth() / (double(totalItems) / n_rows);

     for (auto row = 0; row < n_rows; ++row) {
         for (auto col = 0; col < n_colums; ++col) {
             auto pt = col + row * n_colums;
             auto btn = buttons[pt];
             btn->setBounds(col * buttonWidth, getHeight() - (row + 1) * buttonHeight, buttonWidth, buttonHeight);
         }
     }
 }


 inline void FrequencyMatrix::updateBtnColour(FrequencyButton* btn, FrequencyButton* temp1)
 {
     //FrequencyButton* temp{};
     btn->setColour(FrequencyButton::buttonColourId, juce::Colours::green);
     if (temp1 == nullptr) {
         temp1 = btn;
     }
     if (btn != temp1)
        temp1->removeColour(FrequencyButton::buttonColourId);
 }

 inline std::string FrequencyMatrix::double2string(double value, int precision)
 {
     std::ostringstream streamObj;
     streamObj << std::fixed;
     streamObj << std::setprecision(precision);
     streamObj << value;
     return streamObj.str();
     //return std::string();
 }