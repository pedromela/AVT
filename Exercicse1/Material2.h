#pragma once
#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "Header.h"

class Material2 {
public:
	float diffuse[4];
	float ambient[4];
	float specular[4];
	float emissive[4];
	float shininess;
	int texCount;
	Material2() {}
	~Material2() {}

	void defineMaterial(float* amb, float* diff, float* spec, float shine);
};

#endif
