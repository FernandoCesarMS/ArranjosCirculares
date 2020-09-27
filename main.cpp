#include <iostream>
#include <stdlib.h>
#include "RingArray.h"

void fer_assert(const bool expr, const char *msg)
{
  if (!expr)
  {
    std::cout << msg << std::endl;
    exit(1);
  }
}

template <class T, unsigned N>
void RingArray<T, N>::add(T value)
{
  if (this->_size == 0)
  {
    this->_first = 0;
    this->_last = 0;
    this->buf[0] = value;
    this->_size++;
  }
  else if (this->_size > 0 && this->_size < N)
  {
    this->_last = this->_size;
    this->buf[this->_size] = value;
    this->_size++;
  }
  else
    throw "anel cheio.";
}

template <class T, unsigned N>
T RingArray<T, N>::get()
{
  T oldest = this->buf[this->_first];
  if (this->_size == 1)
  {
    this->_size--;
    return oldest;
  }
  else if (this->_size == 0)
  {
    throw "anel vazio.";
    return oldest;
  }

  else
  {
    this->_size--;
    for (int i = 0; i < this->_size; i++)
      this->buf[i] = this->buf[i + 1];
    return oldest;
  }
}

template <class T, unsigned N>
bool RingArray<T, N>::isFull() const
{
  if (this->_size >= N - 1)
    return true;
  else
    return false;
}

template <class T, unsigned N>
bool RingArray<T, N>::isEmpty() const
{
  if (this->_size == 0)
    return true;
  else
    return false;
}

template <class T>
void test_add_then_get()
{
  RingArray<T, 8> r;
  T value;
  while (std::cin >> value)
  {
    r.add(value);
  }
  while (!r.isEmpty())
  {
    std::cout << r.get() << std::endl;
  }
}

template <class T>
void test_add_or_get()
{
  RingArray<T, 8> r;
  T value;
  char c;
  while (std::cin >> c)
  {
    if (c == '+')
    {
      std::cin >> value;
      r.add(value);
    }
    else if (c == '-')
    {
      std::cout << r.get() << std::endl;
    }
    else
    {
      std::cout << "Invalid operation\n";
    }
  }
}

int main()
{
  try
  {
    char data;
    while (std::cin >> data)
    {
      switch (data)
      {
      case 'd':
        test_add_then_get<double>();
        break;
      case 's':
        test_add_then_get<std::string>();
        break;
      case 'D':
        test_add_or_get<double>();
        break;
      case 'S':
        test_add_or_get<std::string>();
        break;
      default:
        std::cout << "Invalid type\n";
      }
    }
  }
  catch (const char *e)
  {
    std::cerr << "Erro: " << e << std::endl;
  }
  catch (...){
    std::cerr << "Erro Inesperado" << std::endl;
  }
  return 0;
}
