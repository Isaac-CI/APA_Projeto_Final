#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

class JobXServer {
    public:
        int n, m;
        std::vector <std::vector <int>> T, C;
        std::vector<int> b;
        
        JobXServer(const char *path){
            std::fstream file;
            std::vector<std::string> lines;
            
            file.open(path, std::ios::in);
            // reads data and stores into a string vector
            try{
                if(!file.is_open()){
                    throw "File could not be open!\n";
                }
                
                for(std::string line; getline(file, line); ){
                    lines.push_back(line);
                }

            }catch(const char *error){
                std::cout << error;
            }
            
            file.close();
            
            // storing the numbers of jobs and servers
            n = stoi(lines[0]);
            m = stoi(lines[1]);

            // reading the capacity of each sever and storing into a vector
            std::stringstream bString(lines[3]);
            std::string bStringValue;
            
            while(getline(bString, bStringValue, ' ')){
                b.push_back(stoi(bStringValue));
            }

            // reading T matrix and storing into a vector of vectors
            for(int i = 5; i <= 6 ;i++){
                std::vector<int> aux;

                std::stringstream currentLine(lines[i]);
                std::string currentLineValue;

                while(getline(currentLine, currentLineValue, ' ')){
                    aux.push_back(stoi(currentLineValue));
                }

                T.push_back(aux);
            }

            // reading C matrix and storing into a vector of vectors
            for(int i = 8; i <= 9 ;i++){
                std::vector<int> aux;

                std::stringstream currentLine(lines[i]);
                std::string currentLineValue;

                while(getline(currentLine, currentLineValue, ' ')){
                    aux.push_back(stoi(currentLineValue));
                }

                C.push_back(aux);
            }
        
        }

};

int main(void){

    JobXServer instance = JobXServer("./input.txt");

    
    return 0;
}