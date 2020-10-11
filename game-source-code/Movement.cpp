#include "Movement.h"
#include <iostream>

using namespace std;

Movement::Movement()
{
    //ctor
}

void Movement::MoveBlueGhost(DIRECTION dir)
{
    Coordinates BlueMan;
    BlueMan = getCoordinates(Blue);
    switch (dir)
    {
    case Left:
    {
        setSpritePos(BlueMan.x, BlueMan.y-1, Blue);
        break;
    }
    case Right:
    {
        setSpritePos(BlueMan.x, BlueMan.y+1, Blue);
        break;
    }
    case Up:
    {
        setSpritePos(BlueMan.x-1, BlueMan.y, Blue);
        break;
    }
    case Down:
    {
        setSpritePos(BlueMan.x+1, BlueMan.y, Blue);
        break;
    }
    }
}

void Movement::MoveRedGhost(DIRECTION dir)
{
    Coordinates RedMan;
    RedMan = getCoordinates(Red);
    switch (dir)
    {
    case Left:
    {
        setSpritePos(RedMan.x, RedMan.y-1, Red);
        break;
    }
    case Right:
    {
        setSpritePos(RedMan.x, RedMan.y+1, Red);
        break;
    }
    case Up:
    {
        setSpritePos(RedMan.x-1, RedMan.y, Red);
        break;
    }
    case Down:
    {
        setSpritePos(RedMan.x+1, RedMan.y, Red);
        break;
    }
    }
}

void Movement::MoveOrangeGhost(DIRECTION dir)
{
    Coordinates OrangeMan;
    OrangeMan = getCoordinates(Orange);
    switch (dir)
    {
    case Left:
    {
        setSpritePos(OrangeMan.x, OrangeMan.y-1, Orange);
        break;
    }
    case Right:
    {
        setSpritePos(OrangeMan.x, OrangeMan.y+1, Orange);
        break;
    }
    case Up:
    {
        setSpritePos(OrangeMan.x-1, OrangeMan.y, Orange);
        break;
    }
    case Down:
    {
        setSpritePos(OrangeMan.x+1, OrangeMan.y, Orange);
        break;
    }
    }
}

void Movement::MovePinkGhost(DIRECTION dir)
{

    Coordinates PinkMan;
    PinkMan = getCoordinates(Pink);
    switch (dir)
    {
    case Left:
    {
        setSpritePos(PinkMan.x, PinkMan.y-1, Pink);

        break;
    }
    case Right:
    {
        setSpritePos(PinkMan.x, PinkMan.y+1, Pink);

        break;
    }
    case Up:
    {
        setSpritePos(PinkMan.x-1, PinkMan.y, Pink);

        break;
    }
    case Down:
    {
        setSpritePos(PinkMan.x+1, PinkMan.y, Pink);

        break;
    }
    }
}

void Movement::TurnGhostMode(bool Mode)
{
    GhostBluemode = Mode;
    GhostOrangeMode = Mode;
    GhostRedMode = Mode ;
    GhostPinkMode = Mode;
}

void Movement::TurnGhostModeOff(IDENTITY ID, bool Mode)
{
    switch (ID)
    {
    case Blue:
    {
        GhostBluemode = Mode;
        break;
    }
    case Pink:
    {
        GhostPinkMode = Mode;
        break;
    }
    case Red:
    {
        GhostRedMode = Mode;
        break;
    }
    case Orange:
    {
        GhostOrangeMode = Mode;
        break;
    }
    }
}

void Movement::TurnSuperMode(bool Mode)
{
    SuperPac = Mode;
}

bool Movement::getGhostMode(IDENTITY ID)
{
    switch(ID)
    {
    case Blue:
    {
        return GhostBluemode;
    }
    case Red:
    {
        return GhostRedMode;
    }
    case Orange:
    {
        return GhostOrangeMode;
    }
    case Pink:
    {
        return GhostPinkMode;
    }
    }
}

Coordinates Movement::GetNextCoord(DIRECTION dir, IDENTITY ID)
{
    Coordinates Character ;
    Character = getCoordinates(ID);

    switch (dir)
    {
    case Left:
    {
        Character.y = Character.y-1 ;
        break;
    }
    case Right:
    {
        Character.y = Character.y+1;
        break;
    }
    case Up:
    {
        Character.x = Character.x-1;
        break;
    }
    case Down:
    {
        Character.x = Character.x+1 ;
        break;
    }
    }
    return Character;
}

TEXTURE Movement::CheckWalLock(DIRECTION dir, IDENTITY ID)
{
    Coordinates Character ;
    Character = GetNextCoord(dir,ID) ;

    if (getStorePos(Character.x,Character.y)== 1)
    {
        return Wall ;
    }
    else if( getStorePos(Character.x,Character.y)== 7)
    {
        return Lock;
    }
    else if(getStorePos(Character.x,Character.y)== 5)
    {
        return Key;
    }
    else if(getStorePos(Character.x,Character.y)== 6)
    {
        return Power;
    }
    else if(getStorePos(Character.x,Character.y)== 10)
    {
        return Super;
    }
    else if(getStorePos(Character.x,Character.y)== 3 || getStorePos(Character.x,Character.y)== 0 || getStorePos(Character.x,Character.y)== 4)
    {
        return Food;
    }
    return blank;
}

TEXTURE Movement::MovePac(DIRECTION dir)
{
    Coordinates Pacman;
    Pacman = getCoordinates(Pac);

    TEXTURE ChangeTex;
    ChangeTex = CheckWalLock(dir,Pac);

    if(ChangeTex == Lock && SuperPac == true)
    {
        switch (dir)
        {
        case Left:
        {
            setSpritePos(Pacman.x, Pacman.y-1, Pac);
            break;
        }
        case Right:
        {
            setSpritePos(Pacman.x, Pacman.y+1, Pac);
            break;
        }
        case Up:
        {
            setSpritePos(Pacman.x-1, Pacman.y, Pac);
            break;
        }
        case Down:
        {
            setSpritePos(Pacman.x+1, Pacman.y, Pac);
            break;
        }
        }
        return BreakLock;
    }
    else if(ChangeTex!= Wall && ChangeTex!= Lock)
    {
        switch (dir)
        {
        case Left:
        {
            setSpritePos(Pacman.x, Pacman.y-1, Pac);
            break;
        }
        case Right:
        {
            setSpritePos(Pacman.x, Pacman.y+1, Pac);
            break;
        }
        case Up:
        {
            setSpritePos(Pacman.x-1, Pacman.y, Pac);
            break;
        }
        case Down:
        {
            setSpritePos(Pacman.x+1, Pacman.y, Pac);
            break;
        }
        }
    }
    return ChangeTex;
}

Movement::~Movement()
{
    //dtor
}
