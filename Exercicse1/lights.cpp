#include <vector>
#include <iostream>

#define N_LIGHTS 9
#define DIR_LIGHT 0
#define POINTLIGHT 1
#define SPOTLIGHT 7
#define N_POINTLIGHTS 6

typedef struct Light{
	float LightPos[3];	//direction for directional light
	int LightType;

	float ambient[3];
	float diffuse[3];
	float specular[3];

	float constant = 1.0f;	//these 3 constants are not used in directional light
	float linear = 0.09f;
	float quadratic = 0.032f;

	float direction[3] = { 0.0f, 0.0f, 0.0f };	//also only used for spotlight
	float cutoff = 0; //default to 0 since its only used for spotlight

	void init_Pos(float* values)
	{
		for (int i = 0; i < 3; i++)
			LightPos[i] = values[i];
	}

	void init_ambient(float* values)
	{
		for (int i = 0; i < 3; i++)
			ambient[i] = values[i];
	}

	void init_diffuse(float* values)
	{
		for (int i = 0; i < 3; i++)
			diffuse[i] = values[i];
	}

	void init_specular(float* values)
	{
		for (int i = 0; i < 3; i++)
			specular[i] = values[i];
	}

	void init_direction(float* values)
	{
		for (int i = 0; i < 3; i++)
			direction[i] = values[i];
	}
};

std::vector<Light> _lights(N_LIGHTS);

void initLights() {
	//directional light
	Light dl;
	
	float pos[3] = { 4.0f, 6.0f, 2.0f };
	float ambient[3] = { 0.0f, 0.0f, 0.0f };
	float diffuse[3] = { 1.0f, 1.0f, 1.0f };
	float specular[3] = { 1.0f, 1.0f, 1.0f };
	
	dl.init_Pos( pos );
	dl.LightType = DIR_LIGHT;

	dl.init_ambient(ambient);
	dl.init_diffuse(diffuse);
	dl.init_specular(specular);

	_lights.push_back(dl);

	
	//pointlights
	int i = 0;
	float ambient[3] = { 0.05f, 0.05f, 0.05f };
	float diffuse[3] = { 0.8f, 0.8f, 0.8f };
	float specular[3] = { 1.0f, 1.0f, 1.0f };
	for (i = POINTLIGHT; i < POINTLIGHT + N_POINTLIGHTS; i++) {
		Light pl;
		
		float pos[3] = { 4.0f + i * 2, 7.0f, 2.0f };
		
		pl.init_Pos( pos );
		pl.LightType = POINTLIGHT;

		pl.init_ambient( ambient );
		pl.init_diffuse( diffuse );
		pl.init_specular( specular );

		_lights.push_back(pl);
	}


	//spotlights
	Light pl1;

	float pos[3] = { 3.0f, 6.0f, 2.0f };
	float ambient[3] = { 0.0f, 0.0f, 0.0f };
	float diffuse[3] = { 1.0f, 1.0f, 1.0f };
	float specular[3] = { 1.0f, 1.0f, 1.0f };
	float direction[3] = { 1.0f, 1.0f, 1.0f }; //gotta select car direction

	pl1.init_Pos( pos );
	pl1.LightType = SPOTLIGHT;

	pl1.init_ambient( ambient );
	pl1.init_diffuse( diffuse );
	pl1.init_specular( specular );

	pl1.init_direction( direction );
	pl1.cutoff = 12.5f;

	_lights.push_back(pl1);


	Light pl2;

	float pos[3] = { 5.0f, 6.0f, 2.0f };

	pl2.init_Pos( pos );
	pl2.LightType = SPOTLIGHT;

	pl2.init_ambient(ambient);
	pl2.init_diffuse(diffuse);
	pl2.init_specular(specular);

	pl2.init_direction(direction);
	pl2.cutoff = 12.5f;

	_lights.push_back(pl2);
}
