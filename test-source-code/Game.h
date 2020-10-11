#ifndef GAME_H
#define GAME_H
#include "Datatypes.h"
#include "PositionHandler.h"
#include "Movement.h"
#include "Ghosts.h"
#include "eater.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <math.h>
#include <dos.h>
#include <windows.h>
#include <string>
#include <vector>

using namespace sf;
using namespace std;

class Game
{
public:
    Game(string FileName);
    Game();
    void StartGame();

    int getTotalFood();
    int getScore();

    void ChangesAfterPelletEaten(TEXTURE tir);
    Sprite getSprite(IDENTITY ID);
    Ghosts getGhostObj();
    Movement getMovementObj();
    Eater getEaterObj();

    virtual ~Game();

private:
    //Functions
    void LoadTextures();
    void CreateMaze();
    void ResetPos();
    void setKey(int r, int c);

    void GhostMovement();
    void ChangeTexture(TEXTURE Tir);
    void ChangeGhostTexture(IDENTITY ID);
    void ChangeGhostSuper();

    void Update();

    void PacDead(RenderWindow& window);
    void Controler(RenderWindow& window);
    void EventTracker(RenderWindow& window);
    void WindowDraw_Display(RenderWindow& window);

    void FinalDisplay(int Fin);

    //Objects
    Movement Tracker;
    Ghosts Enemy;
    Eater Eating;

    const int rows = 22;
    const int cols = 19;
    const int Grid_size = 30 ;
    const unsigned Window_WIDTH = 571 ;
    const unsigned Window_HEIGHT = 660 ;
    string FileName_;

    int unlockCount=0;
    int TempCount = 0 ;
    int LockCount=0;
    int Speed = 85; // speed Pac moves

    int totalFood, Score;
    int GhostCounter = 5;   //Delays the movement of the ghosts
    int startGhostModeTimer = 0, SuperPacTimer = 0;
    DIRECTION BlueMove, OrangeMove;
    bool GhostModeOn = false;
    bool SuperPac = false;
    bool isDead;

    //Need my Sprite 2D array
    Sprite maze[22][19];
    //Need player
    Sprite player_;
    //Ghosts
    Sprite blueGhost, redGhost, orangeGhost, pinkGhost;
    //Locks we need
    Sprite Locks[22][19];

    vector<int> GPelStorR; //stores where the locks are
    vector<int> GPelStorC;

    vector<int> GPelStorR2; //stores where the locks are
    vector<int> GPelStorC2;

    vector<int> GPelStorR3; //stores where the locks are
    vector<int> GPelStorC3;

    //textures
    Texture pacManLeft, pacManRight, pacManUp, pacManDown, ghostBlue, ghostRed, ghostOrange, ghostPink, VulnerableGhost;
    Texture brick, YellowPellets, SuperPel, PowerPel, Berry, PacKey, Locker;
};

#endif // GAME_H
