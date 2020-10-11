#include "Game.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <math.h>
#include <dos.h>
#include <windows.h>

using namespace std;
using namespace sf ;
int main() {

    const unsigned Window_WIDTH = 800 ;
    const unsigned Window_HEIGHT = 800 ;


    // Make a window that is 571 by 660 pixels
 Splash:   RenderWindow window(VideoMode(Window_WIDTH, Window_HEIGHT), "Pac Man - A Parody"); // a window to sort Admin
 //go to pointer

    Text TheMessage;


    Font PacM ;
    PacM.loadFromFile("Resoruces/Fonts/PAC-FONT.TTF");

    TheMessage.setFont(PacM);

    TheMessage.setCharacterSize(35);

    Texture welScreen ;
    Sprite welcome ;


    welScreen.loadFromFile("Resoruces/Fonts/PacMan.png") ;
    welcome.setTexture(welScreen);
    welcome.scale(2,2);




    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)

                window.close();

            if ( event.type == sf::Event::KeyPressed) {

                if (event.key.code == sf::Keyboard:: A){

                    window.close();
                   Game player("Resoruces/Maze/m1.txt");
                   player.StartGame();

                    goto Splash;


                }

            }
        }




        window.clear();


        window.draw(welcome);
        window.draw(TheMessage);


        // Show everything we just drew
        window.display();
    }

//Game game1("C:/Users/Home/Desktop/Final Project/1318803 - 1911499/executables/Resoruces/Maze/m1.txt");



    return 0;
}
