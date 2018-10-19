#pragma once
#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include "Camera.h"
#include <math.h>

class PerspectiveCamera : public Camera {
	double _fovy;
	double _aspect;
	Car *car;
	float _r;
public:

	PerspectiveCamera(double fovy, double aspect, double zNear, double zFar);
	~PerspectiveCamera();

	void update(unsigned long delta) override;
	//void update(double x, double y, double z);
	void set(double cam, float ratio);
	void computeProjectionMatrix();
	void computeVisualizationMatrix();
	void computeProjectionMatrix(double cam, float ratio);
	void computeVisualizationMatrix(double cam);
	void setCar(Car *car_);
	void setRaio(float r) override;
};

#endif
