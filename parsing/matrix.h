#ifndef _MATRIX
#define _MATRIX

#include <vector>
#include <string>

using namespace std;

class Matrix {
	float** data;
public:
	Matrix(float X);
	Matrix(const Matrix& old);
	~Matrix();
	void print();
	void set_val(float val, int x,int y);
	float get_val(int x, int y) const ;
	void operator() (vector<float>& V, vector<float>& result);
	Matrix* operator*(Matrix& M);
	int operator==(Matrix& M);
	void scalex(float scale);
	void scaley(float scale);
	void scale(float x, float y);
	void rotate(float theta);
	void shiftx(float shift);
	void shifty(float shift);
	void shift(float x, float y);
	void shift_on_angle(float x, float theta);
	vector<float>* operator*(vector<float>& V);
	void operator=(Matrix* old);
};



#endif
