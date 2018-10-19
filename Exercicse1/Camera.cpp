#include "Camera.h"



Camera::Camera(double near, double far) : _near(near), _far(far) {}
Camera::~Camera() {}

void Camera::update(unsigned long delta) {}

void Camera::update(double x, double y, double z) {}

void Camera::set(double cam) {}
void Camera::computeProjectionMatrix() {}
void Camera::computeVisualizationMatrix()
{
}
void Camera::setCar(Car *car_) {}

void Camera::setRaio(float r){}
