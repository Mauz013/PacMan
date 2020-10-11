#include "Game.h"
#include "PositionHandler.h"
#include "Datatypes.h"
#include "Movement.h"
#include "Ghosts.h"


#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <math.h>
#include <dos.h>
#include <windows.h>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>

using namespace sf ;
using namespace std ;
/** @brief Game
  *
  * @todo: document this function
  */
Game::Game(string FileName) // store everything in the array
{
    FileName_ = FileName ;
    LoadTextures();
    totalFood  = 0 ;
    Score = 0 ;
    Tracker.Init_StorePos(FileName);
    CreateMaze();
    ResetPos();
}

Game::Game()
{
    FileName_ = "Resoruces/Maze/m1.txt" ;
    LoadTextures();
    totalFood = 0 ;
    Score = 0 ;
    Tracker.Init_StorePos(FileName_);
    CreateMaze();
    ResetPos();
}

void Game::StartGame()
{
    RenderWindow window(VideoMode(Window_WIDTH, Window_HEIGHT), "PacMan Maze");
    Controler(window);
}

void Game::LoadTextures()
{
    brick.loadFromFile("Resoruces/backgrounds/BlueBrickwall.png");
    pacManRight.loadFromFile("Resoruces/Pac and Crew/PacmanRight.PNG");
    pacManLeft.loadFromFile("Resoruces/Pac and Crew/PacmanLeft.PNG");
    pacManUp.loadFromFile("Resoruces/Pac and Crew/PacmanUP.PNG");
    pacManDown.loadFromFile("Resoruces/Pac and Crew/PacmanDown.PNG");
    ghostBlue.loadFromFile("Resoruces/Pac and Crew/Bluey.PNG");
    ghostRed.loadFromFile("Resoruces/Pac and Crew/Reddy.PNG");
    ghostOrange.loadFromFile("Resoruces/Pac and Crew/Orangey.PNG");
    ghostPink.loadFromFile("Resoruces/Pac and Crew/Pinky.PNG");
    VulnerableGhost.loadFromFile("Resoruces/Pac and Crew/Ghost.PNG");
    PacKey.loadFromFile("Resoruces/backgrounds/Key.png");
    Locker.loadFromFile("Resoruces/backgrounds/lock.png");
    Berry.loadFromFile("Resoruces/backgrounds/Fruit.png");
    YellowPellets.loadFromFile("Resoruces/backgrounds/YellowSpot.png");
    SuperPel.loadFromFile("Resoruces/backgrounds/Super.png");
    PowerPel.loadFromFile("Resoruces/backgrounds/Power.png");
}

void Game::CreateMaze()
{
    Score = 0;

    for(int r = 0; r < rows; r++)
    {
        for(int c = 0; c < cols; c++)
        {
            if(Tracker.getStorePos(r, c) == 1)
            {
                maze[r][c].setTexture(brick);
                maze[r][c].setScale(0.35, 0.35);
                maze[r][c].setPosition(c*Grid_size,r*Grid_size);
            }
        }
    }
    blueGhost.setTexture(ghostBlue);
    blueGhost.setScale(0.11, 0.11);

    redGhost.setTexture(ghostRed);
    redGhost.setScale(0.11, 0.11);

    orangeGhost.setTexture(ghostOrange);
    orangeGhost.setScale(0.11, 0.11);

    pinkGhost.setTexture(ghostPink);
    pinkGhost.setScale(0.11, 0.11);
    //initialize player
    player_.setTexture(pacManRight);
    player_.setScale(0.025, 0.023);
}

