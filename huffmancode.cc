#include "huffmancode.h"

HuffmanCode::HuffmanCode():
  m_numElem(0)
{
  
}

void HuffmanCode::Encode(string input, string output, uint alphabetSize)
{
  m_alphabetSize = alphabetSize;
  OpenFile (input,"read");
  MakeHistogram();
  MakeNodes();
  BuildHuffmanTree();
  
  
  
  //  fstream outputFile;
  //  outputFile.write(m_ocorrencia,sizeof(int), sizeof(m_ocorrencia)/sizeof(int));
  
  
}

void HuffmanCode::MakeHistogram(void)
{  
  char letter;
  m_frequency = vector<uint>(m_alphabetSize, (uint) 0);
  
  while (m_inputFile.get(letter))
    {
      m_frequency[(uchar) letter]++;
      m_numElem++;
    }
  m_inputFile.clear();
}

void HuffmanCode::MakeNodes(void)
{ 
  BinNode *node; 
  
  for (uint i = 0; i < m_alphabetSize; i++) 
    {
      if (m_frequency[i] == 0) continue; // pule caracteres com 0 ocorrencias
      
      node = new BinNode;        
      node->m_letter = i;
      node->m_frequency = m_frequency[i];
      m_leafs.push_back (node);
    }      
}

void HuffmanCode::BuildHuffmanTree()
{
  vector<BinNode*> leafs = m_leafs;
  BinNode *parent;
  BinNode *left;
  BinNode *right;
  m_tree = leafs;
  
  while (leafs.size() > 1)
    {
      stable_sort(leafs.begin(), leafs.end (), ComparaFrequency);
      
      // mostrar construção
      if (false)
        {            
          cout << "\n huffman.leafs \n";
          for (size_t i = 0; i < leafs.size(); i++)
            {
              cout << 
                      "\t m_left = " << (leafs[i])->m_left <<
                      "\t m_right = " << (leafs[i])->m_right <<
                      "\t m_parent = " << (leafs[i])->m_parent <<
                      "\t m_letter = " << (leafs[i])->m_letter <<
                      "\t m_frequency = " << (leafs[i])->m_frequency <<
                      endl;
            }
          
          printf("leafs.size() = %ld \n", leafs.size());
          cin.get();
        }
      
      left = leafs.back();
      leafs.pop_back ();
      
      right = leafs.back();
      leafs.pop_back ();
      
      parent = new BinNode(left,right);
      leafs.push_back (parent);
      m_tree.push_back (parent);
    }
  
  // Mostra arvore final
  if (false) 
    {            
      cout << "\n huffman.tree \n";
      
      for (uint i = 0;i < m_tree.size(); i++) 
        {
          cout <<                  
                  "\t m_left = " << (m_tree[i])->m_left <<
                  "\t m_right = " << (m_tree[i])->m_right <<
                  "\t m_parent = " << (m_tree[i])->m_parent <<
                  "\t m_letter = " << (m_tree[i])->m_letter <<
                  "\t m_frequency = " << (m_tree[i])->m_frequency <<
                  endl; 
        }
      
      cout << "m_tree.size() = " << m_tree.size() << endl;
      cin.get();
    }  
}

void HuffmanCode::OpenFile(string name, string mode)
{
  if (mode == string("read"))
    {
      m_inputFile.open (name, ios::in|ios::binary);
      assert(m_inputFile.good());
    }
  else if (mode == string("write"))
    {
      m_outputFile.open (name, ios::out|ios::binary);
      assert(m_outputFile.good());
    }
}

void HuffmanCode::Code(void)
{
  deque<bool> code;
  char letter;
  while (m_inputFile.get(letter))
    {
      code = GetCodeFromTree(letter);      
      SendBuffer(code);      
    }
}

deque<bool> HuffmanCode::GetCodeFromTree(int letter)
{  
  deque<bool> code;
  
  for (BinNode *leaf : m_leafs)
    {
      if (leaf->m_letter == (uint) letter)
        {
          BinNode *current = leaf;
          BinNode *parent = current->m_parent;
          
          while(parent != nullptr)
            {
              if (parent->m_left == current) 
                code.push_front(true); 
              else if (parent->m_right == current) 
                code.push_front(false);
              
              current = parent;
              parent = current->m_parent;
            }
          return code;         
        } 
    }
  
  cout << "erro ao codificar. Caractere de entrada (" << letter << ") não encontrado na árvore.\n";
  cout << "os caracteres são: \n";
  for (BinNode *leaf : m_leafs) printf("%02X,  ",leaf->m_letter);
  exit(-1); 
}

void HuffmanCode::SendBuffer(deque<bool> code)
{  
  m_buffer.insert(m_buffer.end(),code.begin(), code.end());
  
  while (m_buffer.size() >= 8) 
    {
      m_outputFile.put ((char) GetBitsFromBuffer(8)); 
    }  
}

int HuffmanCode::GetBitsFromBuffer(int byteSize = 0)
{
  if (byteSize == 0)
      byteSize = m_buffer.size();
  
  int saida = 0;
  for (int i = 0; i < byteSize; i++) 
    {
      if(m_buffer[0] == true) 
          saida += (0x80 >> i); 
      
      m_buffer.pop_front();
    }
  
  return saida;
}

bool HuffmanCode::ComparaFrequency(BinNode *left, BinNode *right)
{
  return left->m_frequency > right->m_frequency;
}
