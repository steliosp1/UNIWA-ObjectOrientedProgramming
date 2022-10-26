#include "Moving.cpp"

class Traal : public Moving{
    vector<vector<int>> dist;

    public:
        Traal(char, int, int);
        void move(Moving &, vector<vector<char>> &);
        void initDistances(vector<vector<char>> &);
        void calculateDistances(Moving & p, vector<vector<char>> &);
        bool checkDistMap(vector<vector<char>> &);
};
