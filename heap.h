#include <iostream>
using namespace std;
template <class T>
class heap
{
  T *data;
  int n, m;
  void swap(int i, int j)
  {
    T x = data[i];
    data[i] = data[j];
    data[j] = x;
  }
  void _subir_(int i)
  {
    int j = (i - 1) / 2;
    if (i == 0)
      return;
    if (data[j] > data[i])
    {
      swap(i, j);
      _subir_(j);
    }
  }
  void _descer_(int i)
  {
    int j = 2 * i + 1;
    if (j > m - 1)
      return;
    if (j == m - 1)
    {
      if (data[i] > data[j])
        swap(i, j);
      _descer_(j);
    }
    else
    {
      int p = data[j] < data[j + 1] ? j : j + 1;
      if (data[i] > data[p])
      {
        swap(i, p);
        _descer_(p);
      }
    }
  }

public:
  heap(int n)
  {
    this->n = n;
    m = 0;
    data = new T[n];
  }
  void push(T x)
  {
    if (m == n)
      return;
    m++;
    data[m - 1] = x;
    _subir_(m - 1);
  }
  T pop()
  {
    if (m == 0)
      throw "HEAP UNDERFLOW";
    T x = data[0];
    data[0] = data[m - 1];
    m--;
    _descer_(0);
    return x;
  }
  int len() { return m; }
  int capacity() { return n; }
  T value(int i)
  {
    return data[i];
  }
  ~heap()
  {
    delete[] data;
  }
};
template <class T>
void heapsort(T *u, int n)
{
  heap<int> h(n);
  for (int i = 0; i < n; i++)
    h.push(u[i]);
  for (int i = 0; h.len() > 0; i++)
    u[i] = h.pop();
}