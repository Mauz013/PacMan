#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "PositionHandler.h"


class Movement: public PositionHandler
{
public:
    Movement();
    ~Movement();

    void MoveBlueGhost(DIRECTION dir);
    void MoveRedGhost(DIRECTION dir);
    void MoveOrangeGhost(DIRECTION dir);
    void MovePinkGhost(DIRECTION dir);

    void TurnGhostMode(bool Mode);
    void TurnGhostModeOff(IDENTITY ID,bool Mode);
    void TurnSuperMode(bool Mode);

    bool getGhostMode(IDENTITY ID);

    Coordinates GetNextCoord(DIRECTION dir, IDENTITY ID);
    TEXTURE CheckWalLock(DIRECTION dir, IDENTITY ID);
    TEXTURE MovePac(DIRECTION dir);

private:
    bool GhostBluemode = false;
    bool GhostRedMode =  false;
    bool GhostPinkMode = false;
    bool GhostOrangeMode = false;
    bool SuperPac = false;






};

#endif // MOVEMENT_H
