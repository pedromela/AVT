#pragma once
#ifndef ORTHOGONALCAMERA_H
#define ORTHOGONALCAMERA_H

#include "Camera.h"

class OrthogonalCamera : public Camera {
	double _left;
	double _right;
	double _bottom;
	double _top;
public:
	OrthogonalCamera(double left, double right, double bottom, double top, double near, double far);
	~OrthogonalCamera();

	void update();
	void set(double cam);
	void computeProjectionMatrix();
	void computeVisualizationMatrix();
};

#endif
