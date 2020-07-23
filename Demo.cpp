//
//  Demo for itertools exercise.
//
//  Version 1 by Adam Lev-Ari on 02/2020. Copyright © 2020 Adam Lev-Ari. All rights reserved.
//  Version 2 by Erel Segal-Halevi on 06/2020.
//

#include <iostream>
#include <vector>

#include "range.hpp"
#include "accumulate.hpp"
#include "filterfalse.hpp"
#include "compress.hpp"


using namespace itertools;
using namespace std;


struct lessThan3 {
    bool operator()(int i) const { return i < 3; }
};

int main(int argc, const char * argv[]) {
    
    cout << "####  range:  ####\n";
	for (int i: range(5,9))
		cout << i << " ";      // 5 6 7 8

    vector<int> vecInt = {1,2,3,4};
    vector<string> vecString = {"Hello", "Bye", "Adam"};
    vector<float> vecFloat = {-1, 0.3, 5.2, -8.3};
    
    cout << "\n####  accumulate:  ####\n";
    cout << endl << "accumulate of range: " << endl;
	for (int i: accumulate(range(5,9)))
		cout << i << " ";      // 5 11 18 26

    cout << endl << "accumulate of vector<string>: " << endl;
    for (auto i: accumulate(vecString))
        cout << i << " ";  // Hello HelloBye HelloByeAdam
    cout << endl << endl;

    cout << endl << "accumulate of range with binary operator: " << endl;
	for (int i: accumulate(range(5,9), [](int x, int y){return x*y;}))
		cout << i << " ";      // 5 30 210 1680
    cout <<endl<< "####  compress:  ####";
    cout << endl << "compress a string" << endl;
    for (auto i: compress(string("abcd"), vector<bool>({true,true,false,true})) )
        cout << i << " ";  // a b d
    cout << endl << "compress a range" << endl;
    for (auto i: compress(range(5,9), vector<bool>({false,true,false,true})) )
        cout << i << " ";  // 5 6 8
    cout << endl << endl;
    cout << "\n####  Filter False:  ####";
    cout << endl << "Filter out all numbers less than 3 in vector{1,2,3,4}: " << endl;
    for (auto i: filterfalse(lessThan3{}, vecInt) )
        cout << i << " ";   // 3 4
    cout << endl << "Filter out all even numbers in range(5,9): " << endl;
    for (auto i: filterfalse([](int i){return i%2==0;}, range(5,9)) )
        cout << i << " ";   // 5 7
    cout << endl << endl;



    cout << endl;
    return 0;
}
