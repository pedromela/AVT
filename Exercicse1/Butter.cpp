#include "Butter.h"

static void drawBox(GLfloat size, GLenum type)
{
	static GLfloat n[6][3] =
	{
	  {-1.0, 0.0, 0.0},
	  {0.0, 1.0, 0.0},
	  {1.0, 0.0, 0.0},
	  {0.0, -1.0, 0.0},
	  {0.0, 0.0, 1.0},
	  {0.0, 0.0, -1.0}
	};
	static GLint faces[6][4] =
	{
	  {0, 1, 2, 3},
	  {3, 2, 6, 7},
	  {7, 6, 5, 4},
	  {4, 5, 1, 0},
	  {5, 6, 2, 1},
	  {7, 4, 0, 3}
	};
	GLfloat v[8][3];
	GLint i;

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

	for (i = 5; i >= 0; i--) {
		glBegin(type);
		glNormal3fv(&n[i][0]);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3fv(&v[faces[i][0]][0]);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3fv(&v[faces[i][1]][0]);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3fv(&v[faces[i][2]][0]);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
}

void glutSolidCube1(GLdouble size)
{
	drawBox(size, GL_QUADS);
}
Butter::Butter(double x, double y, double z) : angle(rand() % 180) {
	setPosition(x, y, z);
	tamanho = 0.75;
	setRaio((tamanho*tamanho) + ((tamanho / 2)*(tamanho / 2)));
	setSpeed(0, 0, 0);
	setTexMd(3);
	//mate.defineMaterial(amb, diff, spec, shine);
}

Butter::Butter(double x, double y, double z, MyMesh * _mesh)
{
	setPosition(x, y, z);
	tamanho = 0.75;
	setRaio((tamanho*tamanho) + ((tamanho / 2)*(tamanho / 2)));
	setTexMd(5);
	setSpeed(0, 0, 0);
	float amb2[4] = { 0.74f,0.74f,0.0f,0.2f };
	float diff2[4] = { 0.5f,0.5f,0.4f,0.2f };
	float spec2[4] = { 0.7f,0.7f,0.04f,0.2f };
	float emissive[4] = { 0.0f, 0.0f, 0.0f, 12.0f };
	float pos[3] = { 0.0f, 0.0f, 0.0f };

	float shininess = 100.0f;
	int texcount = 3;
	mesh = _mesh;
	memcpy(mesh->mat.ambient, amb2, 4 * sizeof(float));
	memcpy(mesh->mat.diffuse, diff2, 4 * sizeof(float));
	memcpy(mesh->mat.specular, spec2, 4 * sizeof(float));
	memcpy(mesh->mat.emissive, emissive, 4 * sizeof(float));
	memcpy(mesh->position, pos, 3 * sizeof(float));
	mesh->mat.shininess = shininess;
	mesh->mat.texCount = texcount;
	createCube();
}


void Butter::update(double delta) {
	double x = getPosition()->getX(), y = getPosition()->getY(), z = getPosition()->getZ();
	if (HasSpeed()) {
		setPosition(x + getSpeed().getX()*cos(getCollisionAngle()*PI / 180)*delta, y + getSpeed().getY()*sin(getCollisionAngle()*PI / 180)*delta, z);
		setSpeed(getSpeed().getX() - 0.3*getSpeed().getX(), getSpeed().getX() - 0.3*getSpeed().getX(), 0);
	}


}


void Butter::draw() {
	pushMatrix(MODEL);
	translate(MODEL, getPosition()->getX() - 0.5f, getPosition()->getZ(), getPosition()->getY() - 0.5f);
}

void Butter::draw(VSShaderLib shader, GLint vm_uniformId, GLint pvm_uniformId, GLint normal_uniformId)
{
	// send the material
	GLint loc = glGetUniformLocation(shader.getProgramIndex(), "mat.ambient");
	glUniform4fv(loc, 1, mesh->mat.ambient);
	loc = glGetUniformLocation(shader.getProgramIndex(), "mat.diffuse");
	glUniform4fv(loc, 1, mesh->mat.diffuse);
	loc = glGetUniformLocation(shader.getProgramIndex(), "mat.specular");
	glUniform4fv(loc, 1, mesh->mat.specular);
	loc = glGetUniformLocation(shader.getProgramIndex(), "mat.shininess");
	glUniform1f(loc, mesh->mat.shininess);
	pushMatrix(MODEL);
	translate(MODEL, getPosition()->getX(), getPosition()->getZ(), getPosition()->getY());
	// send matrices to OGL
	//printf("%f %f %f %f\n", i, _orange_objects[i]->getPosition()->getY(), _orange_objects[i]->getPosition()->getY(), _orange_objects[i]->getPosition()->getZ());
	computeDerivedMatrix(PROJ_VIEW_MODEL);
	glUniformMatrix4fv(vm_uniformId, 1, GL_FALSE, mCompMatrix[VIEW_MODEL]);
	glUniformMatrix4fv(pvm_uniformId, 1, GL_FALSE, mCompMatrix[PROJ_VIEW_MODEL]);
	computeNormalMatrix3x3();
	glUniformMatrix3fv(normal_uniformId, 1, GL_FALSE, mNormal3x3);

	// Render mesh
	glBindVertexArray(mesh->vao);

	if (!shader.isProgramValid()) {
		printf("Program Not Valid!\n");
		exit(1);
	}
	glDrawElements(mesh->type, mesh->numIndexes, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	popMatrix(MODEL);
}