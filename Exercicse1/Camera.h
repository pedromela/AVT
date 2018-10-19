#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "Entity.h"
#include "Vector3.h"
#include "Car.h"
#include <vector>
#include "AVTmathLib.h"

class Camera : public Entity {
	double _near;
	double _far;
	Vector3 _up;
	Vector3 _center;
	Vector3 _at;
	float _r = 5.0;
public:
	Vector3 eye;

	Camera(double near, double far);
	~Camera();

	virtual void update(unsigned long delta);
	virtual void update(double x, double y, double z);
	virtual void set(double cam);
	virtual void computeProjectionMatrix();
	virtual void computeVisualizationMatrix();
	virtual void setCar(Car *car_);
	virtual void setRaio(float r);
};

#endif