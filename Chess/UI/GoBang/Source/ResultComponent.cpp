
#include "./ResultComponent.h"

ResultContentComponent::ResultContentComponent() {
    mMessage = "Unknown message";
}

ResultContentComponent::ResultContentComponent(const std::string message) : mMessage(message) {
    setSize (200, 100);
}

ResultContentComponent::~ResultContentComponent() {
    // do nothing here
}

void ResultContentComponent::paint(Graphics& g) {
    g.fillAll(Colours::white);

    g.setFont (Font (26.0f));
    g.setColour (Colours::red);

    g.drawSingleLineText(mMessage, 100, 50, Justification::Flags::centred);
}

void ResultContentComponent::resized() {
    // resized
}










