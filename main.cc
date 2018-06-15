#include <iostream>
#include "huffmancode.h"

using namespace std;

int main(int argc, char *argv[] )
{
  if (argc != 2)
    {
      printf("Uso errado: %s arquivo. \n", argv[0]);
      exit(-1);
    }
  
  string saida = string(argv[1]);
  saida = string(argv[1], (saida.rfind(".", saida.size ()))) + ".huff";
  
  HuffmanCode encoder;  
  encoder.Encode(string(argv[1]), saida, 256);
  
  //  HuffmanCode decoder;
  //  decoder.decodes(saida,saida2);
  
  
  return 0;
}
