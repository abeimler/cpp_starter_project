#include <catch2/catch.hpp>
#include "Game.h"

TEST_CASE("Game", "[Game]")
{
    foo::game::Game game;

    SECTION( "update" ) {
        game.update();
    }

    SECTION( "render" ) {
        game.render();
    }
}