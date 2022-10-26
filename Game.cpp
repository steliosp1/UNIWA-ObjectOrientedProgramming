#include "GameEngine.cpp"
#include "HiScore.cpp"
#include <curses.h>

using namespace std;

int main(int argc, char** argv){
    if(argc != 3) {//1st variable is executable name, so we have to check for 3 in order for our program to work properly
      cout << "You have to give 2 arguments.\n[1]: Text file containing map\t[2]: Binary file containing the scores\n";
      return -1;
   }
    int ch;
    string fileName = argv[1];
    vector<vector<char>> map;
    vector<vector<char>> copy_map;//Copy used to preserve original map for easier game restart (never implemented)
    //Object initialization
    GameEngine game = GameEngine();
    Potter p = Potter('P', 0, 0);
    Gnome g = Gnome('G', 0, 0);
    Traal t = Traal('T', 0, 0);
    HiScore score = HiScore();
    //Initializing components
    game.getMap(fileName, map);
    copy_map = map;
    game.initGemsMap(copy_map);
    game.initObjects(p, g, t, copy_map);
    //Initializing ncurses
    initscr();
    noecho();
    cbreak();
    curs_set(false);
    keypad(stdscr, true);
    printw ("Welcome to Ptixio se 2 xronia an ola pane kala\n\nPress any key to continue....");
    getch ();
	clear ();
    game.refreshMap(copy_map);//Print map after refreshing
    for(size_t j=0; j<copy_map.size(); j++)
            for(size_t k=0; k<copy_map[0].size(); k++)
                mvwprintw(stdscr, j, k, "%c", copy_map[j][k]);
    refresh();
    do
	{//After every user input the corresponding move will be executed
		ch = getch ();
		switch (ch)
		{
			case KEY_UP :
                p.move(1, copy_map);//first parameter int shows direction of movement
                g.move(p, copy_map);
                t.move(p, copy_map);
                game.unitCollision(p, g, t, copy_map);//After units have moved we check for collisions
                game.refreshMap(copy_map);//Refresh map in case of collision (could have made a flag to save some processing time)
                break;
			case KEY_DOWN :
                p.move(2, copy_map);
                g.move(p, copy_map);
                t.move(p, copy_map);
                game.unitCollision(p, g, t, copy_map);
                game.refreshMap(copy_map);
                break;
			case KEY_LEFT:
                p.move(3, copy_map);
                g.move(p, copy_map);
                t.move(p, copy_map);
                game.unitCollision(p, g, t, copy_map);
                game.refreshMap(copy_map);
                break;
			case KEY_RIGHT:
                p.move(4, copy_map);
                g.move(p, copy_map);
                t.move(p, copy_map);
                game.unitCollision(p, g, t, copy_map);
                game.refreshMap(copy_map);
                break;
            case 32/*SPACE*/: //If user presses space monsters will move nonetheless
                g.move(p, copy_map);
                t.move(p, copy_map);
                game.unitCollision(p, g, t, copy_map);
                game.refreshMap(copy_map);
		}
        game.refreshMap(copy_map);
        if(game.gemEaten())//Check for a game changing event
            game.updateScore(50);
        if(game.parchmentEaten())
            game.updateScore(100);
        if(game.getGemCounter() == 10){
            if(game.getParchmentCounter() < 1){//Spawn parchment only if user has eaten 10 gems
                game.spawnParchment(copy_map);
                game.refreshMap(copy_map);
            }    
        }//Check for game ending conditions
        if(game.getWinFlag())
            break;
        if(game.getLossFlag())
            break;
        //print map again after changes
        for(size_t j=0; j<copy_map.size(); j++)
            for(size_t k=0; k<copy_map[0].size(); k++)
                mvwprintw(stdscr, j, k, "%c", copy_map[j][k]);
        refresh();
	}
	while (ch != 27/*ESCAPE*/); //if user presses esc button game ends
	endwin (); //close ncurses too, not regular terminal will be used
    string name; //ask user for his name to go along side his score
    cout << "Give your name: ";
    cin >> name;
    score << name << game.getScore(); //overloaded << operator to make pass values in HiScore object 
    score.saveScore(argv[2]); //Save score on user provided binary file
	return 0;
}