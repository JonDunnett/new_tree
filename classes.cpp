
struct  matrix_size {
  int rows;
  int cols;
};

class Matrix {
  float* data;
  matrix_size size;
  void mem_alloc(void);
public:
  Matrix()=0; // ctor but like don't use this
  Matrix(int rows, int cols); // ctor defining # of rows/ cols
  Matrix(matrix_size size);
  Matrix(const Matrix& copy); // copy ctor
  Matrix* operator*(const Matrix& other);
  matrix_size get_size(void);
};

Matrix::Matrix(int rows, int cols) {
  this->size.rows = rows;
  this->size.cols = cols;
  mem_alloc();
}

Matrix::Matrix(matrix_size in_size) {
  this->size.rows = in_size.rows;
  this->size.cols = in_size.cols;
  mem_alloc();
}

Matrix::Matrix(const Matrix& copy) {
  matrix_size copy_size = copy.get_size()
  this->size.rows = copy_size.rows;
  this->size.cols = copy_size.rows;
  mem_alloc();

}

void Matrix::mem_alloc(void) {

}

Matrix* Matrix::operator*(const Matrix& other) {

}

matrix_size Matrix::get_size(void) {

}
