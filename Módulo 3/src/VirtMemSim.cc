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

void log_status(MainMemory main, SecondaryMemory sec) {
  return;
}

///////////////////////////
// Classe abstrata Memory
///////////////////////////
Memory::Memory(int memory_size) {
  size = memory_size;
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