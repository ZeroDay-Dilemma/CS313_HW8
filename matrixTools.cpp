#include "matrixTools.h"

WMatrix::WMatrix(unsigned int rows, unsigned int cols,...) : rows(rows), cols(cols){
  total = rows * cols;
  data = new int[total];
  //int64_t* ptrArgs = (int64_t*)(&total+1); //after count is the args
  //unsigned int boundsCheck=0;
  //for(unsigned int i = 0; i < total; i++){
  //  std::cout<<"iterating, loop #"<<i<<std::endl;
  //  if(boundsCheck>=total){
  //    std::cerr<<" HIT END OF ARGS, PADDING WITH 0! \n";
  //    data[i]=0;
  //  }
  //  else{

  //    int value = *(ptrArgs + boundsCheck);
  //    data[i] = static_cast<int64_t>(value);
  //    std::cout<<value<<" -> "<<data[i]<<std::endl;
  //  }
  //  ++boundsCheck;

  //}

  va_list args;
  va_start(args, cols);
  for (unsigned int i = 0; i < total; ++i){
    //  for (unsigned int j = 0; j < cols; ++j)
    data[i]=va_arg(args, int);
  }
  va_end(args);
}
WMatrix::WMatrix(const WMatrix& other)
: rows(other.rows), cols(other.cols), total(other.total) {
  data = new int[total];
  for (unsigned int i = 0; i<total; ++i) {
    data[i] = other.data[i];
  }
}
int WMatrix::getSize(){
  return total;
}
bool WMatrix::rangeCheck(unsigned int row, unsigned int col){
  if( row >= rows || cols <= col){
    std::cout<<"INVALID INDEX PROVIDED!!"<<std::endl;
    return false;
  }
  return true;
}
void WMatrix::setter(unsigned int row, unsigned int col, int newVal){
  if(rangeCheck(row,col) == false) return; 
  data[row*cols+col]=newVal;
}
bool WMatrix::compareTo(WMatrix other){
  if(other.total != total){
    std::cout<<"INVALID COMPARISON, WRONG SIZE"<<std::endl;
    return false;
  }

  for (int i = 0; i < total; ++i){
    if(other._get(i) != _get(i)){
      std::cout<<"matrix are not the same!!"<<std::endl;
      return false;
    } 
  }
  std::cout<<"compared WMatrix are the same!!"<<std::endl;
  return true;
}
void WMatrix::_set(unsigned int index, int newVal){
  if(index >= total) return;
  data[index] = newVal;
}
int WMatrix::_get(int index){
  if(index >= total) return 0;
  return data[index];
}
void WMatrix::multi_mult(unsigned int index, int mult){
  if(index >= total) return;
  data[index] = data[index]*mult;
}


void WMatrix::mult(unsigned int row, unsigned int col, int mult, int newVal){
  if(rangeCheck(row,col)==false) return;
  setter(row,col,(mult*data[row*cols+col]) );
}

void WMatrix::_transpose(){
  rows ^= cols;
  cols ^= rows;
  rows ^= cols;
}
unsigned int WMatrix::getRows(){
  return rows;
}

unsigned int WMatrix::getCols(){
  return cols;
}
unsigned int WMatrix::getTotal(){
  return total;
}
void WMatrix::print() const{
  std::cout<<"matrix of size " << rows << " x " << cols << ", " << sizeof(data) << ", " << total << std::endl;
  for (unsigned int i = 0; i < total; ++i){
    //std::cout<<"matrix of size " << rows << " x " << cols << ", " << sizeof(data) << ", " << total << std::endl;
    if (i%cols==0)
      std::cout<<std::endl;
    std::cout<<data[i] << " ";

  }
  std::cout<<std::endl;
}

//WMatrix::~WMatrix(){
//  delete[] data;
//}


