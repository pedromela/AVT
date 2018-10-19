#include "OrthogonalCamera.h"

OrthogonalCamera::OrthogonalCamera(double left, double right, double bottom, double top, double near2, double far2) : Camera(near2, far2), _left(left), _right(right), _bottom(bottom), _top(top) {}
OrthogonalCamera::~OrthogonalCamera() {}

void OrthogonalCamera::update() {}

void OrthogonalCamera::set(double cam) {
	computeProjectionMatrix();
	computeVisualizationMatrix();
}
void OrthogonalCamera::computeProjectionMatrix() {
	loadIdentity(PROJECTION);
	ortho(-2.0f, 21.0f, -2.0f, 21.0f, -40.0f, 40.0f);

}
void OrthogonalCamera::computeVisualizationMatrix() {
}