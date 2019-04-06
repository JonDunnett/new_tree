#include <vector>
#include "shapes.h"
#include "matrix.h"
#include <math.h>
#include <iostream>
#include <string>
#include <assert.h>

#define PI 3.14159265358979323

using namespace std;
void vcopy(vector<float>& A, const vector<float>& B);
void vcopy(vector<float>& A, vector<float>* B);


Triangle::Triangle() {
	pT.reserve(3);
	pL.reserve(3);
	pR.reserve(3);
	normal.reserve(3);
}

Triangle::Triangle(vector<float>& A, vector<float>& B, vector<float>& C) {
	pT.reserve(3);
	pL.reserve(3);
	pR.reserve(3);
	normal.reserve(3);
	vcopy(pT,A);
	vcopy(pL,B);
	vcopy(pR,C);
	calculate_normal();
}

void Triangle::calculate_normal() {
	normal[0] = (pT[1]*pL[2]) - (pT[2]*pL[1]);
	normal[1] = (pT[2]*pL[0]) - (pT[0]*pL[2]);
	normal[2] = (pT[0]*pL[1]) - (pT[1]*pL[0]);
}

void Triangle::print(ostream& output) {
	/* NEEDS FIXING */
	output << "facet normal " << normal[0] << " " << normal[1] << " " << normal[2] << endl;
	output << "\touter loop" << endl;
	output << "\t\tvertex " << pT[0] << " " << pT[1] << " " << pT[2] << endl;
	output << "\t\tvertex " << pL[0] << " " << pL[1] << " " << pL[2] << endl;
	output << "\t\tvertex " << pR[0] << " " << pR[1] << " " << pR[2] << endl;
	output << "\tendloop" << endl;
	output << "endfacet" << endl;
}

void Triangle::print() {
	/* NEEDS FIXING */
	int a =0;
	cout << "facet normal " << normal[0] << " " << normal[1] << " " << normal[2] << endl;
	cout << "\touter loop" << endl;
	cout << "\t\tvertex " << pT[0] << " " << pT[1] << " " << pT[2] << endl;
	cout << "\t\tvertex " << pL[0] << " " << pL[1] << " " << pL[2] << endl;
	cout << "\t\tvertex " << pR[0] << " " << pR[1] << " " << pR[2] << endl;
	cout << "\tendloop" << endl;
	cout << "endfacet" << endl;
}

Rectangle::Rectangle() {
	pTL.reserve(3);
	pBR.reserve(3);
	pTR.reserve(3);
	pBL.reserve(3);
	pO.reserve(3);
	for(short i=0;i<3;i++) {
		pBL[i]=0;
		pBR[i]=0;
		pTR[i]=0;
		pTL[i]=0;
	}
}

Rectangle::Rectangle(float l, float w) {
	W = w;
	L=l;
	pTL.reserve(3);
	pBR.reserve(3);
	pTR.reserve(3);
	pBL.reserve(3);
	pO.reserve(3);
}

void Rectangle::set_width (float w) {W = w;}
void Rectangle::set_length(float l) {L=l;}
float Rectangle::get_length() {return L;}
float Rectangle::get_width() {return L;}


void Rectangle::set_point(vector<float>& p, int s) {
	if (s>0) {
		vcopy(pBL,p);
		p[0] = p[0] + W;
		vcopy(pBR,p);
		p[1] = p[1] + L;
		vcopy(pTR,p);
		p[0] = p[0] - W;
		vcopy(pTL,p);
	} else {
		vcopy(pBR,p);
		p[0] = p[0] - W;
		vcopy(pBL,p);
		p[1] = p[1] + L;
		vcopy(pTL,p);
		p[0] = p[0] + W;
		vcopy(pTR,p);
	}
	pO[0] = pBL[0] + 0.5*W;
	pO[1] = pBL[1] + 0.5*L;
	pO[2] = 1;

}

