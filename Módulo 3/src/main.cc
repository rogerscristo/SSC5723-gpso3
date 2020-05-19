#include <iostream>
#include "VirtMemSim.h"

using namespace std;

#define TAM_PAG 11
#define TAM_QUAD_PAG 22
#define TAM_END_LOG 33
#define TAM_MEM_FIS 44
#define TAM_MAX_MEM_SEC 55
#define TAM_MAX_IMG_PROC 66

int main(int argc, char** argv) {
  tuple_list input;
  parsed_tuple_list parsed_input;

  input = read_input(argv[1]);

  parsed_input = parse_input(input);

  print_input(parsed_input);
    
  return 0;
}