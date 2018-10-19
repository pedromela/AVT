#pragma once
#ifndef ORANGE_H_
#define ORANGE_H_
#define PI 3.14159265

#include "Obstacle.h"
#include "math.h"
#include "basic_geometry.h"
#include "AVTmathLib.h"

class Orange : public Obstacle {
	double angle;
	double angleZ;
	int fall;
	int i;
	Material2 mate;
	float amb[4] = { 1.0f,0.11f,0.0f,1.0f };
	float diff[4] = { 0.88f,0.69f,0.0f,1.0f };
	float spec[4] = { 0.26f,0.46f,0.09f,1.0f };
	float pos[3] = { 0.0f, 0.0f, 0.0f };
	float emissive[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float shine = 65.0f;
	float shininess = 64.0f;
	int texcount = 0;

	GLUquadric *quad;

public:
	Orange();
	Orange(double x, double y, double z);
	Orange(double x, double y, double z, struct MyMesh *_mesh);

	~Orange();

	//	void draw(double _a);
	void draw();
	void update(double delta) override;

};

#endif