void Rectangle::set_origin(vector<float>&p, float draw_angle) {
	vcopy(pO,p);
	float X,x1,y1,theta, thcn;

	thcn = atan((0.5*W)/(0.5*L)) * 180 / PI;
	theta = draw_angle - thcn;
	X = sqrt((0.5*W)*(0.5*W) + (0.5*L)*(0.5*L));
	x1 = X*sin(theta*PI/180);
	y1 = X*cos(theta*PI/180);

	pTR[0] = pO[0] - y1;
	pTR[1] = pO[1] + x1;
	pTR[2] = 1;

	pTL[0] = pO[0] - x1;
	pTL[1] = pO[1] + y1;
	pTL[2] = 1;

	pBR[0] = pO[0] + x1;
	pBR[1] = pO[1] - y1;
	pBR[2] = 1;

	pBL[0] = pO[0] + y1;
	pBL[1] = pO[1] - x1;
	pBL[2] = 1;
}


void Rectangle::get_point(vector<float>& p,string point) const{
	if (point == "BR") {
		vcopy(p,pBR);
	} else if (point == "BL") {
		vcopy(p,pBL);
	} else if (point == "TL") {
		vcopy(p,pTL);
	} else if (point == "TR") {
		vcopy(p,pTR);
	} else {
		vcopy(p,pO);
	}
}

void Rectangle::operator*(Matrix& M) {
	vector<float>* tmp;

	tmp = M*pBL;
	vcopy(pBL,tmp);
	delete tmp;

	tmp = M*pBR;
	vcopy(pBR,tmp);
	delete tmp;

	tmp = M*pTL;
	vcopy(pTL,tmp);
	delete tmp;

	tmp = M*pTR;
	vcopy(pTR,tmp);
	delete tmp;

	tmp = M*pO;
	vcopy(pO,tmp);
	delete tmp;

}

Rectangle::Rectangle(const Rectangle & old) {
	old.get_point(this->pBL,"BL");
	old.get_point(this->pBR,"BR");
	old.get_point(this->pTR,"TR");
	old.get_point(this->pTL,"TL");
}

void Rectangle::operator=(const Rectangle & old) {
	old.get_point(this->pBL,"BL");
	old.get_point(this->pBR,"BR");
	old.get_point(this->pTR,"TR");
	old.get_point(this->pTL,"TL");
}

Triangle* Rectangle::triangulateL() {
	Triangle* p = new Triangle(pTL, pBL, pBR);

	return p;
}

Triangle* Rectangle::triangulateU() {
	Triangle* p = new Triangle(pTL, pBR, pTR);

	return p;
}


void vcopy(vector<float>& A, const vector<float>& B) {
	for(short i=0;i<3;i++){
		A[i] = B[i];
	}
}

void vcopy(vector<float>& A, vector<float>* B) {
	for(short i=0;i<3;i++){
		A[i] = (*B)[i];
	}
}

/*
int main() {
	/* for testing * /

	Rectangle R(1.0,1.0);

	vector<float> point,result;
	point.reserve(3);
	result.reserve(3);
	point[0] = 1.0;
	point[1] = 1.0;
	point[2] = 1.0;



    R.set_point(point, 1);



	vector<float> a,b,c,d;
	a.reserve(3);
	b.reserve(3);
	c.reserve(3);
	d.reserve(3);

	R.get_point(a,"BR");
	R.get_point(b,"TL");
	R.get_point(c,"TR");
	R.get_point(d,"BL");


	cout << a[0] << "," << a[1] << "," << a[2] << endl;
	cout << b[0] << "," << b[1] << "," << b[2] << endl;
	cout << c[0] << "," << c[1] << "," << c[2] << endl;
	cout << d[0] << "," << d[1] << "," << d[2] << endl;



	Matrix M(1.0);
	M.rotate(90);


	R*M;

	R.get_point(a,"BR");
	R.get_point(b,"TL");
	R.get_point(c,"TR");
	R.get_point(d,"BL");


	cout << a[0] << "," << a[1] << "," << a[2] << endl;
	cout << b[0] << "," << b[1] << "," << b[2] << endl;
	cout << c[0] << "," << c[1] << "," << c[2] << endl;
	cout << d[0] << "," << d[1] << "," << d[2] << endl;


	return 0;
}
*/
