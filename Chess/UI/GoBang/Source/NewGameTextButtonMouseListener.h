/**
 * @file   NewGameTextButtonMouseListener.h
 * @author Ken <ken@ken-Ubuntu>
 * @date   Mon Dec  7 00:13:07 2015
 * 
 * @brief  
 * 
 * 
 */

#ifndef NEWGAMETEXTBUTTONMOUSELISTENER_H
#define NEWGAMETEXTBUTTONMOUSELISTENER_H

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"

class NewGameTextButtonMouseListener : public MouseListener {
  public:
    NewGameTextButtonMouseListener() ;
    NewGameTextButtonMouseListener(MainContentComponent* c);
    
    void mouseDown(const MouseEvent& event) override;
    void setComponent(MainContentComponent* c);
  private:
    MainContentComponent* mComponent;
};


#endif /* NEWGAMETEXTBUTTONMOUSELISTENER_H */

