#include "Server.h"

Server::Server(int id, int custoParaServidor, std::vector <Jobs> jobs){
    this->id = id;
    this->custoParaServidor = custoParaServidor;
    this->jobs = jobs;
}
