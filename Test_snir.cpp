#include "doctest.h"
#include "range.hpp"
#include "accumulate.hpp"
#include "filterfalse.hpp"
#include "compress.hpp"
#include <vector>
#include <string>
#include <set>
#include <iostream>
using namespace itertools;
using namespace std;

TEST_CASE("Test Range")
{
    vector<int> result = {5, 6, 7, 8};
    int j = 0;
    for (int i : range(5, 9))
    {
        CHECK(i == result.at(j));
        ++j;
    }
    CHECK(j == 4);

    j = 0;
    result.clear();
    result = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

    for (int i : range(0, 21))
    {
        CHECK(i == result.at(j));
        ++j;
    }
    CHECK(j == 21);

    j = 0;
    result.clear();
    result = {5, 5};

    for (int i : range(5, 5))
    {
        CHECK(0 == 1); // dont need to get
    }
}

TEST_CASE("Test Accumulate")
{
    vector<int> result1 = {3, 7, 12, 18, 25, 33};
    int j = 0;
    range r39(3, 9);
    for (int i : accumulate(r39)) // 3, 3+4, 3+4+5, 3+4+5+6, 3+4+5+6+7, 3+4+5+6+7+8 = 3,7,12,18,25,33
    {
        CHECK(i == result1.at(j));
        ++j;
    }
    CHECK(j == 6);

    vector<int> vec = {3, 4, 5, 6, 7, 8};
    j = 0;
    for (int i : accumulate(vec)) // 3, 3+4, 3+4+5, 3+4+5+6, 3+4+5+6+7, 3+4+5+6+7+8 = 3,7,12,18,25,33
    {
        CHECK(i == result1.at(j));
        ++j;
    }
    CHECK(j == 6);

    j = 0;
    vector<string> result2 = {"I", "ILove", "ILoveC++"};
    vector<string> vecString = {"I", "Love", "C++"};
    for (auto i : accumulate(vecString)) // I,ILove,ILoveC++
    {
        CHECK(result2.at(j) == i);
        ++j;
    }
    CHECK(j == 3);

    j = 0;
    vector<int> result3 = {3, 12, 60, 360, 2520, 20160};

    for (int i : accumulate(r39, [](int x, int y) { return x * y; })) // 3,12,60,360,2520,20160
    {
        CHECK(i == result3.at(j));
        ++j;
    }
    CHECK(j == 6);

    j = 0;
    result3.clear();

    result3 = {3, 7, 12, 18, 25, 33};
    for (int i : accumulate(r39, [](int x, int y) { return x + y; })) // 3,7,12,18,25,33
    {
        CHECK(i == result3.at(j));
        ++j;
    }
    CHECK(j == 6);

    j = 0;
    vector<int> set1 = {3, 12, 60, 360, 2520, 20160};
    set<int> myset = {3, 4, 5, 6, 7, 8};
    for (int i : accumulate(myset, [](int x, int y) { return x * y; })) //3,3*4,3*4*5 ...
    {
        CHECK(i == set1.at(j));
        ++j;
    }
    CHECK(j == 6);
}

TEST_CASE("Test Filterfalse")
{
    vector<int> result = {5, 7};
    int j = 0;
    range r59(5, 9);
    for (auto i : filterfalse([](int i) { return i % 2 == 0; }, r59))
    {
        CHECK(i == result.at(j));
        ++j;
    }
    CHECK(j == 2);

    result.clear();
    j = 0;

    result = {6, 8};
    for (auto i : filterfalse([](int i) { return i % 2 != 0; }, r59))
    {
        CHECK(i == result.at(j));
        ++j;
    }
    CHECK(j == 2);

    result.clear();
    j = 0;
    result = {3, 4, 5, 7, 8};
    set<int> myset = {3, 4, 5, 6, 7, 8};
    for (auto i : filterfalse([](int i) { return i == 6; }, myset))
    {
        CHECK(i == result.at(j));
        ++j;
    }
    CHECK(j == 5);

    result.clear();
    j = 0;
    result = {-99, -20, -2, -1, 0};
    set<int> myset2 = {-20, -2, -1, 0, 1, 3, 4, 5, 6, 7, 8, 20, 30, 40, 50, 60, 70, 72, 80, 90, -99, 100};
    for (auto i : filterfalse([](int i) { return i > 0; }, myset2))
    {
        CHECK(i == result.at(j));
        ++j;
    }
    CHECK(j == 5);

    result.clear();
    j = 0;
    result = {-99};
    set<int> myset3 = {-20, -2, -1, 0, 1, 3, 4, 5, 6, 7, 8, 20, 30, 40, 50, 60, 70, 72, 80, 90, -99, 100};
    for (auto i : filterfalse([](int i) { return i > -99; }, myset2))
    {
        CHECK(i == result.at(j));
        ++j;
    }
    CHECK(j == 1);

    result.clear();
    j = 0;
    result = {};
    set<int> myset4 = {-20, -2, -1, 0, 1, 3, 4, 5, 6, 7, 8, 20, 30, 40, 50, 60, 70, 72, 80, 90, -99, 100};
    for (auto i : filterfalse([](int i) { return i >= -99; }, myset2))
    {
        CHECK(0 == 1); // not need to get in
        ++j;
    }
    CHECK(j == 0);
}

TEST_CASE("Test Compress")
{
    vector<int> result = {7};
    int j = 0;
    vector<bool> fftf{false, false, true, false};
    for (auto i : compress(range(5, 9), fftf))
    {
        CHECK(i == result.at(j));
        ++j;
    }
    CHECK(j == 1);

    result.clear();
    j = 0;

    result = {1, 7, 11, 20};
    j = 0;
    vector<int> myvec = {1, 3, 7, 10, 11, 16, 20};
    vector<bool> tftftft{true, false, true, false, true, false, true};
    for (auto i : compress(myvec, tftftft))
    {
        CHECK(i == result.at(j));
        ++j;
    }
    CHECK(j == 4);

    result.clear();
    j = 0;

    vector<char> resultString = {'I', 'L', 'o', 'v', 'e', 'C', '+', '+'};
    j = 0;

    vector<bool> tfffttttttt{true, false, false, false, true, true, true, true, true, true, true};
    string s1{"InotLoveC++"};
    for (auto i : compress(s1, tfffttttttt))
    {
        CHECK(resultString.at(j) == i);
        ++j;
    }
    CHECK(j == 8);

    j = 0;

    vector<bool> myVectorBool2{false, false, false, false, false, false, false, false, false, false, false};

    for (auto i : compress(string("InotLoveC++"), myVectorBool2))
    {
        CHECK(0 == 1); // not need to get in
        ++j;
    }
    CHECK(j == 0);

    result.clear();
    j = 0;
}
