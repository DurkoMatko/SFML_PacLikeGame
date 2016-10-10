#include "IncreaseSettingsButton.h"

IncreaseSettingsButton::IncreaseSettingsButton():SettingsButton()
{
    //ctor
}

IncreaseSettingsButton::~IncreaseSettingsButton()
{
    //dtor
}

IncreaseSettingsButton::IncreaseSettingsButton(int xPosition,int yPosition):SettingsButton()
{
    rect.setPoint(0,Vector2f(xPosition,yPosition));
    rect.setPoint(1,Vector2f(xPosition-10,yPosition-10));
    rect.setPoint(2,Vector2f(xPosition-10,yPosition+10));
    rect.setFillColor(Color::White);
}
