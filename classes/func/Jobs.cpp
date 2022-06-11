#include "../interfaces/Jobs.h"

Jobs::Jobs(int id, int tempo, int custo, int idServerAlloc){
    this->id = id;
    this->tempo = tempo;
    this->custo = custo;
    this->idServerAlloc = idServerAlloc;
}