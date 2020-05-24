#include "VirtMemSim.h"
using namespace std;

// Vetor de processos
vector <Process> PROCESS_LIST; // Talvez seja melhor trocar por um map

////////////////////
// Métodos globais
////////////////////
tuple_list read_input(const char * file_path) {
  tuple_list input;
  ifstream infile(file_path);
  string process_id, value_term;
  char operation;

  while (infile >> process_id >> operation >> value_term) {
    input.push_back({process_id, operation, value_term});
  }

  return input;
}

void print_input(parsed_tuple_list input) {
  for(const auto &i : input) {
    cout << get<0>(i) << " " << get<1>(i) << " " << get<2>(i) << endl;
  }
}

parsed_tuple_list parse_input(tuple_list input) {
  parsed_tuple_list parsed_inputs;
  string parsed_buffer;
  int parsed_number;
  unsigned first, last;
  string start_marker = "(";
  string stop_marker = ")2";

  for(const auto &i : input) {
    if (get<1>(i) == 'C') {
      parsed_number = stoi(get<2>(i));
      parsed_inputs.push_back({get<0>(i), get<1>(i), parsed_number});
    } else {
      first = get<2>(i).find(start_marker);
      last = get<2>(i).find(stop_marker);
      parsed_buffer = get<2>(i).substr(first + 1, last - 1);
      parsed_number = stoi(parsed_buffer);
      parsed_inputs.push_back({get<0>(i), get<1>(i), parsed_number});
    } 
  }
  
  return parsed_inputs;
}

void log_status(MainMemory main, SecondaryMemory sec) {
  return;
}

///////////////////////////
// Classe abstrata Memory
///////////////////////////
Memory::Memory(int memory_size) {
  size = memory_size;
  memory_process_list.resize(size);
}

void Memory::read(string proc_id, int address) {
  return;
}

void Memory::write(string proc_id, int address) {
  return;
}

void Memory::process_in_cpu(string proc_id, int instruction) {
  return;
}

void Memory::send_to_io(string proc_id, int instruction) {
  return;
}

//////////////////////
// Classe MainMemory
//////////////////////
void MainMemory::read(string proc_id, int address) {
  return;
}

void MainMemory::write(string proc_id, int address) {
  return;
}

void MainMemory::process_in_cpu(string proc_id, int instruction) {
  return;
}

void MainMemory::send_to_io(string proc_id, int instruction) {
  return;
}

///////////////////////////
// Classe SecondaryMemory
///////////////////////////
void SecondaryMemory::read(string proc_id) {
  return;
}

void SecondaryMemory::write(string proc_id) {
  return;
}

void SecondaryMemory::process_in_cpu(string proc_id, int instruction) {
  return;
}

void SecondaryMemory::send_to_io(string proc_id, int instruction) {
  return;
}
