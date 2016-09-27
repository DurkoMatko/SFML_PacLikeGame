#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace std;
using namespace sf;

int main()
{
    //variables for navigation of player
    enum Directions{DOWN,LEFT,RIGHT,UP};
    Vector2i source(1,DOWN);

    float frameCounter = 0, switchFrame=50, frameSpeed = 500;
    Clock clock;

    // Game window
    RenderWindow window(VideoMode(1200, 500), "SFML works!");
    Vector2u size(1200,500);
    window.setSize(size);
    window.setPosition(sf::Vector2i(200,200));

    string display="";
    Keyboard keyboard;

    //player picture
    Texture pTexture;
    pTexture.setSmooth(true);
    Sprite playerImage;
    if(!pTexture.loadFromFile("chibi4.png")){
        cout << "Not able to load player image" << endl;
    }
    playerImage.setTexture(pTexture,true);
    playerImage.setPosition(0,0);
    //playerImage.scale(0.3,0.3);



    int index = 0;
    window.setKeyRepeatEnabled(true);

    while (window.isOpen())     //main game loop
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch(event.type){
                case Event::Closed:
                    window.close();
                    break;
                case Event::GainedFocus:
                    cout << "Window active" << endl;
                    break;
                case Event::LostFocus:
                    cout << "Window NOT active" << endl;
                    break;
                case Event::Resized:
                    cout << "Width: " << event.size.width << "Height: " << event.size.height<< endl;
                    break;
                case Event::TextEntered:
                    if(event.text.unicode!=8)
                        //cout << (char) event.text.unicode<< endl;
                        display += (char) event.text.unicode;
                    else
                        display = display.substr(0,display.length()-1);
                    system("clear");
                    cout << display << endl;
                    break;
                /*case Event::KeyPressed:
                    if(event.key.code == keyboard.Up){
                        source.y=UP;
                    }
                    else if(event.key.code == keyboard.Down){
                        source.y=DOWN;
                    }
                    else if(event.key.code == keyboard.Right){
                        source.y=RIGHT;
                    }
                    else if(event.key.code == keyboard.Left){
                        source.y=LEFT;
                    }
                    */
            }
        }

        if(keyboard.isKeyPressed(keyboard.Up)){
            source.y=UP;
            //source.x++;
            frameCounter += frameSpeed*clock.restart().asSeconds();
            playerImage.move(0,-2);
        }
        else if(keyboard.isKeyPressed(keyboard.Down)){
            source.y=DOWN;
            //source.x++;
            frameCounter += frameSpeed*clock.restart().asSeconds();
            playerImage.move(0,2);
        }
        else if(keyboard.isKeyPressed(keyboard.Right)){
            source.y=RIGHT;
            //source.x++;
            frameCounter += frameSpeed*clock.restart().asSeconds();
            playerImage.move(2,0);
        }
        else if(keyboard.isKeyPressed(keyboard.Left)){
            source.y=LEFT;
            //source.x++;
            frameCounter += frameSpeed*clock.restart().asSeconds();
            playerImage.move(-2,0);
        }

        //frameCounter += frameSpeed*clock.restart().asSeconds();
        if(frameCounter >=switchFrame){
            frameCounter=0;

            //animation...each cycle shifts displayed chibi by 64pixels to the right...if size of picture is smaller than current pixel position,
            // then go again from pixel 0.
            source.x++;
            if(source.x*64 >= pTexture.getSize().x){
                source.x=0;
            }
        }




        playerImage.setTextureRect(IntRect(source.x * 64, source.y *110, 64, 110));   //(start cropping X, start cropping Y, size in X, size in Y direction)
        //playerImage.setTextureRect(IntRect(0,0,64,*110));
        window.draw(playerImage);
        window.display();
        window.clear();

    }

    return 0;
}
