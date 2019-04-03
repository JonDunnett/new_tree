// Parse.cpp
#include "shapes.h"
//#include "Tree.h"
#include "matrix.h"
#include <stack>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <assert.h>
#include <string>
#include <string.h>



using namespace std;


int main(int argc, char ** argv) {
	FILE * fp;
	fstream fout;
	fout.open("test.stl",fstream::out);
	fp = fopen("output_tree.trf","r");

	fout << "solid Tree" << endl;

	//stack<Matrix> T;
	/* --------------------------------------------- */
	stack<Rectangle*> R;
	float draw_angle=0.0, _ANGLE, _LENGTH, _WIDTH,
		  angle, length, width, s;
	char c, sign, angle_char,length_char,width_char;
	string read;
	if (argc == 4){
		if (strlen(argv[1]) == 2) {
			_ANGLE  = ((argv[1][0] - '0') * 10) + (argv[1][1] - '0');
		} else {
			_ANGLE  = argv[1][0] - '0';
		}
		_LENGTH = argv[2][0] - '0';
	    _WIDTH  = argv[3][0] - '0';
	}
	/*----------------------------------------------- */

	Rectangle* newRect = new Rectangle, *old;
	vector<float> zero(3,0);
	zero[2] = 1;
	vector<float> one(3,1);
	vector<float> negone(3,-1);
	Matrix SA(1),SO(1),RC(1),SB(1),F(1);
	vector<float> origin;
	origin.reserve(3);

	/*------------------------------------------------ */

	fscanf(fp,"%c%c%c%c%c",&sign,&angle_char,&length_char,&width_char,&c);
	angle  = angle_char - '0';
	length = length_char - '0';
	width  = width_char - '0';
	if (sign == '+') {
		s = 1;
	} else {
		s = -1;
	}
	/* ------------------------------------------------- */
	if (R.empty()) {
		newRect->set_length(length);
		newRect->set_width(width);
		one = zero;
		newRect->set_point(zero,1);
		(newRect->triangulateL())->print(fout);
		(newRect->triangulateU())->print(fout);
		R.push(newRect);
	}


	while (1) {

		if (c == ']') {
			R.pop();
		} else if (c == '[') {
			/* ====================================== */
			fscanf(fp,"%c%c%c%c",&sign,&angle_char,&length_char,&width_char);
			angle  = angle_char - '0';
			length = length_char - '0';
			width  = width_char - '0';
			if (sign == '+') {s = 1;} else {s = -1;}
			/* ====================================== */
			old = R.top();
			draw_angle = s*angle*_ANGLE;
			newRect = new Rectangle;
			newRect->set_length(length);
			newRect->set_width(width);

			if(s==1) {
				old->get_point(origin,"TL");
				newRect->set_point(origin,s);
				newRect->get_point(one,"BL");
			} else {
				old->get_point(origin,"TR");
				newRect->set_point(origin,s);
				newRect->get_point(one,"BR");
			}

			SO.shift(-1*one[0],-1*one[1]);
			RC.rotate(draw_angle);
			SB.shift(one[0],one[1]);

			(*newRect)*SO;
			(*newRect)*RC;
			(*newRect)*SB;

			(newRect->triangulateL())->print(fout);
			(newRect->triangulateU())->print(fout);


			R.push(newRect);


		} else if (c == ';') {
			return 0;
		}





		fscanf(fp,"%c",&c);
		//R.push(newRect);

	/*
	newRect.get_point(negone,"TL");
	cout << negone[0] << "," << negone[1] << "," << negone[2] << endl;
	zero = negone;
	old.set_point(negone,1);
	negone = zero;
	one_more.set_point(negone,1);
	newRect.get_point(negone,"TR");





	//SO.shift(-1*zero[0],-1*zero[1]);
	//cout << -1*negone[0] << -1*negone[1] << endl;
	//SB.shift(zero[0],zero[1]);
	//RC.rotate(40);
	//old*SO;
	//old*RC;
	//old*SB;



	/* make triangle * /
		vector<float> T1,T2,T3;
		T1.reserve(3);
		T2.reserve(3);
		T3.reserve(3);

		newRect.get_point(T1,"TL");
		old.get_point(T2,"BL");
		newRect.get_point(T3,"TR");

		Triangle poop(T1,T2,T3);



/*   print
*/	//(old.triangulateU())->print(fout);
	//(old.triangulateL())->print(fout);

		//poop.print(fout);
	}

	/*(one_more.triangulateL())->print(fout);
	(one_more.triangulateU())->print(fout);


	//(Triangle(zero,one,negone)).print(cout);

	//Triangle* Twizzel = new Triangle(zero,one,negone);

	//Twizzel->print(cout);

	*/
	fout << "endsolid Tree";
	return 0;
}
