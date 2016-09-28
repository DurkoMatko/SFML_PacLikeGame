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
    bool updateFrame;

    // Game window
    RenderWindow window(VideoMode(1200, 800), "SFML works!");
    Vector2u wSize(1200,800);
    window.setSize(wSize);
    window.setPosition(sf::Vector2i(200,0));

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
    playerImage.setPosition(window.getSize().x/2 -32,window.getSize().y/2 - 55);   //coordinates of left upper corner need to be shifted by half of picture size
    //playerImage.scale(0.3,0.3);

    //background picture
    Texture bTexture;
    bTexture.setSmooth(true);
    bTexture.setRepeated(true);
    if(!bTexture.loadFromFile("floor.jpg")){
        cout << "Not able to load background image" << endl;
    }

    RectangleShape backgroundRectangle;
    backgroundRectangle.setSize(Vector2f(window.getSize().x*2*10,window.getSize().y*2*10));     //2times bigger than screen...*10 because of scale
    backgroundRectangle.scale(Vector2f(0.1,0.1));
    int xBackgroundShift = window.getSize().x/2;        //dont know why but value needs to be saved in variable first
    int yBackgroundShift = window.getSize().y/2;
    backgroundRectangle.setPosition(-xBackgroundShift,-yBackgroundShift);
    backgroundRectangle.setOutlineColor(Color::Blue);
    backgroundRectangle.setOutlineThickness(50.0f);
    backgroundRectangle.setTexture(&bTexture);
    backgroundRectangle.setTextureRect(IntRect(0,0,window.getSize().x*2*10,window.getSize().y*2*10));

    ///VIEW
    View view;
    view.reset(FloatRect(0,0,wSize.x,wSize.y));
    view.setViewport(FloatRect(0,0,1.0f,1.0f));
    Vector2f position;
    position.x = playerImage.getPosition().x + 32 - wSize.x/2;
    position.y = playerImage.getPosition().y + 55 - wSize.y/2;

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
                case Event::KeyPressed:
                    if(event.key.code == keyboard.Escape){
                        window.close();
                        break;
                    }
            }
        }
        //mouse.isButtonPressed(mouse.Left))

        ///GETTING THE DIRECTION OF MOVEMENT FROM KEYBOARD ARROWS
        if(keyboard.isKeyPressed(keyboard.Up)){
            source.y=UP;
            frameCounter += frameSpeed*clock.restart().asSeconds();
            playerImage.move(0,-2);
            position.y += -2;
        }
        else if(keyboard.isKeyPressed(keyboard.Down)){
            source.y=DOWN;
            frameCounter += frameSpeed*clock.restart().asSeconds();
            playerImage.move(0,2);
            position.y += 2;
        }
        else if(keyboard.isKeyPressed(keyboard.Right)){
            source.y=RIGHT;
            frameCounter += frameSpeed*clock.restart().asSeconds();
            playerImage.move(2,0);
            position.x += 2;
        }
        else if(keyboard.isKeyPressed(keyboard.Left)){
            source.y=LEFT;
            frameCounter += frameSpeed*clock.restart().asSeconds();
            playerImage.move(-2,0);
            position.x += -2;
        }
        cout << "X: " << position.x << " Y: " << position.y <<endl;
        if(position.x < -700){
            if(position.y>500 || position.y<-500){}
            else{
                view.reset(FloatRect(-700,position.y,wSize.x,wSize.y));
            }
        }
        else if(position.x>700)
            if(position.y>500 || position.y<-500){}
            else{
                view.reset(FloatRect(700,position.y,wSize.x,wSize.y));
            }
        else if(position.y>500)
            view.reset(FloatRect(position.x,500,wSize.x,wSize.y));
        else if(position.y<-500)
            view.reset(FloatRect(position.x,-500,wSize.x,wSize.y));
        else{
            view.reset(FloatRect(position.x,position.y,wSize.x,wSize.y));
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


        window.setView(view);

        playerImage.setTextureRect(IntRect(source.x * 64, source.y *110, 64, 110));   //(start cropping X, start cropping Y, size in X, size in Y direction)
        window.draw(backgroundRectangle);
        window.draw(playerImage);
        window.display();
        window.clear();

    }

    return 0;
}
