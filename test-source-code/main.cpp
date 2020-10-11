#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Game.h"
#include "eater.h"
#include "Ghosts.h"
#include "Movement.h"
#include "PositionHandler.h"
#include "Datatypes.h"
#include <iostream>

#include <SFML/Graphics.hpp>
using namespace sf;

////////////////INITIALISATION TESTS/////////////////
TEST_CASE("Set Position Function sets the correct position for Pac")
{
    Game Play;
    Movement Moving = Play.getMovementObj();
    Moving.setSpritePos(7, 14, Pac);
    CHECK(Moving.getCoordinates(Pac).x == 7);
    CHECK(Moving.getCoordinates(Pac).y == 14);
}
TEST_CASE("Set Position Function sets the correct position for Ghost")
{
    Game Play;
    Movement Moving = Play.getMovementObj();
    Moving.setSpritePos(19, 8, Blue);
    CHECK(Moving.getCoordinates(Blue).x == 19);
    CHECK(Moving.getCoordinates(Blue).y == 8);
}
TEST_CASE("Get Position Function Returns Correct Positons")
{
    Game Play;
    Movement Moving = Play.getMovementObj();
    Moving.setSpritePos(10, 6, Pac);
    CHECK(Moving.getCoordinates(Pac).x == 10);
    CHECK(Moving.getCoordinates(Pac).y == 6);
}
TEST_CASE("PacMan Spawns in the correct Position")
{
    Game Play;
    Movement Moving = Play.getMovementObj();
    CHECK(Moving.getCoordinates(Pac).x == 16);
    CHECK(Moving.getCoordinates(Pac).y == 9);
}
TEST_CASE("BlueGhost Spawns in the correct Position")
{
    Game Play;
    Movement Moving = Play.getMovementObj();
    CHECK(Moving.getCoordinates(Blue).x == 8);
    CHECK(Moving.getCoordinates(Blue).y == 8);
}
TEST_CASE("RedGhost Spawns in the correct Position")
{
    Game Play;
    Movement Moving = Play.getMovementObj();
    CHECK(Moving.getCoordinates(Red).x == 8);
    CHECK(Moving.getCoordinates(Red).y == 10);
}
TEST_CASE("OrangeGhost Spawns in the correct Position")
{
    Game Play;
    Movement Moving = Play.getMovementObj();
    CHECK(Moving.getCoordinates(Orange).x == 11);
    CHECK(Moving.getCoordinates(Orange).y == 8);
}
TEST_CASE("PinkGhost Spawns in the correct Position")
{
    Game Play;
    Movement Moving = Play.getMovementObj();
    CHECK(Moving.getCoordinates(Pink).x == 11);
    CHECK(Moving.getCoordinates(Pink).y == 10);
}
TEST_CASE("Get TotalFood that user has to reach to win")
{
    Game Play;
    CHECK(Play.getTotalFood()== 167);
}

