#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string> 

#define FILE_NAME "input.txt"

using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::ifstream;
using std::string;

typedef struct Server
{
    vector<int> allocatedJobs;
    int totalCost;
    int TimeSpent;
    Data* data;
};

typedef struct Data
{
    int jobAmmount;
    int serverAmmount;
    int** timeTable;
    int** costTable;
    int*  capacityTable;
};


typedef struct Solution
{
    vector<Server> servers;
    int solutionCost;
    int solutionTimeSpent;
};

void handleFile(string fileName, Data* data)
{
    ifstream inData;
    int jobAmmount, serverAmmount;
    inData.open(FILE_NAME);

    if(!inData){ // file couldn't be opened
      cerr << "Error: file could not be opened" << endl;
      exit(1);
    }

    inData >> jobAmmount;
    inData >> serverAmmount;
    cout << "Quantidade de Jobs: " <<jobAmmount << '\n' << "Quantidade de Servers: " <<serverAmmount << endl;

    data->costTable = (int**)malloc(serverAmmount * sizeof(int*));
    data->timeTable = (int**)malloc(serverAmmount * sizeof(int*));
    data->capacityTable = (int*)malloc(serverAmmount * sizeof(int));
    for(int i = 0; i < serverAmmount; i++) {
        data->costTable[i] = (int*)malloc(jobAmmount * sizeof(int));
        data->timeTable[i] = (int*)malloc(jobAmmount * sizeof(int));
    }

    for(unsigned int i = 0; i < serverAmmount; i++){
        inData >> data->capacityTable[i];
        cout << "capacityTable[" << i << "] = " << data->capacityTable[i] << endl;
    }

    for(unsigned int i = 0; i < serverAmmount; i++){
        for(unsigned int j = 0; j < jobAmmount; j++){
            inData >> data->timeTable[i][j];
            cout << "timeTable[" << i << "][" << j << "] = " << data->timeTable[i][j] << endl;
        }
    }

    for(unsigned int i = 0; i < serverAmmount; i++){
        for(unsigned int j = 0; j < jobAmmount; j++){
            inData >> data->costTable[i][j];
            cout << "costTable[" << i << "][" << j << "] = " << data->costTable[i][j] << endl;
        }
    }        
}

void freeData(Data* data)
{
    for(unsigned int i = 0; i < data->jobAmmount; i++){
        free(data->costTable[i]);
        free(data->timeTable[i]);
    }
    free(data->capacityTable);
    free(data->costTable);
    free(data->timeTable);
    free(data); 
}

int main(){
    Data* data = (Data*) malloc(sizeof(Data));
    handleFile(FILE_NAME, data);
    freeData(data);
    return 0;
}