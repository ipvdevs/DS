#define CATCH_CONFIG_MAIN
#include "../../Catch2/catch.hpp"
#include "./stack_static.hpp"

TEST_CASE("CONSTRUCTORS", "[DEFAULT]")
{
    SECTION("DEFAULT")
    {
        const size_t MAX_SIZE = 10;
        StaticStack<int, MAX_SIZE> stk;

        REQUIRE(stk.isEmpty());
        REQUIRE(stk.size() == 0);
        REQUIRE(stk.maxSize() == MAX_SIZE);
    }
}

TEST_CASE("ABSTRACT OPERATIONS", "[PUSH][POP][TOP]")
{
    SECTION("PUSH")
    {
        const int N1 = 100, N2 = 200;
        const size_t EXPECTED_SIZE = 2;
        StaticStack<int, EXPECTED_SIZE> stk;

        stk.push(N1);
        stk.push(N2);

        REQUIRE_FALSE(stk.isEmpty());
        REQUIRE(stk.size() == EXPECTED_SIZE);

        REQUIRE_NOTHROW(stk.pop());
        REQUIRE(stk.top() == N1);
    }

    SECTION("POP")
    {
        const int N1 = 100, N2 = 200;
        const size_t EXPECTED_SIZE = 2;
        StaticStack<int, EXPECTED_SIZE> stk;

        stk.push(N1);
        stk.push(N2);

        REQUIRE_NOTHROW(stk.pop());
        REQUIRE(stk.size() == 1);

        REQUIRE_NOTHROW(stk.pop());
        REQUIRE(stk.size() == 0);

        REQUIRE(stk.isEmpty());

        REQUIRE_THROWS(stk.pop());
    }

    SECTION("TOP")
    {
        const int N1 = 100, N2 = 200;
        StaticStack<int, 2> stk;

        stk.push(N1);
        stk.push(N2);

        REQUIRE(stk.top() == N2);
        stk.pop();
        REQUIRE(stk.top() == N1);
        stk.pop();

        REQUIRE_THROWS(stk.top());
    }
}
