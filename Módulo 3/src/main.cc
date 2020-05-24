#include <iostream>
#include "VirtMemSim.h"

using namespace std;

#define TAM_PAGINAS 4
#define TAM_QUADRO_PAGINAS 4
#define TAM_BITS_ENDERECO_LOGICO 32
#define TAM_MEMORIA_FISICA 44
#define TAM_MAX_MEMEMORIA_SECUNDARIA 44
#define TAM_MAX_IMG_PROC 4

int main(int argc, char** argv) {
  tuple_list input;
  parsed_tuple_list parsed_input;

  input = read_input(argv[1]);

  parsed_input = parse_input(input);

  print_input(parsed_input);

  return 0;
}