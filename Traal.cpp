#include "Traal.h"

//Same as potter
Traal::Traal(char ch, int x, int y) : Moving(ch, x, y){
    
}
//For this monster's move we generate a map containing information about the faster path to potter's position
//According to the values stored on that map, we chose to perform a move
void Traal::move(Moving & player, vector<vector<char>> & map){
    initDistances(map);//more info on these functions below
    while(checkDistMap(map))
        calculateDistances(player, map);
    if(dist[y][x - 1] < dist[y][x] && map[y][x - 1] != 'G'){
        move_left(map);
        
    }
    else if(dist[y][x +1] < dist[y][x] && map[y][x + 1] != 'G'){
        move_right(map);
    }
    else if(dist[y - 1][x] < dist[y][x] && map[y - 1][x] != 'G'){
        move_up(map);
    }
    else if(dist[y + 1][x] < dist[y][x] && map[y + 1][x] != 'G')
        move_down(map);
}
//init a map with max values in every position
void Traal::initDistances(vector<vector<char>> & map){
    dist.clear();
    for(size_t j=0; j<map.size(); j++){
        dist.push_back(vector<int>());
        for(size_t k=0; k<map[0].size(); k++)
                dist[j].push_back(INT_MAX);
    }  
}
//only potters position will have 0 as a value meaning that we can now compare adjacent cells in order to set a distance from potter
void Traal::calculateDistances(Moving & p, vector<vector<char>> & map){
    dist[p.getY()][p.getX()] = 0;
    //bool flag = false;
    for(size_t j=0; j<map.size(); j++)
        for(size_t k=0; k<map[j].size(); k++){
            if(map[j][k] != '*' && dist[j][k - 1] < dist[j][k]){
                dist[j][k] = dist[j][k - 1] + 1;
            }
            if(map[j][k] != '*' && dist[j][k + 1] < dist[j][k]){
                dist[j][k] = dist[j][k + 1] + 1;
            }
            if(map[j][k] != '*' && dist[j - 1][k] < dist[j][k]){                                              
                dist[j][k] = dist[j - 1][k] + 1+2;//by adding more we make the monster choose horizontal lines    
            }                                       //instead of vertical in case of a draw, thats the difference between the 2 monsters
            if(map[j][k] != '*' && dist[j + 1][k] < dist[j][k]){
                dist[j][k] = dist[j + 1][k] + 1+2;
            }
        }    
}
//if we have found a path till the monster we stop, because we dont need to check anymore
bool Traal::checkDistMap(vector<vector<char>> & map){
    if(dist[y][x] != INT_MAX)
        return false;
    else
        return true;
}