#define CATCH_CONFIG_MAIN
#include "../Catch2/catch.hpp"
#include "stack_linked.hpp"

using namespace ds;

TEST_CASE("CONSTRUCTORS", "[DEFAULT][COPY][OPERATOR]")
{
    SECTION("DEFAULT")
    {
        Stack<int> stk;

        REQUIRE(stk.empty());
        REQUIRE(stk.size() == 0);
    }

    SECTION("COPY CONSTRUCTOR")
    {
        Stack<int> stk;
        // Used operations are tested later
        stk.push(123);

        CHECK_FALSE(stk.empty());
        CHECK(stk.size() == 1);

        Stack<int> cpyStk = stk; // cpyStk(stk)
        REQUIRE(stk.size() == cpyStk.size());
        REQUIRE(stk.top() == cpyStk.top());
    }

    SECTION("OPERATOR=")
    {
        Stack<int> stk;
        // Used operations are tested later
        stk.push(123);
        stk.push(456);

        CHECK_FALSE(stk.empty());
        CHECK(stk.size() == 2);

        Stack<int> assignStk; // Calls default ctor
        assignStk = stk;      // Calls assignStk.operator=(stk);

        REQUIRE(stk.size() == assignStk.size());
        REQUIRE(stk.pop() == assignStk.pop());
        REQUIRE(stk.top() == assignStk.top());
    }
}

TEST_CASE("ABSTRACT OPERATIONS", "[PUSH][POP][INFORMATION]")
{
    SECTION("PUSH")
    {
        const int N1 = 100, N2 = 200;
        const size_t EXPECTED_SIZE = 2;
        Stack<int> stk;

        stk.push(N1);
        stk.push(N2);

        REQUIRE_FALSE(stk.empty());
        REQUIRE(stk.size() == EXPECTED_SIZE);

        REQUIRE(stk.pop() == N2);
        REQUIRE(stk.top() == N1);
    }

    SECTION("POP")
    {
        const int N1 = 100, N2 = 200;
        Stack<int> stk;

        stk.push(N1);
        stk.push(N2);

        REQUIRE(stk.pop() == N2);
        REQUIRE(stk.size() == 1);

        REQUIRE(stk.pop() == N1);
        REQUIRE(stk.size() == 0);

        REQUIRE(stk.empty());

        REQUIRE_THROWS(stk.pop());
    }

    SECTION("TOP")
    {
        const int N1 = 100, N2 = 200;
        Stack<int> stk;

        stk.push(N1);
        stk.push(N2);

        REQUIRE(stk.top() == N2);
        stk.pop();
        REQUIRE(stk.top() == N1);
        stk.pop();

        REQUIRE_THROWS(stk.top());
    }
}