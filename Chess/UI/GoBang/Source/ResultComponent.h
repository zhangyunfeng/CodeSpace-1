/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef RESULTCOMPONENT_H
#define RESULTCOMPONENT_H

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class ResultContentComponent   : public Component
{
public:
    //==============================================================================
    ResultContentComponent();
    ResultContentComponent(const std::string message);
    
    ~ResultContentComponent();

    /* void mouseDown(const MouseEvent& event) override; */
    void paint (Graphics&);
    void resized();
    
    
private:
    std::string mMessage;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ResultContentComponent)
};


#endif /* RESULTCOMPONENT_H */
