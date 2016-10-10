#include "SettingsButton.h"


SettingsButton::SettingsButton():rect(3)
{
    //ctor
}

SettingsButton::~SettingsButton()
{
    //dtor
}

ConvexShape SettingsButton::getButtonShape(){
    return this->rect;
}

void SettingsButton::setButtonColor(Color color){
    rect.setFillColor(color);
}
