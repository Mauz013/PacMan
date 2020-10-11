#ifndef EATER_H
#define EATER_H
#include "Movement.h"
#include "Datatypes.h"

class Eater
{
    public:
        Eater();
        ~Eater();

        bool GhostEatPac(Movement& Track);
        IDENTITY PacEatGhost(Movement& Track);
};

#endif // EATER_H