WMatrix WMatrix_utils::intMult(int scalar, WMatrix otherInput){
  WMatrix out = otherInput;
  int size = out.getSize();
  for(unsigned int i = 0; i < size; i++){
    out.multi_mult(i,scalar);
  }
  return out;


}
WMatrix WMatrix_utils::transpose(WMatrix& input) {
  //WMatrix out = input;
  //unsigned int rows = out.getRows();
  //unsigned int cols = out.getCols();
  //
  //int k = 0;
  //for(int i = 0; i < rows; i++){
  //  for (int j = 0; j < cols; j++){
  //    std::cout<<input._get(j*cols+i)<<std::endl;
  //    out._set(k++, (input._get(j*cols + i))  );
  //  }
  //}
  //out._transpose();
  ////out._transpose();
  //return out;
  //}
  unsigned int rows = input.getRows();
  unsigned int cols = input.getCols();

  WMatrix out(cols,rows);
  for (unsigned int i = 0; i < rows; i++) {
    for (unsigned int j = 0; j < cols; j++) {
      int val = input._get(i * cols + j);
      out._set(j * rows + i, val);
    }
  }

  return out;
}

WMatrix WMatrix_utils::mult_matrix(WMatrix A, WMatrix B){
  if(A.getRows() != B.getCols()){
    std::cout<<"INVALID MULTIPLICATION"<<std::endl;
    return WMatrix(0,0);
  }

  unsigned int n = A.getCols(); //devunsigned int m = A.getRows();
  unsigned int m = A.getCols(); // a cols = b rows so use for both
  unsigned int p = B.getCols();

  WMatrix result(A.getRows(), B.getCols());
  //std::cout<<"grgrngjrgorijg oirgnijrngoro ngrj"<<result.getRows()<<" "<<result.getCols()<<std::endl;

  for (unsigned int i = 0; i < m; i++) {
    for (unsigned int j = 0; j < p; j++) {
      int sum = 0;
      for (unsigned int k = 0; k < n; k++) {

        int aVal = A._get(i * n + k);
        int bVal = B._get(k * p + j);
        std::cout<<aVal<<" "<<bVal<<" ";
        sum += aVal * bVal;
      }
      std::cout<<"\nsum " << sum<<std::endl;
      result._set(i * p + j, sum);
    }
  }

  return result;

}
WMatrix WMatrix_utils::wmatrix_addition(WMatrix A, WMatrix B){
  std::cout<<"attempting to add: A, B"<<std::endl;
  A.print();
  B.print();
  //have to have same dimensions, then we can just like. add each index to each index
  if( A.getRows() != B.getRows() || A.getCols() != B.getCols() ){
    std::cout<<"INVALID DIMENSIONS FOR MATRIX ADDITION!"<<std::endl;
    return WMatrix(0,0);
  } 
  WMatrix outputAdd(A.getRows(), B.getCols());

  unsigned int iter = A.getTotal();
  for (unsigned int i = 0; i < iter; ++i){


    std::cout<<A._get(i)<<" + "<<B._get(i)<<" the 2 being added, on loop" <<i<<std::endl;
    outputAdd._set( i, (A._get(i) + B._get(i)));
  }
  return outputAdd;
}



//int main(){
//  WMatrix_utils tools;
//  WMatrix A(2,2,6,4,8,3);
//  A.print();
//  WMatrix B(2,3,1,2,3,4,5,6);
//  B.print();
//  WMatrix C(2,3,2,4,6,1,3,5);
//  C.print();
//  
//  std::cout<<"attempting A + (3*B) * C^T"<<std::endl;
//
//  WMatrix output = tools.wmatrix_addition(tools.mult_matrix((tools.intMult(3,B)), tools.transpose(C)),A);
//  output.print();
//
//  WMatrix outputValidate(2,2,90,70,200,150);
//  outputValidate.compareTo(output);
//  //WMatrix MultTest = tools.intMult(3,A);
//  //MultTest.print();
//  //WMatrix TransposeTest = tools.transpose(C);
//  //TransposeTest.print();
//  //std::cout<<"attempt to multiply:";
//  //B.print();
//  //TransposeTest.print();
//  //WMatrix twoMultTest = tools.mult_matrix(B,TransposeTest);
//  //twoMultTest.print();
//  //WMatrix addTest = tools.wmatrix_addition(A, twoMultTest);
//  //addTest.print();
//
//  return 0;
//}
