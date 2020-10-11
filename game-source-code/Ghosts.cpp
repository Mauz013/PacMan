#include "Ghosts.h"
#include "Movement.h"
#include "Datatypes.h"
#include <vector>
#include <cmath>

using namespace std ;

Ghosts::Ghosts()
{
    //ctor
}
void Ghosts::BlueGhostMoves(Movement& Track, DIRECTION dir)
{
    TEXTURE NextTexture = Track.CheckWalLock(dir, Blue);

    if(dir == Left && NextTexture!= Wall && NextTexture!= Lock && (PrevBlue!='r' || IsNextToLock(Track, Blue)))
    {
        Track.MoveBlueGhost(Left);
        PrevBlue = 'l';
    }
    else if(dir == Right && NextTexture!= Wall && NextTexture!= Lock &&  (PrevBlue!='l'  ||  IsNextToLock(Track,Blue)))
    {
        Track.MoveBlueGhost(Right);
        PrevBlue = 'r';
    }
    else if(dir == Up && NextTexture!= Wall && NextTexture!= Lock && (PrevBlue!='d' ||  IsNextToLock(Track,Blue)))
    {
        Track.MoveBlueGhost(Up);
        PrevBlue = 'u';
    }
    else if(dir == Down && NextTexture!= Wall && NextTexture!= Lock && (PrevBlue!='u' ||   IsNextToLock(Track,Blue)))
    {
        Track.MoveBlueGhost(Down);
        PrevBlue = 'd';
    }
    else
    {
        vector<bool> ValidMoves;

        if(Track.CheckWalLock(Left, Blue)!= Wall && Track.CheckWalLock(Left, Blue)!= Lock)
            ValidMoves.push_back(true);
        else
            ValidMoves.push_back(false);

        if(Track.CheckWalLock(Right, Blue)!= Wall && Track.CheckWalLock(Right, Blue)!= Lock)
            ValidMoves.push_back(true);
        else
            ValidMoves.push_back(false);

        if(Track.CheckWalLock(Up, Blue)!= Wall && Track.CheckWalLock(Up, Blue)!= Lock)
            ValidMoves.push_back(true);
        else
            ValidMoves.push_back(false);

        if(Track.CheckWalLock(Down, Blue)!= Wall && Track.CheckWalLock(Down, Blue)!= Lock)
            ValidMoves.push_back(true);
        else
            ValidMoves.push_back(false);

        if(ValidMoves[0]==true && (PrevBlue!='r' ||  IsNextToLock(Track,Blue)))//left
        {
            Track.MoveBlueGhost(Left);
            PrevBlue = 'l';
        }
        else if(ValidMoves[1]==true && (PrevBlue!='l'  ||  IsNextToLock(Track,Blue)))//right
        {
            Track.MoveBlueGhost(Right);
            PrevBlue = 'r';
        }
        else if(ValidMoves[2]==true && (PrevBlue!='d'||  IsNextToLock(Track,Blue)))//up
        {
            Track.MoveBlueGhost(Up);
            PrevBlue = 'u';
        }
        else if(ValidMoves[3]==true && (PrevBlue!='u' ||  IsNextToLock(Track,Blue)))//down
        {
            Track.MoveBlueGhost(Down);
            PrevBlue = 'd';
        }
        ValidMoves.clear();
    }
}

