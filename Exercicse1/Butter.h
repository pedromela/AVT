#pragma once
#ifndef BUTTER_H_
#define BUTTER_H_
#include "Obstacle.h"
#include <math.h>

#define PI 3.14159265

class Butter : public Obstacle {
	double angle;
	float tamanho;

	Material2 mate;
	//Texture tex;
	float amb[4] = { 0.74f,0.74f,0.0f,1.0f };
	float diff[4] = { 0.5f,0.5f,0.4f,1.0f };
	float spec[4] = { 0.7f,0.7f,0.04f,1.0f };
	float shine = 10.0f;

public:
	Butter() { tamanho = 0.75; setRaio((tamanho*tamanho) + ((tamanho / 2)*(tamanho / 2))); }
	Butter(double x, double y, double z);
	Butter(double x, double y, double z, struct MyMesh *_mesh);

	~Butter() {}

	void draw();
	void draw(VSShaderLib shader, GLint vm_uniformId, GLint pvm_uniformId, GLint normal_uniformId) override;
	void update(double delta);
	double getAngle() { return angle; }

};

#endif