//
// AVT demo light 
// based on demos from GLSL Core Tutorial in Lighthouse3D.com   
//
// This demo was built for learning purposes only.
// Some code could be severely optimised, but I tried to
// keep as simple and clear as possible.
//
// The code comes with no warranties, use it at your own risk.
// You may use it, or parts of it, wherever you want.
//

#include <math.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#include <string>
#include "Header.h"
// Use Very Simple Libs
#include "VSShaderlib.h"
#include "AVTmathLib.h"
#include "VertexAttrDef.h"
#include "basic_geometry.h"
#include "Header.h"
#include "Table.h"
#include "Car.h"
#include "Roadside.h"
#include "ImageRgb.h"
#include "Orange.h"
#include "Butter.h"
#include "Roadside.h"
#include "OrthogonalCamera.h"
#include "PerspectiveCamera.h"

// include DevIL for image loading
#include "Dependencies/IL/il.h"

// assimp include files. These three are usually needed.
#include "Dependencies/assimp/Importer.hpp" //OO version Header!
#include "Dependencies/assimp/PostProcess.h"
#include "Dependencies/assimp/Scene.h"

#define UPDATE_TIME 60
#define PI 3.14159265
#define N_BUTTERS 5
#define N_ORANGES 1
#define N_CHEERIOS 18
#define N_OBJECTS N_ORANGES+N_BUTTERS+1+N_CHEERIOS*4+((N_CHEERIOS/2) +1)*4+1
#define CAPTION "AVT Project"

// Uniform Buffer for Matrices
// this buffer will contain 3 matrices: projection, view and model
// each matrix is a float array with 16 components
GLuint matricesUniBuffer;
#define MatricesUniBufferSize sizeof(float) * 16 * 3
#define ProjMatrixOffset 0
#define ViewMatrixOffset sizeof(float) * 16
#define ModelMatrixOffset sizeof(float) * 16 * 2
#define MatrixSize sizeof(float) * 16


int WindowHandle = 0;
int WinX = 640, WinY = 480;

unsigned int FrameCount = 0;



VSShaderLib shader;

// Create an instance of the Importer class
Assimp::Importer importer;

// the global Assimp scene object
const aiScene* scene = NULL;

// images / texture
// map image filenames to textureIds
// pointer to texture Array
std::map<std::string, GLuint> textureIdMap;

// scale factor for the model to fit in the window
float scaleFactor;

// For push and pop matrix
std::vector<float *> matrixStack;

//External array storage defined in AVTmathLib.cpp

/// The storage for matrices
extern float mMatrix[COUNT_MATRICES][16];
extern float mCompMatrix[COUNT_COMPUTED_MATRICES][16];

/// The normal matrix
extern float mNormal3x3[9];

// Model Matrix (part of the OpenGL Model View Matrix)
float modelMatrix[16];

// The sampler uniform for textured models
// we are assuming a single texture so this will
//always be texture unit 0
GLuint texUnit = 0;

GLint pvm_uniformId;
GLint vm_uniformId;
GLint normal_uniformId;
GLint lPos_uniformId;
	
// Camera Position
float camX, camY, camZ;

// Mouse Tracking Variables
int startX, startY, tracking = 0;

// Camera Spherical Coordinates
float alpha = 270.0f, beta = 45.0f;
float r = 10.0f;

// Frame counting and FPS computation
long myTime,timebase = 0,frame = 0;
char s[32];
float lightPos[4] = {4.0f, 6.0f, 2.0f, 1.0f};


GLuint matricesUniLoc = 1, materialUniLoc = 2;

GLuint texture[10];

static const std::string modelname = "carro.obj";


std::vector<struct MyMesh> mesh(N_OBJECTS);
std::vector<struct MyMesh> myMeshes;

//struct MyMesh mesh[N_OBJECTS];
int objId = 0; //id of the object mesh - to be used as index of mesh: mesh[objID] means the current mesh

std::vector<GameObject*> _game_objects;
std::vector<Butter*> _butter_objects;
std::vector<Orange*> _orange_objects;
std::vector<Car*> _car_objects;
std::vector<Roadside*> _road_objects;
std::vector<Cheerios*> c_out;
std::vector<Cheerios*> c_in;
std::vector<Camera*> _cameras;
int UP, DOWN, RIGHT, LEFT;
double angle = 0.0f; // carro
double posx = 4, posy = 1;
int apressed = 0, npressed = 0, gpressed = 0, lpressed = 0, cpressed = 0, spressed = 0, hpressed = 1;
int CAM = 1;
double tempo_atual = 0, tempo_anterior = 0, tempo_oranges = 0;
Roadside *pista;
Car *car;

int y = 100;
int z = 120;

bool pause = false;

void add(GameObject* obj) {
	_game_objects.push_back(obj);
}

void add_cam(Camera* obj) {
	_cameras.push_back(obj);
}