void Ghosts::RedGhostMoves(Movement& Track)
{
    vector<bool> ValidMoves;

    if(Track.CheckWalLock(Left, Red)!= Wall && Track.CheckWalLock(Left, Red)!= Lock)
        ValidMoves.push_back(true);
    else
        ValidMoves.push_back(false);

    if(Track.CheckWalLock(Right, Red)!= Wall && Track.CheckWalLock(Right, Red)!= Lock)
        ValidMoves.push_back(true);
    else
        ValidMoves.push_back(false);

    if(Track.CheckWalLock(Up, Red)!= Wall && Track.CheckWalLock(Up, Red)!= Lock)
        ValidMoves.push_back(true);
    else
        ValidMoves.push_back(false);

    if(Track.CheckWalLock(Down, Red)!= Wall && Track.CheckWalLock(Down, Red)!= Lock)
        ValidMoves.push_back(true);
    else
        ValidMoves.push_back(false);

    int X =  Track.getCoordinates(Red).x - Track.getCoordinates(Pac).x;
    int Y =  Track.getCoordinates(Red).y - Track.getCoordinates(Pac).y;

    if(fabs(X) < fabs(Y)) //if x co-ordinate of pac is closer to x of RedGhost
    {
        if(X < 0 && Track.CheckWalLock(Down, Red) != Wall && Track.CheckWalLock(Down, Red) != Lock && (PrevRed!='u' ||  IsNextToLock(Track,Red)))
        {
            Track.MoveRedGhost(Down);
            PrevRed = 'd';
        }
        else if(X > 0 && Track.CheckWalLock(Up, Red) != Wall && Track.CheckWalLock(Up, Red) != Lock && (PrevRed!='d' || IsNextToLock(Track,Red)))
        {
            Track.MoveRedGhost(Up);
            PrevRed = 'u';
        }
        else if( Y < 0 && Track.CheckWalLock(Right, Red) != Wall && Track.CheckWalLock(Right, Red) != Lock  && (PrevRed!='l' || IsNextToLock(Track,Red)))
        {
            Track.MoveRedGhost(Right);
            PrevRed = 'r';
        }
        else if( Y>0 && Track.CheckWalLock(Left, Red) != Wall && Track.CheckWalLock(Left, Red) != Lock && (PrevRed!='r'  || IsNextToLock(Track,Red)))
        {
            Track.MoveRedGhost(Left);
            PrevRed = 'l';
        }
        else
        {
            if(ValidMoves[0]==true && (PrevRed!='r' || IsNextToLock(Track,Red)))
            {
                Track.MoveRedGhost(Left);
                PrevRed = 'l';
            }
            else if(ValidMoves[1]==true && (PrevRed!='l' || IsNextToLock(Track,Red)))
            {
                Track.MoveRedGhost(Right);
                PrevRed = 'r';
            }
            else if(ValidMoves[2]==true && (PrevRed!='d' || IsNextToLock(Track,Red)))//up
            {
                Track.MoveRedGhost(Up);
                PrevRed = 'u';
            }
            else if(ValidMoves[3]==true && (PrevRed!='u' || IsNextToLock(Track,Red)))//down
            {
                Track.MoveRedGhost(Down);
                PrevRed = 'd';
            }
        }
    }
    else //if y co-ordinate of pac is closer to y of RedGhost
    {
        if(Y < 0 &&  Track.CheckWalLock(Right, Red) != Wall && Track.CheckWalLock(Right, Red) != Lock && (PrevRed!='l' ||  IsNextToLock(Track,Red)))
        {
            Track.MoveRedGhost(Right);
            PrevRed = 'r';
        }
        else if(Y>0 && Track.CheckWalLock(Left, Red) != Wall && Track.CheckWalLock(Left, Red) != Lock && (PrevRed!='r' || IsNextToLock(Track,Red)))
        {
            Track.MoveRedGhost(Left);
            PrevRed = 'l';
        }
        else if( X<0 && Track.CheckWalLock(Down, Red) != Wall && Track.CheckWalLock(Down, Red) != Lock && (PrevRed!='u' || IsNextToLock(Track,Red)))
        {
            Track.MoveRedGhost(Down);
            PrevRed = 'd';
        }
        else if( X>0 && Track.CheckWalLock(Up, Red) != Wall && Track.CheckWalLock(Up, Red) != Lock && (PrevRed!='d' ||  IsNextToLock(Track,Red)))
        {
            Track.MoveRedGhost(Up);
            PrevRed = 'u';
        }
        else
        {
            if(ValidMoves[0]==true && (PrevRed!='r' || IsNextToLock(Track,Red)))//left
            {
                Track.MoveRedGhost(Left);
                PrevRed = 'l';
            }
            else if(ValidMoves[1]==true && (PrevRed!='l' || IsNextToLock(Track,Red)))//right
            {
                Track.MoveRedGhost(Right);
                PrevRed = 'r';
            }
            else if(ValidMoves[2]==true && (PrevRed!='d' || IsNextToLock(Track,Red)))//up
            {
                Track.MoveRedGhost(Up);
                PrevRed = 'u';
            }
            else if(ValidMoves[3]==true && (PrevRed!='u' || IsNextToLock(Track,Red)))//down
            {
                Track.MoveRedGhost(Down);
                PrevRed = 'd';
            }
        }
    }
    ValidMoves.clear();
}

