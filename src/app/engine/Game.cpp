#include "Game.h"
#include "raylib.h"

namespace foo::game {

void Game::update()
{
}

void Game::render()
{
  ClearBackground(RAYWHITE);

  DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
}

}// namespace foo::game