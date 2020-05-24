#ifndef VIRTMEMSIM_H
#define VIRTMEMSIM_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream> 
#include <fstream>
#include <sstream>
#include <iomanip>

#include <vector> 
#include <map>
#include <deque>
#include <tuple> 
#include <list>
#include <queue>
#include <string>

using namespace std;

typedef vector <tuple<string, char, string>> tuple_list; // Definição do tipo tuple_list
typedef vector <tuple<int, char, int>>  parsed_tuple_list; // Definição do tipo parsed_tuple_list

class Pagina {
    
  public:
      ostringstream ss;
      int idProcesso;    // id do processo associado a página
      int idPagina; // id único da página
      int bitAlocacaoMemoria;   // 1 se estiver na memória e 0 do contrário
      int bitReferencia;   // bit de referência usado no Relógio. Inicializado em 0
      string tempoUltimoAcesso;
      
      Pagina (int idDoProcesso, int idDaPagina, int bitAlocacaoMemoria, int bitReferencia) {
          this->idProcesso = idDoProcesso;
          this->idPagina = idDaPagina;
          ss << idPagina;
          this->bitAlocacaoMemoria = bitAlocacaoMemoria;
          this->bitReferencia = bitReferencia;
      }
};

class Processo {

  public:
      int idProcesso; // id do processo
      int tamanho;   // tamanho em memória
      int numPaginas;   // quantidade de páginas
      vector<Pagina*> tabelaPaginas;    // tabela de páginas
      
      Processo (int id, int tam, int tamPaginas) {
          idProcesso = id;
          tamanho = tam;
          numPaginas = tamanho/tamPaginas;
          // Cria páginas extras caso haja espaço disponível em memória
          if (tamanho%tamPaginas>0) {
              numPaginas++;
          }
          for (int i = 0; i < numPaginas; i++) {
              Pagina* novaPagina = new Pagina(idProcesso, i, 0, 0);
              tabelaPaginas.push_back(novaPagina);
          }
      }
};

#endif