void Ghosts::OrangeGhostMoves(Movement& Track, DIRECTION dir)
{
    TEXTURE NextTexture = Track.CheckWalLock(dir, Orange);

    if(dir == Left && NextTexture!= Wall && NextTexture!= Lock && (PrevOrange!='r' || IsNextToLock(Track,Orange)))
    {
        Track.MoveOrangeGhost(Left);
        PrevOrange = 'l';
    }
    else if(dir == Right && NextTexture!= Wall && NextTexture!= Lock &&  (PrevOrange!='l'  ||  IsNextToLock(Track,Orange)))
    {
        Track.MoveOrangeGhost(Right);
        PrevOrange = 'r';
    }
    else if(dir == Up && NextTexture!= Wall && NextTexture!= Lock && (PrevOrange!='d' ||  IsNextToLock(Track,Orange)))
    {
        Track.MoveOrangeGhost(Up);
        PrevOrange = 'u';
    }
    else if(dir == Down && NextTexture!= Wall && NextTexture!= Lock && (PrevOrange!='u' ||  IsNextToLock(Track,Orange)))
    {
        Track.MoveOrangeGhost(Down);
        PrevOrange = 'd';
    }
    else
    {
        vector<bool> ValidMoves;

        if(Track.CheckWalLock(Left, Orange)!= Wall && Track.CheckWalLock(Left, Orange)!= Lock)
            ValidMoves.push_back(true);
        else
            ValidMoves.push_back(false);

        if(Track.CheckWalLock(Right, Orange)!= Wall && Track.CheckWalLock(Right, Orange)!= Lock)
            ValidMoves.push_back(true);
        else
            ValidMoves.push_back(false);

        if(Track.CheckWalLock(Up, Orange)!= Wall && Track.CheckWalLock(Up, Orange)!= Lock)
            ValidMoves.push_back(true);
        else
            ValidMoves.push_back(false);

        if(Track.CheckWalLock(Down, Orange)!= Wall && Track.CheckWalLock(Down, Orange)!= Lock)
            ValidMoves.push_back(true);
        else
            ValidMoves.push_back(false);

        if(ValidMoves[0]==true && (PrevOrange!='r' || IsNextToLock(Track,Orange)))//left
        {
            Track.MoveOrangeGhost(Left);
            PrevOrange = 'l';
        }
        else if(ValidMoves[1]==true && (PrevOrange!='l'  || IsNextToLock(Track,Orange)))//right
        {
            Track.MoveOrangeGhost(Right);
            PrevOrange = 'r';
        }
        else if(ValidMoves[2]==true && (PrevOrange!='d'|| IsNextToLock(Track,Orange)))//up
        {
            Track.MoveOrangeGhost(Up);
            PrevOrange = 'u';
        }
        else if(ValidMoves[3]==true && (PrevOrange!='u' || IsNextToLock(Track,Orange)))//down
        {
            Track.MoveOrangeGhost(Down);
            PrevOrange = 'd';
        }
        ValidMoves.clear();
    }
}

