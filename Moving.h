//check if moving is already defined by another class to avoid conflicts
#ifndef moving_h
#define moving_h

#include <string>
#include <vector>
#include <climits>

using namespace std;

class Moving{
protected://attributes every living entity will need to have
    int x, y;
    char entity_char;


public:
    Moving(char, int, int);
    //bool functions to check if corresponding moves are valid
    bool check_move_up(vector<vector<char>> & map);
    bool check_move_down(vector<vector<char>> & map);
    bool check_move_right(vector<vector<char>> & map);
    bool check_move_left(vector<vector<char>> & map);
    //functions to perform corresponding moves
    void move_up(vector<vector<char>> & map);
    void move_down(vector<vector<char>> & map);
    void move_right(vector<vector<char>> & map);
    void move_left(vector<vector<char>> & map);
    //getters/setters
    char getCharacter();
    int getX();
    int getY();
    void setX(int);
    void setY(int);
};

#endif