////////////////////////CHECKING FUNCTIONS FOR MOVEMENT///////////////////////
TEST_CASE("Getting Next co-ordinates in specified direction for pacman works")
{
    Game Play;
    Movement Moving = Play.getMovementObj();
    CHECK(Moving.GetNextCoord(Right, Pac).x == 16);
    CHECK(Moving.GetNextCoord(Right, Pac).y == 10);
}
TEST_CASE("Getting Next co-ordinates in specified direction for Ghost works")
{
    Game Play;
    Movement Moving = Play.getMovementObj();
    CHECK(Moving.GetNextCoord(Left, Red).x == 8);
    CHECK(Moving.GetNextCoord(Left, Red).y == 9);
}
TEST_CASE("Check wall returns Texture when looking all around pacman/ghost")
{
    Game Play;
    Movement Moving = Play.getMovementObj();
    CHECK(Moving.CheckWalLock(Up, Pac)== Wall);
    CHECK(Moving.CheckWalLock(Down, Pac)== Wall);
    CHECK(Moving.CheckWalLock(Right, Pac)== Food);
    CHECK(Moving.CheckWalLock(Left, Pac)== Food);
}
TEST_CASE("Moving PacMan left, right, up and down if conditions are met")
{
    Game Play;
    Movement Moving = Play.getMovementObj();
    Moving.setSpritePos(4, 17, Pac);
    Moving.MovePac(Left);
    CHECK(Moving.getCoordinates(Pac).y == 16);
    Moving.MovePac(Right);
    CHECK(Moving.getCoordinates(Pac).y == 17);
    Moving.MovePac(Down);
    CHECK(Moving.getCoordinates(Pac).x == 5);
    Moving.MovePac(Up);
    CHECK(Moving.getCoordinates(Pac).x == 4);
}
TEST_CASE("Not Moving PacMan left, right, up and down if conditions are not met")
{
    Game Play;
    Movement Moving = Play.getMovementObj();

    Moving.setSpritePos(6, 16, Pac);
    Moving.MovePac(Left);                           //Cannot move left because of Wall
    CHECK(Moving.getCoordinates(Pac).y == 16);
    CHECK(Moving.getCoordinates(Pac).x == 6);

    Moving.MovePac(Down);                           //Cannot move down because of Wall
    CHECK(Moving.getCoordinates(Pac).y == 16);
    CHECK(Moving.getCoordinates(Pac).x == 6);

    Moving.MovePac(Up);                             //Cannot move up because of wall
    CHECK(Moving.getCoordinates(Pac).y == 16);
    CHECK(Moving.getCoordinates(Pac).x == 6);

    Moving.setSpritePos(4, 2, Pac);                 //Cannot move right because of Lock
    Moving.MovePac(Right);
    CHECK(Moving.getCoordinates(Pac).y == 2);
    CHECK(Moving.getCoordinates(Pac).x == 4);


}
TEST_CASE("Moving Ghost left, right, up and down if conditions are met")
{
    Game Play;
    Movement Moving = Play.getMovementObj();
    Ghosts Lisa = Play.getGhostObj();

    Lisa.OrangeGhostMoves(Moving, Left);
    CHECK(Moving.getCoordinates(Orange).x == 11);
    CHECK(Moving.getCoordinates(Orange).y == 7);

    Moving.setSpritePos(15, 4, Orange);
    Lisa.OrangeGhostMoves(Moving, Up);
    CHECK(Moving.getCoordinates(Orange).x == 14);
    CHECK(Moving.getCoordinates(Orange).y == 4);

    Moving.setSpritePos(14, 4, Orange);
    Lisa.OrangeGhostMoves(Moving, Right);
    CHECK(Moving.getCoordinates(Orange).x == 14);
    CHECK(Moving.getCoordinates(Orange).y == 5);

    Moving.setSpritePos(14, 4, Orange);
    Lisa.OrangeGhostMoves(Moving, Down);
    CHECK(Moving.getCoordinates(Orange).x == 15);
    CHECK(Moving.getCoordinates(Orange).y == 4);
}
TEST_CASE("Ghost cannot move backward when not next to locks")
{
    Game Play;
    Movement Moving = Play.getMovementObj();
    Ghosts Lisa = Play.getGhostObj();

    Lisa.OrangeGhostMoves(Moving, Left);
    Lisa.OrangeGhostMoves(Moving, Right);
    CHECK(Moving.getCoordinates(Orange).y != 8);

    Moving.setSpritePos(15, 8, Orange);
    Lisa.OrangeGhostMoves(Moving, Up);
    Lisa.OrangeGhostMoves(Moving, Down);
    CHECK(Moving.getCoordinates(Orange).x != 15);
}
TEST_CASE("Ghost can move backward when next to locks")
{
    Game Play;
    Movement Moving = Play.getMovementObj();
    Ghosts Lisa = Play.getGhostObj();

    Moving.setSpritePos(4, 17, Orange);
    Lisa.OrangeGhostMoves(Moving, Left);
    Lisa.OrangeGhostMoves(Moving, Right);
    CHECK(Moving.getCoordinates(Orange).y == 17);
}

