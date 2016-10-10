#include "DecreaseSettingsButton.h"
#include <iostream>

using namespace std;
DecreaseSettingsButton::DecreaseSettingsButton():SettingsButton()
{
    //ctor
}

DecreaseSettingsButton::DecreaseSettingsButton(int xPosition,int yPosition):SettingsButton()
{
    rect.setPoint(0,Vector2f(xPosition,yPosition));
    rect.setPoint(1,Vector2f(xPosition+10,yPosition-10));
    rect.setPoint(2,Vector2f(xPosition+10,yPosition+10));
    rect.setFillColor(Color::White);
}

DecreaseSettingsButton::~DecreaseSettingsButton()
{
    //dtor
}
