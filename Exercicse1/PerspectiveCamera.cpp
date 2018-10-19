#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(double fovy, double aspect, double zNear, double zFar) : Camera(zNear, zFar) {
	_fovy = fovy;
	_aspect = aspect;
	setPosition(0, 0, 0);
}
PerspectiveCamera::~PerspectiveCamera() {}

void PerspectiveCamera::update(unsigned long delta) {
	eye.set(car->getPosition()->getX() - cos((PI*car->getAngle()) / 180)*_r, 3, car->getPosition()->getY() - sin((PI*car->getAngle()) / 180)*_r);
	//setPosition(eye.getX(),eye.getY(),eye.getZ());
	printf("car angle : %f\n", car->getAngle());
	printf("cos car angle : %f\n", cos((PI*car->getAngle())));
	printf("r : %f\n", _r);


}

void PerspectiveCamera::set(double cam, float ratio) {
	computeProjectionMatrix(cam, ratio);
	//computeVisualizationMatrix(cam);
}

void PerspectiveCamera::computeProjectionMatrix(double cam, float ratio) {
	if (cam == 2) {
		loadIdentity(PROJECTION);
		perspective(53.13f, ratio, 0.1f, 1000.0f);
		printf("PERSPECTIVE CAMERA\n");
	}
	if (cam == 3) {
		
	}
}
void PerspectiveCamera::computeVisualizationMatrix(double cam) {
	if (cam == 2) {
		//lookAt(10, 27, 20, 10, 5, -10, 0, 0, 1);
		//loadIdentity(MODEL);
		//loadIdentity();
	}
	if (cam == 3) {
		//eye.set(car->getPosCar().getX() - cos((PI*car->getAngle()) / 180) * 3, car->getPosCar().getY() + 1 - sin((PI*car->getAngle()) / 180) * 3, 3);
		//lookAt(eye.getX(), eye.getY(), eye.getZ(), eye.getX() + cos((PI*car->getAngle()) / 180), eye.getY() + sin((PI*car->getAngle()) / 180), eye.getZ() - 0.5, 0, 0, 1);
		//MatrixMode(MODEL);
		//loadIdentity();
	}

}

void PerspectiveCamera::setCar(Car *car_) {
	car = car_;
}
void PerspectiveCamera::setRaio(float r)
{
	_r = r;
}
void PerspectiveCamera::computeProjectionMatrix() {}
void PerspectiveCamera::computeVisualizationMatrix() {}
