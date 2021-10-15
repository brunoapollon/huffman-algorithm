#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <stack>
#include <queue>
#include <bitset>
#include "heap.h"
#include "tree.h"

nodo CreateTreeCompact(string arquivo){
  int vet[256];

  for (int i = 0; i < 256; i++){
    vet[i] = 0;
  }

  int ichar;
  char aux;
  unsigned char charAux;

  ifstream myfile(arquivo.c_str(), ifstream::binary);
  myfile.read(&aux, 1);

  while (!myfile.eof()){
    charAux = aux;
    ichar = (int)charAux;
    for (int i = 0; i < 256; i++){
      if (ichar == i){
        vet[i]++;
      }
    }
    myfile.read(&aux, 1);
  }

  myfile.close();

  int tamHeap = 0, cont = 0;
  for (int i = 0; i < 256; i++){
    if (vet[i] != 0){
      tamHeap++;
    }
  }
  stack<nodo> pilha;
  for (int i = 0; i < 256; i++){
    if (vet[i] != 0){
      nodo no(vet[i], i);
      pilha.push(no);
      cont++;
    }
  }
  
  heap<nodo> heapAux(cont);
  for (int i = 0; i < cont; i++){
    heapAux.push(pilha.top());
    pilha.pop();
  }

  nodo lAux, rAux;
  while (heapAux.len() > 1){
    lAux = heapAux.pop();
    rAux = heapAux.pop();
    nodo no(&lAux, &rAux);
    heapAux.push(no);
  }

  rAux = heapAux.pop();
  nodo retorno = new nodo(rAux);

  return retorno;
}


