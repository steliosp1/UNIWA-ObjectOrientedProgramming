#include "Gnome.h"

//Same as potter
Gnome::Gnome(char ch, int x, int y) : Moving(ch, x, y){
    
}
//For this monster's move we generate a map containing information about the faster path to potter's position
//According to the values stored on that map, we chose to perform a move
void Gnome::move(Moving & player, vector<vector<char>> & map){
    initDistances(map);//more info on these functions below
    while(checkDistMap(map))
        calculateDistances(player, map);
    if(dist[y][x - 1] < dist[y][x] && map[y][x - 1] != 'T'){
        move_left(map);
        
    }
    else if(dist[y][x +1 ] < dist[y][x] && map[y][x + 1] != 'T'){
        move_right(map);
    }
    else if(dist[y - 1][x] < dist[y][x] && map[y - 1][x] != 'T'){
        move_up(map);
    }
    else if(dist[y + 1][x] < dist[y][x] && map[y + 1][x] != 'T')
        move_down(map);
}
//init a map with max values in every position
void Gnome::initDistances(vector<vector<char>> & map){
    dist.clear();
    for(size_t j=0; j<map.size(); j++){
        dist.push_back(vector<int>());
        for(size_t k=0; k<map[0].size(); k++)
                dist[j].push_back(INT_MAX);
    }  
}
//only potters position will have 0 as a value meaning that we can now compare adjacent cells in order to set a distance from potter
void Gnome::calculateDistances(Moving & p, vector<vector<char>> & map){
    dist[p.getY()][p.getX()] = 0;
    for(size_t j=0; j<map.size(); j++)//with each loop we find cells that their adjacent ones have lower values than them
        for(size_t k=0; k<map[j].size(); k++){//we get their value and set ours on +1 [0|1|2|3|INT_MAX|INT_MAX]
            if(map[j][k] != '*' && dist[j][k - 1] < dist[j][k]){
                dist[j][k] = dist[j][k - 1] + 1+2;//by adding more we make the monster choose vertical lines            
            }                                       //instead of horizontal in case of a draw, thats the difference between the 2 monsters
            if(map[j][k] != '*' && dist[j][k + 1] < dist[j][k]){
                dist[j][k] = dist[j][k + 1] + 1+2;
            }
            if(map[j][k] != '*' && dist[j - 1][k] < dist[j][k]){
                dist[j][k] = dist[j - 1][k] + 1;
            }
            if(map[j][k] != '*' && dist[j + 1][k] < dist[j][k]){
                dist[j][k] = dist[j + 1][k] + 1;
            }
        }    
}
//if we have found a path till the monster we stop, because we dont need to check anymore
bool Gnome::checkDistMap(vector<vector<char>> & map){
    if(dist[y][x] != INT_MAX)
        return false;
    else
        return true;
}