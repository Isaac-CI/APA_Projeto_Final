#include <iostream>
#include "JobXServer.h"

using namespace std;

int main(void){

    JobXServer instance = JobXServer("./input.txt");

    instance.printProblemInput();
    
    return 0;
}