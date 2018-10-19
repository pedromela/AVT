#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Entity.h"
#include "Material2.h"
#include "Texture.h"
#include "basic_geometry.h"
//#include "vsShaderLib.h"
#include "AVTmathLib.h"

/// The storage for matrices
extern float mMatrix[COUNT_MATRICES][16];
extern float mCompMatrix[COUNT_COMPUTED_MATRICES][16];

/// The normal matrix
extern float mNormal3x3[9];

class GameObject : public Entity {
	double _xm, _xM, _ym, _yM;
	double raio, collision_agle;
	int _tex;
	VSShaderLib shader;
	GLint pvm_uniformId;
	GLint vm_uniformId;
	GLint normal_uniformId;

public:
	struct MyMesh *mesh;

	GameObject();
	~GameObject();

	virtual void draw(double angle);
	virtual void draw();
	virtual void draw(VSShaderLib shader, GLint vm_uniformId, GLint pvm_uniformId , GLint normal_uniformId);
	virtual void draw(double angle, double px, double py);
	virtual void update(double delta);
	bool Colision(GameObject* obj, double angle, double _obj_angle);
	void setRaio(float _r) { raio = _r; }
	double getRaio() { return raio; }
	void setCollisionAngle(double _a);
	double getCollisionAngle();
	void setBox(double xm, double xM, double ym, double yM);
	double getXm();
	double getXM();
	double getYm();
	double getYM();
	int getTex();
	void setTex(int tex);
};
#endif