void add_road(Roadside* obj) {
	_road_objects.push_back(obj);
}

void add_car(Car* _car) {
	_car_objects.push_back(_car);
	car = _car;
}

void add_butter(Butter* _butter) {
	_butter_objects.push_back(_butter);
}

void add_orange(Orange* _orange) {
	_orange_objects.push_back(_orange);
}

void add_cheerioIn(Cheerios* _cheerios) {
	c_in.push_back(_cheerios);
}

void add_cheerioOut(Cheerios* _cheerios) {
	c_out.push_back(_cheerios);
}

void togglePause() {
	if (pause)
		pause = false;
	else
		pause = true;
}

void restart() {
	int i = 0;
	car->setVidas(5);
	car->setPontos(0);
	car->setPosition(4, 2, 0.1);
	car->setSpeed(0, 0, 0);
	for (i = 0; i < _orange_objects.size(); i++) {
		_orange_objects[i]->setSpeed(0.002, 0.002, _orange_objects[i]->getSpeed().getZ());
	}
	for (i = 0; i <c_in.size(); i++) {
		c_in[i]->returnToInitPos();
	}
	for (i = 0; i < c_out.size(); i++) {
		c_out[i]->returnToInitPos();
	}
}

void checkCar_Butters() {
	int i, count = 0;

	for (i = 0; i < _butter_objects.size(); i++) {
		if (car->Colision(_butter_objects[i], car->getAngle(), _butter_objects[i]->getAngle())) {
			std::cout << "MANTEIGA" << std::endl;
			_butter_objects[i]->setCollisionAngle(car->getAngle());
			_butter_objects[i]->setSpeed(car->getSpeed());
			car->setColidiu(true);
			car->setSpeed(0, 0, 0);
			car->setPontos(0);
			count++;
		}
	}

	if (count == 0)
		car->setColidiu(false);
}

void checkCar_Cheerios() {
	int i, count = 0;
	double size_in = c_in.size();
	double size_out = c_out.size();
	Cheerios* _cheer;

	for (i = 0; i < size_in; i++) {
		_cheer = c_in[i];

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
		_cheer = c_out[i];

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

void checkCar_Oranges() {
	int i;

	for (i = 0; i < _orange_objects.size(); i++) {
		if (car->Colision(_orange_objects[i], car->getAngle(), 0)) {
			if (car->getVidas() > 0) {
				std::cout << "LARANJA" << std::endl;
				std::cout << "RESET" << std::endl;
				car->setSpeed(0, 0, 0);
				car->setPosition(4, 2, 0.1);
				car->setAngle(0);
				car->setVidas(car->getVidas() - 1);
				car->setPontos(0);
			}
			else { restart();}
		}
	}
}

void checkAllCollisions() {
	checkCar_Oranges();
	checkCar_Cheerios();
	checkCar_Butters();
}

GLuint loadTextureFromFile(const char *filename)
{
	ImageRgb theTexMap(filename);
	glGenTextures(1, &texture[0]);					// Create The Texture
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData());
	return texture[0];
}
// ----------------------------------------------------------------------------

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)

void get_bounding_box_for_node(const aiNode* nd,
	aiVector3D* min,
	aiVector3D* max)

{
	aiMatrix4x4 prev;
	unsigned int n = 0, t;

	for (; n < nd->mNumMeshes; ++n) {
		const aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];
		for (t = 0; t < mesh->mNumVertices; ++t) {

			aiVector3D tmp = mesh->mVertices[t];

			min->x = aisgl_min(min->x, tmp.x);
			min->y = aisgl_min(min->y, tmp.y);
			min->z = aisgl_min(min->z, tmp.z);

			max->x = aisgl_max(max->x, tmp.x);
			max->y = aisgl_max(max->y, tmp.y);
			max->z = aisgl_max(max->z, tmp.z);
		}
	}

	for (n = 0; n < nd->mNumChildren; ++n) {
		get_bounding_box_for_node(nd->mChildren[n], min, max);
	}
}

void get_bounding_box(aiVector3D* min, aiVector3D* max)
{

	min->x = min->y = min->z = 1e10f;
	max->x = max->y = max->z = -1e10f;
	get_bounding_box_for_node(scene->mRootNode, min, max);
}