void Game::ResetPos()
{
    GPelStorC.clear();
    GPelStorR.clear();

    int counter=0, posX=0, posY=0;

    for(int r = 0; r < rows; r++)
    {
        for(int c = 0; c < cols; c++)
        {
            if(Tracker.getStorePos(r, c)== 4)
            {
                counter++;

                maze[r][c].setTexture(YellowPellets);
                maze[r][c].setScale(0.25, 0.25);
                maze[r][c].setPosition(c*Grid_size+5,r*Grid_size+5);
                totalFood++;

                if(counter == 1)
                {
                    Tracker.SetInit(Blue,r,c);
                }
                else if(counter == 2)
                {
                    Tracker.SetInit(Red,r,c);
                }
                else if(counter == 3)
                {
                    Tracker.SetInit(Orange,r,c);
                }
                else if(counter == 4)
                {
                    Tracker.SetInit(Pink,r,c);
                }
            }
            if(Tracker.getStorePos(r, c) == 9) // player
            {
                Tracker.SetInit(Pac,r,c);
            }
            else if(Tracker.getStorePos(r, c) == 6) // Red Pellet
            {
                maze[r][c].setTexture(PowerPel);
                maze[r][c].setScale(0.35, 0.35);
                maze[r][c].setPosition(c*Grid_size,r*Grid_size);
            }
            else if(Tracker.getStorePos(r, c) == 3)
            {
                maze[r][c].setTexture(Berry);
                maze[r][c].setScale(0.35, 0.35);
                maze[r][c].setPosition(c*Grid_size,r*Grid_size);
                totalFood++;
            }
            //Locks we need
            else if(Tracker.getStorePos(r, c) == 7)
            {
                Locks[r][c].setTexture(Locker);
                Locks[r][c].setPosition(c*Grid_size,r*Grid_size);
                Locks[r][c].setScale(0.35, 0.35);

                TempCount++;
                if(TempCount % 2 != 0)
                {
                    LockCount ++;
                }
                if(LockCount == 4)
                {
                    LockCount = 1;
                }
                setKey(r,c);
            }
            else if (Tracker.getStorePos(r, c) == 10)
            {
                maze[r][c].setTexture(SuperPel);
                maze[r][c].setScale(0.40, 0.40);
                maze[r][c].setPosition(c*Grid_size,r*Grid_size);
            }
            else if (Tracker.getStorePos(r, c) == 0) // normal pellet
            {
                maze[r][c].setTexture(YellowPellets);
                maze[r][c].setScale(0.25, 0.25);
                maze[r][c].setPosition(c*Grid_size+5,r*Grid_size+5);
                totalFood++;
            }
            else if(Tracker.getStorePos(r, c) == 5)
            {
                maze[r][c].setTexture(PacKey);
                maze[r][c].setScale(0.35, 0.35);
                maze[r][c].setPosition(c*Grid_size,r*Grid_size);
            }
        }
    }
    Update();
}

void Game::setKey(int r, int c)
{
    switch(LockCount)
    {
    case 0:
    {
        GPelStorR.push_back(r);
        GPelStorC.push_back(c);
        break;
    }
    case 1:
    {
        GPelStorR.push_back(r);
        GPelStorC.push_back(c);
        break;
    }
    case 2:
    {
        GPelStorR2.push_back(r);
        GPelStorC2.push_back(c);
        break;
    }
    case 3:
    {
        GPelStorR3.push_back(r);
        GPelStorC3.push_back(c);
        break;
    }
    }
}

int Game::getTotalFood()
{
    return totalFood;
}

int Game::getScore()
{
    return Score;
}

Ghosts Game::getGhostObj()
{
    return Enemy;
}

Movement Game::getMovementObj()
{
    return Tracker;
}

Eater Game::getEaterObj()
{
    return Eating;
}

void Game::ChangesAfterPelletEaten(TEXTURE tir)
{
    ChangeTexture(tir);
}

Sprite Game::getSprite(IDENTITY ID)
{
    switch(ID)
    {
    case Blue:
    {
        return blueGhost;
    }
    case Red:
    {
        return redGhost;
    }
    case Orange:
    {
        return orangeGhost;
    }
    case Pink:
    {
        return pinkGhost;
    }
    case Pac:
    {
        return player_;
    }
    }
}

void Game::GhostMovement()
{
    if(GhostCounter == 0)
    {
        if(GhostModeOn == true) // Ghost mode Functions
        {
            if(((clock()-startGhostModeTimer)/(double)(CLOCKS_PER_SEC))<10)
            {
                if(Tracker.getGhostMode(Blue) == true)
                {
                    Enemy.GhostMode(Tracker, Blue);
                }
                else
                {
                    Enemy.BlueGhostMoves(Tracker, BlueMove);
                }
                if(Tracker.getGhostMode(Red) == true)
                {
                    Enemy.GhostMode(Tracker, Red);
                }
                else
                {
                    Enemy.RedGhostMoves(Tracker);
                }
                if(Tracker.getGhostMode(Orange) == true)
                {
                    Enemy.GhostMode(Tracker, Orange);
                }
                else
                {
                    Enemy.OrangeGhostMoves(Tracker, OrangeMove);
                }
                if(Tracker.getGhostMode(Pink) == true)
                {
                    Enemy.GhostMode(Tracker, Pink);
                }
                else
                {
                    Enemy.PinkGhostMoves(Tracker);
                }
            }
            else
            {
                GhostModeOn = false ;
                Tracker.TurnGhostMode(GhostModeOn);
                blueGhost.setTexture(ghostBlue);
                blueGhost.setScale(0.11,0.11);
                redGhost.setTexture(ghostRed);
                redGhost.setScale(0.11,0.11);
                orangeGhost.setTexture(ghostOrange);
                orangeGhost.setScale(0.11,0.11);
                pinkGhost.setTexture(ghostPink);
                pinkGhost.setScale(0.11,0.11);
            }
        }
        else
        {
            Enemy.BlueGhostMoves(Tracker, BlueMove);
            Enemy.OrangeGhostMoves(Tracker, OrangeMove);
            Enemy.RedGhostMoves(Tracker);
            Enemy.PinkGhostMoves(Tracker);
        }
        GhostCounter=3;
    }
    else
        GhostCounter--;
}

