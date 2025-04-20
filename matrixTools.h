#ifndef MATRIX_TOOLS_H // include guard
#define MATRIX_TOOLS_H
#include <iostream>
#include <cstdarg>

class WMatrix {
private:
  int* data;
  unsigned int rows, cols, total;

public:
  WMatrix(unsigned int rows, unsigned int cols,...);
  WMatrix(const WMatrix& other);
  int getSize();
  bool rangeCheck(unsigned int row, unsigned int col);
  void setter(unsigned int row, unsigned int col, int newVal);
  bool compareTo(WMatrix other);
  void _set(unsigned int index, int newVal);
  int _get(int index);
  void multi_mult(unsigned int index, int mult);
  void mult(unsigned int row, unsigned int col, int mult, int newVal);
  void _transpose();
  unsigned int getRows();
  unsigned int getCols();
  unsigned int getTotal();
  void print() const;
  ~WMatrix(){
    delete[] data;
  }
};


class WMatrix_utils{

public:
  friend class WMatrix;
  WMatrix intMult(int scalar, WMatrix otherInput);
  WMatrix transpose(WMatrix& input); 
  WMatrix mult_matrix(WMatrix A, WMatrix B);
  WMatrix wmatrix_addition(WMatrix A, WMatrix B);
};

#endif /* MATRIX_TOOLS_H */
