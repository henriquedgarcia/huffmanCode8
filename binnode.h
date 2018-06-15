#ifndef BINNODE_H
#define BINNODE_H

#define uint unsigned int

class BinNode
{
public:
  BinNode();
  BinNode(BinNode *left, BinNode *right);
  ~BinNode();
  BinNode *m_left;
  BinNode *m_right;
  BinNode *m_parent;
  uint m_letter;
  uint m_frequency;
  
  void SetLeft(BinNode *left); 
  void SetRight(BinNode *right);
  void SetParent(BinNode *parent);
};

#endif // BINNODE_H
