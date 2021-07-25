#define CATCH_CONFIG_MAIN
#include "../Catch2/catch.hpp"
#include "dynamic_array.hpp"

using namespace ds;

TEST_CASE("CONSTRUCTORS_DESTRUCTOR", "[CONSTRUCTOR][DESTRUCTOR]")
{
    SECTION("DEFAULT")
    {
        dynamic_array<int> def;

        REQUIRE(def.size() == 0);
        REQUIRE(def.empty());
        REQUIRE(def.capacity() == INIT_CAPACITY);
        REQUIRE_THROWS(def.at(0));
    }

    SECTION("CONSTRUCTOR WITH CAPACITY PARAMETER")
    {
        const unsigned int EXPECTED_CAPACITY = 5;

        dynamic_array<double> foo(EXPECTED_CAPACITY);

        REQUIRE(foo.size() == 0);
        REQUIRE(foo.empty());
        REQUIRE(foo.capacity() == EXPECTED_CAPACITY);
        REQUIRE_THROWS(foo.at(0));
    }

    SECTION("FILL CONSTRUCTOR")
    {
        const unsigned int SIZE = 10;
        const double ELEMENT = 3.141592;
        bool EQUAL_FALG = true;

        dynamic_array<double> foo(SIZE, ELEMENT);
        for (size_t i = 0; i < SIZE; i++)
        {
            if (foo.at(i) != ELEMENT)
            {
                EQUAL_FALG = false;
                break;
            }
        }

        REQUIRE(foo.size() == SIZE);
        REQUIRE_FALSE(foo.empty());
        REQUIRE(foo.capacity() == SIZE);

        CHECK_NOTHROW(foo.at(0));

        CHECK(foo.at(0) == ELEMENT);
        REQUIRE(EQUAL_FALG);
    }
}