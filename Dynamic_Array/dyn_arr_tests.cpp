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

    SECTION("CONSTRUCTOR WITH IL")
    {
        const int EXPECTED_SIZE = 3;

        dynamic_array<char> foo = {'a', 'b', 'c'};
        bool EQUAL_FALG = foo[0] == 'a' && foo[1] == 'b' && foo[2] == 'c';

        REQUIRE(foo.size() == EXPECTED_SIZE);
        REQUIRE(foo.capacity() == EXPECTED_SIZE);
        REQUIRE(EQUAL_FALG);
    }

    SECTION("COPY CONSTRUCTOR")
    {
        const int NUM = 3, SIZE = 3;
        dynamic_array<char> foo(SIZE, NUM);

        dynamic_array<char> bar(foo);
        dynamic_array<char> baz = bar;

        CHECK(bar.capacity() == foo.capacity());
        REQUIRE(bar.size() == foo.size());
        REQUIRE(bar.at(0) == foo.at(0));

        CHECK(baz.capacity() == foo.capacity());
        REQUIRE(baz.size() == foo.size());
        REQUIRE(baz.at(0) == foo.at(0));
    }

    SECTION("OPERATOR=")
    {
        const int NUM = 3, SIZE = 3;
        dynamic_array<char> foo(SIZE, NUM);

        dynamic_array<char> bar;
        bar = foo;

        REQUIRE(bar.size() == foo.size());
        REQUIRE(bar.capacity() == foo.capacity());
        REQUIRE(bar.at(0) == foo.at(0));
    }
}

TEST_CASE("DEFAULT OPERATIONS", "[OPERATIONS]")
{
    SECTION("PUSH BACK AND RESERVE SIZE")
    {
        const size_t MIN_CAPACITY = 1; // Set min possible capacity
        const u_short NUM_COUNT = 2;
        int randNum1 = rand(), randNum2 = rand(); // Generate two random number
        dynamic_array<int> def(MIN_CAPACITY);     // Construct structure with min capacity

        CHECK(def.size() == 0);
        CHECK(def.empty());
        CHECK(def.capacity() == MIN_CAPACITY);

        def.push_back(randNum1);
        def.push_back(randNum2);

        CHECK(def.size() == NUM_COUNT);
        REQUIRE_FALSE(def.empty());
        REQUIRE(def.capacity() == GROWTH_RATE * MIN_CAPACITY);
        REQUIRE(def[0] == randNum1);
        REQUIRE(def[1] == randNum2);
    }

    SECTION("POP BACK, FRONT, BACK")
    {
        const size_t MIN_CAPACITY = 1;            // Set min possible capacity
        const u_short NUM_COUNT = 2;              // Count of random numbers generated
        int randNum1 = rand(), randNum2 = rand(); // Generate two random number
        dynamic_array<int> def(MIN_CAPACITY);     // Construct structure with min capacity

        def.push_back(randNum1);
        def.push_back(randNum2);

        REQUIRE(def.front() == randNum1);
        REQUIRE(def.back() == randNum2);

        REQUIRE_NOTHROW(def.pop_back());
        CHECK(def.front() == def.back());
        REQUIRE_NOTHROW(def.pop_back());

        REQUIRE_THROWS(def.front());
        REQUIRE_THROWS(def.back());
        REQUIRE_THROWS(def.pop_back());
    }

    SECTION("EQUAL COMPARISON OPERATOR")
    {
        dynamic_array<int> foo = {1, 2, 3, 4, 5};
        dynamic_array<int> boo = {1, 2, 3, 4, 5};

        REQUIRE(foo == boo);
    }

    SECTION("INSERT")
    {
        const int ELEMENT = 56, POS = 0;
        dynamic_array<int> foo = {1, 2, 3, 4, 5};
        dynamic_array<int> expect = {ELEMENT, 1, 2, 3, 4, 5};

        foo.insert(POS, ELEMENT);

        REQUIRE(foo == expect);
        REQUIRE_THROWS(foo.insert(foo.size(), ELEMENT));
        REQUIRE_THROWS(foo.insert(foo.size() + ELEMENT, ELEMENT));
    }

    SECTION("ERASE AND CLEAR")
    {
        const int POS1 = 0, POS2 = 2, POS3 = 2;
        const int SIZE = 5;
        dynamic_array<int> foo = {1, 2, 3, 4, 5};
        dynamic_array<int> expect1 = {2, 3, 4, 5};
        dynamic_array<int> expect2 = {2, 3, 5};
        dynamic_array<int> expect3 = {2, 3};

        foo.erase(POS1);
        CHECK(foo.size() == SIZE - 1);
        REQUIRE(foo == expect1);

        foo.erase(POS2);
        CHECK(foo.size() == SIZE - 2);
        REQUIRE(foo == expect2);

        foo.erase(POS3);
        CHECK(foo.size() == SIZE - 3);
        REQUIRE(foo == expect3);

        foo.clear();
        REQUIRE(foo.size() == 0);
        REQUIRE_THROWS(foo.at(0));
    }
}

TEST_CASE("ITERATOR", "[ITERATOR]")
{
    SECTION("DEFAULT ITERATOR")
    {
        dynamic_array<int> vec = {1, 2, 3, 4};
        bool EQUAL_FLAG = true;

        dynamic_array<int>::Iterator it = vec.begin();

        for (int num = 1; it != vec.end(); ++num, ++it)
        {
            if (*it != num)
            {
                EQUAL_FLAG = false;
                break;
            }
        }

        REQUIRE(EQUAL_FLAG);
    }

    SECTION("RANGE-BASED-FOR")
    {
        dynamic_array<int> vec = {1, 2, 3, 4};
        bool EQUAL_FLAG = true;

        int num = 1;
        for (auto el : vec)
        {
            if (el != num++)
            {
                EQUAL_FLAG = false;
                break;
            }
        }

        REQUIRE(EQUAL_FLAG);
    }
}
