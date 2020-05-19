#ifndef CORE_H
#define CORE_H

#include<iostream> 
#include <fstream>
#include <vector> 
#include <tuple> 
#include <string> 
using namespace std;

typedef vector <tuple<string, char, string>> tuple_list; // Definição do tipo tuple_list
typedef vector <tuple<string, char, int>>  parsed_tuple_list; // Definição do tipo parsed_tuple_list

////////////////////////////////
// Estruturas de dados básicas
////////////////////////////////

struct Process {
  string process_id; // ID do processo. Exemplo P2
  int size; // Tamanho do processo
  char current_status; // Status atual do processo (C, R, W, P ou I)
} ;

struct Page {
  int size; // Tamanho da página
  string content; // Conteúdo da página TODO: Talvez deveria ser um vector aqui
};

///////////////////////////
// Classe abstrata Memory
///////////////////////////
class Memory {
  public:
    int size; // Tamanho da memória

    // Vetor de processos na memória
    vector <Process> memory_process_list; // TODO: Talvez seja melhor trocar por um map

    // Construtor
    Memory(int memory_size);

    void read(string proc_id, int address); // Processo lê do endereço
    void write(string proc_id, int address); // Processo escreve no endereço
    void process_in_cpu(string proc_id, int instruction); // Processo indicando instrução de CPU
    void send_to_io(string proc_id, int instruction); // Processo indicando instrução de I/O
};

//////////////////////
// Classe MainMemory
//////////////////////
class MainMemory: public Memory {
  public:
    // Overwrite de métodos caso seja necessário
    void read(string proc_id, int address); // Processo lê do endereço
    void write(string proc_id, int address); // Processo escreve no endereço
    void process_in_cpu(string proc_id, int instruction); // Processo indicando instrução de CPU
    void send_to_io(string proc_id, int instruction); // Processo indicando instrução de I/O
};

///////////////////////////
// Classe SecondaryMemory
///////////////////////////
class SecondaryMemory: public Memory {
  private:
    void lru(); // Algoritmo LRU para paginação
    void clock(); // Algoritmo Clock para paginação

  public:
    vector <Page> pages_list; // Quadro de páginas
    string alg_param; // Parâmetro de escolha do algoritmo de paginação ("lru" ou "clock")

    // Overwrite de métodos caso seja necessário
    void read(string proc_id); // Processo lê do endereço
    void write(string proc_id); // Processo escreve no endereço
    void process_in_cpu(string proc_id, int instruction); // Processo indicando instrução de CPU
    void send_to_io(string proc_id, int instruction); // Processo indicando instrução de I/O
};

////////////////////
// Métodos globais
////////////////////
tuple_list read_input(const char * file_path); // Lê arquivo de entrada
void print_input(parsed_tuple_list input); // Imprime na tela os elementos capturados no input
parsed_tuple_list parse_input(tuple_list input); // Interpreta a entrada e transforma valores ()2 para int
void log_status(MainMemory main, SecondaryMemory sec); // Imprime os status das memórias principal e secundária


#endif