void Ghosts::PinkGhostMoves(Movement& Track)
{
    vector<bool> ValidMoves;

    if(Track.CheckWalLock(Left, Pink)!= Wall && Track.CheckWalLock(Left, Pink)!= Lock)
        ValidMoves.push_back(true);
    else
        ValidMoves.push_back(false);

    if(Track.CheckWalLock(Right, Pink)!= Wall && Track.CheckWalLock(Right, Pink)!= Lock)
        ValidMoves.push_back(true);
    else
        ValidMoves.push_back(false);

    if(Track.CheckWalLock(Up, Pink)!= Wall && Track.CheckWalLock(Up, Pink)!= Lock)
        ValidMoves.push_back(true);
    else
        ValidMoves.push_back(false);

    if(Track.CheckWalLock(Down, Pink)!= Wall && Track.CheckWalLock(Down, Pink)!= Lock)
        ValidMoves.push_back(true);
    else
        ValidMoves.push_back(false);

    int X =  Track.getCoordinates(Pink).x - Track.getCoordinates(Pac).x;
    int Y =  Track.getCoordinates(Pink).y - Track.getCoordinates(Pac).y;

    if(fabs(X) > fabs(Y)) //if x co-ordinate of pac is further to x of PinkGhost
    {
        if(X < 0 && Track.CheckWalLock(Down, Pink) != Wall && Track.CheckWalLock(Down, Pink) != Lock && (PrevPink!='u' ||  IsNextToLock(Track,Pink)))
        {
            Track.MovePinkGhost(Down);
            PrevPink = 'd';
        }
        else if(X > 0 && Track.CheckWalLock(Up, Pink) != Wall && Track.CheckWalLock(Up, Pink) != Lock && (PrevPink!='d' || IsNextToLock(Track,Pink)))
        {
            Track.MovePinkGhost(Up);
            PrevPink = 'u';
        }
        else if( Y < 0 && Track.CheckWalLock(Right, Pink) != Wall && Track.CheckWalLock(Right, Pink) != Lock  && (PrevPink!='l' || IsNextToLock(Track,Pink)))
        {
            Track.MovePinkGhost(Right);
            PrevPink = 'r';
        }
        else if( Y>0 && Track.CheckWalLock(Left, Pink) != Wall && Track.CheckWalLock(Left, Pink) != Lock && (PrevPink!='r'  || IsNextToLock(Track,Pink)))
        {
            Track.MovePinkGhost(Left);
            PrevPink = 'l';
        }
        else
        {
            if(ValidMoves[0]==true && (PrevPink!='r' || IsNextToLock(Track,Pink)))
            {
                Track.MovePinkGhost(Left);
                PrevPink = 'l';
            }
            else if(ValidMoves[1]==true && (PrevPink!='l' || IsNextToLock(Track,Pink)))
            {
                Track.MovePinkGhost(Right);
                PrevPink = 'r';
            }
            else if(ValidMoves[2]==true && (PrevPink!='d' || IsNextToLock(Track,Pink)))//up
            {
                Track.MovePinkGhost(Up);
                PrevPink = 'u';
            }
            else if(ValidMoves[3]==true && (PrevPink!='u' || IsNextToLock(Track,Pink)))//down
            {
                Track.MovePinkGhost(Down);
                PrevPink = 'd';
            }
        }
    }
    else //if y co-ordinate of pac is Further to y of PinkGhost
    {
        if(Y < 0 &&  Track.CheckWalLock(Right, Pink) != Wall && Track.CheckWalLock(Right, Pink) != Lock && (PrevPink!='l' ||  IsNextToLock(Track,Pink)))
        {
            Track.MovePinkGhost(Right);
            PrevPink = 'r';
        }
        else if(Y>0 && Track.CheckWalLock(Left, Pink) != Wall && Track.CheckWalLock(Left, Pink) != Lock && (PrevPink!='r' || IsNextToLock(Track,Pink)))
        {
            Track.MovePinkGhost(Left);
            PrevPink = 'l';
        }
        else if( X<0 && Track.CheckWalLock(Down, Pink) != Wall && Track.CheckWalLock(Down, Pink) != Lock && (PrevPink!='u' || IsNextToLock(Track,Pink)))
        {
            Track.MovePinkGhost(Down);
            PrevPink = 'd';
        }
        else if( X>0 && Track.CheckWalLock(Up, Pink) != Wall && Track.CheckWalLock(Up, Pink) != Lock && (PrevPink!='d' ||  IsNextToLock(Track,Pink)))
        {
            Track.MovePinkGhost(Up);
            PrevPink = 'u';
        }
        else
        {
            if(ValidMoves[0]==true && (PrevPink!='r' || IsNextToLock(Track,Pink)))//left
            {
                Track.MovePinkGhost(Left);
                PrevPink = 'l';
            }
            else if(ValidMoves[1]==true && (PrevPink!='l' || IsNextToLock(Track,Pink)))//right
            {
                Track.MovePinkGhost(Right);
                PrevPink = 'r';
            }
            else if(ValidMoves[2]==true && (PrevPink!='d' || IsNextToLock(Track,Pink)))//up
            {
                Track.MovePinkGhost(Up);
                PrevPink = 'u';
            }
            else if(ValidMoves[3]==true && (PrevPink!='u' || IsNextToLock(Track,Pink)))//down
            {
                Track.MovePinkGhost(Down);
                PrevPink = 'd';
            }
        }
    }
    ValidMoves.clear();
}

