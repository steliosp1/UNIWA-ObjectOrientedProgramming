#ifndef moving_cpp
#define moving_cpp
#include "Moving.h"

Moving::Moving(char entity_char, int x, int y){
    this->entity_char = entity_char;
    this->x = x;
    this->y = y;
}
//we check a move by seeing if the place the user wants to go is a wall
bool Moving::check_move_up(vector<vector<char>> & map){
        if(map[y - 1][x] == '*')
            return false;
        else
            return true;
}
bool Moving::check_move_down(vector<vector<char>> & map){
        if(map[y + 1][x] == '*')
            return false;
        else
            return true;
}
bool Moving::check_move_right(vector<vector<char>> & map){
        if(map[y][x + 1] == '*')
            return false;
        else
            return true;
}
bool Moving::check_move_left(vector<vector<char>> & map){
    if(map[y][x - 1] == '*')
        return false;
    else 
        return true; 
}
//we perform a move by placing the corresponding character on the map, moved by 1 place in a direction
void Moving::move_up(vector<vector<char>> & map){
    if(check_move_up(map)){
        map[y][x] = ' ';
        map[y - 1][x] = entity_char;
        y--;
    }
}
void Moving::move_down(vector<vector<char>> & map){
    if(check_move_down(map)){
        map[y][x] = ' ';
        map[y + 1][x] = entity_char;
        y++;
    }
}
void Moving::move_right(vector<vector<char>> & map){
    if(check_move_right(map)){
        map[y][x] = ' ';
        map[y][x + 1] = entity_char;
        x++;
    }
}
void Moving::move_left(vector<vector<char>> & map){
    if(check_move_left(map)){
        map[y][x] = ' ';
        map[y][x - 1] = entity_char;
        x--;
    }
}

char Moving::getCharacter(){
    return this->entity_char;
}

int Moving::getX(){
    return this->x;
}

int Moving::getY(){
    return this->y;
}

void Moving::setX(int x){
    this->x = x;
}

void Moving::setY(int y){
    this->y = y;
}

#endif