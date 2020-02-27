
#include <catch2/catch.hpp>
#include "Bar.h"

TEST_CASE("Bar", "[Bar]")
{
    foo::Bar bar;

    SECTION( "baz" ) {
        bar.baz();
    }
}