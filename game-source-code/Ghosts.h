#ifndef GHOSTS_H
#define GHOSTS_H

#include "Movement.h"
#include "Datatypes.h"


class Ghosts
{
    public:
        Ghosts();
        ~Ghosts();

        void BlueGhostMoves(Movement& Track, DIRECTION dir);
        void RedGhostMoves(Movement& Track);
        void OrangeGhostMoves(Movement& Track, DIRECTION dir);
        void PinkGhostMoves(Movement& Track);
        void GhostMode(Movement& Track, IDENTITY ID);
        bool IsNextToLock(Movement& Track, IDENTITY ID);

    private:
        char PrevBlue = ' ';
        char PrevRed = ' ';
        char PrevOrange = ' ';
        char PrevPink = ' ';
};

#endif // GHOSTS_H
