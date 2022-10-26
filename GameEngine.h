#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

#include "Potter.cpp"
#include "Gnome.cpp"
#include "Traal.cpp"
//GameEngine is responsible for loading the map, initializing objects on map, 
                //keeping track of score and determining game state (win or loss)

using namespace std;
class GameEngine{
        bool loss = false;
        bool win = false;
        bool ateGem = false;
        bool ateParchemnt = false;  //flags for checking game's state
        int gemCounter = 0; //used to determine when the game will end
        int parchmentCounter = 0;
        vector<vector<char>> gemsMap; //use of a seperate map for gems, to handle collision with monsters and potter
        int score = 0;
        int remainingGems=0;
    public:
        GameEngine();
        void getMap(string, vector<vector<char>> &);
        void initGemsMap(vector<vector<char>> &);
        void initObjects(Potter &, Gnome &, Traal &, vector<vector<char>> &);
        void setGems(vector<vector<char>> &);
        void setPotterPosition(Potter &, char, char, vector<vector<char>> &);
        void setGnomePosition(Gnome &, char, char, vector<vector<char>> &);
        void setTraalPosition(Traal &, char, char, vector<vector<char>> &);
        void startGame(Potter &, Gnome &, Traal &, vector<vector<char>> &);
        void unitCollision(Potter &, Gnome &, Traal &, vector<vector<char>> &);
        int getGemCounter();
        bool getLossFlag();
        bool getWinFlag();
        void refreshMap(vector<vector<char>> &);
        void spawnParchment(vector<vector<char>> &);
        int getParchmentCounter();
        void updateScore(int);
        int getScore();
        bool gemEaten();
        bool parchmentEaten();

};