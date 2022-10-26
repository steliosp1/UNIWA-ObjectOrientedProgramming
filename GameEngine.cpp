#include "GameEngine.h"

GameEngine::GameEngine(){}
void GameEngine::startGame(Potter & p, Gnome & g, Traal & t, vector<vector<char>> & map)
{  
    //This is kinda useless, because we could do the things that initObjects() is doing here, but the
    //original plan was to add some more functions here for playing new game without exiting the program
    //which was never implemented
    initObjects(p, g, t, map);  
}

void GameEngine::getMap(string fileName, vector<vector<char>> & map)
{
    // Open the File
    try{
        ifstream in(fileName);
        // Check if object is valid
        if(!in){
            throw "Could not open map file. Check if you are giving the correct file";
        }
        string line;
        // Read the next line from File untill it reaches the end.
        while (getline(in, line)){
            vector<char> row;
            // push to vector row contents of line, then push that vector on another vector to create a 2d vector
            for(char & c : line )
                row.push_back(c);
            map.push_back(row);
        }
        //Close The File
        in.close();
    }catch(const char * msg){
        cout<< msg << endl;
        exit(-1);
    }   
}
//Create gems map, a copy of original map which will be used to place gems on it
//to have an easier time detecting collisions
void GameEngine::initGemsMap(vector<vector<char>> & map){
    gemsMap.clear();
    for(size_t j=0; j<map.size(); j++){
        gemsMap.push_back(vector<char>());
        for(size_t k=0; k<map[0].size(); k++)
            gemsMap[j].push_back(' ');
    }  
}
//Initialize objects on map
void GameEngine::initObjects(Potter & p, Gnome & g, Traal & t, vector<vector<char>> & map){
    srand((unsigned) time(0));
    
    setGems(map);
    setPotterPosition(p, g.getCharacter(), t.getCharacter(), map);
    setGnomePosition(g, p.getCharacter(), t.getCharacter(), map);
    setTraalPosition(t, g.getCharacter(), p.getCharacter(), map);
}
//Set gems on map
void GameEngine::setGems(vector<vector<char>> & map){
    int x, y, i = 0;
    while(true){
        x = (rand() % map[0].size());
        y = (rand() % map.size());
        if(map[y][x] != '*' && gemsMap[y][x] != '@'){
            gemsMap[y][x] = '@';
            i++;
            if(i==10)
                break;
        }
    }
}
//Generate random position for Potter
void GameEngine::setPotterPosition(Potter & p, char gnome, char traal, vector<vector<char>> & map){
    int x, y;
    while(true){
        x = (rand() % map[0].size());
        y = (rand() % map.size());
        if(map[y][x] != '*' && map[y][x] != '@' && map[y][x] != gnome && map[y][x] != traal){
            map[y][x] = p.getCharacter();
            p.setX(x);
            p.setY(y);
            break;
        }
    }
}
//Generate random position for Gnome
void GameEngine::setGnomePosition(Gnome & g, char potter, char traal, vector<vector<char>> & map){
    int x, y;
    while(true){
        x = (rand() % map[0].size());
        y = (rand() % map.size());
        if(map[y][x] != '*' && map[y][x] != '@' && map[y][x] != potter && map[y][x] != traal){
            map[y][x] = g.getCharacter();
            g.setX(x);
            g.setY(y);
            break;
        }
    }
}
//Generate random position for Traal
void GameEngine::setTraalPosition(Traal & t, char gnome, char potter, vector<vector<char>> & map){
    int x, y, i = 0;
    while(true){
        x = (rand() % map[0].size());
        y = (rand() % map.size());
        if(map[y][x] != '*' && map[y][x] != '@' && map[y][x] != potter && map[y][x] != gnome){
            map[y][x] = t.getCharacter();
            t.setX(x);
            t.setY(y);
            break;
        }
    }

}
//Here we handle collisions between objects on map
void GameEngine::unitCollision(Potter & p, Gnome & g, Traal & t, vector<vector<char>> & map){
    if(gemsMap[p.getY()][p.getX()] == '@'){//Using potter's location we check on our gems_map if a gem exists in that position
        gemsMap[p.getY()][p.getX()] = ' ';
        gemCounter++;//If the above is treu gemsCounter will increment along with its corresponding flag
        ateGem = true;//This flag is used from main to detect a gemEaten event
    }
    if(gemsMap[p.getY()][p.getX()] == '#'){//Same as above but for parchment(pergamini)
        gemsMap[p.getY()][p.getX()] = ' ';
        win = true;
        ateParchemnt = true;
    }
    if(gemsMap[g.getY()][g.getX()] == '@' || gemsMap[g.getY()][g.getX()] == '#'){//If monster and gem are on the same location
        map[g.getY()][g.getX()] == g.getCharacter(); //prioritize monster
    }
    if(gemsMap[t.getY()][t.getX()] == '@' || gemsMap[g.getY()][g.getX()] == '#'){// Same as above
        map[t.getY()][t.getX()] == t.getCharacter();
    }
    if((p.getY() == g.getY() && p.getX() == g.getX()) || (p.getY() == t.getY() && p.getX() == t.getX())){
        loss = true;//If potter is on same spot as monsters you lose
    }
}
//Getters for getting game state
int GameEngine::getGemCounter(){
    return gemCounter;
}

bool GameEngine::getLossFlag(){
    return loss;
}

bool GameEngine::getWinFlag(){
    return win;
}

int GameEngine::getParchmentCounter(){
    return parchmentCounter;
}
//Refresh map every time we make a change (add gems/parchment on map, gemEaten event)
void GameEngine::refreshMap(vector<vector<char>> & map){
    for(size_t j = 0; j < map.size(); j++){
        for(size_t k = 0; k < map[0].size(); k++){
            if(gemsMap[j][k] == '@' && map[j][k] != 'G' && map[j][k] != 'T')
                map[j][k] = '@';
            if(gemsMap[j][k] == '#' && map[j][k] != 'G' && map[j][k] != 'T')
                map[j][k] = '#';
        }
    }
}
//set parchment on gems_map
void GameEngine::spawnParchment(vector<vector<char>> & map){
    int x, y;
    while(true){
        x = (rand() % map[0].size());
        y = (rand() % map.size());
        if(map[y][x] != '*' && map[y][x] != 'P' && map[y][x] != 'G' && map[y][x] != 'T'){
            gemsMap[y][x] = '#';
            parchmentCounter++;
            break;
        }
    }
}
//Increment score
void GameEngine::updateScore(int score){
    this->score+=score;
}
//Score getter
int GameEngine::getScore(){
    return score;
}
//Return a gemEaten event and then reset the event
bool GameEngine::gemEaten(){
    if(ateGem){
        ateGem = false;
        return true;
    }  
    else
        return false;
}
//Same as above (would be more usefull if game could be restarted without exiting program)
bool GameEngine::parchmentEaten(){
    if(ateParchemnt){
        ateParchemnt = false;
        return true;
    }  
    else
        return false;
}