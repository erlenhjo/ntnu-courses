#pragma once

#include <string>
#include <set>
#include <map>
#include <iostream>

using namespace std;

struct Food {
    string name;
    double price;
    string where;
};

bool operator<(Food& lhs,Food& rhs);
void addPrice(map<string,set<Food>>& db, Food fp);
void printAllPrices(const map<string,set<Food>>& db);
void bestPrice(const map<string, set<Food>>& db, string name);