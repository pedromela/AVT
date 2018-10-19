#pragma once
#ifndef DYNAMICOBJECT_H
#define DYNAMICOBJECT_H

#include "GameObject.h"
#include "Vector3.h"

class DynamicObject : public GameObject {
	Vector3 _speed;
	Vector3 _acelaration;
public:
	DynamicObject();
	~DynamicObject();
	virtual void update(double delta);
	void setSpeed(const Vector3 &speed);
	void setSpeed(double x, double y, double z);
	bool HasSpeed();
	void setAcelaration(const Vector3 &acelaration);
	void setAcelaration(double x, double y, double z);
	Vector3 getSpeed();
	Vector3 getAcelaration();
};

#endif
