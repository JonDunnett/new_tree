#ifndef _SHAPES
#define _SHAPES

#include "Matrix.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Triangle {
	vector<float> pT,pL,pR,normal;
public:
	Triangle();
	Triangle(vector<float>& A, vector<float>& B, vector<float>& C);
	void print(ostream & output);
	void print();
	void calculate_normal();
};

class Rectangle {
	int L,W;
	vector<float> pTL, pBR, pTR, pBL,pO;
public:
	Rectangle();
	Rectangle(float L, float W);
	Rectangle(const Rectangle & old);
	void set_width(float w);
	void set_length(float l);
	void set_point(vector<float>& p, int s); // set point and which side 1->L, -1->R
	void rotate(float theta);       // rotate theta degrees
	void get_point(vector<float>& p,string point) const;
	void operator=(const Rectangle & old);
	void operator*(Matrix& M);
	Triangle* triangulateL();
	Triangle* triangulateU();
	void set_origin(vector<float>&p, float draw_angle);
	float get_length(); 
	float get_width();
};

#endif