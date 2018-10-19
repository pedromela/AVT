#include "Entity.h"


Entity::Entity() {}
Entity::~Entity() {}

Vector3* Entity::getPosition() {
	return &_position;
}

Vector3* Entity::setPosition(double x, double y, double z) {
	_position.set(x, y, z);

	return &_position;
}

Vector3* Entity::setPosition(const Vector3 &p) {
	_position = p;

	return &_position;
}
