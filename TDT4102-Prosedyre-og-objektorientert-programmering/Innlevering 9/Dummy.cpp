#include "Dummy.h"
#include "iostream"
using namespace std;

void dummyTest() {
    Dummy a;
    *a.num = 4;
    Dummy b{a};
    Dummy c;
    c = a;
    cout << "a: " << *a.num << '\n';
    cout << "b: " << *b.num << '\n';
    cout << "c: " << *c.num << '\n';
    *b.num = 3;
    *c.num = 5;
    cout << "a: " << *a.num << '\n';
    cout << "b: " << *b.num << '\n';
    cout << "c: " << *c.num << '\n';
}

