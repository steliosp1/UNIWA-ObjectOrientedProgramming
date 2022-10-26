#include "Moving.cpp"

class Potter : public Moving{
    public:
        Potter(char, int, int);
        void move(int, vector<vector<char>> &);
        
};
