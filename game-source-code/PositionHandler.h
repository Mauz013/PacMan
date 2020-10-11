#ifndef POSITIONHANDLER_H
#define POSITIONHANDLER_H
#include "Datatypes.h"

#include <string>

using namespace std;

class PositionHandler
{
    public:
        PositionHandler();
        ~PositionHandler();
        void Init_StorePos(string Filename_);
        void setStorePos(int r, int c, int ChangeNum);
        void setSpritePos(int x, int y, IDENTITY ID);
        void SetInit(IDENTITY ID, int r, int c);
        int getStorePos(int r, int c);
        Coordinates getCoordinates(IDENTITY ID);
        Coordinates GetInit(IDENTITY ID);

    private:
        int StorePos[22][19];

        Coordinates PacPos;
        Coordinates BluePos;
        Coordinates RedPos;
        Coordinates OrangePos;
        Coordinates PinkPos;

        Coordinates BlueInit;
        Coordinates PinkInit;
        Coordinates RedInit;
        Coordinates OrangeInit;
        Coordinates PacInit;
};

#endif // POSITIONHANDLER_H
