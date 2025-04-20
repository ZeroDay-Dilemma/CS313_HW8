
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>


typedef unsigned int uint;
struct WMatrix{
  uint m_rows;
  uint m_cols;
  uint m_total;
  int data[];
};

void printWMatrix(struct WMatrix* matrix) {
  for (unsigned int i = 0; i < matrix->m_total; ++i) {
    if(i%matrix->m_cols == 0){
      printf("\n");
    }
    printf("%d ", matrix->data[i]);

  }
  printf("\n");
}
struct WMatrix* copyConstruct(struct WMatrix* matrix){
  uint totalSize = sizeof(struct WMatrix) + (matrix->m_total * sizeof(int));
  struct WMatrix* copy = malloc(totalSize);
  memcpy(copy,matrix, totalSize);
  return copy;
}

struct WMatrix* WMatrixGen(uint rows, uint cols,...){
  uint total = rows  * cols;
  struct WMatrix* out = malloc(sizeof(struct WMatrix) + total * sizeof(int));
  out->m_rows = rows;
  out->m_cols = cols;
  out->m_total = total;
  va_list args;
  va_start(args, cols);
  for (uint i = 0; i<total; ++i){
    out->data[i]=va_arg(args,int);
  }

  return out;
}
void safeSet(struct WMatrix* toSet, uint index, int value){
  if (index >= toSet->m_total){
    printf("ATTEMPTING TO SET OUTSIDE OF SAFE RANGE, FAILING");
    return;
  }
  toSet->data[index] = value;
}

int compareWMatrix(struct WMatrix* A, struct WMatrix* B){
  uint totalSizeA = sizeof(struct WMatrix) + A->m_total * sizeof(int);
  uint totalSizeB = sizeof(struct WMatrix) + B->m_total * sizeof(int);


  if(totalSizeA != totalSizeB){
    printf("found difference!!");
    return 0;
  }

  unsigned char* bytesA = (unsigned char*)A;
  unsigned char* bytesB = (unsigned char*)B;
  for (size_t i = 0; i < totalSizeA; ++i) {
    if((bytesB[i] != bytesA[i])){

      printf("found difference!");
      return 0;
    }
  }
  printf("identical matrix");
  return 1;

}



struct WMatrix* wmutil_intMult(struct WMatrix* input, int scalar){
  struct WMatrix* output = copyConstruct(input);
    int* dataAddr = output->data;  // pointer to the start of data[]
    for (uint i = 0; i < output->m_total; ++i) {
        dataAddr[i] *= scalar;
    }
  return output;
}

struct WMatrix* wmutil_transpose(struct WMatrix* input){
  struct WMatrix* output = copyConstruct(input);
  for(uint i = 0; i < output->m_rows; i++){
    for(uint j = 0; j < output->m_cols; j++){
      output->data[j*(output->m_rows)+i] = input->data[i*(input->m_cols)+j];
    
    }
  }
  output->m_rows ^= output->m_cols;
  output->m_cols ^= output->m_rows;
  output->m_rows ^= output->m_cols;
  return output;
}



struct WMatrix* wmutil_mult_matrix(struct WMatrix* A, struct WMatrix* B){
  if(A->m_rows != B->m_cols){
    printf("INVALID DIMENSIONS FOR OPERATION!"); 
    return A;
  }

  uint n = A->m_rows; //devunsigned int m = A.getRows();
  uint m = A->m_cols; // a cols = b rows so use for both
  uint p = B->m_cols;
  struct WMatrix* result = WMatrixGen(n,p);

  //std::cout<<"grgrngjrgorijg oirgnijrngoro ngrj"<<result.getRows()<<" "<<result.getCols()<<std::endl;

  for (uint i = 0; i < n; i++) {
    for (uint j = 0; j < p; j++) {
      int sum = 0;
      for (uint k = 0; k < m; k++) {

        int aVal = A->data[i * m + k];
        int bVal = B->data[k * p + j];
        sum += aVal * bVal;
        
      }
      result->data[i * p + j]= sum;
    }
  }
  return result;
}
struct WMatrix * wmutil_add_matrix(struct WMatrix* A, struct WMatrix* B){

  if( A->m_rows != B->m_rows || A->m_cols != B->m_cols ){
    printf("INVALID DIMENSIONS FOR MATRIX ADDITION!");
    return A;
  }
  
  struct WMatrix* result = WMatrixGen(A->m_rows,B->m_cols);
  uint iter = A->m_total;
  for (uint i = 0; i < iter; ++i){
    result->data[i] = (A->data[i] + B->data[i]);
  }
  return result;
}







int main(){
  int arrayLength = 4;
  struct WMatrix* G = malloc(sizeof(struct WMatrix) + arrayLength * sizeof(int));
  G->m_rows = 2;
  G->m_cols = 2;
  G->m_total = G->m_cols * G->m_rows;
  G->data[0] = 1;
  G->data[1] = 2;
  G->data[2] = 3;
  G->data[3] = 4;

  printWMatrix(G);
  struct WMatrix* A = WMatrixGen(2,2,6,4,8,3);
  printWMatrix(A);
  struct WMatrix* B = WMatrixGen(2,3,1,2,3,4,5,6);

  struct WMatrix* copyB = copyConstruct(A);
  printWMatrix(copyB);

  compareWMatrix(A,copyB);
  safeSet(copyB, 2, -999);
  printWMatrix(copyB);
  //test if actually safe 
  safeSet(copyB, 5, -999);
  printWMatrix(copyB);

  compareWMatrix(B,copyB);

  printf("Multiplying By 3:");
  printWMatrix(B);
  struct WMatrix* flatMultRes = wmutil_intMult(A,3);
  printWMatrix(flatMultRes);
  
  struct WMatrix* C = WMatrixGen(2,3,2,4,6,1,3,5);
  printWMatrix(C);
  struct WMatrix* C_Transpose = wmutil_transpose(C);
  printWMatrix(C_Transpose);

  struct WMatrix* B_multip = wmutil_intMult(B,3);
  printWMatrix(B_multip);
  printWMatrix(C_Transpose);
  struct WMatrix* B_C_out = wmutil_mult_matrix(B_multip,C_Transpose);
  printWMatrix(B_C_out);

  struct WMatrix* fullOut = wmutil_add_matrix(A,B_C_out);
  printWMatrix(fullOut);

  free(G);
  free(A);
  free(B);
  free(copyB);
  free(flatMultRes);
  free(C);
  free(B_multip);
  free(C_Transpose);
  free(B_C_out);
  free(fullOut);
  return 0;
}