nodo *CreateTreeDescompact(string arquivo){

  int contStop = 0, contBarras = 0, contPontoVirgulas = 0;
  char aux;
  unsigned char bAux, caracAnterior, posTabela;
  string vetor[256], sequence = "";

  for (int i = 0; i < 256; i++){
    vetor[i] = "";
  }

  nodo *retorno = new nodo();
  ifstream myfile(arquivo.c_str(), ifstream::binary);
  myfile.read(&aux, 1);

  while (!myfile.eof()){
    bAux = aux;

    if (contBarras > 1){
      if (caracAnterior == '/'){
        posTabela = bAux;
        myfile.read(&aux, 1);
        myfile.read(&aux, 1);
        caracAnterior = aux;
        continue;
      }
      else{
        if (bAux != '/' || bAux != '|'){
          if (bAux == '|'){
            contStop++;
          }
          else if (bAux == '/'){
            vetor[(int)posTabela] = sequence;
            sequence = "";
          }
          else{
            sequence += bAux;
          }
        }
      }
    }

    if (bAux == '/'){
      contBarras++;
    }
    if (contStop == 3){
      vetor[(int)posTabela] = sequence;
      break;
    }
    caracAnterior = aux;
    myfile.read(&aux, 1);
  }

  for (int i = 0; i < 256; i++){
    nodo *aux = retorno;
    sequence = vetor[i];

    for (int j = 0; j < sequence.length(); j++){
      if (sequence[j] == '0'){
        if (aux->left == 0){
          nodo *temp = new nodo();
          aux->left = temp;
          aux = aux->left;
        }
        else{
          aux = aux->left;
        }
      }
      else{
        if (aux->right == 0){
          nodo *temp = new nodo();
          aux->right = temp;
          aux = aux->right;
        }
        else{
          aux = aux->right;
        }
      }
      if (j + 1 == sequence.length()){
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



string retornaArqSaida(string nomeArquivo){
  string newName = "";
  for (int j = 0; j < nomeArquivo.length(); j++){
    if (nomeArquivo[j] == '.'){
      break;
    }
    newName += nomeArquivo[j];
  }

  newName += ".bruno";
  return newName;
}

string retornaExtensaoArq(string nomeArquivo){

  string ext = "";
  int pos;

  for (int j = 0; j < nomeArquivo.length(); j++){
    if (nomeArquivo[j] == '.'){
      pos = j;
    }
  }

  for (int j = pos + 1; j < nomeArquivo.length(); j++){
    ext += nomeArquivo[j];
  }

  return ext;
}


string retornaNome(string nomeArquivo){
  string nome = "";
  int pos;

  for (int j = 0; j < nomeArquivo.length(); j++){
    if (nomeArquivo[j] == '.'){
      pos = j;
    }
  }
  for (int j = 0; j < pos; j++){
    nome += nomeArquivo[j];
  }

  nome += ".";
  char aux;
  unsigned char bAux;
  int contBarras = 0;
  ifstream myfile(nomeArquivo.c_str(), ifstream::binary);
  myfile.read(&aux, 1);

  while (!myfile.eof()){
    bAux = aux;
    if (contBarras > 0){
      if (bAux == '/'){
        break;
      }
      nome += bAux;
    }

    if (bAux == '/'){
      contBarras++;
    }

    myfile.read(&aux, 1);
  }

  myfile.close();
  return nome;
}


int quantidadePosComValor(string vet[]){
  int cont = 0;

  for (int i = 0; i < 256; i++){
    if (vet[i] != ""){
      cont++;
    }
  }

  return cont;
}
void compactar(string nomeArquivo){
  ifstream myFileInput(nomeArquivo.c_str(), ifstream::binary);

  if (!myFileInput){
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

  for (int i = 0; i < 256; i++){
    if (vetor[i] != ""){
      cont++;
      myFileOutput << (char)i << ';';
      by = vetor[i];
      for (int j = 0; j < by.length(); j++){
        myFileOutput << by[j];
      }
      if (cont == tamTabela){
        myFileOutput << '|' << '|' << '|';
      }
      else{
        myFileOutput << '/';
      }
    }
  }

  char aux;
  unsigned char bAux;
  queue<char> fila;
  cont = 0;
  myFileInput.read(&aux, 1);

  while (!myFileInput.eof()){
    bAux = aux;
    sequence = "";

    for (int i = 0; i < 256; i++){
      if (bAux == i){
        cont++;
        sequence = vetor[i];

        for (int j = 0; j < sequence.length(); j++){
          fila.push(sequence[j]);
        }
      }
    }

    while (fila.size() > 7){
      sequence = "";
      for (int i = 0; i < 8; i++){
        sequence += fila.front();
        fila.pop();
      }
      for (int i = 0, j = sequence.length() - 1; i < sequence.length(); i++, j--){
        if (sequence[j] == '1'){
          soma += pow(2, i);
        }
      }

      myFileOutput << (char)soma;
      soma = 0;
    }

    myFileInput.read(&aux, 1);
  }

  int tamFila;

  if (fila.size() < 8){
    tamFila = fila.size();
    sequence = "";

    while (!fila.empty()){
      sequence += fila.front();
      fila.pop();
    }
    for (int i = tamFila; i < 8; i++){
      sequence += '0';
    }

    for (int i = 0, j = sequence.length() - 1; i < sequence.length(); i++, j--){
      if (sequence[j] == '1'){
        soma += pow(2, i);
      }
    }

    myFileOutput << (char)soma;
  }

  myFileOutput.close();
  myFileInput.close();

  cout << "concluido." << endl;
}


void descompactar(string nomeArquivo){
  ifstream myfileInput(nomeArquivo.c_str(), ifstream::binary);

  if (!myfileInput){
    cout << "Arquivo Inexistente!!" << endl;
    return;
  }

  cout << "Descompactando o arquivo..." << endl;

  tree *arvore = new tree(CreateTreeDescompact(nomeArquivo));
  string nomeDescompact = retornaNome(nomeArquivo), sequence = "";
  char aux;
  bool achouCarac = false;
  unsigned char bAux;
  nodo *no;
  int quantCaracteres, contCarac = 0, fimTable = 0;
  queue<char> fila;
  ofstream myfileOutput(nomeDescompact.c_str(), ofstream::binary);
  myfileInput.read(&aux, 1);
  while (!myfileInput.eof()){
    if (aux == '/'){
      break;
    }
    bAux = aux;
    sequence += bAux;
    myfileInput.read(&aux, 1);
  }
  myfileInput.read(&aux, 1);
  while (!myfileInput.eof()){
    if (aux == '|'){
      myfileInput.read(&aux, 1);

      if (aux == '|'){
        myfileInput.read(&aux, 1);
        if (aux == '|')
        {
          break;
        }
      }
    }

    myfileInput.read(&aux, 1);
  }
  quantCaracteres = stoi(sequence);
  myfileInput.read(&aux, 1);
  no = arvore->getNodoRaiz();

  while (!myfileInput.eof()){
    bAux = aux;
    bitset<8> bs3((int)bAux);
    sequence = bs3.to_string();
    for (int j = 0; j < sequence.length(); j++){
      fila.push(sequence[j]);
    }

    while (!fila.empty()){
      if (contCarac == quantCaracteres){
        break;
      }
      if (fila.front() == '0'){
        fila.pop();

        no = no->left;
        if (no->left == 0 && no->right == 0){
          myfileOutput << no->caractere;
          no = arvore->getNodoRaiz();
          contCarac++;
        }
      }
      else if (fila.front() == '1'){
        fila.pop();
        no = no->right;

        if (no->left == 0 && no->right == 0){

          myfileOutput << no->caractere;
          no = arvore->getNodoRaiz();
          contCarac++;
        }
      }
    }
    myfileInput.read(&aux, 1);
  }

  myfileOutput.close();
  myfileInput.close();
  cout << "Concluido." << endl;
}