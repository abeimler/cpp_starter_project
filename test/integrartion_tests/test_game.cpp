
#include <catch2/catch.hpp>
#include "Game.h"
#include "raylib.h"

SCENARIO("Game", "[Game]")
{

  GIVEN("A Window")
  {
    InitWindow(800, 600, "raylib [core] example - basic window");
    SetTargetFPS(60);// Set our game to run at 60 frames-per-second

    AND_GIVEN("a Game")
    {
      foo::game::Game game;

      WHEN("render")
      {
        BeginDrawing();
        game.render();
        EndDrawing();
      }
    }

    CloseWindow();// Close window and OpenGL context
  }
}