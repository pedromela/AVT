#include "GameManager.h"
#include <iostream>
#include "ImageRgb.h"

GameManager::GameManager() {
	angle = 0.0f;
	posx = 4;
	posy = 1;
	tempo_anterior = 0;
	tempo_oranges = 0;
	CAM = 1;
	apressed = 0;
	npressed = 0;
	gpressed = 0;
	lpressed = 0;
	cpressed = 0;
	spressed = 0;
	hpressed = 1;
}

GameManager::~GameManager() {}

void GameManager::add(GameObject* obj) {
	_game_objects.push_back(obj);
}

void GameManager::add_cam(Camera* obj) {
	_cameras.push_back(obj);
}

void GameManager::add_road(Roadside* obj) {
	_road_objects.push_back(obj);
}

void GameManager::add_car(Car* _car) {
	_car_objects.push_back(_car);
	car = _car;
}

void GameManager::add_butter(Butter* _butter) {
	_butter_objects.push_back(_butter);
}

void GameManager::add_orange(Orange* _orange) {
	_orange_objects.push_back(_orange);
}

void GameManager::drawAll() {
	int i;
	/*for (i = 0; i < _road_objects.size(); i++)
		_road_objects[i]->draw();
	for (i = 0; i < _car_objects.size(); i++)
		_car_objects[i]->draw();
	for (i = 0; i < _butter_objects.size(); i++)
		_butter_objects[i]->draw();*/
	for (i = 0; i < _orange_objects.size(); i++)
		_orange_objects[i]->draw();
}

GLuint GameManager::loadTextureFromFile(const char *filename)
{
	ImageRgb theTexMap(filename);
	GLuint texture[1];
	glGenTextures(1, &texture[0]);					// Create The Texture
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData());
	return texture[0];
}

void GameManager::display(void) {

	//  Limpa a tela e o Z-Buffer
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_cameras[CAM - 1]->set(CAM);

	// Reinicia transformações
	glLoadIdentity();

	// move back a bit
	//glRotatef(-90.0, 1.0, 0.0, 0.0); 
	glTranslatef(1, 1, 1);

	//if (spressed == 1)
	desenhaPausa();
	drawAll();


	glFlush();
	glutSwapBuffers();
}

void GameManager::reshape(int w, int h) {
	float aspect = (float)w / h;
	if (aspect > 1)
		glViewport((w - h) / 2, 0, h, h);
	else
		glViewport(0, (h - w) / 2, w, w);
}
void GameManager::add_texture_road(int tex) {
	_road_objects[0]->setTex(tex);
}
void GameManager::add_texture_butter(int tex) {
	int i;
	for (i = 0; i < _butter_objects.size(); i++)
		_butter_objects[i]->setTex(tex);
}
void GameManager::add_texture_orange(int tex) {
	int i;
	for (i = 0; i < _orange_objects.size(); i++)
		_orange_objects[i]->setTex(tex);
}


