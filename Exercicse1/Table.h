#pragma once
#include "Obstacle.h"
class Table :
	public Obstacle {
	
	double angle;
	float tamanho;

	Material2 mate;
	//Texture tex;
	float amb[4] = { 0.74f,0.74f,0.0f,1.0f };
	float diff[4] = { 0.5f,0.5f,0.4f,1.0f };
	float spec[4] = { 0.7f,0.7f,0.04f,1.0f };
	float shine = 10.0f;
public:
	Table();
	Table(double x, double y, double z);
	Table(double x, double y, double z, struct MyMesh *_mesh);

	~Table();

	void draw();
	void update(double delta);
	double getAngle() { return angle; }
};