int LoadGLTextures(const aiScene* scene)
{
	ILboolean success;

	/* initialization of DevIL */
	ilInit();

	/* scan scene's materials for textures */
	for (unsigned int m = 0; m < scene->mNumMaterials; ++m)
	{
		int texIndex = 0;
		aiString path;	// filename
		
		aiReturn texFound = scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
		while (texFound == AI_SUCCESS) {
			//fill map with textures, OpenGL image ids set to 0
			textureIdMap[path.data] = 0;
			printf("tex path : %s\n", path.data);
			// more textures?
			texIndex++;
			texFound = scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
		}
	}

	int numTextures = textureIdMap.size();

	/* create and fill array with DevIL texture ids */
	ILuint* imageIds = new ILuint[numTextures];
	ilGenImages(numTextures, imageIds);

	/* create and fill array with GL texture ids */
	GLuint* textureIds = new GLuint[numTextures];
	glGenTextures(numTextures, textureIds); /* Texture name generation */

	/* get iterator */
	std::map<std::string, GLuint>::iterator itr = textureIdMap.begin();
	int i = 0;
	for (; itr != textureIdMap.end(); ++i, ++itr)
	{
		//save IL image ID
		std::string filename = (*itr).first;  // get filename
		(*itr).second = textureIds[i];	  // save texture id for filename in map

		ilBindImage(imageIds[i]); /* Binding of DevIL image name */
		ilEnable(IL_ORIGIN_SET);
		ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
		success = ilLoadImage((ILstring)filename.c_str());

		if (success) {
			/* Convert image to RGBA */
			ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

			/* Create and load textures to OpenGL */
			glBindTexture(GL_TEXTURE_2D, textureIds[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ilGetInteger(IL_IMAGE_WIDTH),
				ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGBA, GL_UNSIGNED_BYTE,
				ilGetData());
		}
		else
			printf("Couldn't load Image: %s\n", filename.c_str());
	}
	/* Because we have already copied image data into texture data
	we can release memory used by image. */
	ilDeleteImages(numTextures, imageIds);

	//Cleanup
	delete[] imageIds;
	delete[] textureIds;

	//return success;
	return true;
}

bool Import3DFromFile(const std::string& pFile)
{

	//check if file exists
	std::ifstream fin(pFile.c_str());
	if (!fin.fail()) {
		fin.close();
	}
	else {
		printf("Couldn't open file: %s\n", pFile.c_str());
		printf("%s\n", importer.GetErrorString());
		return false;
	}

	scene = importer.ReadFile(pFile, aiProcessPreset_TargetRealtime_Quality);

	// If the import failed, report it
	if (!scene)
	{
		printf("%s\n", importer.GetErrorString());
		return false;
	}

	// Now we can access the file's contents.
	printf("Import of scene %s succeeded.", pFile.c_str());

	aiVector3D scene_min, scene_max, scene_center;
	get_bounding_box(&scene_min, &scene_max);
	float tmp;
	tmp = scene_max.x - scene_min.x;
	tmp = scene_max.y - scene_min.y > tmp ? scene_max.y - scene_min.y : tmp;
	tmp = scene_max.z - scene_min.z > tmp ? scene_max.z - scene_min.z : tmp;
	scaleFactor = 1.f / tmp;

	// We're done. Everything will be cleaned up by the importer destructor
	return true;
}


//// Can't send color down as a pointer to aiColor4D because AI colors are ABGR.
//void Color4f(const aiColor4D *color)
//{
//	glColor4f(color->r, color->g, color->b, color->a);
//}

void set_float4(float f[4], float a, float b, float c, float d)
{
	f[0] = a;
	f[1] = b;
	f[2] = c;
	f[3] = d;
}

void color4_to_float4(const aiColor4D *c, float f[4])
{
	f[0] = c->r;
	f[1] = c->g;
	f[2] = c->b;
	f[3] = c->a;
}

void genVAOsAndUniformBuffer(const aiScene *sc) {

	struct MyMesh aMesh;
	struct MyMaterial aMat;
	GLuint buffer;

	// For each mesh
	for (unsigned int n = 0; n < sc->mNumMeshes; ++n)
	{
		const aiMesh* mesh = sc->mMeshes[n];

		// create array with faces
		// have to convert from Assimp format to array
		unsigned int *faceArray;
		faceArray = (unsigned int *)malloc(sizeof(unsigned int) * mesh->mNumFaces * 3);
		unsigned int faceIndex = 0;

		for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
			const aiFace* face = &mesh->mFaces[t];

			memcpy(&faceArray[faceIndex], face->mIndices, 3 * sizeof(unsigned int));
			faceIndex += 3;
		}
		aMesh.numFaces = sc->mMeshes[n]->mNumFaces;
		// generate Vertex Array for mesh
		glGenVertexArrays(1, &(aMesh.vao));
		glBindVertexArray(aMesh.vao);

		// buffer for faces
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh->mNumFaces * 3, faceArray, GL_STATIC_DRAW);

		// buffer for vertex positions
		if (mesh->HasPositions()) {
			glGenBuffers(1, &buffer);
			glBindBuffer(GL_ARRAY_BUFFER, buffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * mesh->mNumVertices, mesh->mVertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(VERTEX_COORD_ATTRIB);
			glVertexAttribPointer(VERTEX_COORD_ATTRIB, 3, GL_FLOAT, 0, 0, 0);
		}

		// buffer for vertex normals
		if (mesh->HasNormals()) {
			glGenBuffers(1, &buffer);
			glBindBuffer(GL_ARRAY_BUFFER, buffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * mesh->mNumVertices, mesh->mNormals, GL_STATIC_DRAW);
			glEnableVertexAttribArray(NORMAL_ATTRIB);
			glVertexAttribPointer(NORMAL_ATTRIB, 3, GL_FLOAT, 0, 0, 0);
		}

		// buffer for vertex texture coordinates
		if (mesh->HasTextureCoords(0)) {
			float *texCoords = (float *)malloc(sizeof(float) * 2 * mesh->mNumVertices);
			for (unsigned int k = 0; k < mesh->mNumVertices; ++k) {

				texCoords[k * 2] = mesh->mTextureCoords[0][k].x;
				texCoords[k * 2 + 1] = mesh->mTextureCoords[0][k].y;

			}
			glGenBuffers(1, &buffer);
			glBindBuffer(GL_ARRAY_BUFFER, buffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * mesh->mNumVertices, texCoords, GL_STATIC_DRAW);
			glEnableVertexAttribArray(TEXTURE_COORD_ATTRIB);
			glVertexAttribPointer(TEXTURE_COORD_ATTRIB, 2, GL_FLOAT, 0, 0, 0);
		}

		// unbind buffers
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// create material uniform buffer
		aiMaterial *mtl = sc->mMaterials[mesh->mMaterialIndex];

		aiString texPath;	//contains filename of texture
		if (AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, 0, &texPath)) {
			//bind texture
			unsigned int texId = textureIdMap[texPath.data];
			aMesh.texIndex = texId;
			aMat.texCount = 1;
		}
		else
			aMat.texCount = 0;

		float c[4];
		set_float4(c, 0.8f, 0.8f, 0.8f, 1.0f);
		aiColor4D diffuse;
		if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
			color4_to_float4(&diffuse, c);
		memcpy(aMat.diffuse, c, sizeof(c));

		set_float4(c, 0.2f, 0.2f, 0.2f, 1.0f);
		aiColor4D ambient;
		if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
			color4_to_float4(&ambient, c);
		memcpy(aMat.ambient, c, sizeof(c));

		set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
		aiColor4D specular;
		if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
			color4_to_float4(&specular, c);
		memcpy(aMat.specular, c, sizeof(c));

		set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
		aiColor4D emission;
		if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
			color4_to_float4(&emission, c);
		memcpy(aMat.emissive, c, sizeof(c));

		float shininess = 0.0;
		unsigned int max;
		aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
		aMat.shininess = shininess;

		glGenBuffers(1, &(aMesh.uniformBlockIndex));
		glBindBuffer(GL_UNIFORM_BUFFER, aMesh.uniformBlockIndex);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(aMat), (void *)(&aMat), GL_STATIC_DRAW);

		myMeshes.push_back(aMesh);
	}
}
void update(int value) {
	if (!pause) {
		car->update(value);
		for (int i = 0; i < _game_objects.size(); i++)
			_game_objects[i]->update(value);
		if (CAM == 3) {
			//printf("CAM 3 %d\n", value);
			_cameras[2]->update(value);
			_cameras[2]->setRaio(r);
		}
		checkAllCollisions();
	}
}

