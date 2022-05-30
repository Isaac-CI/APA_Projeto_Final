#include "JobXServer.h"

JobXServer::JobXServer(const char *path){
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

void JobXServer::printProblemInput(){
    std::cout << "Número de jobs: " << n << std::endl;
    std::cout << "Número de servers: " << m << std::endl;

    std::cout << "Vetor b(capacidade maxima de tempo de processamento): ";

    for(int i : b){
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "Matriz T:"<< std::endl;;

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            std::cout << T[i][j] << " ";;
        }
        std::cout << std::endl;

    }

    std::cout << "Matriz C:"<< std::endl;;

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            std::cout << C[i][j] << " ";;
        }
        std::cout << std::endl;

    }
}