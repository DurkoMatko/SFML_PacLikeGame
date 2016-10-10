#ifndef SETTINGSBUTTON_H
#define SETTINGSBUTTON_H

#include <SFML/Graphics.hpp>

using namespace sf;

class SettingsButton
{
    public:
        SettingsButton();
        virtual ~SettingsButton();
        ConvexShape getButtonShape();
        void setButtonColor(Color color);

        ConvexShape rect;
    protected:
    private:
};

#endif // SETTINGSBUTTON_H
