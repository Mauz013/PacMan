#include "eater.h"
#include "Datatypes.h"

Eater::Eater()
{
    //ctor
}

bool Eater::GhostEatPac(Movement& Track)
{
    Coordinates PacMan;
    PacMan = Track.getCoordinates(Pac);

    if(PacMan.x == Track.getCoordinates(Blue).x && PacMan.y == Track.getCoordinates(Blue).y && Track.getGhostMode(Blue) == false)
    {
        return true;
    }
    if(PacMan.x == Track.getCoordinates(Red).x && PacMan.y == Track.getCoordinates(Red).y && Track.getGhostMode(Red) == false)
    {
        return true;
    }
    if(PacMan.x == Track.getCoordinates(Pink).x && PacMan.y == Track.getCoordinates(Pink).y && Track.getGhostMode(Pink) == false)
    {
        return true;
    }
    if(PacMan.x == Track.getCoordinates(Orange).x && PacMan.y == Track.getCoordinates(Orange).y && Track.getGhostMode(Orange) == false)
    {
        return true;
    }
    return false;
}

IDENTITY Eater::PacEatGhost(Movement& Track)
{
    Coordinates PacMan;
    PacMan = Track.getCoordinates(Pac);

    if(PacMan.x == Track.getCoordinates(Blue).x && PacMan.y == Track.getCoordinates(Blue).y && Track.getGhostMode(Blue) == true)
    {
        Track.setSpritePos(Track.GetInit(Blue).x,Track.GetInit(Blue).y,Blue);
        Track.TurnGhostModeOff(Blue,false);
        return Blue;
    }
    if(PacMan.x == Track.getCoordinates(Red).x && PacMan.y == Track.getCoordinates(Red).y && Track.getGhostMode(Red)  == true)
    {
        Track.setSpritePos(Track.GetInit(Red).x,Track.GetInit(Red).y,Red);
        Track.TurnGhostModeOff(Red,false);
        return Red;
    }
    if(PacMan.x == Track.getCoordinates(Pink).x && PacMan.y == Track.getCoordinates(Pink).y && Track.getGhostMode(Pink) == true)
    {
        Track.setSpritePos(Track.GetInit(Pink).x,Track.GetInit(Pink).y,Pink);
        Track.TurnGhostModeOff(Pink,false);
        return Pink;
    }
    if(PacMan.x == Track.getCoordinates(Orange).x && PacMan.y == Track.getCoordinates(Orange).y && Track.getGhostMode(Orange) == true)
    {
        Track.setSpritePos(Track.GetInit(Orange).x,Track.GetInit(Orange).y,Orange);
        Track.TurnGhostModeOff(Orange,false);
        return Orange;
    }
    return Pac;
}

Eater::~Eater()
{
    //dtor
}
