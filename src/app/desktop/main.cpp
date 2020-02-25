/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "engine/Game.h"

int main(void)
{
  // Initialization
  //--------------------------------------------------------------------------------------
  const int SCREENWIDTH = 800;
  const int SCREENHEIGHT = 450;
  const int FPS = 60;

  InitWindow(SCREENWIDTH, SCREENHEIGHT, "raylib [core] example - basic window");

  SetTargetFPS(FPS);// Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  foo::game::Game game;

  // Main game loop
  while (!WindowShouldClose())// Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    game.update();
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
    game.render();
    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow();// Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
