#pragma once
#ifndef ROADSIDE_H_
#define ROADSIDE_H_

#include "StaticObject.h"
#include "Cheerios.h"
#include "Butter.h"
#include "Orange.h"
#include <iostream>
#include <vector>


class Roadside : public StaticObject {
	double comprimento;
	float comp_pist_out;
	float comp_pist_in;
	double n_cheer_out;
	double n_cheer_in;
	double i;
	float inc;
	Material2 mate;
	//Texture tex;
	float amb[4] = { 0.9125f,0.9275f,0.954f,1.0f };
	float diff[4] = { 0.914f,0.9284f,0.98144f,1.0f };
	float spec[4] = { 0.993548f,0.971906f,0.966721f,1.0f };
	float shine = 100.0f;
	int start = 0;

public:
	std::vector<Cheerios*> c_out;
	std::vector<Cheerios*> c_in;
	struct MyMesh *mesh;
	std::vector<GameObject*> *game_objects;


	Roadside(double comp);
	Roadside(double comp, struct MyMesh *mesh, int _start, std::vector<GameObject*> *_game_objects);
	Roadside(double comp, struct MyMesh *mesh);

	~Roadside() {}

	void draw();
	void update(unsigned long delta);
	void inicializarCheerios();
	double getN_Cheerios_Out();
	double getN_Cheerios_In();
	Cheerios* getCheerio_In(int i);
	Cheerios* getCheerio_Out(int i);
};

#endif