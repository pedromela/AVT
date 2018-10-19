#include "DynamicObject.h"

DynamicObject::DynamicObject() {
	setSpeed(0, 0, 0);
}
DynamicObject::~DynamicObject() {
}

void DynamicObject::update(double delta) {
	setPosition(getPosition()->getX() + getSpeed().getX() * delta / 1000,
		getPosition()->getY() + getSpeed().getY() * delta / 1000,
		getPosition()->getZ());
}
void DynamicObject::setSpeed(const Vector3 &speed) {
	_speed = speed;
}
void DynamicObject::setSpeed(double x, double y, double z) {
	if (x<0.01 && x>-0.01 && y<0.01 && y >-0.01)
		_speed.set(x, y, z);
}
Vector3 DynamicObject::getSpeed() {
	return _speed;
}
bool DynamicObject::HasSpeed() {
	if (_speed.getX() != 0 && _speed.getY() != 0)
		return true;
	return false;
}
void DynamicObject::setAcelaration(const Vector3 &acelaration) {
	_acelaration = acelaration;
}
void DynamicObject::setAcelaration(double x, double y, double z) {
	_acelaration.set(x, y, z);
}
Vector3 DynamicObject::getAcelaration() {
	return _acelaration;
}
