#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

class HiScore{
        string name;
        int score;
    public:
        HiScore();
        HiScore& operator << (string);
        HiScore& operator << (int);
        HiScore& operator >> (string & name);
        HiScore& operator >> (int & score);
        void saveScore(string filename);

};