#include "binnode.h"

BinNode::BinNode():
  m_left (nullptr),
  m_right (nullptr),
  m_parent (nullptr),
  m_letter (0x00),
  m_frequency (0)
{}

BinNode::BinNode(BinNode *left, BinNode *right) : BinNode()
{
  SetLeft(left); 
  SetRight(right);
  this->m_frequency = left->m_frequency + right->m_frequency;
}

BinNode::~BinNode(){}

void BinNode::SetLeft(BinNode *left)
{
  m_left = left;
  left->SetParent(this); // registra quem é o pai de node
}

void BinNode::SetRight(BinNode *right)
{
  m_right = right;
  right->SetParent(this);            // registra quem é o pai de node
}

void BinNode::SetParent(BinNode *parent)
{
  m_parent = parent;      // registra quem é o pai
}
