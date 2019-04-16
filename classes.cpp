#ifndef _CLASSES
#define _CLASSES

struct  matrix_size {
  int rows;
  int cols;
};

class Matrix {
  float** data;          // holds the values inside the matrix
  matrix_size size;      // struct containing the numer of rows and cols in matrix
  void mem_alloc(void);  // allocates memory for data
  void identity(void);   // sets this matrix to be identity matrix
public:
  Matrix();                                      // ctor but like don't use this
  Matrix(int rows, int cols);                    // ctor defining # of rows/ cols
  Matrix(matrix_size size);                      // ctor defining # of rows/ cols
  Matrix(const Matrix& copy);                    // copy ctor
  ~Matrix();                                     // default dtor
  Matrix operator*(const Matrix& other);         // operator overload matrix multiplication
  matrix_size get_size(void) const;              // gets matrix_size struct
  float get_value(int row, int col);             // get value at location
  void set_value(int row, int col, float value); // set value at location
};

Matrix::Matrix(int rows, int cols) {
// CTOR
// PRE : Two ints representing the number of rows and columns respectively
// POST: This matrix will have memory allocated and set to the identity matrix
//       of the given size
  this->size.rows = rows;
  this->size.cols = cols;
  mem_alloc();
  this->identity();
}

Matrix::Matrix(matrix_size in_size) {
// CTOR
// PRE : A matrix_size struct with initialized integer values
// POST: This matrix will be set to the identity matrix of the given size
  this->size.rows = in_size.rows;
  this->size.cols = in_size.cols;
  mem_alloc();
  this->identity();
}

Matrix::Matrix(const Matrix& copy) {
// Copy ctor
// PRE : An existing matrix; MUST have values
// POST: This matrix will be a copy of given matrix
  matrix_size copy_size = copy.get_size();
  this->size.rows = copy_size.rows;
  this->size.cols = copy_size.rows;
  mem_alloc();

}

Matrix::~Matrix() {
// dtor
// PRE : Matrix must have memory allocated for data
// POST: All memory freed
  for(short i=0;i<size.rows;i++) {
      free(data[i]);
  }
  free(data);
}

void Matrix::mem_alloc(void) {
// allocating memory for the values
// PRE : This matrix_size struct must be initialized with row and col values
// POST: Memory will be allocated based on the values in matrix_size struct
  data = (float**) malloc(sizeof(float*)*this->size.rows);
  for(short i=0;i<size.rows;i++){
    data[i] = (float*) malloc(sizeof(float)*size.cols);
  }
}

Matrix Matrix::operator*(const Matrix& other) {
// operator overload for matrix multiplication
// PRE : 
// POST: returns a matrix containing the result of matrix multiplication 
//       this matrix * other matrix 
  
}

matrix_size Matrix::get_size(void) const{
// gets this matrix's matrix_size struct
// PRE : matrix_size struct must be initialized with the size of the matrix
// POST: Returns matrix_size struct
}

void Matrix::identity(void) {
// initializes this matrix as identity matrix
// PRE : Memory allocated for data
// POST: Matrix will be identity matrix 
}


void Matrix::set_value(int row, int col, float value) {
// sets value at given location
// PRE : Data allocated for this object
// POST: value assigned to given location 
  data[row][col]=value;
}

#endif
