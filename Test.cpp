#include "doctest.h"
#include "range.hpp"
#include "accumulate.hpp"
#include "filterfalse.hpp"
#include "compress.hpp"
#include <math.h>
// #include <iostream>
#include <vector>
using namespace itertools;
// using namespace std;
TEST_CASE("range")
{
    int i = 0;
    for (int current : range(0, 15))
    {
        CHECK(current == i++);
    }
    i = -5;
    for (int current : range(-5, 9))
    {
        CHECK(current == i++);
    }
    for (int current : range(7, 7)) //there is nothing to iterate in [7,6)
    {
        CHECK(false);
    }
}
TEST_CASE("accumulate")
{
    vector<string> vecString = {"halla", "Madrid", "y", "nada", "mas"};
    string arr[] = {"halla", "hallaMadrid", "hallaMadridy", "hallaMadridynada", "hallaMadridynadamas"};
    int j = 0;
    for (auto i : accumulate(vecString))
    {
        CHECK(i == arr[j++]);
    }
    int a[] = {1, 3, 6, 10, 15, 21, 28, 36, 45, 55};
    j = 0;
    for (int i : accumulate(range(1, 11)))
    {
        CHECK(i == a[j++]);
    }
    int b[] = {2, 8, 4096};
    j = 0;
    for (int i : accumulate(range(2, 5), [](int x, int y) { return pow(x, y); }))
    {
        CHECK(i == b[j++]);
    }
}
TEST_CASE("filterfalse")
{
    int j = 0;
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23};
    for (auto i : filterfalse([](int n) { return n % 2 == 0; }, range(1, 25)))
        CHECK(i == arr[j++]);
    vector<string> vs = {"hala", "madrid", "y", "nada", "mas", ", ", "el", "mejor", "football", "club", "del", "mundo", "los", "blancos", "reyes", "del", "europa"};
    vector<string> ans = {"hala", "y", "nada", "mas", ", ", "el", "club", "del", "los", "del"};
    j = 0;
    for (auto i : filterfalse([](string s) { return s.length() > 4; }, vs))
        CHECK(i == ans.at(j++));

    vector<string> cr7 = {"dhala", "de madrid", "dandy", "donde", "estas", "didi", "david", "dcristiano", "football", "club", "del", "dddddd", "los", "blancos", "reyes", "dell", "europa"};
    vector<string> answ = {"dhala", "de madrid", "dandy", "donde", "didi", "david", "dcristiano", "del", "dddddd", "dell"};
    j = 0;
    for (auto i : filterfalse([](string s) { return s.at(0) != 'd'; }, cr7))
        CHECK(i == answ.at(j++));
}
TEST_CASE("compress")
{
    vector<bool> myVectorBool2{false, false, false, false, false, false, false, false, false, false, false};

    for (auto i : compress(string("InotLoveC++"), myVectorBool2))
    {
        cout << i<<", ";
    }
    int arr[] = {21, 23, 25, 27, 29, 31, 33};
    int j = 0;
    for (int i : compress(range(20, 35), vector<bool>{false, true, false, true, false, true, false, true, false, true, false, true, false, true, false}))
    {
        CHECK(i == arr[j++]);
    }
    j = 0;
    string s = "halaMadrid";
    for (auto i : compress(string("abhyalaxMadbruidp"), vector<bool>({false, false, true, false, true, true, true, false, true, true, true, false, true, false, true, true, false})))
        CHECK(i == s.at(j++));
}
TEST_CASE("Exceptions")
{
    CHECK_THROWS(compress(range(20, 35), vector<bool>{false, true, false, true}));
    CHECK_THROWS(compress(range(20, 35), range(1, 10)));
    CHECK_THROWS(range(20, 19));
}