void Game::ChangeTexture(TEXTURE Tir)
{
    switch(Tir)
    {
    case Super:
    {
        SuperPac = true;
        SuperPacTimer = clock();

        player_.setScale(0.035, 0.035);

        ChangeGhostSuper();
        Tracker.TurnSuperMode(SuperPac);

        Tracker.setStorePos(Tracker.getCoordinates(Pac).x,Tracker.getCoordinates(Pac).y,2);
        break;
    }
    case Power:
    {
        blueGhost.setTexture(VulnerableGhost);
        blueGhost.setScale(0.18,0.16);

        redGhost.setTexture(VulnerableGhost);
        redGhost.setScale(0.18,0.16);

        orangeGhost.setTexture(VulnerableGhost);
        orangeGhost.setScale(0.18,0.16);

        pinkGhost.setTexture(VulnerableGhost);
        pinkGhost.setScale(0.18,0.16);

        GhostModeOn = true ;
        Tracker.TurnGhostMode(GhostModeOn);

        Tracker.setStorePos(Tracker.getCoordinates(Pac).x,Tracker.getCoordinates(Pac).y,2);
        startGhostModeTimer = clock();
        break;
    }
    case Key:
    {
        Tracker.setStorePos(GPelStorR[0],GPelStorC[0],2);
        Tracker.setStorePos(Tracker.getCoordinates(Pac).x,Tracker.getCoordinates(Pac).y,2);
        Locks[GPelStorR[0]][GPelStorC[0]].setColor(sf::Color::Transparent);
        GPelStorR.erase(GPelStorR.begin());
        GPelStorC.erase(GPelStorC.begin());

        Tracker.setStorePos(GPelStorR2[0],GPelStorC2[0],2);
        Locks[GPelStorR2[0]][GPelStorC2[0]].setColor(sf::Color::Transparent);
        GPelStorR2.erase(GPelStorR2.begin());
        GPelStorC2.erase(GPelStorC2.begin());

        Tracker.setStorePos(GPelStorR3[0],GPelStorC3[0],2);
        Locks[GPelStorR3[0]][GPelStorC3[0]].setColor(sf::Color::Transparent);
        GPelStorR3.erase(GPelStorR3.begin());
        GPelStorC3.erase(GPelStorC3.begin());
        break;
    }
    case BreakLock:
    {
        Locks[Tracker.getCoordinates(Pac).x][Tracker.getCoordinates(Pac).y].setColor(sf::Color::Transparent);
        Tracker.setStorePos(Tracker.getCoordinates(Pac).x,Tracker.getCoordinates(Pac).y,2);
        break;
    }
    case Food:
    {
        Tracker.setStorePos(Tracker.getCoordinates(Pac).x,Tracker.getCoordinates(Pac).y,2);
        Score++;
    }
    }
}

void Game::ChangeGhostTexture(IDENTITY ID)
{
    switch (ID)
    {
    case Blue:
    {
        blueGhost.setTexture(ghostBlue);
        blueGhost.setScale(0.11,0.11);
        break;
    }
    case Red:
    {
        redGhost.setTexture(ghostRed);
        redGhost.setScale(0.11,0.11);
        break;
    }
    case Orange:
    {
        orangeGhost.setTexture(ghostOrange);
        orangeGhost.setScale(0.11,0.11);
        break;
    }
    case Pink:
    {
        pinkGhost.setTexture(ghostPink);
        pinkGhost.setScale(0.11,0.11);
        break;
    }
    }
}

void Game::ChangeGhostSuper()
{
    blueGhost.setScale(0.05, 0.11);
    redGhost.setScale(0.05, 0.11);
    orangeGhost.setScale(0.05, 0.11);
    pinkGhost.setScale(0.05, 0.11);
}

