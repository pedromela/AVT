#pragma once
#ifndef CAR_H_
#define CAR_H_
#define PI 3.14159265

#include "DynamicObject.h"
#include "Vector3.h"
#include <math.h>

class Car : public DynamicObject {
	double angle, angle_w;
	int UP, DOWN, RIGHT, LEFT;
	int vidas = 5;
	float escala;
	float largura;
	float comprimento;
	bool colidiu;
	bool lights;

	Material2 mate = Material2();
	float amb[4] = { 0.1745f,0.01175f,0.01175f,1.0f };
	float diff[4] = { 0.61424f,0.04136f,0.04136f,1.0f };
	float spec[4] = { 0.727811f,0.626959f,0.626959f,1.0f };
	float shine = 76.8f;

public:
	Car();
	Car(double x, double y, double z);
	Car(double x, double y, double z, struct MyMesh *mesh);
	~Car();

	void draw() override;
	void draw(VSShaderLib shader, GLint vm_uniformId, GLint pvm_uniformId, GLint normal_uniformId) override;
	void update(double delta) override;
	double getAngle();
	Vector3 getPosCar();
	void setAngle(double _a);
	void setDir(int up, int down, int right, int left);
	void setColidiu(bool bo);
	bool getColidou();
	void setVidas(int v);
	int  getVidas();
	void initLights();
	void onLights();
	void offLights();
};

#endif