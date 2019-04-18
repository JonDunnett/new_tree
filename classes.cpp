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


class Triangle {
  Matrix A,B,C;
public:
  void calculate_normal(void);
  void output(/* output object */);
};

class Rectangle {
  Matrix A,B,C,D; // representing the four verticies 

public:
  Rectangle();                // default ctor
  void transform(Matrix M);   // transform rectangle
  Triangle upper(void);       // get upper triangle 
  Triangle lower(void);       // get lower triangle
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

// [HEY JON THIS NEEDS TO GET DONE!!]
 
}

matrix_size Matrix::get_size(void) const{
// gets this matrix's matrix_size struct
// PRE : matrix_size struct must be initialized with the size of the matrix
// POST: Returns matrix_size struct
  return this->size;
}

void Matrix::identity(void) {
// initializes this matrix as identity matrix
// PRE : Memory allocated for data
// POST: Matrix will be identity matrix 
  for(short i=0;i<this->size.rows;i++) {
    for (short j=0;this->size.cols;j++) {
      if (i==j) {data[i][j] == 1.0;}
      else { data[i][j] == 0.0;}
    }
  }
}


void Matrix::set_value(int row, int col, float value) {
// sets value at given location
// PRE : Data allocated for this object
// POST: value assigned to given location 
  data[row][col]=value;
}

void Rectangle::transform(Matrix M) {
// transform rectangle specified by givem matrix M
// PRE : matrix must contain values (memory allocated)
// POST: rectangle will be transformed
  this->A = (this->A)*M;
  this->B = (this->B)*M;
  this->C = (this->C)*M;
  this->D = (this->D)*M;
}

Rectangle::Rectangle() {
// default ctor
// PRE : 
// POST: Rectangle points initialized such that the rectangle 
//       center is at the origin
  A = Matrix(3,1);
  B = Matrix(3,1);
  C = Matrix(3,1);
  D = Matrix(3,1);
  // A -------------
  A.set_value(0,0,-1.0);
  A.set_value(1,0,1.0);
  A.set_value(2,0,0.0);
  // B -------------
  B.set_value(0,0,1.0);
  B.set_value(1,0,1.0);
  B.set_value(2,0,0.0);
  // C -------------
  C.set_value(0,0,1.0);
  C.set_value(1,0,-1.0);
  C.set_value(2,0,0.0);
  // D -------------
  D.set_value(0,0,-1.0);
  D.set_value(1,0,-1.0);
  D.set_value(2,0,0.0);
}


#endif
