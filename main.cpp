#include "compactaDescompacta.h"
using namespace std;
int main(int argq, char **argv)
{
  if (argq < 3)
  {
    cout << "Falta de argumentos!!!" << endl;
    return 0;
  }
  string arq = argv[2];
  string op = argv[1];
  if (op == "compactar")
  {
    compactar(arq);
  }
  else if (op == "descompactar")
  {
    descompactar(arq);
  }
  else
  {
    cout << "Erro: " << op << " é invalida!" << endl;
  }

  return 0;
}
