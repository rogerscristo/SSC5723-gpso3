#include "VirtMemSim.h"
using namespace std;

////////////////////
// Métodos globais
////////////////////
tuple_list read_input(string file_path) {
  return;
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