void timer(int value)
{
	std::ostringstream oss;
	oss << CAPTION << ": " << car->getVidas() << " lifes, " << (int)car->getPontos() << " points";
	std::string s = oss.str();
	glutSetWindow(WindowHandle);
	glutSetWindowTitle(s.c_str());
    FrameCount = 0;
	update(value);
	glutTimerFunc(1000, timer, 0);
}

void refresh(int value)
{
	std::ostringstream oss;
	oss << CAPTION << ": " << car->getVidas() << " lifes, " << (int)car->getPontos() << " points";
	std::string s = oss.str();
	glutSetWindow(WindowHandle);
	glutSetWindowTitle(s.c_str());
	FrameCount = 0;
	update(UPDATE_TIME);
	glutPostRedisplay();
	glutTimerFunc(1000/UPDATE_TIME, refresh, 0);
}

// ------------------------------------------------------------
//
// Reshape Callback Function
//

void changeSize(int w, int h) {

	float ratio;
	// Prevent a divide by zero, when window is too short
	if(h == 0)
		h = 1;
	// set the viewport to be the entire window
	glViewport(0, 0, w, h);
	// set the projection matrix
	ratio = (1.0f * w) / h;

}
void setModelMatrix() {

	glBindBuffer(GL_UNIFORM_BUFFER, matricesUniBuffer);
	glBufferSubData(GL_UNIFORM_BUFFER,
		ModelMatrixOffset, MatrixSize, modelMatrix);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

}

// Render Assimp Model