void Ghosts::GhostMode(Movement& Track, IDENTITY ID)
{
    char PrevDir = ' ';
    DIRECTION toMove;
    switch(ID)
    {
    case Blue:
    {
        PrevDir = PrevBlue;
        break;
    }
    case Red:
    {
        PrevDir = PrevRed;
        break;
    }
    case Orange:
    {
        PrevDir = PrevOrange;
        break;
    }
    case Pink:
    {
        PrevDir = PrevPink;
        break;
    }
    case Pac: {

        break;
    }
    }
    vector<bool> ValidMoves;

    if(Track.CheckWalLock(Left, ID)!= Wall && Track.CheckWalLock(Left, ID)!= Lock)
        ValidMoves.push_back(true);
    else
        ValidMoves.push_back(false);

    if(Track.CheckWalLock(Right, ID)!= Wall && Track.CheckWalLock(Right, ID)!= Lock)
        ValidMoves.push_back(true);
    else
        ValidMoves.push_back(false);

    if(Track.CheckWalLock(Up, ID)!= Wall && Track.CheckWalLock(Up, ID)!= Lock)
        ValidMoves.push_back(true);
    else
        ValidMoves.push_back(false);

    if(Track.CheckWalLock(Down, ID)!= Wall && Track.CheckWalLock(Down, ID)!= Lock)
        ValidMoves.push_back(true);
    else
        ValidMoves.push_back(false);

    int X =  Track.getCoordinates(ID).x - Track.getCoordinates(Pac).x;
    int Y =  Track.getCoordinates(ID).y - Track.getCoordinates(Pac).y;

    if(fabs(X) < fabs(Y)) //if x co-ordinate of pac is closer to x of IDGhost
    {
        if(X > 0 && Track.CheckWalLock(Down, ID) != Wall && Track.CheckWalLock(Down, ID) != Lock && (PrevDir!='u' ||  IsNextToLock(Track,ID)))
        {
            toMove = Down;
            PrevDir = 'd';
        }
        else if(X < 0 && Track.CheckWalLock(Up, ID) != Wall && Track.CheckWalLock(Up, ID) != Lock && (PrevDir!='d' || IsNextToLock(Track,ID)))
        {
            toMove = Up;
            PrevDir = 'u';
        }
        else if( Y > 0 && Track.CheckWalLock(Right, ID) != Wall && Track.CheckWalLock(Right, ID) != Lock  && (PrevDir!='l' || IsNextToLock(Track,ID)))
        {
            toMove = Right;
            PrevDir = 'r';
        }
        else if( Y < 0 && Track.CheckWalLock(Left, ID) != Wall && Track.CheckWalLock(Left, ID) != Lock && (PrevDir!='r'  || IsNextToLock(Track,ID)))
        {
            toMove = Left;
            PrevDir = 'l';
        }
        else
        {
            if(ValidMoves[0]==true && (PrevDir!='r' || IsNextToLock(Track,ID)))
            {
                toMove = Left;
                PrevDir = 'l';
            }
            else if(ValidMoves[1]==true && (PrevDir!='l' || IsNextToLock(Track,ID)))
            {
                toMove = Right;
                PrevDir = 'r';
            }
            else if(ValidMoves[2]==true && (PrevDir!='d' || IsNextToLock(Track,ID)))//up
            {
                toMove = Up;
                PrevDir = 'u';
            }
            else if(ValidMoves[3]==true && (PrevDir!='u' || IsNextToLock(Track,ID)))//down
            {
                toMove = Down;
                PrevDir = 'd';
            }
        }
    }
    else //if y co-ordinate of pac is closer to y of IDGhost
    {
        if(Y > 0 &&  Track.CheckWalLock(Right, ID) != Wall && Track.CheckWalLock(Right, ID) != Lock && (PrevDir!='l' ||  IsNextToLock(Track,ID)))
        {
            toMove = Right;
            PrevDir = 'r';
        }
        else if(Y < 0 && Track.CheckWalLock(Left, ID) != Wall && Track.CheckWalLock(Left, ID) != Lock && (PrevDir!='r' || IsNextToLock(Track,ID)))
        {
            toMove = Left;
            PrevDir = 'l';
        }
        else if( X > 0 && Track.CheckWalLock(Down, ID) != Wall && Track.CheckWalLock(Down, ID) != Lock && (PrevDir!='u' || IsNextToLock(Track,ID)))
        {
            toMove = Down;
            PrevDir = 'd';
        }
        else if( X < 0 && Track.CheckWalLock(Up, ID) != Wall && Track.CheckWalLock(Up, ID) != Lock && (PrevDir!='d' ||  IsNextToLock(Track,ID)))
        {
            toMove = Up;
            PrevDir = 'u';
        }
        else
        {
            if(ValidMoves[0]==true && (PrevDir!='r' || IsNextToLock(Track,ID)))//left
            {
                toMove = Left;
                PrevDir = 'l';
            }
            else if(ValidMoves[1]==true && (PrevDir!='l' || IsNextToLock(Track,ID)))//right
            {
                toMove = Right;
                PrevDir = 'r';
            }
            else if(ValidMoves[2]==true && (PrevDir!='d' || IsNextToLock(Track,ID)))//up
            {
                toMove = Up;
                PrevDir = 'u';
            }
            else if(ValidMoves[3]==true && (PrevDir!='u' || IsNextToLock(Track,ID)))//down
            {
                toMove = Down;
                PrevDir = 'd';
            }
        }
    }
    ValidMoves.clear();
    switch(ID)
    {
    case Blue:
    {
        PrevBlue = PrevDir;
        Track.MoveBlueGhost(toMove);
        break;
    }
    case Red:
    {
        PrevRed = PrevDir;
        Track.MoveRedGhost(toMove);
        break;
    }
    case Orange:
    {
        PrevOrange = PrevDir;
        Track.MoveOrangeGhost(toMove);
        break;
    }
    case Pink:
    {
        PrevPink = PrevDir;
        Track.MovePinkGhost(toMove);
        break;
    }
    case Pac:{
            break;
    }
    }
}

bool Ghosts::IsNextToLock(Movement& Track, IDENTITY ID)
{
    if(Track.CheckWalLock(Left, ID) == Lock || Track.CheckWalLock(Right, ID) == Lock || Track.CheckWalLock(Up, ID) == Lock || Track.CheckWalLock(Down, ID) == Lock)
    {
        return true;
    }
    else
        return false;
}

Ghosts::~Ghosts()
{
    //dtor
}
