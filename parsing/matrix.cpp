#include <iostream>
#include <vector>
#include <assert.h>
#include "Shapes.h"
#include "Matrix.h"
#include <math.h>
using namespace std;

#define PI 3.14159265358979323 /* helps to know a lot of pi */

Matrix::Matrix(float X) {
	data = new float*[3];
	for(short i=0;i<3;i++) {data[i] = new float[3];}

	for(short i=0;i<3;i++){
		for(short j=0;j<3;j++){
			if (i==j) {
				data[i][j] = X;
			} else {
				data[i][j] = 0;
			}
		}
	}
}

Matrix::Matrix(const Matrix& old) {
	data = new float*[3];
	for(short i=0;i<3;i++) {data[i] = new float[3];}

	for(short i=0;i<3;i++) {
		for (short j=0;j<3;j++) {
			this->data[i][j] = old.get_val(i,j);
		}
	}
}

Matrix::~Matrix(){
	for(short i=0;i<3;i++) { delete data[i];}
}

void Matrix::print() {
	for(short i=0;i<3;i++){
		for(short j=0;j<3;j++){
			cout << data[i][j] << "   ";
		}
		cout << endl;
	}
}

void Matrix::set_val(float val, int x, int y){
	data[x][y] = val;
}

float Matrix::get_val(int x, int y) const {
	return data[x][y];
}

void Matrix::scalex(float scale) {
	data[0][0] = scale;
}

void Matrix::scaley(float scale){
	data[1][1] = scale;
}

void Matrix::scale(float x, float y) {
	data[0][0] = x;
	data[1][1] = y;
}

void Matrix::rotate(float theta) {
	data[0][0] = cos(theta*PI/180);
	data[0][1] = (-1)*sin(theta*PI/180);
	data[1][0] = sin(theta*PI/180);
	data[1][1] = cos(theta*PI/180);
}

void Matrix::shiftx(float x) {
	data[0][2] = x;
}

void Matrix::shifty(float y) {
	data[1][2] = y;
}

void Matrix::shift(float x, float y) {
	data[0][2] = x;
	data[1][2] = y;
}

void Matrix::shift_on_angle(float X, float theta) {
	data[0][2] = X*sin(theta*PI/180);
	data[1][2] = X*cos(theta*PI/180);
}

void Matrix::operator() (vector<float>& V, vector<float>& result) {
	for(short i=0;i<3;i++){
		result[i] = V[0]*data[i][0] + V[1]*data[i][1] + V[2]*data[i][2];
	}
}

vector<float>* Matrix::operator*(vector<float>& V){
	vector<float>* result = new vector<float>(3);
	for(short i=0;i<3;i++){
		float tmp = V[0]*data[i][0] + V[1]*data[i][1] + V[2]*data[i][2];
		result->insert(result->begin()+i,tmp);
	}
	return result;
}

Matrix* Matrix::operator*(Matrix& M) {
	Matrix* NEW = new Matrix(0);
	float tmp;
	for(short i=0;i<3;i++){
		for(short j=0;j<3;j++){
			for(short k=0;k<3;k++){
				tmp = data[i][k] * M.get_val(k,j);
				tmp += NEW->get_val(i,j);
				NEW->set_val(tmp,i,j);
			}
		}
	}
	return NEW;
}

void Matrix::operator=(Matrix* old) {
	for(short i=0;i<3;i++) {
		for (short j=0;j<3;j++) {
			this->data[i][j] = old->get_val(i,j);
		}
	}
}

int Matrix::operator==(Matrix& M) {
	int match=1;
	for(short i=0;i<3;i++){
		for(short j=0;j<3;j++){
			if (!(data[i][j] == M.get_val(i,j))) {
				return 0;
			}
		}
	}

	return 1;
}

/*
int main() {

	Matrix T(1);
	int k=0;
	for(short i=0;i<3;i++){
		for(short j=0;j<3;j++){
			k++;
			T.set_val(k,i,j);
		}
	}

	T.print();

	cout << endl << endl;

	vector<float> X(3);
	X[0]=10;
	X[1]=11;
	X[2]=12;

	vector<float>* result = T*X;

	Matrix A(1),P(1),L(1);

	assert(1==1);
	assert(A*T==T);
	assert(A*A==A);

	(T*T).print();


	Matrix F(1.0),
	       r(1.0),
	       tO(1.0),
	       tBa(1.0),
	       tBr(1.0);

	F = r*tO*tBa*tBr;

	F.print();



	return 0;
}
*/