void GameManager::keyPressed(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		if (apressed == 0) {
			apressed = 1;
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else if (apressed == 1) {
			apressed = 0;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		break;
	case 'A':
		if (apressed == 0) {
			apressed = 1;
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else if (apressed == 1) {
			apressed = 0;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		break;
	case 'h':
		if (npressed == 1) {
			if (hpressed == 0) {
				hpressed = 1;
				glEnable(GL_LIGHT7);
			}
			else if (hpressed == 1) {
				hpressed = 0;
				glDisable(GL_LIGHT7);
			}
		}
		break;
	case 'H':
		if (npressed == 1) {
			if (hpressed == 0) {
				hpressed = 1;
				glEnable(GL_LIGHT7);
			}
			else if (hpressed == 1) {
				hpressed = 0;
				glDisable(GL_LIGHT7);
			}
		}
		break;
	case 's':
		if (spressed == 0) {
			spressed = 1;
			desenhaPausa();
		}
		else
			spressed = 0;
		break;
	case 'S':
		if (spressed == 0) {
			spressed = 1;
			desenhaPausa();
		}
		else
			spressed = 0;
		break;
	case 'n':
		if (npressed == 0) {
			glDisable(GL_LIGHT0);
			glEnable(GL_LIGHT1);
			glEnable(GL_LIGHT2);
			glEnable(GL_LIGHT3);
			glEnable(GL_LIGHT4);
			glEnable(GL_LIGHT5);
			glEnable(GL_LIGHT6);
			cpressed = 0;
			npressed = 1;
		}
		else {
			glEnable(GL_LIGHT0);
			glDisable(GL_LIGHT1);
			glDisable(GL_LIGHT2);
			glDisable(GL_LIGHT3);
			glDisable(GL_LIGHT4);
			glDisable(GL_LIGHT5);
			glDisable(GL_LIGHT6);
			cpressed = 1;
			npressed = 0;
		}
		break;
	case 'N':
		if (npressed == 0) {
			glDisable(GL_LIGHT0);
			glEnable(GL_LIGHT1);
			glEnable(GL_LIGHT2);
			glEnable(GL_LIGHT3);
			glEnable(GL_LIGHT4);
			glEnable(GL_LIGHT5);
			glEnable(GL_LIGHT6);
			cpressed = 0;
			npressed = 1;
		}
		else {
			glEnable(GL_LIGHT0);
			glDisable(GL_LIGHT1);
			glDisable(GL_LIGHT2);
			glDisable(GL_LIGHT3);
			glDisable(GL_LIGHT4);
			glDisable(GL_LIGHT5);
			glDisable(GL_LIGHT6);
			cpressed = 1;
			npressed = 0;
		}
		break;
	case 'l':
		if (lpressed == 0) {
			glDisable(GL_LIGHTING);
			lpressed = 1;
		}
		else {
			glEnable(GL_LIGHTING);
			lpressed = 0;
		}
		break;
	case 'L':
		if (lpressed == 0) {
			glDisable(GL_LIGHTING);
			lpressed = 1;
		}
		else {
			glEnable(GL_LIGHTING);
			lpressed = 0;
		}
		break;
	case 'g':
		if (gpressed == 1) {
			glShadeModel(GL_SMOOTH);
			gpressed = 0;
		}
		else {
			glShadeModel(GL_FLAT);
			gpressed = 1;
		}
		break;
	case 'G':
		if (gpressed == 1) {
			glShadeModel(GL_SMOOTH);
			gpressed = 0;
		}
		else {
			glShadeModel(GL_FLAT);
			gpressed = 1;
		}
		break;
	case 'c':
		if (cpressed == 1) {
			glEnable(GL_LIGHT1);
			glEnable(GL_LIGHT2);
			glEnable(GL_LIGHT3);
			glEnable(GL_LIGHT4);
			glEnable(GL_LIGHT5);
			glEnable(GL_LIGHT6);
			cpressed = 0;
		}
		else {
			glDisable(GL_LIGHT1);
			glDisable(GL_LIGHT2);
			glDisable(GL_LIGHT3);
			glDisable(GL_LIGHT4);
			glDisable(GL_LIGHT5);
			glDisable(GL_LIGHT6);
			cpressed = 1;
		}
		break;
	case 'C':
		if (cpressed == 1) {
			glEnable(GL_LIGHT1);
			glEnable(GL_LIGHT2);
			glEnable(GL_LIGHT3);
			glEnable(GL_LIGHT4);
			glEnable(GL_LIGHT5);
			glEnable(GL_LIGHT6);
			cpressed = 0;
		}
		else {
			glDisable(GL_LIGHT1);
			glDisable(GL_LIGHT2);
			glDisable(GL_LIGHT3);
			glDisable(GL_LIGHT4);
			glDisable(GL_LIGHT5);
			glDisable(GL_LIGHT6);
			cpressed = 1;
		}
		break;
	case '1':
		CAM = 1;
		//set(_cameras[CAM-1],CAM);
		break;
	case '2':
		CAM = 2;
		//set(_cameras[CAM-1],CAM);
		break;
	case '3':
		CAM = 3;
		//set(_cameras[CAM-1],CAM);
		break;
	case 'f': glutFullScreen(); break;
	case 27: exit(0); break;
	}
	//glutPostRedisplay();
}

void GameManager::desenhaPausa() {
	glPushMatrix();
	glTranslatef(9, 9, 0);
	glScalef(7.0f, 4.0f, 1.0f);
	glColor3f(0.5f, 0.5f, 0.5f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, loadTextureFromFile("gamePause.bmp"));
	glutSolidCube(0.75);
	glFlush();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void GameManager::init_velas() {
	GLfloat diffuse0[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat ambient[] = { 0.5, 0.5, 0.5, 0.5 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light1_pos[] = { 6.0, 6.0, 5.0, 1.0 };
	GLfloat light2_pos[] = { 6.0, 2.0, 5.0, 1.0 };
	GLfloat light3_pos[] = { 3.0, 3.0, 5.0, 1.0 };
	GLfloat light4_pos[] = { 17.0, 3.0, 5.0, 1.0 };
	GLfloat light5_pos[] = { 3.0, 17.0, 5.0, 1.0 };
	GLfloat light6_pos[] = { 17.0, 17.0, 5.0, 1.0 };
	GLfloat light7_pos[] = { 3.0, 4.0, 5.0, 1.0 };
	GLfloat position[] = { 0.0, 0.0, -1.0, 2.0 };
	GLfloat directional[] = { 0.5, 0.5, 0.5, 5.0 };
	GLfloat *light_pos[8] = { light1_pos,light2_pos,light3_pos,light4_pos,light5_pos,light6_pos,light7_pos };
	int i;
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	// point light 

	for (i = 1; i < 8; i++) {
		glLightfv(GL_LIGHT0 + i, GL_POSITION, light_pos[i - 1]);
		// directional light 
		glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, directional);
		glLightfv(GL_LIGHT0 + i, GL_SPECULAR, directional);
		glLightfv(GL_LIGHT0 + i, GL_SPOT_DIRECTION, position);
		glLightf(GL_LIGHT0 + i, GL_SPOT_CUTOFF, 60); // 0~180 
		glLightf(GL_LIGHT0 + i, GL_SPOT_EXPONENT, 1);
	}
}
void GameManager::specialKeys(int key, int x, int y) {
	if (key == GLUT_KEY_UP) {
		UP = 1;
		//rotate_x -= 5;
	}
	else if (key == GLUT_KEY_DOWN) {
		DOWN = 1;
		//rotate_x += 5;
	}
	//  Seta direita - aumenta rotação em 5 graus
	else if (key == GLUT_KEY_RIGHT) {
		RIGHT = 1;
		//rotate_y -= 5;
	}
	//  Seta para esquerda - diminui a rotação por 5 graus
	else if (key == GLUT_KEY_LEFT) {
		LEFT = 1;
		//rotate_y += 5;
	}
	//  Requisitar atualização do display
	car->setDir(UP, DOWN, RIGHT, LEFT);
}

void GameManager::specialupKeys(int key, int x, int y) {
	if (key == GLUT_KEY_UP) {
		UP = 0;
	}
	else if (key == GLUT_KEY_DOWN) {
		DOWN = 0;
	}
	//  Seta direita - aumenta rotação em 5 graus
	else if (key == GLUT_KEY_RIGHT) {
		RIGHT = 0;
	}
	//  Seta para esquerda - diminui a rotação por 5 graus
	else if (key == GLUT_KEY_LEFT) {
		LEFT = 0;
	}
	car->setDir(UP, DOWN, RIGHT, LEFT);
	//  Requisitar atualização do display
}

void GameManager::onTimer() {
	int i;
	tempo_atual = glutGet(GLUT_ELAPSED_TIME);
	//glutPostRedisplay();
	if (spressed == 0) {
		update(tempo_atual - tempo_anterior);
	}
	tempo_anterior = tempo_atual;
	tempo_oranges++;
	if (tempo_oranges == 10) {
		for (i = 0; i < _orange_objects.size(); i++)
			_orange_objects[i]->setSpeed(_orange_objects[i]->getSpeed().getX() + 0.0001, _orange_objects[i]->getSpeed().getY() + 0.0001, _orange_objects[i]->getSpeed().getZ());
		tempo_oranges = 0;
	}
}

void GameManager::idle() {}

void GameManager::update(unsigned long delta) {
	int i;
	GLfloat directional_[] = { 1., 1., 1., 1.0 };
	GLfloat light_pos_[] = { (GLfloat)_car_objects[0]->getPosition()->getX(),(GLfloat)_car_objects[0]->getPosition()->getY(),5.0, 1.0 };
	//GLfloat light_pos1_[]={(GLfloat)_car_objects[0]->getPosition()->getX()+3,(GLfloat)_car_objects[0]->getPosition()->getY()+3,5.0, 1.0};
	GLfloat direction_[] = { (GLfloat)cos(_car_objects[0]->getAngle()*PI / 180), (GLfloat)sin(_car_objects[0]->getAngle()*PI / 180), -1.0, 1.0 };
	glLightfv(GL_LIGHT7, GL_POSITION, light_pos_);
	//glLightfv(GL_LIGHT7, GL_DIFFUSE, directional_);
	//glLightfv(GL_LIGHT7, GL_SPECULAR, directional_);
	glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, direction_);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, directional_);
	glLightfv(GL_LIGHT7, GL_SPECULAR, directional_);
	glLightf(GL_LIGHT7, GL_SPOT_CUTOFF, 70); // 0~180 
	glLightf(GL_LIGHT7, GL_SPOT_EXPONENT, 1.0);

	//glLightfv(GL_LIGHT0+8, GL_POSITION, light_pos1_); 	
	//glLightfv(GL_LIGHT7, GL_DIFFUSE, directional_);
	//glLightfv(GL_LIGHT7, GL_SPECULAR, directional_);
	//glLightfv(GL_LIGHT0+8, GL_SPOT_DIRECTION, direction_); 

	for (i = 0; i < _car_objects.size(); i++)
		_car_objects[i]->update(delta);
	for (i = 0; i < _butter_objects.size(); i++)
		_butter_objects[i]->update(delta);
	for (i = 0; i < _orange_objects.size(); i++)
		_orange_objects[i]->update(delta);
	for (i = 0; i < _road_objects.size(); i++)
		_road_objects[i]->update(delta);

	if (CAM == 3)
		_cameras[2]->update(delta);

	checkAllCollisions();
	glutPostRedisplay();


}

void GameManager::checkAllCollisions() {

	checkCar_Oranges();
	checkCar_Cheerios();
	checkCar_Butters();

	//car->setSpeed(0, 0, 0);
	/*MUDAR ISTO !!*/
	//car->setColidiu(false);

}

void GameManager::checkCar_Butters() {
	int i, count = 0;

	for (i = 0; i < _butter_objects.size(); i++) {
		if (car->Colision(_butter_objects[i], car->getAngle(), _butter_objects[i]->getAngle())) {
			std::cout << "MANTEIGA" << std::endl;
			_butter_objects[i]->setCollisionAngle(car->getAngle());
			_butter_objects[i]->setSpeed(car->getSpeed());
			car->setColidiu(true);
			car->setSpeed(0, 0, 0);
			count++;
		}
	}

	if (count == 0)
		car->setColidiu(false);
}

void GameManager::checkCar_Cheerios() {
	int i, count = 0;
	Roadside* road = _road_objects[0];
	double size_in = road->getN_Cheerios_In();
	double size_out = road->getN_Cheerios_Out();
	Cheerios* _cheer;

	for (i = 0; i < size_in; i++) {
		_cheer = road->getCheerio_In(i);

		if (car->Colision(_cheer, car->getAngle(), 0)) {
			car->setColidiu(true);
			std::cout << "CHEERIO" << std::endl;
			_cheer->setCollisionAngle(car->getAngle());
			_cheer->setSpeed(car->getSpeed());
			std::cout << car->getSpeed().getX() << std::endl;
			//std::cout << _cheer->getSpeed().getX() << std::endl;
			car->setSpeed(0, 0, 0);
			count++;
		}
	}
	for (i = 0; i < size_out; i++) {
		_cheer = road->getCheerio_Out(i);

		if (car->Colision(_cheer, car->getAngle(), 0)) {
			car->setColidiu(true);
			std::cout << "CHEERIO" << std::endl;
			_cheer->setCollisionAngle(car->getAngle());
			_cheer->setSpeed(car->getSpeed());
			car->setSpeed(0, 0, 0);
			count++;
		}
	}
	if (count == 0)
		car->setColidiu(false);
}

void GameManager::checkCar_Oranges() {
	int i;
	DynamicObject* aux_speed = new DynamicObject();

	for (i = 0; i < _orange_objects.size(); i++) {
		if (car->Colision(_orange_objects[i], car->getAngle(), 0)) {
			std::cout << "LARANJA" << std::endl;
			std::cout << "RESET" << std::endl;
			car->setSpeed(0, 0, 0);
			car->setPosition(4, 2, 0.1);
			car->setAngle(0);
		}
	}
}


void GameManager::timer(int extra) {
	tempo_atual = glutGet(GLUT_ELAPSED_TIME);
	update(tempo_atual - tempo_anterior);
	tempo_anterior = tempo_atual;
	//setupTimerCallback(16);
}

void GameManager::init() {
	int i;
	UP = 0, DOWN = 0, RIGHT = 0, LEFT = 0;
	add_car(new Car(4, 2, 0.1));

	for (i = 0; i < N_ORANGES; i++)
		add_orange(new Orange(rand() % 21 - 1.5, rand() % 21 - 1.5, 0.5));
	for (i = 0; i < N_BUTTERS; i++)
		add_butter(new Butter(rand() % 19, rand() % 19, 0.4));

	add_cam(new OrthogonalCamera(-1.0, 21.0, -1.0, 21.0, -4.0, 4.0));
	add_cam(new PerspectiveCamera(45, 1, 1, 50));
	add_cam(new PerspectiveCamera(45, 1, 1, 20));
	_cameras[2]->setCar(car);

}

void GameManager::load_texturas() {


}