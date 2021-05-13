struct nodo
{
  int freq;
  char caractere;
  bool visit = false;
  nodo *left;
  nodo *right;
  nodo(int quant, char carac);
  nodo(nodo *a, nodo *b);
  nodo(nodo *a);
  nodo();
  bool operator<(const nodo &b);
  bool operator>(const nodo &b);
};
nodo::nodo()
{
  this->left = 0;
  this->right = 0;
};
nodo::nodo(nodo *a)
{
  freq = a->freq;
  caractere = a->caractere;
  left = a->left;
  right = a->right;
};
nodo::nodo(nodo *a, nodo *b)
{
  freq = a->freq + b->freq;
  caractere = '*';
  left = new nodo(a);
  right = new nodo(b);
};
nodo::nodo(int quant, char carac)
{
  this->freq = quant;
  this->caractere = carac;
  this->left = 0;
  this->right = 0;
};
bool nodo::operator<(const nodo &b)
{
  if (freq < b.freq)
  {
    return true;
  }
  return false;
}
bool nodo::operator>(const nodo &b)
{
  if (freq > b.freq)
  {
    return true;
  }
  return false;
}
class tree
{
  nodo *nodoRaiz;

public:
  tree(const nodo &n)
  {
    nodoRaiz = new nodo(n);
  }
  nodo *getNodoRaiz()
  {
    return nodoRaiz;
  }
  void deletaNodo(nodo *no)
  {
    if (no == 0)
    {
      return;
    }
    deletaNodo(no->left);
    deletaNodo(no->right);
    delete no;
  }
  ~tree()
  {
    if (nodoRaiz == 0)
    {
      return;
    }
    deletaNodo(nodoRaiz);
    delete nodoRaiz;
  }
};