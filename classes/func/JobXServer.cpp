#include "../interfaces/JobXServer.h"

using namespace std;
std::vector<int> getVectorNumberFromString(string s) {
   stringstream str_strm;
   std::vector<int> vetor;
   str_strm << s; //convert the string s into stringstream
   string temp_str;
   int temp_int;
   while(!str_strm.eof()) {
      str_strm >> temp_str; //take words into temp_str one by one
      if(stringstream(temp_str) >> temp_int) { //try to convert string to int
        vetor.push_back(temp_int);
      }
      temp_str = ""; //clear temp string
   }

   return vetor;
}

JobXServer::JobXServer(){
    this->b = {};
    this->C = {};
    this->m = 0;
    this->n = 0;
    this->p = 0;
    this->T = {};
}

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
            //std::cout << line << std::endl;
        }

    }catch(const char *error){
        std::cout << error;
    }
    
    file.close();

    // // storing the numbers of jobs and servers
    n = stoi(lines[0]);
    m = stoi(lines[1]);
    p = stoi(lines[2]);

    // // reading the capacity of each sever and storing into a vector
    std::stringstream bString(lines[4]);
    std::string bStringValue;

    while(getline(bString, bStringValue, ' ')){
        b.push_back(stoi(bStringValue));
        //std::cout << bStringValue << std::endl;
    }

    
    // reading T matrix and storing into a vector of vectors
    for(int i = 6; i <= 5 + m ;i++){
        T.push_back(getVectorNumberFromString(lines[i]));
    }

    // reading C matrix and storing into a vector of vectors
    for(int i = 5 + m + 2; i <= 5 + m + 1 +  b.size();i++){
        C.push_back(getVectorNumberFromString(lines[i]));
    }

}

void JobXServer::printProblemInput(){
    std::cout << "Número de jobs: " << n << std::endl;
    std::cout << "Número de servers: " << m << std::endl;

    std::cout << "Penalidade: " << p << std::endl;

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