#include "Moving.cpp"

class Gnome : public Moving{
        vector<vector<int>> dist;
    public:
        Gnome(char, int, int);
        void move(Moving &, vector<vector<char>> &);
        void initDistances(vector<vector<char>> & map);
        void calculateDistances(Moving & p, vector<vector<char>> &);
        bool checkDistMap(vector<vector<char>> &);
};
