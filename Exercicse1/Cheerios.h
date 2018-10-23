#pragma once
#ifndef CHEERIOS_H_
#define CHEERIOS_H_


#include "Obstacle.h"

#define PI 3.14159265

class Cheerios : public Obstacle {

	Material2 mate;
	float amb[4] = { 0.93f,0.56f,0.0f,1.0f };
	float diff[4] = { 0.26f,0.27f,0.0f,1.0f };
	float spec[4] = { 0.22f,0.41f,0.23f,1.0f };
	float shine = 55.0f;
	Vector3 initPos;

public:
	Cheerios();
	Cheerios(double x, double y, double z);
	Cheerios(double x, double y, double z, struct MyMesh *_mesh);
	~Cheerios() {}

	void draw();
	void update(double delta);
	void returnToInitPos();

};

#endif