void recursive_render(const aiScene *sc, const aiNode* nd)
{

	// Get node transformation matrix
	//aiMatrix4x4 m = nd->mTransformation;
	// OpenGL matrices are column major
	//m.Transpose();
	
	//m.Translation();
	// save model matrix and apply node transformation
	//pushMatrix();

	//float aux[16];
	//memcpy(aux, &m, sizeof(float) * 16);
	//multMatrix(modelMatrix, aux);
	
	//setModelMatrix();

	// draw all meshes assigned to this node
	for (unsigned int n = 0; n < nd->mNumMeshes; ++n) {
		computeDerivedMatrix(PROJ_VIEW_MODEL);
		glUniformMatrix4fv(vm_uniformId, 1, GL_FALSE, mCompMatrix[VIEW_MODEL]);
		glUniformMatrix4fv(pvm_uniformId, 1, GL_FALSE, mCompMatrix[PROJ_VIEW_MODEL]);
		computeNormalMatrix3x3();
		glUniformMatrix3fv(normal_uniformId, 1, GL_FALSE, mNormal3x3);
		// bind material uniform
		glBindBufferRange(GL_UNIFORM_BUFFER, materialUniLoc, myMeshes[nd->mMeshes[n]].uniformBlockIndex, 0, sizeof(struct MyMaterial));
		// bind texture
		glBindTexture(GL_TEXTURE_2D, myMeshes[nd->mMeshes[n]].texIndex);
		// bind VAO
		glBindVertexArray(myMeshes[nd->mMeshes[n]].vao);
		// draw
		glDrawElements(GL_TRIANGLES, myMeshes[nd->mMeshes[n]].numFaces * 3, GL_UNSIGNED_INT, 0);

	}

	// draw all children
	for (unsigned int n = 0; n < nd->mNumChildren; ++n) {
		recursive_render(sc, nd->mChildren[n]);
	}
	//popMatrix();
}
// ------------------------------------------------------------
//
// Render stufff
//

