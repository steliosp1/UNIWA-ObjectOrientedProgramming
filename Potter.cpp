#include "Potter.h"

//Potter inherits class moving which is the one containg below information
//because every living entity in this game has a character representing it, a x value, and a y one
//with the below constructor we use moving's constructor to initialize objects
Potter::Potter(char ch, int x, int y) : Moving(ch, x, y){
    
}
//Added checks for direction and collision with monsters, if potter tries to go in a plaec where a monster is he stays still
//meaning that the monster will devour him
void Potter::move(int direction, vector<vector<char>> & map){
    if(direction == 1 && map[y-1][x] != 'G' && map[y-1][x] != 'T'){
        move_up(map);
    }
    else if(direction == 2 && map[y+1][x] != 'G' && map[y+1][x] != 'T'){
        move_down(map);
    }
    else if(direction == 3 && map[y][x-1] != 'G' && map[y][x-1] != 'T'){
        move_left(map);
    }
    else if(direction == 4 && map[y][x+1] != 'G' && map[y][x+1] != 'T'){
        move_right(map);
    }
        
}