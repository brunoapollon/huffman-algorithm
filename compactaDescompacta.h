#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <stack>
#include <queue>
#include <bitset>
#include "heap.h"
#include "tree.h"
nodo CreateTreeCompact(string arquivo)
{
  int vet[256];
  for (int i = 0; i < 256; i++)
  {
    vet[i] = 0;
  }
  int ichar;
  char a;
  unsigned char b;
  int teste = 0;
  ifstream myfile(arquivo.c_str(), ifstream::binary);
  myfile.read(&a, 1);
  while (!myfile.eof())
  {
    b = a;
    ichar = (int)b;
    for (int i = 0; i < 256; i++)
    {
      if (ichar == i)
      {
        vet[i]++;
      }
    }
    myfile.read(&a, 1);
  }
  myfile.close();
  int tamHeap = 0, cont = 0;
  for (int i = 0; i < 256; i++)
  {
    if (vet[i] != 0)
    {
      tamHeap++;
    }
  }
  stack<nodo> pilha;
  for (int i = 0; i < 256; i++)
  {
    if (vet[i] != 0)
    {
      nodo a(vet[i], i);
      pilha.push(a);
      cont++;
    }
  }
  heap<nodo> h(cont);
  for (int i = 0; i < cont; i++)
  {
    h.push(pilha.top());
    pilha.pop();
  }
  nodo l, r;
  while (h.len() > 1)
  {
    l = h.pop();
    r = h.pop();
    nodo c(&l, &r);
    h.push(c);
  }
  r = h.pop();
  nodo retorno = new nodo(r);
  return retorno;
}
nodo *CreateTreeDescompact(string arquivo)
{
  int contStop = 0, contBarras = 0, contPontoVirgulas = 0;
  char a;
  unsigned char b, caracAnterior, posTabela;
  string vetor[256], sequence = "";
  for (int i = 0; i < 256; i++)
  {
    vetor[i] = "";
  }
  nodo *retorno = new nodo();
  ifstream myfile(arquivo.c_str(), ifstream::binary);
  myfile.read(&a, 1);
  while (!myfile.eof())
  {
    b = a;
    if (contBarras > 1)
    {
      if (caracAnterior == '/')
      {
        posTabela = b;
        myfile.read(&a, 1);
        myfile.read(&a, 1);
        caracAnterior = a;
        continue;
      }
      else
      {
        if (b != '/' || b != '|')
        {
          if (b == '|')
          {
            contStop++;
          }
          else if (b == '/')
          {
            vetor[(int)posTabela] = sequence;
            sequence = "";
          }
          else
          {
            sequence += b;
          }
        }
        else
        {
        }
      }
    }
    if (b == '/')
    {
      contBarras++;
    }
    if (contStop == 3)
    {
      vetor[(int)posTabela] = sequence;
      break;
    }
    caracAnterior = a;
    myfile.read(&a, 1);
  }
  for (int i = 0; i < 256; i++)
  {
    nodo *aux = retorno;
    sequence = vetor[i];
    for (int j = 0; j < sequence.length(); j++)
    {
      if (sequence[j] == '0')
      {
        if (aux->left == 0)
        {
          nodo *temp = new nodo();
          aux->left = temp;
          aux = aux->left;
        }
        else
        {
          aux = aux->left;
        }
      }
      else
      {
        if (aux->right == 0)
        {
          nodo *temp = new nodo();
          aux->right = temp;
          aux = aux->right;
        }
        else
        {
          aux = aux->right;
        }
      }
      if (j + 1 == sequence.length())
      {
        aux->caractere = i;
      }
    }
  }
  myfile.close();
  return retorno;
}
void codigoCarac(nodo *no, string sequence, string vet[])
{
  if (no->left == 0 && no->right == 0)
  {
    unsigned char a = no->caractere;
    vet[(int)a] = sequence;
  }
  else
  {
    codigoCarac(no->left, sequence + '0', vet);
    codigoCarac(no->right, sequence + '1', vet);
  }
}
string retornaArqSaida(string nomeArquivo)
{
  string newName = "";
  for (int j = 0; j < nomeArquivo.length(); j++)
  {
    if (nomeArquivo[j] == '.')
    {
      break;
    }
    newName += nomeArquivo[j];
  }
  newName += ".bruno";
  return newName;
}
string retornaExtensaoArq(string nomeArquivo)
{
  string ext = "";
  int pos;
  for (int j = 0; j < nomeArquivo.length(); j++)
  {
    if (nomeArquivo[j] == '.')
    {
      pos = j;
    }
  }
  for (int j = pos + 1; j < nomeArquivo.length(); j++)
  {
    ext += nomeArquivo[j];
  }
  return ext;
}
string retornaNome(string nomeArquivo)
{
  string nome = "";
  int pos;
  for (int j = 0; j < nomeArquivo.length(); j++)
  {
    if (nomeArquivo[j] == '.')
    {
      pos = j;
    }
  }
  for (int j = 0; j < pos; j++)
  {
    nome += nomeArquivo[j];
  }
  nome += ".";
  char a;
  unsigned char b;
  int contBarras = 0;
  ifstream myfile(nomeArquivo.c_str(), ifstream::binary);
  myfile.read(&a, 1);
  while (!myfile.eof())
  {
    b = a;
    if (contBarras > 0)
    {

      if (b == '/')
      {
        break;
      }

      nome += b;
    }
    if (b == '/')
    {
      contBarras++;
    }
    myfile.read(&a, 1);
  }
  myfile.close();
  return nome;
}
int quantidadePosComValor(string vet[])
{
  int cont = 0;
  for (int i = 0; i < 256; i++)
  {
    if (vet[i] != "")
    {
      cont++;
    }
  }
  return cont;
}
void compactar(string nomeArquivo)
{
  ifstream myFileInput(nomeArquivo.c_str(), ifstream::binary);
  if (!myFileInput)
  {
    cout << "Arquivo Inexistente!!" << endl;
    return;
  }
  cout << "Compactando o arquivo..." << endl;
  int soma = 0, cont = 0, tamTabela;
  tree *arvore = new tree(CreateTreeCompact(nomeArquivo));
  string sequence = "", by = "";
  string vetor[256];
  codigoCarac(arvore->getNodoRaiz(), sequence, vetor);
  ofstream myFileOutput(retornaArqSaida(nomeArquivo).c_str(), ofstream::binary);
  myFileOutput << arvore->getNodoRaiz()->freq << '/';
  myFileOutput << retornaExtensaoArq(nomeArquivo) << '/';
  tamTabela = quantidadePosComValor(vetor);
  for (int i = 0; i < 256; i++)
  {
    if (vetor[i] != "")
    {
      cont++;
      myFileOutput << (char)i << ';';
      by = vetor[i];
      for (int j = 0; j < by.length(); j++)
      {
        myFileOutput << by[j];
      }
      if (cont == tamTabela)
      {
        myFileOutput << '|' << '|' << '|';
      }
      else
      {
        myFileOutput << '/';
      }
    }
  }
  char a;
  unsigned char b;
  queue<char> fila;
  cont = 0;
  myFileInput.read(&a, 1);
  while (!myFileInput.eof())
  {
    b = a;
    sequence = "";
    for (int i = 0; i < 256; i++)
    {
      if (b == i)
      {
        cont++;
        sequence = vetor[i];
        for (int j = 0; j < sequence.length(); j++)
        {
          fila.push(sequence[j]);
        }
      }
    }
    while (fila.size() > 7)
    {
      sequence = "";
      for (int i = 0; i < 8; i++)
      {
        sequence += fila.front();
        fila.pop();
      }
      for (int i = 0, j = sequence.length() - 1; i < sequence.length(); i++, j--)
      {
        if (sequence[j] == '1')
        {
          soma += pow(2, i);
        }
      }
      myFileOutput << (char)soma;
      soma = 0;
    }
    myFileInput.read(&a, 1);
  }
  int tamFila;
  if (fila.size() < 8)
  {
    tamFila = fila.size();
    sequence = "";
    while (!fila.empty())
    {
      sequence += fila.front();
      fila.pop();
    }
    for (int i = tamFila; i < 8; i++)
    {
      sequence += '0';
    }
    for (int i = 0, j = sequence.length() - 1; i < sequence.length(); i++, j--)
    {
      if (sequence[j] == '1')
      {
        soma += pow(2, i);
      }
    }
    myFileOutput << (char)soma;
  }
  myFileOutput.close();
  myFileInput.close();
  cout << "concluido." << endl;
}
void descompactar(string nomeArquivo)
{
  ifstream myfileInput(nomeArquivo.c_str(), ifstream::binary);
  if (!myfileInput)
  {
    cout << "Arquivo Inexistente!!" << endl;
    return;
  }
  cout << "Descompactando o arquivo..." << endl;
  tree *arvore = new tree(CreateTreeDescompact(nomeArquivo));
  string nomeDescompact = retornaNome(nomeArquivo), sequence = "";
  char a;
  bool achouCarac = false;
  unsigned char b;
  nodo *aux;
  int quantCaracteres, contCarac = 0, fimTable = 0;
  queue<char> fila;
  ofstream myfileOutput(nomeDescompact.c_str(), ofstream::binary);
  myfileInput.read(&a, 1);
  while (!myfileInput.eof())
  {
    if (a == '/')
    {
      break;
    }
    b = a;
    sequence += b;
    myfileInput.read(&a, 1);
  }
  myfileInput.read(&a, 1);
  while (!myfileInput.eof())
  {
    if (a == '|')
    {
      myfileInput.read(&a, 1);
      if (a == '|')
      {
        myfileInput.read(&a, 1);
        if (a == '|')
        {
          break;
        }
      }
    }
    myfileInput.read(&a, 1);
  }
  quantCaracteres = stoi(sequence);
  myfileInput.read(&a, 1);
  aux = arvore->getNodoRaiz();
  while (!myfileInput.eof())
  {
    b = a;
    bitset<8> bs3((int)b);
    sequence = bs3.to_string();
    for (int j = 0; j < sequence.length(); j++)
    {
      fila.push(sequence[j]);
    }
    while (!fila.empty())
    {
      if (contCarac == quantCaracteres)
      {
        break;
      }
      if (fila.front() == '0')
      {
        fila.pop();
        aux = aux->left;
        if (aux->left == 0 && aux->right == 0)
        {
          myfileOutput << aux->caractere;
          aux = arvore->getNodoRaiz();
          contCarac++;
        }
      }
      else if (fila.front() == '1')
      {
        fila.pop();
        aux = aux->right;
        if (aux->left == 0 && aux->right == 0)
        {
          myfileOutput << aux->caractere;
          aux = arvore->getNodoRaiz();
          contCarac++;
        }
      }
    }
    myfileInput.read(&a, 1);
  }
  myfileOutput.close();
  myfileInput.close();
  cout << "Concluido." << endl;
}