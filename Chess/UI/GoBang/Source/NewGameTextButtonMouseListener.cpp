#include "NewGameTextButtonMouseListener.h"



NewGameTextButtonMouseListener::NewGameTextButtonMouseListener() : mComponent(nullptr) {
    
}

NewGameTextButtonMouseListener::NewGameTextButtonMouseListener(MainContentComponent* c) : mComponent(c) {
    
}

void NewGameTextButtonMouseListener::setComponent(MainContentComponent* c) {
    mComponent = c;
}

void NewGameTextButtonMouseListener::mouseDown(const MouseEvent& event) {
    if (mComponent != nullptr) {
        mComponent->startNewGame();
    }
}