void renderScene(void) {

	GLint loc;

	FrameCount++;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//_cameras[CAM - 1]->set(CAM);
	float ratio = (1.0f * WinX) / WinY;
	if (CAM == 1) {
		loadIdentity(PROJECTION);
		ortho(-3.0f, 21.0f, -3.0f, 21.0f, -40.0f, 40.0f);
		// load identity matrices
		loadIdentity(VIEW);
		loadIdentity(MODEL);
		// set the camera using a function similar to gluLookAt
		lookAt(0, 18, 0, 0, 9, 0, 9, 1, 0);
	}
	if (CAM == 2) {
		loadIdentity(PROJECTION);
		perspective(53.13f, ratio, 0.1f, 1000.0f);
		// load identity matrices
		loadIdentity(VIEW);
		loadIdentity(MODEL);
		// set the camera using a function similar to gluLookAt
		lookAt(18, 18, 0, 9, 0, 9, 0, 1, 0);
	}
	if (CAM == 3) {
		loadIdentity(PROJECTION);
		perspective(53.13f, ratio, 0.1f, 1000.0f);
		// load identity matrices
		loadIdentity(VIEW);
		loadIdentity(MODEL);
		// set the camera using a function similar to gluLookAt
		//printf("%f %f %f\n", camX, camY, camZ);
		//printf("car : %f %f %f\n", car->getPosition()->getX(), car->getPosition()->getZ(), car->getPosition()->getY());
		//printf("cam %d: %f %f %f\n", CAM, _cameras[CAM - 1]->eye.getX(), _cameras[CAM - 1]->eye.getY(), _cameras[CAM - 1]->eye.getZ());
		//lookAt(_cameras[CAM - 1]->eye.getX()+camX, _cameras[CAM - 1]->eye.getZ()+camY, _cameras[CAM - 1]->eye.getY()+camZ,car->getPosition()->getX(), car->getPosition()->getZ(),car->getPosition()->getY(),0, 1, 0);
		lookAt(_cameras[CAM - 1]->eye.getX(), _cameras[CAM - 1]->eye.getY(), _cameras[CAM - 1]->eye.getZ(), car->getPosition()->getX(), car->getPosition()->getZ(), car->getPosition()->getY(), 0, 1, 0);

	}
	// use our shader
	glUseProgram(shader.getProgramIndex());

	//send the light position in eye coordinates

	//glUniform4fv(lPos_uniformId, 1, lightPos); //efeito capacete do mineiro, ou seja lighPos foi definido em eye coord 

	float *res =(float*) malloc(sizeof(float) * _game_objects.size());
	multMatrixPoint(VIEW, lightPos,res);   //lightPos definido em World Coord so is converted to eye space
	glUniform4fv(lPos_uniformId, 1, res);
	//printf("size %d\n", _game_objects.size());
	//printf("N_OBJECTS %d\n", N_OBJECTS);
	//car->draw(shader, vm_uniformId, pvm_uniformId, normal_uniformId);
	for (int i = 0; i < _game_objects.size(); i++) {
		// send the material
		//pushMatrix(MODEL); // don in obj->draw()

		loc = glGetUniformLocation(shader.getProgramIndex(), "mat.ambient");
		glUniform4fv(loc, 1, _game_objects[i]->mesh->mat.ambient);
		loc = glGetUniformLocation(shader.getProgramIndex(), "mat.diffuse");
		glUniform4fv(loc, 1, _game_objects[i]->mesh->mat.diffuse);
		loc = glGetUniformLocation(shader.getProgramIndex(), "mat.specular");
		glUniform4fv(loc, 1, _game_objects[i]->mesh->mat.specular);
		loc = glGetUniformLocation(shader.getProgramIndex(), "mat.shininess");
		glUniform1f(loc, _game_objects[i]->mesh->mat.shininess);

		_game_objects[i]->draw();
		
		// send matrices to OGL
		//printf("%f %f %f %f\n", i, _orange_objects[i]->getPosition()->getY(), _orange_objects[i]->getPosition()->getY(), _orange_objects[i]->getPosition()->getZ());
		computeDerivedMatrix(PROJ_VIEW_MODEL);
		glUniformMatrix4fv(vm_uniformId, 1, GL_FALSE, mCompMatrix[VIEW_MODEL]);
		glUniformMatrix4fv(pvm_uniformId, 1, GL_FALSE, mCompMatrix[PROJ_VIEW_MODEL]);
		computeNormalMatrix3x3();
		glUniformMatrix3fv(normal_uniformId, 1, GL_FALSE, mNormal3x3);

		// Render mesh
		glBindVertexArray(_game_objects[i]->mesh->vao);

		if (!shader.isProgramValid()) {
			printf("Program Not Valid!\n");
			exit(1);
		}
		glDrawElements(_game_objects[i]->mesh->type, _game_objects[i]->mesh->numIndexes, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		popMatrix(MODEL);
	}
	//pushMatrix(MODEL);

	//translate(MODEL, 0, 0, 0);
	//rotate(MODEL, 180, 0, 1, 0);
	car->draw();
	//glUniform1i(texUnit, 0);
	
	recursive_render(scene, scene->mRootNode);
	popMatrix(MODEL);

	glutSwapBuffers();
}

// ------------------------------------------------------------
//
// Events from the Keyboard
//
void processKeysUp(unsigned char key, int xx, int yy)
{
	switch (key) {
	case 'p':
		LEFT = 0;
		break;
	case 'P':
		LEFT = 0;
		break;
	case 'o':
		RIGHT = 0;
		break;
	case 'O':
		RIGHT = 0;
		break;
	case 'q':
		UP = 0;
		break;
	case 'Q':
		UP = 0;
		break;
	case 'a':
		DOWN = 0;
		break;
	case 'A':
		DOWN = 0;
		break;
	}
	car->setDir(UP, DOWN, RIGHT, LEFT);
}
void processKeys(unsigned char key, int xx, int yy)
{
	switch(key) {

		case 27:
			glutLeaveMainLoop();
			break;

		case 'c': 
			printf("Camera Spherical Coordinates (%f, %f, %f)\n", alpha, beta, r);
			break;
		case 'm': glEnable(GL_MULTISAMPLE); break;
		case 'n': glDisable(GL_MULTISAMPLE); break;
		case '1':
			CAM = 1;
			break;
		case '2':
			CAM = 2;
			printf("2\n");
			break;
		case '3':
			CAM = 3;
			break;
		case 'p':
			LEFT = 1;
			break;
		case 'P':
			LEFT = 1;
			break;
		case 'o':
			RIGHT = 1;
			break;
		case 'O':
			RIGHT = 1;
			break;
		case 'q':
			UP = 1;
			break;
		case 'Q':
			UP = 1;
			break;
		case 'a':
			DOWN = 1;
			break;
		case 'A':
			DOWN = 1;
			break;
		case 'r':
			restart();
			break;
		case 'R':
			restart();
			break;
		case 's':
			togglePause();
			break;
		case 'S':
			togglePause();
			break;
	}
	car->setDir(UP, DOWN, RIGHT, LEFT);
}


// ------------------------------------------------------------
//
// Mouse Events
//

void processMouseButtons(int button, int state, int xx, int yy)
{
	// start tracking the mouse
	if (state == GLUT_DOWN)  {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
	}

	//stop tracking the mouse
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha -= (xx - startX);
			beta += (yy - startY);
		}
		else if (tracking == 2) {
			r += (yy - startY) * 0.01f;
			if (r < 0.1f)
				r = 0.1f;
		}
		tracking = 0;
	}
}

// Track mouse motion while buttons are pressed

