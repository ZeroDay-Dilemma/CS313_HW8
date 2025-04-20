#include "matrixTools.h"



int main(){
  WMatrix_utils tools;
  WMatrix A(2,2,6,4,8,3);
  A.print();
  WMatrix B(2,3,1,2,3,4,5,6);
  B.print();
  WMatrix C(2,3,2,4,6,1,3,5);
  C.print();

  std::cout<<"multiplying by 3"<<std::endl;
  A.print();
  WMatrix MultTest = tools.intMult(3,A);
  MultTest.print();

  std::cout<<"transposing matrix"<<std::endl;
  C.print();
  WMatrix TransposeTest = tools.transpose(C);
  TransposeTest.print();

  std::cout<<"attempt to multiply 2 matrix:"<<std::endl;
  B.print();
  TransposeTest.print();
  WMatrix twoMultTest = tools.mult_matrix(B,TransposeTest);
  twoMultTest.print();
  std::cout<<"adding 2 matrix"<<std::endl;
  A.print();
  twoMultTest.print();
  WMatrix addTest = tools.wmatrix_addition(A, twoMultTest);
  addTest.print();



  
  std::cout<<"attempting A + (3*B) * C^T"<<std::endl;

  WMatrix output = tools.wmatrix_addition(tools.mult_matrix((tools.intMult(3,B)), tools.transpose(C)),A);
  output.print();

  WMatrix outputValidate(2,2,90,70,200,150);
  outputValidate.compareTo(output);


  return 0;
}
