#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#define PI 3.14159265
#define N_BUTTERS 5
#define N_ORANGES 5

#include "Header.h"
#include "DynamicObject.h"
#include "StaticObject.h"
#include "Car.h"
#include "Orange.h"
#include "Butter.h"
#include "Roadside.h"
#include "OrthogonalCamera.h"
#include "PerspectiveCamera.h"
#include <math.h>

class GameManager {

	std::vector<GameObject*> _game_objects;
	std::vector<Butter *> _butter_objects;
	std::vector<Orange *> _orange_objects;
	std::vector<Car *> _car_objects;
	std::vector<Roadside*> _road_objects;
	std::vector<Camera*> _cameras;
	int UP, DOWN, RIGHT, LEFT;
	double angle; // carro
	double posx, posy;
	int apressed, npressed, gpressed, lpressed, cpressed, spressed, hpressed;
	int CAM;
	double tempo_atual, tempo_anterior, tempo_oranges;
	Car *car;

	//std::vector<LightSource*> _light_sources;

public:
	GameManager();
	~GameManager();

	//void
	void add(GameObject * obj);
	void add_cam(Camera * obj);
	void add_road(Roadside* obj);
	//void add_dynamic(DynamicObject* obj);
	void desenhaPausa();
	void add_car(Car *car);
	void add_butter(Butter *butter);
	void add_orange(Orange *orange);
	void checkAllCollisions();
	void checkCar_Oranges();
	GLuint loadTextureFromFile(const char *filename);
	void checkCar_Cheerios();
	void checkCar_Butters();
	void display();
	void drawAll();
	void reshape(int w, int h);
	void keyPressed(unsigned char key, int x, int y);
	void specialKeys(int key, int x, int y);
	void specialupKeys(int key, int x, int y);
	void onTimer();
	void idle();
	void update(unsigned long delta);
	void timer(int extra);
	void init_velas();
	void load_texturas();
	void init();
	void add_texture_road(int tex);
	void add_texture_butter(int tex);
	void add_texture_orange(int tex);
};
#endif