void Game::Update()
{
    player_.setPosition(Tracker.getCoordinates(Pac).y*Grid_size, Tracker.getCoordinates(Pac).x*Grid_size);

    blueGhost.setPosition(Tracker.getCoordinates(Blue).y*Grid_size, Tracker.getCoordinates(Blue).x*Grid_size);
    orangeGhost.setPosition(Tracker.getCoordinates(Orange).y*Grid_size, Tracker.getCoordinates(Orange).x*Grid_size);
    redGhost.setPosition(Tracker.getCoordinates(Red).y*Grid_size, Tracker.getCoordinates(Red).x*Grid_size);
    pinkGhost.setPosition(Tracker.getCoordinates(Pink).y*Grid_size, Tracker.getCoordinates(Pink).x*Grid_size);
    maze[Tracker.getCoordinates(Pac).x][Tracker.getCoordinates(Pac).y].setColor(sf::Color::Transparent);
    Tracker.setStorePos(Tracker.getCoordinates(Pac).x,Tracker.getCoordinates(Pac).y,2);
}

void Game::PacDead(RenderWindow& window)
{
    window.clear() ;

    window.close();
    FinalDisplay(1);
}

void Game::Controler(RenderWindow& window)
{
    while (window.isOpen())
    {
        EventTracker(window);

        if(((clock()-SuperPacTimer)/(double)(CLOCKS_PER_SEC))>15)
        {
            SuperPac = false;
            Tracker.TurnSuperMode(SuperPac);
            player_.setScale(0.025, 0.023);

            blueGhost.setScale(0.11, 0.11);
            redGhost.setScale(0.11, 0.11);
            orangeGhost.setScale(0.11, 0.11);
            pinkGhost.setScale(0.11, 0.11);
        }

        IDENTITY GhostTex;
        GhostTex = Eating.PacEatGhost(Tracker);
        if( GhostTex == Pac)
        {
            isDead = Eating.GhostEatPac(Tracker) ;

            if(SuperPac)
            {
                ChangeGhostSuper();
                isDead = false;
            }
            if(isDead)
            {
                PacDead(window);
            }
        }
        if(Score == totalFood)
        {
            window.close();
            FinalDisplay(2);
        }

        if(Keyboard::isKeyPressed(Keyboard::Up))
        {
            player_.setTexture(pacManUp);
            ChangeTexture(Tracker.MovePac(Up)) ;

            BlueMove = Up;
            OrangeMove=Down;
        }
        if(Keyboard::isKeyPressed(Keyboard::Down))
        {
            player_.setTexture(pacManDown);
            ChangeTexture(Tracker.MovePac(Down)) ;

            BlueMove = Down;
            OrangeMove=Up;
        }
        if(Keyboard::isKeyPressed(Keyboard::Left))
        {
            player_.setTexture(pacManLeft);
            ChangeTexture(Tracker.MovePac(Left)) ;

            BlueMove = Left;
            OrangeMove=Right;
        }
        if(Keyboard::isKeyPressed(Keyboard::Right))
        {
            player_.setTexture(pacManRight);
            ChangeTexture(Tracker.MovePac(Right)) ;

            BlueMove = Right;
            OrangeMove=Left;
        }
        ChangeGhostTexture(GhostTex);
        GhostMovement();
        WindowDraw_Display(window);
        Sleep( Speed );
    }
}

void Game::EventTracker(RenderWindow& window)
{
    // The next 6 lines of code detect if the window is closed
    // And then shuts down the program

    //Process events
    Event event;

    while (window.pollEvent(event))
    {
        //close window: exit
        if (event.type == Event::Closed)
        {
            // Someone closed the window
            window.close();
        }
        if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
        {
            window.close();
        }
    }
    // Clear everything from the last run of the while loop/screen
    window.clear();

    Update();
}

void Game::WindowDraw_Display(RenderWindow& window)
{
    // Draw our game scene here
    for(int r = 0; r < rows; r++)
    {
        for(int c = 0; c <cols; c++)
        {
            window.draw(maze[r][c]);
            window.draw(Locks[r][c]);
        }
    }
    window.draw(blueGhost);
    window.draw(redGhost);
    window.draw(orangeGhost);
    window.draw(pinkGhost);
    window.draw(player_);

    // Show everything we just drew
    window.display();
}

void Game::FinalDisplay(int Fin)
{
    Sprite Finish ;
    Texture over,win;

    over.loadFromFile("Resoruces/Fonts/GameOver.png") ;
    win.loadFromFile("Resoruces/Fonts/win.png") ;

    switch(Fin)
    {
    case 1:
    {
        Finish.setTexture(over);
        break;
    }
    case 2:
    {
        Finish.setTexture(win);
        break;
    }
    }
    Finish.setScale(2, 2);

    RenderWindow GameOver(VideoMode(800, 800), "Game Over");

    while (GameOver.isOpen())
    {
        sf::Event event;
        while (GameOver.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)

                GameOver.close();

            if ( event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard:: Escape)
                {
                    GameOver.close();
                }
            }
        }
        GameOver.clear();

        GameOver.draw(Finish);

        // Show everything we just drew
        GameOver.display();
    }
}

Game::~Game()
{
    //dtor
}
