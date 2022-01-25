struct Node
{
  int freq;
  char caractere;
  bool visit = false;
  Node *left;
  Node *right;
  Node(int quant, char carac);
  Node(Node *a, Node *b);
  Node(Node *a);
  Node();
  bool operator<(const Node &b);
  bool operator>(const Node &b);
};
Node::Node()
{
  this->left = 0;
  this->right = 0;
};
Node::Node(Node *a)
{
  freq = a->freq;
  caractere = a->caractere;
  left = a->left;
  right = a->right;
};
Node::Node(Node *a, Node *b)
{
  freq = a->freq + b->freq;
  caractere = '*';
  left = new Node(a);
  right = new Node(b);
};
Node::Node(int quant, char carac)
{
  this->freq = quant;
  this->caractere = carac;
  this->left = 0;
  this->right = 0;
};
bool Node::operator<(const Node &b)
{
  if (freq < b.freq)
  {
    return true;
  }
  return false;
}
bool Node::operator>(const Node &b)
{
  if (freq > b.freq)
  {
    return true;
  }
  return false;
}
class Tree
{
  Node *nodeRaiz;

public:
  Tree(const Node &n)
  {
    nodeRaiz = new Node(n);
  }
  Node *getNodeRaiz()
  {
    return nodeRaiz;
  }
  void deletaNode(Node *no)
  {
    if (no == 0)
    {
      return;
    }
    deletaNode(no->left);
    deletaNode(no->right);
    delete no;
  }
  ~Tree()
  {
    if (nodeRaiz == 0)
    {
      return;
    }
    deletaNode(nodeRaiz);
    delete nodeRaiz;
  }
};