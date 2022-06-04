#include "../interfaces/Server.h"

Server::Server(int id, int custoParaServidor, std::vector <Jobs> jobs, int jobAmmount){//não era tu que queria deixar tudo em inglês?
    this->id = id;
    this->custoParaServidor = custoParaServidor;
    this->jobs = jobs;
    this->jobAmmount = jobAmmount;
}