//////////////////////Modes (Super and Power)////////////////////
TEST_CASE("Pacman eats power pellet and activates ghostMode, ghost scale changes")
{
    Game Play;
    Movement Moving = Play.getMovementObj();
    Moving.setStorePos(16, 1, 6);
    Moving.setSpritePos(16, 2, Pac);
    TEXTURE Tex = Moving.MovePac(Left);
    CHECK(Tex == Power);
    Play.ChangesAfterPelletEaten(Tex);
    Moving = Play.getMovementObj();
    CHECK(Moving.getGhostMode(Blue)==true);
    CHECK(Moving.getGhostMode(Red)==true);
    CHECK(Moving.getGhostMode(Orange)==true);
    CHECK(Moving.getGhostMode(Pink)==true);

    Sprite Lipa = Play.getSprite(Red);
    CHECK(Lipa.getScale().x == 0.18f);
    CHECK(Lipa.getScale().y == 0.16f);
}
TEST_CASE("Pacman eats super pellet and activates SuperPacManMode, Ghost scale changes")
{
    Game Play;
    Movement Moving = Play.getMovementObj();
    Moving.setSpritePos(4, 8, Pac);
    TEXTURE Tex = Moving.MovePac(Right);
    CHECK(Tex == Super);
    Play.ChangesAfterPelletEaten(Tex);
    Sprite Lira = Play.getSprite(Blue);
    CHECK(Lira.getScale().x == 0.05f);
    CHECK(Lira.getScale().y == 0.11f);
}

////////////////////////////PacMan and Ghosts Eating//////////////////////////////////////////
TEST_CASE("Ghosts Eat PacMan - No ghost mode or super mode")
{
    Game Play;
    Movement Moving = Play.getMovementObj();
    Moving.setSpritePos(15,10, Red);
    Moving.setSpritePos(15,10, Pac);
    Eater Eats = Play.getEaterObj();
    CHECK(Eats.GhostEatPac(Moving));
}
TEST_CASE("Pac Eats Ghosts - Ghostmode")
{
    Game Play;
    Movement Moving = Play.getMovementObj();
    Moving.TurnGhostMode(true);
    Moving.setSpritePos(15,10, Red);
    Moving.setSpritePos(15,10, Pac);
    Eater Eats = Play.getEaterObj();
    CHECK_FALSE(Eats.GhostEatPac(Moving));
    CHECK(Eats.PacEatGhost(Moving) == Red);
}
TEST_CASE("Ghosts return to spawning point when Pacman Eats Ghost during ghostmode")
{
    Game Play;
    Movement Moving = Play.getMovementObj();
    Moving.TurnGhostMode(true);
    Moving.setSpritePos(15,10, Red);
    Moving.setSpritePos(15,10, Pac);
    Eater Eats = Play.getEaterObj();
    Eats.PacEatGhost(Moving);
    CHECK(Moving.getCoordinates(Red).x == 8);
    CHECK(Moving.getCoordinates(Red).y == 10);
}
TEST_CASE("Ghosts return to normal when Pacman Eats Ghost during ghostmode while others stay in ghostmode")
{
    Game Play;
    Movement Moving = Play.getMovementObj();
    Moving.TurnGhostMode(true);
    Moving.setSpritePos(15,10, Red);
    Moving.setSpritePos(15,10, Pac);
    Eater Eats = Play.getEaterObj();
    Eats.PacEatGhost(Moving);
    CHECK(Moving.getGhostMode(Red)==false);
    CHECK(Moving.getGhostMode(Blue)==true);
    CHECK(Moving.getGhostMode(Orange)==true);
    CHECK(Moving.getGhostMode(Pink)==true);
}
TEST_CASE("PacMan eats key and unlocks locks")
{
    Game Play;
    Movement Moving = Play.getMovementObj();
    Moving.setSpritePos(4,5,Pac);
    TEXTURE Tex = Moving.MovePac(Left);
    CHECK(Tex == Key);
    Play.ChangesAfterPelletEaten(Tex);
    Moving = Play.getMovementObj();
    CHECK(Moving.getStorePos(Moving.getCoordinates(Pac).x, Moving.getCoordinates(Pac).y) == 2);
}
TEST_CASE("SuperPacMan unlocks locks without Key")
{
    Game Play;
    Movement Moving = Play.getMovementObj();
    Moving.TurnSuperMode(true);
    Moving.setSpritePos(1,4,Pac);
    CHECK(Moving.MovePac(Up)==Left);
}
