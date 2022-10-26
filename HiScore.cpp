#include "HiScore.h"

HiScore::HiScore(){}
//Return reference to the object so we can chain operators
HiScore& HiScore::operator << (string name){
    this->name = name;
    return *this;
}

HiScore& HiScore::operator << (int score){
    this->score = score;
    return *this;
}
//These operators get values from object in fashion X >> name >> score
HiScore& HiScore::operator >> (string & name){
    name = this->name;
    return *this;
}

HiScore& HiScore::operator >> (int & score){
    score = this->score;
    return *this;
}
//To save the score we get data from binary file then write top5 on it again
void HiScore::saveScore(string filename){
    try {//throws exception if file is not found or could not be opened
        string scores="";
        string score_str="";
        multimap<int, string> mp;//we use a multimap tbecause it is a sorted structure
                                    //we will use this property so we dotdont have to sort anything ourselves
        /*Open the stream in binary mode.*/
        std::ifstream bin_file(filename, ios::binary | ios::in | ios::ate);//ate starts file from end 
                                                                    //so with tellg we can get size of file
    
        if (bin_file.good()) {
            long size = bin_file.tellg();
            char *buff = new char[size];//dynamically allocating a char * buffer
            bin_file.seekg(0, ios::beg);
            bin_file.read(buff, size);//use buffer to store characters from the file
            //deserialize characters from the buffer
            for(int j=0; j<size; j++){//repeat process for each substring in the string (score name\0score name\0score name\0)
                for(int i =j; buff[i]!= '\0'; i++){//we search buff till we hit \0 character (We are writing this to the file too)
                    scores.push_back(buff[i]);//add this to string
                    j = i+1;//make j point to the start of the next substring
                }
                score_str = scores.substr(0, scores.find(" "));//score is in string format (250 Gkiokas) so we split it in two parts
                mp.insert({stoi(score_str), scores.erase(0, scores.find(" ") + 1)});//we convert string score number to int via stoi
                                                                //and get name vie erase which will erase string till the space character
                                                                //leaving us with only the name (250,Gkiokas)
                scores = "";//reset string for next substring
            }
            delete []buff;//we dont need buffer anymore
            bin_file.close();//close file
        }
        else {
            throw "Could not open file for reading scores. Check if you are giving correct file";
        }

        mp.insert({score, name});//this is a function of the object so we can access its attributes freely
        multimap <int, string>::reverse_iterator it;//backwards iterator so we can traverse the multimap in reverse
                                                    //we need this because multimap sorts its items in an ascending order
        string temp;
        int i=0;
        for (it = mp.rbegin(); it != mp.rend(); ++it){//by traversing in reverse we get items in descending order which means top5  
            i++;//counter used to keep track of scores printed
            cout << it->first << " " << it->second << endl;//show scores on user
            temp+=to_string(it->first) + ' ';//serialize output so it can be stored again
            temp+=it->second + '\0';
            if(i == 5)//we need only 5 scores
                break;
        }
        //open file for writing, throws exception if file not found or could not be opened
        std::ofstream file(filename, ios::binary | ios::out);
        if (file.is_open()) {
            file.write(temp.c_str(), temp.size());//use of c_str() to convert string to char *
            file.close();//close file
        }
        else {
            throw "Could not open file for writing scores. Check if you are giving correct file";
        }
    }catch(const char * msg){
        cout<< msg << endl;
        exit(-1);
    }
}