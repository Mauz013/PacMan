#include "PositionHandler.h"

#include <fstream>
#include <iostream>

using namespace std;

PositionHandler::PositionHandler()
{

}

void PositionHandler::Init_StorePos(string Filename_)
{
    ifstream inFile;
    inFile.open(Filename_);

    for(int r = 0; r < 22; r++)
    {
        for(int c = 0; c < 19; c++)
        {
            inFile >> StorePos[r][c];
        }
    }
}

void PositionHandler::setStorePos(int r, int c, int ChangeNum)
{
    StorePos[r][c]= ChangeNum;
}

void PositionHandler::setSpritePos(int x, int y, IDENTITY ID)
{
    switch(ID)
    {
    case Pac:
    {
        PacPos.x = x;
        PacPos.y = y;
        break;
    }
    case Blue:
    {
        BluePos.x = x;
        BluePos.y = y;
        break;
    }
    case Red:
    {
        RedPos.x = x;
        RedPos.y = y;
        break;
    }
    case Orange:
    {
        OrangePos.x = x;
        OrangePos.y = y;
        break;
    }
    case Pink:
    {
        PinkPos.x = x;
        PinkPos.y = y;
        break;
    }
    }
}

void PositionHandler::SetInit(IDENTITY ID, int r, int c)
{
    switch(ID)
    {
    case Blue:
    {
        setSpritePos(r,c,Blue);
        BlueInit.x = r ;
        BlueInit.y = c ;
        break;
    }
    case Red:
    {
        setSpritePos(r,c,Red);
        RedInit.x = r ;
        RedInit.y = c ;
        break;
    }
    case Pink:
    {
        setSpritePos(r,c,Pink);
        PinkInit.x = r ;
        PinkInit.y = c ;
        break;
    }
    case Orange:
    {
        setSpritePos(r,c,Orange);
        OrangeInit.x = r ;
        OrangeInit.y = c ;
        break;
    }
    }
}

int PositionHandler::getStorePos(int r, int c)
{
    return StorePos[r][c];
}

Coordinates PositionHandler::getCoordinates(IDENTITY ID)
{
    switch(ID)
    {
    case Pac:
    {
        return PacPos;
    }
    case Blue:
    {
        return BluePos;
    }
    case Red:
    {
        return RedPos;
    }
    case Orange:
    {
        return OrangePos;
    }
    case Pink:
    {
        return PinkPos;
    }
    }
}

Coordinates PositionHandler::GetInit(IDENTITY ID)
{
    switch(ID)
    {
    case Blue:
    {
        return BlueInit;
    }
    case Red:
    {
        return RedInit;
        break;
    }
    case Pink:
    {
        return PinkInit;
        break;
    }
    case Orange:
    {
        return OrangeInit;
        break;
    }
    }
}

PositionHandler::~PositionHandler()
{
    //dtor
}
