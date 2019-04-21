#ifndef _CLASSES
#define _CLASSES

#include <vector>
#include "functions.cpp"

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
  Matrix* operator*(const Matrix& other);        // operator overload matrix multiplication
  matrix_size get_size(void) const;              // gets matrix_size struct
  float get_value(int row, int col) const;       // get value at location
  void set_value(int row, int col, float value); // set value at location
};


class Triangle {
  std::vector<float>  A,B,C;
public:
  void calculate_normal(void);
  void output(/* output object */);
};

class Rectangle {
  std::vector<float> A,B,C,D; // representing the four verticies 

public:
  Rectangle();                // default ctor
  void transform(Matrix M);   // transform rectangle
  Triangle upper(void);       // get upper triangle 
  Triangle lower(void);       // get lower triangle
};

void  translate(Rectangle rect, const std::vector<Matrix> matrices);
std::vector<float> mult(const Matrix M, const std::vector<float> V); 


Matrix::Matrix() {
// default ctor
// PRE : Don't use it
// POST: just don't
}

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


Matrix* Matrix::operator*(const Matrix& other) {
// operator overload for matrix multiplication
// PRE : 
// POST: returns a matrix containing the result of matrix multiplication 
//       this matrix * other matrix 

// [This now just needs to be tested]
  if (this->size.rows== other.get_size().rows) {
    Matrix* res = new Matrix(other.get_size());
    if (this->size.cols == other.get_size().cols) {
      for (short i=0;i<this->size.cols;i++) {
        for (short j=0;i<this->size.cols;j++) {
          for (short k=0;i<this->size.cols;k++) {
            res->set_value(i,j, this->data[i][j] * other.get_value(k,j)); 
          }  
        } 
      }
    } else /* matrix x vector */ {
      for (short i=0;i<this->size.rows;i++) {
        float a=other.get_value(0,0)*this->data[i][0],
              b=other.get_value(1,0)*this->data[i][1],
              c=other.get_value(2,0)*this->data[i][2];
  
        res->set_value(i,0, a+b+c); 
      }
    }
    return res;
  } else { /* ERROR - incompatible sizes */ }
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
    for (short j=0;j<this->size.cols;j++) {
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
  //this->A = mult(M,this->A);
  //this->B = mult(M,this->B);
  //this->C = mult(M,this->C);
  //this->D = mult(M,this->D);
}

Rectangle::Rectangle() {
// default ctor
// PRE : 
// POST: Rectangle points initialized such that the rectangle 
//       center is at the origin
  // A -------------
  this->A.push_back(-1.0);
  this->A.push_back(1.0);
  this->A.push_back(0.0);
  // B -------------
  this->B.push_back(1.0);
  this->B.push_back(1.0);
  this->B.push_back(0.0);
  // C -------------
  this->C.push_back(1.0);
  this->C.push_back(-1.0);
  this->C.push_back(0.0);
  // D -------------
  this->D.push_back(-1.0);
  this->D.push_back(-1.0);
  this->D.push_back(0.0);
}

float Matrix::get_value(int row, int col) const {
// get value at location 
// PRE : Matrix initialized with data
// POST: value at given indicies returned
  return data[row][col]; 
}

Triangle Rectangle::upper(void) {
// get upper triangle
// PRE : Rectangle must be initialized with points
// POST: returns the lower triangle formed by the 
//       vertices of the rectangle 

} 

Triangle Rectangle::lower(void) {
// get lower triangle
// PRE : Rectangle must be initialized with points
// POST: returns the upper triangle formed by the 
//       vertices of the rectangle

}

void Triangle::output(/* output object */) {
// output the the points and normal in stl format
// PRE : This triangle must be initialize by a rectangle
// POST: Triangle data output to given obj in stl format

}

std::vector<float> mult(const Matrix M, const std::vector<float> V) {
// matrix multiplication matrix * vector
// PRE : Existing matrix M, vector V
// POST: Returns vector representing the result of M*V
  int size = 0;//M.get_size().rows;
  std::vector<float> res;
  float a,b,c;
  for(short i=0;i<size;i++) {
    //a = V[0]*M->get_value(i,0);
    //b = V[1]*M->get_value(i,1);
    //c = V[2]*M->get_value(i,2);

    //res.push_back(a+b+c); 
  }

  return res;  
}

void translate(Rectangle rect, const std::vector<Matrix> matrices) {
// translate rectangle using the series of matrices stored in vector 
// PRE : Rectangle rect must be initialized with points corresponding to
//       the desired starting point.  
// POST: Rectangle rect will be translated, this modifies the object! 
  Matrix* M; 
  for (short i=0;i<matrices.size();i++) {
    rect.transform(matrices[i]);        
  }
}

 
#endif
