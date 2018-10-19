#pragma once
#ifndef VECTOR3_H
#define VECTOR3_H

#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
//#include "Header.h"

class Vector3 {
	double _x;
	double _y;
	double _z;
public:
	Vector3();
	Vector3(double x, double y, double z);
	~Vector3();

	double getX();
	double getY();
	double getZ();
	void set(double x, double y, double z);
	Vector3 operator=(const Vector3 &vec);
	Vector3 operator*(double num);
	Vector3 operator+(const Vector3 &vec);
	Vector3 operator-(const Vector3 &vec);

};
#endif

