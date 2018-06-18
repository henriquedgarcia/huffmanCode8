#include <iostream>
#include "huffmancode.h"

using namespace std;

int main(int argc, char *argv[] )
{
  // -c Comprime
  // -e Expande
  
  if (argc < 4 || argc > 6)
    {
      cout << "Uso errado!\n";
      cout << "\t" << argv[0] << "-c fileIn fileOut\n";
      cout << "ou\n";
      cout << "\t" << argv[0] << "-e table fileIn fileOut\n";
      
      exit(-1);
    }
  
  string saida = string(argv[1]);
  
  if (string(argv[1]) == "-c")
    {
      // saida = string(argv[1], (saida.rfind(".", saida.size ()))) + ".huff";      
      HuffmanCode encoder;  
      encoder.Encode(string(argv[2]), string(argv[3]), 256);
    }
  else if (string(argv[1]) == "-e")
    {
      //  HuffmanCode decoder;
      //  decoder.decodes(string(argv[2]), string(argv[3]), string(argv[4]), 256);
    }
  
  return 0;
}
