#pragma once
#ifndef MINIMAP_H
#define MINIMAP_H

#include "GameObject.h"

class Minimap : public GameObject {

	Material2 mate;
	//Texture tex;
	float amb[4] = { 0.74f,0.74f,0.0f,1.0f };
	float diff[4] = { 0.5f,0.5f,0.4f,1.0f };
	float spec[4] = { 0.7f,0.7f,0.04f,1.0f };
	float shine = 10.0f;

public:
	Minimap(double x, double y, double z, struct MyMesh *_mesh);
	void draw();
	//void draw(VSShaderLib shader, GLint vm_uniformId, GLint pvm_uniformId, GLint normal_uniformId) override;
	//void update(double delta);
};

#endif