void processMouseMotion(int xx, int yy)
{

	int deltaX, deltaY;
	float alphaAux, betaAux;
	float rAux;

	deltaX =  - xx + startX;
	deltaY =    yy - startY;

	// left mouse button: move camera
	if (tracking == 1) {


		alphaAux = alpha + deltaX;
		betaAux = beta + deltaY;

		if (betaAux > 85.0f)
			betaAux = 85.0f;
		else if (betaAux < -85.0f)
			betaAux = -85.0f;
		rAux = r;
	}
	// right mouse button: zoom
	else if (tracking == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r + (deltaY * 0.01f);
		if (rAux < 0.1f)
			rAux = 0.1f;
	}

	camX = rAux * sin(alphaAux * 3.14f / 180.0f) * cos(betaAux * 3.14f / 180.0f);
	camZ = rAux * cos(alphaAux * 3.14f / 180.0f) * cos(betaAux * 3.14f / 180.0f);
	camY = rAux * sin(betaAux * 3.14f / 180.0f);

//  uncomment this if not using an idle or refresh func
//	glutPostRedisplay();
}


void mouseWheel(int wheel, int direction, int x, int y) {

	r += direction * 0.1f;
	if (r < 0.1f)
		r = 0.1f;

	camX = r * sin(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
	camZ = r * cos(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
	camY = r *   						     sin(beta * 3.14f / 180.0f);

//  uncomment this if not using an idle or refresh func
//	glutPostRedisplay();
}

// --------------------------------------------------------
//
// Shader Stuff
//


GLuint setupShaders() {

	// Shader for models
	shader.init();
	shader.loadShader(VSShaderLib::VERTEX_SHADER, "shaders/pointlight.vert");
	shader.loadShader(VSShaderLib::FRAGMENT_SHADER, "shaders/pointlight.frag");

	// set semantics for the shader variables
	glBindFragDataLocation(shader.getProgramIndex(), 0,"colorOut");
	glBindAttribLocation(shader.getProgramIndex(), VERTEX_COORD_ATTRIB, "position");
	glBindAttribLocation(shader.getProgramIndex(), NORMAL_ATTRIB, "normal");
	glBindAttribLocation(shader.getProgramIndex(), TEXTURE_COORD_ATTRIB, "texCoord");

	glLinkProgram(shader.getProgramIndex());

	pvm_uniformId = glGetUniformLocation(shader.getProgramIndex(), "m_pvm");
	vm_uniformId = glGetUniformLocation(shader.getProgramIndex(), "m_viewModel");
	normal_uniformId = glGetUniformLocation(shader.getProgramIndex(), "m_normal");
	lPos_uniformId = glGetUniformLocation(shader.getProgramIndex(), "l_pos");
	
	printf("InfoLog for Per Fragment Phong Lightning Shader\n%s\n\n", shader.getAllInfoLogs().c_str());
	
	return(shader.isProgramLinked());


}

// ------------------------------------------------------------
//
// Model loading and OpenGL setup
//

void init()
{

	loadTextureFromFile("./plank01.bmp");
	//add_texture_orange(loadTextureFromFile("./orange.bmp"));
	//add_texture_butter(loadTextureFromFile("./marble02.bmp"));

	if (!Import3DFromFile(modelname))
		return;
	
	LoadGLTextures(scene);

	genVAOsAndUniformBuffer(scene);

	UP = 0, DOWN = 0, RIGHT = 0, LEFT = 0;
	// set the camera position based on its spherical coordinates
	camX = r * sin(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
	camZ = r * cos(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
	camY = r * sin(beta * 3.14f / 180.0f);
	
	float pos[] = { 0.0f, 0.0f, 0.0f };
	float amb[] = { 0.2f, 0.15f, 0.1f, 1.0f };
	float diff[] = { 0.8f, 0.6f, 0.4f, 1.0f };
	float spec[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	float emissive[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float shininess = 100.0f;
	int texcount = 0;
	//add_orange(new Orange(rand() % 21 - 1.5, rand() % 21 - 1.5, 0.5));
	objId = 0;
	car = new Car(4, 2, 0.1);
	//add(car);
	float amb1[4] = { 1.0f,0.11f,0.0f,1.0f };
	float diff1[4] = { 0.88f,0.69f,0.0f,1.0f };
	float spec1[4] = { 0.26f,0.46f,0.09f,1.0f };
	shininess = 64.0f;
	for (int i = 0; i <= N_ORANGES; i++) {
		objId = i;
		Orange *o = new Orange(rand() % 21 - 1.5, rand() % 21 - 1.5, 0.5, &mesh[objId]);
		add(o);
		add_orange(o);
	}
	float amb2[4] = { 0.74f,0.74f,0.0f,1.0f };
	float diff2[4] = { 0.5f,0.5f,0.4f,1.0f };
	float spec2[4] = { 0.7f,0.7f,0.04f,1.0f };
	shininess=100.0;
	for (int i = N_ORANGES+1; i <= N_ORANGES + N_BUTTERS; i++) {
		objId = i;
		Butter *b = new Butter(rand() % 19, rand() % 19, 0.4, &mesh[objId]);
		add(b);
		add_butter(b);
	}

	float comprimento = N_CHEERIOS;
	float comp_pist_out = N_CHEERIOS;
	float comp_pist_in = (N_CHEERIOS / 2) + 1;
	float n_cheer_out = comp_pist_out * 4;
	float n_cheer_in = comp_pist_in * 4;
	int i = 0;
	float inc = 1;

	float ini_out = 0, ini_in = ini_out + 4, position_x = 0, position_y = 0, z = 0.15;
	objId = N_ORANGES + N_BUTTERS+1;
	/*Cheerios Outside*/
	Cheerios *c;
	for (i = 1; i <= n_cheer_out;) {
		if (i != (n_cheer_out)) {
			c = new Cheerios(position_x, ini_out, z, &mesh[objId]);
			add(c);
			add_cheerioOut(c);
			//printf("start1 %d\n", objId);
			i++;
			objId++;
		}
		if (i > 2 && i != (n_cheer_out)) {
			c = new Cheerios(ini_out, position_y, z, &mesh[objId]);
			//printf("start %d\n", objId);
			add(c);
			add_cheerioOut(c);
			i++;
			objId++;
		}
		if (i != (n_cheer_out)) {
			c = new Cheerios(position_x, comp_pist_out, z, &mesh[objId]);
			add(c);
			add_cheerioOut(c);
			i++;
			objId++;
		}
		if (i != (n_cheer_out)) {
			c = new Cheerios(comp_pist_out, position_y, z, &mesh[objId]);
			add(c);
			add_cheerioOut(c);
			i++;
			objId++;
		}
		if (i == (n_cheer_out)) {
			c = new Cheerios(comp_pist_out, comp_pist_out, z, &mesh[objId]);
			add(c);
			add_cheerioOut(c);
			i++;
			objId++;
		}
		position_x = position_x + inc;
		position_y = position_y + inc;
	}

	/*Cheerios Inside*/
	position_x = ini_in;
	position_y = ini_in;
	objId = i;
	for (i = 1; i <= n_cheer_in;) {
		if (i != (n_cheer_in)) {
			c = new Cheerios(position_x, ini_in, z, &mesh[objId++]);
			add(c);
			add_cheerioIn(c);
			i++;
		}
		if (i > 2 && i != (n_cheer_in)) {
			c = new Cheerios(ini_in, position_y, z, &mesh[objId++]);
			add(c);
			add_cheerioIn(c);
			i++;
		}
		if (i != (n_cheer_in)) {
			c = new Cheerios(position_x, comp_pist_in + ini_in, z, &mesh[objId++]);
			add(c);
			add_cheerioIn(c);
			i++;
		}
		if (i != (n_cheer_in)) {
			c = new Cheerios(comp_pist_in + ini_in, position_y, z, &mesh[objId++]);
			add(c);
			add_cheerioIn(c);
			i++;
		}
		if (i == (n_cheer_in)) {
			c = new Cheerios(comp_pist_in + ini_in, comp_pist_in + ini_in, z, &mesh[objId++]);
			add(c);
			add_cheerioIn(c);
			i++;
		}
		position_x = position_x + inc;
		position_y = position_y + inc;
	}
	//Roadside *r = new Roadside(18, &mesh[objId]);
	Table *t = new Table(-1,-1,-20, &mesh[objId]);
	add(t);
	//add_road(r);
	add_cam(new OrthogonalCamera(-1.0, 21.0, -1.0, 21.0, -4.0, 4.0));
	add_cam(new PerspectiveCamera(45, 1, 1, 50));
	add_cam(new PerspectiveCamera(45, 1, 1, 20));
	_cameras[2]->setCar(car);
	// some GL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

}


// ------------------------------------------------------------
//
// Main function
//


int main(int argc, char **argv) {

	srand(time(NULL));

	//gm.add_road(&pista);
	//gm.init();

//  GLUT initialization
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA|GLUT_MULTISAMPLE);

	glutInitContextVersion (3, 3);
	glutInitContextProfile (GLUT_CORE_PROFILE );
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);

	glutInitWindowPosition(100,100);
	glutInitWindowSize(WinX, WinY);
	WindowHandle = glutCreateWindow(CAPTION);


//  Callback Registration
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	//glutTimerFunc(0, timer, 0);
	glutIdleFunc(renderScene);  // Use it for maximum performance
	glutTimerFunc(0, refresh, 0);    //use it to to get 60 FPS whatever

//	Mouse and Keyboard Callbacks
	glutKeyboardFunc(processKeys);
	glutKeyboardUpFunc(processKeysUp);
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);
	glutMouseWheelFunc ( mouseWheel ) ;
	


//	return from main loop
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

//	Init GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	printf ("Vendor: %s\n", glGetString (GL_VENDOR));
	printf ("Renderer: %s\n", glGetString (GL_RENDERER));
	printf ("Version: %s\n", glGetString (GL_VERSION));
	printf ("GLSL: %s\n", glGetString (GL_SHADING_LANGUAGE_VERSION));

	if (!setupShaders())
		return(1);

	init();

	//  GLUT main loop
	glutMainLoop();

	return(0);

}

