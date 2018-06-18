#ifndef HUFFMANCODE_H
#define HUFFMANCODE_H

#include <iostream>
#include <algorithm>
#include <deque>
#include <stdio.h>
#include "binnode.h"
#include <cmath>
#include <fstream>
#include <cassert>
#include <vector>

#define uchar unsigned char

using namespace std;

class HuffmanCode
{
public:
  vector<BinNode*> m_leafs;
  vector<BinNode*> m_tree;
  fstream m_inputFile;
  fstream m_outputFile;
  vector<uint> m_frequency;
  uint m_numElem;
  uint m_alphabetSize;
  deque<bool> m_buffer;
  
  HuffmanCode();
  void Encode(string input, string output, uint alphabetSize);
  void MakeHistogram(void);
  void MakeNodes(void);
  void BuildHuffmanTree(void); 
  void OpenFile(string name, string mode);
  void Code(void);
  deque<bool> GetCodeFromTree(int letter);
  void SendBuffer(deque<bool> code);
  void FlushBuffer(void);
  int GetBitsFromBuffer(int byteSize);
  double CalcEntropy(void);
  double AverageSize(void);
  static bool ComparaFrequency(BinNode *left, BinNode *right);
};

#endif // HUFFMANCODE_H
