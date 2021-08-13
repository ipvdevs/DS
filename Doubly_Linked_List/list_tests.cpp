#define CATCH_CONFIG_MAIN
#include "../Catch2/catch.hpp"
#include "list.hpp"

using namespace ds;

TEST_CASE("CONSTRUCTORS", "[DEFAULT][COPY][OPERATOR=]")
{
    SECTION("DEFAULT")
    {
        List<int> list;

        REQUIRE(list.empty());
        REQUIRE(list.size() == 0);
    }

    SECTION("FILL")
    {
        const int N = 3, val = 15;
        bool valFlag = true;
        List<int> list(N, val);

        CHECK_FALSE(list.empty());
        CHECK(list.size() == N);

        while (!list.empty())
        {
            if (list.front() != val)
            {
                valFlag = false;
                break;
            }
            list.pop_front();
        }

        REQUIRE(valFlag);
    }

    SECTION("INIIALIZER LIST")
    {
        const int N = 3, val = 15;
        bool valFlag = true;
        List<int> list = {val, val, val};

        CHECK_FALSE(list.empty());
        CHECK(list.size() == N);

        while (!list.empty())
        {
            if (list.front() != val)
            {
                valFlag = false;
                break;
            }
            list.pop_front();
        }

        REQUIRE(valFlag);
    }

    SECTION("COPY")
    {
        const int N = 3;
        bool valFlag = true;
        List<int> list = {1, 2, 3};
        List<int> listCopy = list;

        CHECK_FALSE(listCopy.empty());
        CHECK(listCopy.size() == N);

        int num = 1;
        while (!listCopy.empty())
        {
            if (listCopy.front() != num)
            {
                valFlag = false;
                break;
            }
            listCopy.pop_front();
            ++num;
        }

        REQUIRE(valFlag);
    }

    SECTION("ASSIGNMENT")
    {
        const int N = 3;
        bool valFlag = true;
        List<int> list = {1, 2, 3};
        List<int> listAssignment;

        listAssignment = list;

        CHECK_FALSE(listAssignment.empty());
        CHECK(listAssignment.size() == N);

        int num = 1;
        while (!listAssignment.empty())
        {
            if (listAssignment.front() != num)
            {
                valFlag = false;
                break;
            }
            listAssignment.pop_front();
            ++num;
        }

        REQUIRE(valFlag);
    }
}

TEST_CASE("OPERATIONS", "[PUSH][POP][ACCESS]")
{
    SECTION("PUSH_FRONT")
    {
        List<char> list;

        list.push_front('a');
        list.push_front('b');

        REQUIRE(list.size() == 2);
        CHECK_FALSE(list.empty());
        REQUIRE(list.front() == 'b');
        REQUIRE_NOTHROW(list.pop_front());
        REQUIRE(list.front() == 'a');
        REQUIRE_NOTHROW(list.pop_front());
        REQUIRE(list.empty());
    }

    SECTION("PUSH_BACK")
    {
        List<char> list;

        list.push_back('a');
        list.push_back('b');
        
        REQUIRE(list.size() == 2);
        CHECK_FALSE(list.empty());
        REQUIRE(list.front() == 'a');
    }

    SECTION("POP_FRONT")
    {
        List<char> list;

        list.push_front('a');

        REQUIRE(list.size() == 1);
        CHECK_FALSE(list.empty());
        REQUIRE_NOTHROW(list.pop_front());
        REQUIRE(list.size() == 0);
        REQUIRE(list.empty());
        REQUIRE_THROWS(list.pop_front());
    }

    SECTION("POP_FRONT")
    {
        List<char> list;

        list.push_front('a');

        REQUIRE(list.size() == 1);
        CHECK_FALSE(list.empty());
        REQUIRE_NOTHROW(list.pop_front());
        REQUIRE(list.size() == 0);
        REQUIRE(list.empty());
        REQUIRE_THROWS(list.pop_front());
    }
}