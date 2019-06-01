/*
Semestre 2019-2
Proyecto Final
Autores: 	Iván Rogelio Aco Guerero
			Hernández Arrieta Carlos Alberto
*/
#define STB_IMAGE_IMPLEMENTATION
#pragma comment(lib, "irrKlang.lib")

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <K/include/irrKlang.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"
#include "Mesh_texturizado.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
//para iluminaci�n
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Material.h"

#include"Model.h"
#include "Skybox.h"
#include"SpotLight.h"

using namespace irrklang;

const float toRadians = 3.14159265f / 180.0f;
float movCoche;
float movOffset;
bool avanza;
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
Camera camera;

Texture plainTexture;
Texture Red;
Texture Gray;

//materiales
Material Material_brillante;
Material Material_opaco;
//luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

Model Kitt_M;
Model Llanta_M;
Model Camino_M;
Model Blackhawk_M;
Model Grass;
Model TicketBooth;
Model CoffeeShop;
Model MeatBallCart;
Model ColdBeverage;
Model SnowBall;
Model Rejillas;
Model Table;
Model Chair;
Model Tree;
Model RockWall;
Model Lamp;
Model Girafa;
Model dog;
Model Globo;
Model Roca;
Model Bathroom;
Model Faro;
Model Cat;
Model PacMan;
Model Escenario;
Model Mastil;
Model MastilCanoa;
Model Canoa;
Model Plataforma;
Model Base;
Model Sosten;
Model Rueda;
Model Canasta;
Model MontanaRusa;
Model ParedPato;
Model Shelf;
Model Arma;
Model Duck;

Skybox skybox;
Skybox skybox_12pm;
Skybox skybox_3pm;
Skybox skybox_6pm;
Skybox skybox_10pm;
Skybox skybox_2am;
Skybox skybox_6am;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
float reproduciranimacion, habilitaranimacion, guardoFrame, reinicioFrame, ciclo, ciclo2, contador = 0;

ISoundEngine *engine = createIrrKlangDevice();
ISoundEngine *engine_maquina = createIrrKlangDevice();
ISoundEngine *engine_pistola = createIrrKlangDevice();

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";

void CrearCubo()
{
	unsigned int cubo_indices[] = 
	{
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		4, 5, 6,
		6, 7, 4,
		// back
		8, 9, 10,
		10, 11, 8,

		// left
		12, 13, 14,
		14, 15, 12,
		// bottom
		16, 17, 18,
		18, 19, 16,
		// top
		20, 21, 22,
		22, 23, 20,
	};
	//Ejercicio 1: reemplazar con sus dados de 6 caras texturizados, agregar normales
 // average normals
	GLfloat cubo_vertices[] = {
		// front
		//x		y		z		S		T			NX		NY		NZ
		-0.5f, -0.5f,  0.5f,	0.27f,  0.35f,		0.0f,	0.0f,	-1.0f,	//0
		0.5f, -0.5f,  0.5f,		0.48f,	0.35f,		0.0f,	0.0f,	-1.0f,	//1
		0.5f,  0.5f,  0.5f,		0.48f,	0.64f,		0.0f,	0.0f,	-1.0f,	//2
		-0.5f,  0.5f,  0.5f,	0.27f,	0.64f,		0.0f,	0.0f,	-1.0f,	//3
		// right
		//x		y		z		S		T
		0.5f, -0.5f,  0.5f,	    0.52f,  0.35f,		-1.0f,	0.0f,	0.0f,
		0.5f, -0.5f,  -0.5f,	0.73f,	0.35f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  -0.5f,	0.73f,	0.64f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  0.5f,	    0.52f,	0.64f,		-1.0f,	0.0f,	0.0f,
		// back
		-0.5f, -0.5f, -0.5f,	0.77f,	0.35f,		0.0f,	0.0f,	1.0f,
		0.5f, -0.5f, -0.5f,		0.98f,	0.35f,		0.0f,	0.0f,	1.0f,
		0.5f,  0.5f, -0.5f,		0.98f,	0.64f,		0.0f,	0.0f,	1.0f,
		-0.5f,  0.5f, -0.5f,	0.77f,	0.64f,		0.0f,	0.0f,	1.0f,

		// left
		//x		y		z		S		T
		-0.5f, -0.5f,  -0.5f,	0.0f,	0.35f,		1.0f,	0.0f,	0.0f,
		-0.5f, -0.5f,  0.5f,	0.23f,  0.35f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  0.5f,	0.23f,	0.64f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  -0.5f,	0.0f,	0.64f,		1.0f,	0.0f,	0.0f,

		// bottom
		//x		y		z		S		T
		-0.5f, -0.5f,  0.5f,	0.27f,	0.02f,		0.0f,	1.0f,	0.0f,
		0.5f,  -0.5f,  0.5f,	0.48f,  0.02f,		0.0f,	1.0f,	0.0f,
		 0.5f,  -0.5f,  -0.5f,	0.48f,	0.31f,		0.0f,	1.0f,	0.0f,
		-0.5f, -0.5f,  -0.5f,	0.27f,	0.31f,		0.0f,	1.0f,	0.0f,

		//UP
		 //x		y		z		S		T
		 -0.5f, 0.5f,  0.5f,	0.27f,	0.68f,		0.0f,	-1.0f,	0.0f,
		 0.5f,  0.5f,  0.5f,	0.48f,  0.68f,		0.0f,	-1.0f,	0.0f,
		  0.5f, 0.5f,  -0.5f,	0.48f,	0.98f,		0.0f,	-1.0f,	0.0f,
		 -0.5f, 0.5f,  -0.5f,	0.27f,	0.98f,		0.0f,	-1.0f,	0.0f,

	};
	
	Mesh *cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 192, 36);
	meshList.push_back(cubo);

}

void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

int efecto_pistola(bool empieza, ISound *efecto){
	if (!engine_pistola)
		return 0;

	if(empieza) {
		efecto->setIsPaused(false); // unpause the sound
	}
	else
	{
		efecto->setIsPaused(true); // pause the sound
	}
}

int musica3D(glm::vec3 position, ISound *musica_3d)
{
	irrklang::vec3df position_3d((int)position.x, (int)position.y, (int)position.z);		   // position of the listener
	irrklang::vec3df lookDirection(10, 0, 10); // the direction the listener looks into
	irrklang::vec3df velPerSecond(0, 0, 0);	// only relevant for doppler effects
	irrklang::vec3df upVector(0, 1, 0);		   // where 'up' is in your 3D scene

	engine_maquina->setListenerPosition(position_3d, lookDirection, velPerSecond, upVector);

	if (!engine_maquina)
		return 0;

	if ((position.x < 38.0f && position.x > 22.0f) && (position.z > -8.0f &&
	position.z < 8.0f)){
		musica_3d->setIsPaused(false); // unpause the sound
	} else {
		musica_3d->setIsPaused(false); // unpause the sound
	}
}

int Music()
{
	if (!engine)
		return 0;
	engine->play2D("./Music/cepillin_feria.mp3", true);
}

void Play_Music(bool *keys)
{
	if (keys[GLFW_KEY_G])
	{
		engine->setAllSoundsPaused(true);
	}
	
	if (keys[GLFW_KEY_H])
	{
		engine->setAllSoundsPaused(false);
	}
}

///////////////////////////////KEYFRAMES/////////////////////


bool animacion = false;



//NEW// Keyframes
float posXGlobo = 2.0, posYGlobo = 2.0, posZGlobo = 0;
float	movGlobo_x = 0.0f, movGlobo_y = 0.0f;
float giroGlobo = 0;

#define MAX_FRAMES 13
int i_max_steps = 90;
int i_curr_steps = 5;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float movGlobo_x;		//Variable para PosicionX
	float movGlobo_y;		//Variable para PosicionY
	float movGlobo_xInc;		//Variable para IncrementoX
	float movGlobo_yInc;		//Variable para IncrementoY
	float giroGlobo;
	float giroGloboInc;
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 13;			//introducir datos
bool play = false;
int playIndex = 0;

void saveFrame(void)
{

	// printf("frameindex %d\n", FrameIndex);


	KeyFrame[FrameIndex].movGlobo_x = movGlobo_x;
	KeyFrame[FrameIndex].movGlobo_y = movGlobo_y;
	KeyFrame[FrameIndex].giroGlobo = giroGlobo;

	FrameIndex++;
}

void resetElements(void)
{

	movGlobo_x = KeyFrame[0].movGlobo_x;
	movGlobo_y = KeyFrame[0].movGlobo_y;
	giroGlobo = KeyFrame[0].giroGlobo;
}

void interpolation(void)
{
	KeyFrame[playIndex].movGlobo_xInc = (KeyFrame[playIndex + 1].movGlobo_x - KeyFrame[playIndex].movGlobo_x) / i_max_steps;
	KeyFrame[playIndex].movGlobo_yInc = (KeyFrame[playIndex + 1].movGlobo_y - KeyFrame[playIndex].movGlobo_y) / i_max_steps;
	KeyFrame[playIndex].giroGloboInc = (KeyFrame[playIndex + 1].giroGlobo - KeyFrame[playIndex].giroGlobo) / i_max_steps;

}


void animate(void)
{
	//Movimiento del objeto
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			// printf("playindex : %d\n", playIndex);
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				// printf("Frame index= %d\n", FrameIndex);
				// printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				//printf("entro aquí\n");
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//printf("se quedó aqui\n");
			//printf("max steps: %f", i_max_steps);
			//Draw animation
			movGlobo_x += KeyFrame[playIndex].movGlobo_xInc;
			movGlobo_y += KeyFrame[playIndex].movGlobo_yInc;
			giroGlobo += KeyFrame[playIndex].giroGloboInc;
			i_curr_steps++;
		}

	}
}

void inputKeyframes(bool* keys)
{
	if (keys[GLFW_KEY_O])
	{
		if (reproduciranimacion<1)
		{
			if (play == false && (FrameIndex > 1))
			{
				resetElements();
				//First Interpolation				
				interpolation();
				play = true;
				playIndex = 0;
				i_curr_steps = 0;
				reproduciranimacion++;
				// printf("presiona 0 para habilitar reproducir de nuevo la animación'\n");
				habilitaranimacion = 0;

			}
			else
			{
				play = false;
			}
		}
	}

	if (keys[GLFW_KEY_0])
	{
		if (habilitaranimacion < 1)
		{
			reproduciranimacion = 0;
		}
	}

	if (keys[GLFW_KEY_L])
	{
		if (guardoFrame < 1)
		{
			saveFrame();
			// printf("movAvion_x es: %f\n", movGlobo_x);
			//printf("movAvion_y es: %f\n", movAvion_y);
			// printf("presiona P para habilitar guardar otro frame'\n");
			guardoFrame++;
			reinicioFrame = 0;
		}
	}

	if (keys[GLFW_KEY_P])
	{
		if (reinicioFrame < 1)
		{
			guardoFrame = 0;
		}
	}

	if (keys[GLFW_KEY_1])
	{
		if (ciclo < 1)
		{
			//printf("movAvion_x es: %f\n", movAvion_x);
			movGlobo_x += 1.0f;
			// printf("movAvion_x es: %f\n", movGlobo_x);
			ciclo++;
			ciclo2 = 0;
			// printf("reinicia con 2\n");
		}

	}

	if (keys[GLFW_KEY_2])
	{
		if (ciclo2<1)
		{
			ciclo = 0;
		}
	}

}

/* FIN KEYFRAMES*/

int main()
{
	bool inicio_pistola = false;
	vec3df position_3d(30, 0, 0);
	//-9.65f, -0.3f, 19.8f 
	vec3df postion_pistiola(9, 0, 20);
	ISound *musica_3d = engine_maquina->play3D("./Music/maquina.mp3", position_3d, true, true);
	musica_3d->setMinDistance(5); // a loud sound
	ISound *musica_pistola = engine_pistola->play3D("./Music/metralleta.mp3", postion_pistiola, true, true);
	musica_pistola->setMinDistance(10);

	mainWindow = Window(1900, 1000); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CrearCubo();
	CreateShaders();

	camera = Camera(glm::vec3(-15.0f, 1.0f, -15.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.0f, 0.5f);
	

	// Camera camera_up = Camera(glm::vec3(0.0f, 30.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.0f, 0.5f);


	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();

	Red = Texture("Textures/plain_red.png");
	Red.LoadTextureA();

	Gray = Texture("Textures/plain_gray.png");
	Gray.LoadTextureA();

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);

	Grass = Model();
	Grass.LoadModel("Models/10450_Rectangular_Grass_Patch_v1_iterations-2.obj");

	TicketBooth = Model();
	TicketBooth.LoadModel("Models/15187_CarnivalTicketBooth_v1.obj");

	CoffeeShop = Model();
	CoffeeShop.LoadModel("Models/Coffee Shop.obj");

	MeatBallCart = Model();
	MeatBallCart.LoadModel("Models/street_cart_meetball.obj");

	ColdBeverage = Model();
	ColdBeverage.LoadModel("Models/13925_Cold_Beverage_Vending_Cart_v1_L1.obj");

	SnowBall = Model();
	SnowBall.LoadModel("Models/13926_Snow_Cone_Vending_Cart_v3_l2.obj");

	Rejillas = Model();
	Rejillas.LoadModel("Models/balandongan.obj");

	Table = Model();
	Table.LoadModel("Models/table.obj");

	Chair = Model();
	Chair.LoadModel("Models/Sedia.obj");

	Tree = Model();
	Tree.LoadModel("Models/trees9.3ds");

	RockWall = Model();
	RockWall.LoadModel("Models/RockWall.obj");

	Lamp = Model();
	Lamp.LoadModel("Models/StreetLamp.obj");

	PacMan = Model();
	PacMan.LoadModel("Models/Pac-Man.obj");

	Girafa = Model();
	Girafa.LoadModel("Models/10021_Giraffe_v04.obj");

	Cat = Model();
	Cat.LoadModel("Models/12221_Cat_v1_l3.obj");

	dog = Model();
	dog.LoadModel("Models/12228_Dog_v1_L2.obj");

	Globo = Model();
	Globo.LoadModel("Models/13499_Balloon_Cluster_v1_L2.obj");
	
	Roca = Model();
	Roca.LoadModel("Models/rocks_01_model.obj");

	Bathroom = Model();
	Bathroom.LoadModel("Models/bathroom.obj");

	Faro = Model();
	Faro.LoadModel("Models/rv_lamp_post_3.obj");

	Escenario = Model();
	Escenario.LoadModel("Models/escenario.obj");

	Mastil = Model();
	Mastil.LoadModel("Models/mastil.obj");

	MastilCanoa = Model();
	MastilCanoa.LoadModel("Models/mastil_canoa.obj");

	Plataforma = Model();
	Plataforma.LoadModel("Models/plataforma.obj");

	Canoa = Model();
	Canoa.LoadModel("Models/canoa3.obj");

	Rueda = Model();
	Rueda.LoadModel("Models/rueda.obj");

	Sosten = Model();
	Sosten.LoadModel("Models/sosten.obj");

	Base = Model();
	Base.LoadModel("Models/base.obj");

	Canasta = Model();
	Canasta.LoadModel("Models/canasta.obj");

	MontanaRusa = Model();
	MontanaRusa.LoadModel("Models/MontanaRusa.obj");

	ParedPato = Model();
	ParedPato.LoadModel("Models/concrete_wall.obj");

	Shelf = Model();
	Shelf.LoadModel("Models/4Shelf.obj");

	Arma = Model();
	Arma.LoadModel("Models/Air_Gun-Wavefront.obj");

	Duck = Model();
	Duck.LoadModel("Models/10602_Rubber_Duck_v1_L3.obj");

		//luz direccional, s�lo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
									0.4f, 0.4f,
									1.0f, 0.0f, 0.0f);
	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//Declaraci�n de primer luz puntual
	pointLights[0] = PointLight(1.0f, 1.0f, 1.0f,
								0.0f, 2.0f,
								5.0f, 1.5f, 24.0f,
								0.3f, 0.2f, 0.1f);
	pointLightCount++;
	
	unsigned int spotLightCount = 0;
	//linterna
	spotLights[0] = SpotLight(0.16f, 0.71f, 0.96f,
							0.0f, 2.0f,
							0.0f, 1.0f, -7.0f,
							0.0f, -5.0f, 0.0f,
							1.0f, 0.0f, 0.0f,
							40.0f);
	spotLightCount++;

	spotLights[1] = SpotLight(1.0f, 0.0f, 0.0f,
							0.0f, 2.0f,
							0.0f, 1.0f, 7.0f,
							0.0f, -5.0f, 0.0f,
							1.0f, 0.0f, 0.0f,
							40.0f);
	spotLightCount++;

	spotLights[2] = SpotLight(0.0f, 1.0f, 0.0f,
							0.0f, 2.0f,
							-10.0f, 1.0f, -7.0f,
							0.0f, -5.0f, 0.0f,
							1.0f, 0.0f, 0.0f,
							40.0f);
	spotLightCount++;

	spotLights[3] = SpotLight(0.0f, 0.0f, 1.0f,
							0.0f, 2.0f,
							-10.0f, 1.0f, 7.0f,
							0.0f, -5.0f, 0.0f,
							1.0f, 0.0f, 0.0f,
							40.0f);
	spotLightCount++;

	
	spotLights[4] = SpotLight(1.0f, 1.0f, 0.0f,
							0.0f, 2.0f,
							-15.0f, 1.0f, 0.0f,
							0.0f, -5.0f, 0.0f,
							1.0f, 0.0f, 0.0f,
							40.0f);
	spotLightCount++;

	spotLights[5] = SpotLight(0.3f, 1.0f, 1.0f,
							0.0f, 2.0f,
							-15.0f, 1.0f, 20.0f,
							0.0f, -5.0f, 0.0f,
							1.0f, 0.0f, 0.0f,
							40.0f);
	spotLightCount++;


	spotLights[6] = SpotLight(1.0f, 1.0f, 0.3f,
						0.0f, 2.0f,
						-15.0f, 1.0f, 30.0f,
						0.0f, -5.0f, 0.0f,
						1.0f, 0.0f, 0.0f,
						40.0f);

	spotLightCount++;

	//Luces para kamikaze

	spotLights[7] = SpotLight(1.0f, 0.0f, 0.0f,
							  0.0f, 2.0f,
							  20.0f, 1.0f, 0.0f,
							  5.0f, 5.0f, 0.0f,
							  1.0f, 0.0f, 0.0f,
							  40.0f);

	spotLightCount++;

	spotLights[8] = SpotLight(0.0f, 0.0f, 1.0f,
							  0.0f, 2.0f,
							  24.0f, 3.0f, 4.0f,
							  0.0f, -5.0f, 0.0f,
							  1.0f, 0.0f, 0.0f,
							  40.0f);
	spotLightCount++;

	spotLights[9] = SpotLight(0.0f, 1.0f, 0.0f,
							  0.0f, 2.0f,
							  24.0f, 3.0f, -4.0f,
							  0.0f, -5.0f, 0.0f,
							  1.0f, 0.0f, 0.0f,
							  40.0f);
	spotLightCount++;

	spotLights[10] = SpotLight(1.0f, 0.0f, 0.0f,
							  0.0f, 2.0f,
							  29.0f, 10.0f, 11.0f,
							  0.0f, 0.0f, 5.0f,
							  1.0f, 0.0f, 0.0f,
							  40.0f);
	spotLightCount++;

	spotLights[11] = SpotLight(1.0f, 1.0f, 0.0f,
							  0.0f, 2.0f,
							  29.0f, 10.0f, 28.0f,
							  0.0f, 0.0f, -5.0f,
							  1.0f, 0.0f, 0.0f,
							  40.0f);
	spotLightCount++;

	spotLights[12] = SpotLight(1.0f, 0.0f, 1.0f,
							  0.0f, 2.0f,
							  29.0f, 4.0f, 28.0f,
							  0.0f, -5.0f, 0.0f,
							  1.0f, 0.0f, 0.0f,
							  40.0f);
	spotLightCount++;
	
	spotLights[13] = SpotLight(0.97f, 0.23f, 0.57f,
							  0.0f, 2.0f,
							  29.0f, 4.0f, 11.0f,
							  0.0f, -5.0f, 0.0f,
							  1.0f, 0.0f, 0.0f,
							  40.0f);
	spotLightCount++;

	spotLights[14] = SpotLight(1.0f, 0.0f, 1.0f,
							  0.0f, 0.5f,
							  0.0f, 20.0f, 10.0f,
							  0.0f, -5.0f, 0.0f,
							  1.0f, 0.0f, 0.0f,
							  40.0f);
	spotLightCount++;

	//Rueda de la fortuna

	spotLights[15] = SpotLight(0.0f, 0.0f, 1.0f,
							  0.0f, 2.0f,
							  36.0f, 20.0f, 20.0f,
							  0.0f, -5.0f, 0.0f,
							  1.0f, 0.0f, 0.0f,
							  20.0f);
	spotLightCount++;

	spotLights[16] = SpotLight(0.0f, 0.0f, 1.0f,
							  0.0f, 2.0f,
							  25.0f, 20.0f, 20.0f,
							  0.0f, -5.0f, 0.0f,
							  1.0f, 0.0f, 0.0f,
							  20.0f);
	spotLightCount++;

	spotLights[17] = SpotLight(0.22f, 0.5f, 0.9f,
							  0.0f, 2.0f,
							  60.0f, 20.0f, 10.0f,
							  0.0f, -5.0f, 0.0f,
							  1.0f, 0.0f, 0.0f,
							  40.0f);
	spotLightCount++;

	spotLights[18] = SpotLight(0.9f, 0.1f, 0.1f,
							  0.0f, 2.0f,
							  60.0f, 20.0f, 10.0f,
							  0.0f, -5.0f, 0.0f,
							  1.0f, 0.0f, 0.0f,
							  40.0f);
	spotLightCount++;

	//Rueda de la fortuna

	spotLights[19] = SpotLight(1.0f, 1.0f, 0.0f,
							  0.0f, 2.0f,
							  36.0f, 32.0f, 20.0f,
							  0.0f, -5.0f, 0.0f,
							  1.0f, 0.0f, 0.0f,
							  5.0f);
	spotLightCount++;

	spotLights[20] = SpotLight(1.0f, 1.0f, 0.0f,
							  0.0f, 2.0f,
							  25.0f, 32.0f, 20.0f,
							  0.0f, -5.0f, 0.0f,
							  1.0f, 0.0f, 0.0f,
							  5.0f);
	spotLightCount++;

	

	std::vector<std::string> skyboxFaces_12pm;
	std::vector<std::string> skyboxFaces_3pm;
	std::vector<std::string> skyboxFaces_6pm;
	std::vector<std::string> skyboxFaces_10pm;
	std::vector<std::string> skyboxFaces_2am;
	std::vector<std::string> skyboxFaces_6am;

	skyboxFaces_12pm.push_back("Textures/Skybox/hills_rt_12pm.tga");
	skyboxFaces_12pm.push_back("Textures/Skybox/hills_lf_12pm.tga");
	skyboxFaces_12pm.push_back("Textures/Skybox/hills_dn_12pm.tga");
	skyboxFaces_12pm.push_back("Textures/Skybox/hills_up_12pm.tga");
	skyboxFaces_12pm.push_back("Textures/Skybox/hills_bk_12pm.tga");
	skyboxFaces_12pm.push_back("Textures/Skybox/hills_ft_12pm.tga");

	skyboxFaces_3pm.push_back("Textures/Skybox/hills_rt_3pm.tga");
	skyboxFaces_3pm.push_back("Textures/Skybox/hills_lf_3pm.tga");
	skyboxFaces_3pm.push_back("Textures/Skybox/hills_dn_3pm.tga");
	skyboxFaces_3pm.push_back("Textures/Skybox/hills_up_3pm.tga");
	skyboxFaces_3pm.push_back("Textures/Skybox/hills_bk_3pm.tga");
	skyboxFaces_3pm.push_back("Textures/Skybox/hills_ft_3pm.tga");

	skyboxFaces_6pm.push_back("Textures/Skybox/hills_rt_6pm.tga");
	skyboxFaces_6pm.push_back("Textures/Skybox/hills_lf_6pm.tga");
	skyboxFaces_6pm.push_back("Textures/Skybox/hills_dn_6pm.tga");
	skyboxFaces_6pm.push_back("Textures/Skybox/hills_up_6pm.tga");
	skyboxFaces_6pm.push_back("Textures/Skybox/hills_bk_6pm.tga");
	skyboxFaces_6pm.push_back("Textures/Skybox/hills_ft_6pm.tga");

	skyboxFaces_10pm.push_back("Textures/Skybox/hills_rt_10pm.tga");
	skyboxFaces_10pm.push_back("Textures/Skybox/hills_lf_10pm.tga");
	skyboxFaces_10pm.push_back("Textures/Skybox/hills_dn_10pm.tga");
	skyboxFaces_10pm.push_back("Textures/Skybox/hills_up_10pm.tga");
	skyboxFaces_10pm.push_back("Textures/Skybox/hills_bk_10pm.tga");
	skyboxFaces_10pm.push_back("Textures/Skybox/hills_ft_10pm.tga");

	skyboxFaces_2am.push_back("Textures/Skybox/hills_rt_2am.tga");
	skyboxFaces_2am.push_back("Textures/Skybox/hills_lf_2am.tga");
	skyboxFaces_2am.push_back("Textures/Skybox/hills_dn_2am.tga");
	skyboxFaces_2am.push_back("Textures/Skybox/hills_up_2am.tga");
	skyboxFaces_2am.push_back("Textures/Skybox/hills_bk_2am.tga");
	skyboxFaces_2am.push_back("Textures/Skybox/hills_ft_2am.tga");

	skyboxFaces_6am.push_back("Textures/Skybox/hills_rt_6am.tga");
	skyboxFaces_6am.push_back("Textures/Skybox/hills_lf_6am.tga");
	skyboxFaces_6am.push_back("Textures/Skybox/hills_dn_6am.tga");
	skyboxFaces_6am.push_back("Textures/Skybox/hills_up_6am.tga");
	skyboxFaces_6am.push_back("Textures/Skybox/hills_bk_6am.tga");
	skyboxFaces_6am.push_back("Textures/Skybox/hills_ft_6am.tga");

	skybox_12pm = Skybox(skyboxFaces_12pm);
	skybox_3pm = Skybox(skyboxFaces_3pm);
	skybox_6pm = Skybox(skyboxFaces_6pm);
	skybox_10pm = Skybox(skyboxFaces_10pm);
	skybox_2am = Skybox(skyboxFaces_2am);
	skybox_6am = Skybox(skyboxFaces_6am);

	skybox = skybox_12pm;

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 300.0f);

	float counter = 0, animacionKamikaze = 0.0f, angulo_kamikaze = 0.0f, counterGlobos = 0.0f, animacionRueda = 0.0f, counterLuz1 = 0.0f, counterLuz2 = 0.0f;
	float deltaTmp = 0.0f;
	float caminoPacman1 = -10.0f;
	float giroPacman1 = 180.0f;
	float cuentaGiroPacman1 = 0.0f;
	unsigned int booleanoKamikaze = 0, posicion_kamikaze = 0,
	velocidad_kamikaze = 0, booleanoGlobos = 0, booleanoLuz = 0, booleanoPacman1 = 0, booleanoGiroPacman1 = 0;
	glm::vec3 positionCamara;

	float angulo_pistola = 0.0f;
	GLfloat subida_pistola = 0.0f;
	//////////Variables de los patos////////////////
	float recorridoPato1 = 21.5f; 
	float recorridoPato2 = 20.0f; 
	float recorridoPato3 = 18.5f; 
	float recorridoPato4 = 23.0f; 
	float recorridoPato5 = 21.5f; 
	float recorridoPato6 = 20.0f; 
	float recorridoPato7 = 18.5f; 
	float recorridoPato8 = 17.0f; 
	float recorridoPato9 = 15.5f;
	float escalaPato1 = 0.06f;
	float escalaPato2 = 0.06f;
	float escalaPato3 = 0.06f;
	float escalaPato4 = 0.06f;
	float escalaPato5 = 0.06f;
	float escalaPato6 = 0.06f;
	float escalaPato7 = 0.06f;
	float escalaPato8 = 0.06f;
	float escalaPato9 = 0.06f;
	int animacionCorriendo1 = 0;
	int animacionCorriendo2 = 0;
	int animacionCorriendo3 = 0;
	int animacionCorriendo4 = 0;
	int animacionCorriendo5 = 0;
	int animacionCorriendo6 = 0;
	int animacionCorriendo7 = 0;
	int animacionCorriendo8 = 0;
	int animacionCorriendo9 = 0;
	int patoVivo1 = 1;
	int patoVivo2 = 1;
	int patoVivo3 = 1;
	int patoVivo4 = 1;
	int patoVivo5 = 1;
	int patoVivo6 = 1;
	int patoVivo7 = 1;
	int patoVivo8 = 1;
	int patoVivo9 = 1;
	int patoAumentando1 = 1;
	int patoAumentando2 = 1;
	int patoAumentando3 = 1;
	int patoAumentando4 = 1;
	int patoAumentando5 = 1;
	int patoAumentando6 = 1;
	int patoAumentando7 = 1;
	int patoAumentando8 = 1;
	int patoAumentando9 = 1;
	int direccionPato1 = 1;
	int direccionPato2 = 1;
	int direccionPato3 = 1;
	int direccionPato4 = 1;
	int direccionPato5 = 1;
	int direccionPato6 = 1;
	int direccionPato7 = 1;
	int direccionPato8 = 1;
	int direccionPato9 = 1;
	int patoSeleccionado = 0;
	float tiempoDisparo = 3.0f;
	////////////////////////////////////////////////

	bool booleanoIda_o_Regreso_kamikaze = true, animacion = false;

	GLfloat x_kamikaze = 0.0f, y_kamikaze = 0.0f, x_rueda = 0.0f, y_rueda = 0.0f;
	Music();

	//KEYFRAMES DECLARADOS INICIALES

	

	KeyFrame[0].movGlobo_x = 0.0f;
	KeyFrame[0].movGlobo_y = 0.0f;
	KeyFrame[0].giroGlobo = 0.0f;

	KeyFrame[1].movGlobo_x = 1.0f;
	KeyFrame[1].movGlobo_y = 2.0f;
	KeyFrame[1].giroGlobo = 180.0f;

	KeyFrame[2].movGlobo_x = 0.0f;
	KeyFrame[2].movGlobo_y = 4.0f;
	KeyFrame[2].giroGlobo = 0.0f;

	KeyFrame[3].movGlobo_x = 1.0f;
	KeyFrame[3].movGlobo_y = 6.0f;
	KeyFrame[3].giroGlobo = 180.0f;

 	KeyFrame[4].movGlobo_x = 0.0f;
 	KeyFrame[4].movGlobo_y = 8.0f;
 	KeyFrame[4].giroGlobo = 0.0f;

	KeyFrame[5].movGlobo_x = 1.0f;
 	KeyFrame[5].movGlobo_y = 10.0f;
 	KeyFrame[5].giroGlobo = 180.0f;

	KeyFrame[6].movGlobo_x = 0.0f;
 	KeyFrame[6].movGlobo_y = 12.0f;
 	KeyFrame[6].giroGlobo = 0.0f;

	KeyFrame[7].movGlobo_x = -1.0f;
 	KeyFrame[7].movGlobo_y = 10.0f;
 	KeyFrame[7].giroGlobo = 180.0f;

	KeyFrame[8].movGlobo_x = 0.0f;
 	KeyFrame[8].movGlobo_y = 8.0f;
 	KeyFrame[8].giroGlobo = 0.0f;

	KeyFrame[9].movGlobo_x = -1.0f;
 	KeyFrame[9].movGlobo_y = 6.0f;
 	KeyFrame[9].giroGlobo = 180.0f;

	KeyFrame[10].movGlobo_x = 0.0f;
 	KeyFrame[10].movGlobo_y = 4.0f;
 	KeyFrame[10].giroGlobo = 0.0f;

	KeyFrame[11].movGlobo_x = -1.0f;
 	KeyFrame[11].movGlobo_y = 2.0f;
 	KeyFrame[11].giroGlobo = 180.0f;

	KeyFrame[12].movGlobo_x = 0.0f;
 	KeyFrame[12].movGlobo_y = 0.0f;
 	KeyFrame[12].giroGlobo = 0.0f;

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;
		
		counter = counter + deltaTime;

		if (counter > 44.0f) {
			counter = 0;
		}
		
		if (counter < 23.1f)
		{
			skybox = skybox_12pm;

		}
		else if (counter < 26.1f)
		{
			skybox = skybox_3pm;
		}
		else if (counter < 29.1f)
		{
			skybox = skybox_6pm;
		}
		else if (counter < 32.1f)
		{
			skybox = skybox_10pm;
		}
		else if (counter < 35.1f)
		{
			skybox = skybox_2am;
		}
		else if (counter < 38.1f)
		{
			skybox = skybox_6am;
		}
		
		
		

		glfwPollEvents();

		//para keyframes
		inputKeyframes(mainWindow.getKeys());
		animate();

		Play_Music(mainWindow.getKeys());
		camera.keyControl(mainWindow.getKeys(), deltaTime);
		pointLights[0].keyControl(mainWindow.getKeys());
		for(int i = 0; i <  spotLightCount; i++)
		{
			spotLights[i].keyControl(mainWindow.getKeys());
		}

		
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		// spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		glm::mat4 model(1.0);


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//pisoTexture.UseTexture();
		plainTexture.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[0]->RenderMesh();

		//Grass

		for(int j = -7; j < 7; j++)
		{
			for(int i = -7 ; i < 7; i++)
			{
				model = glm::mat4(1.0);
				model = glm::translate(model, glm::vec3( i * 10.0f, -1.5f, j * 10.0f));
				model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
				model = glm::scale(model, glm::vec3(0.04f, 0.04f, 0.04f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
				Grass.RenderModel();
			}
		}

		//Ticket Booth
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-12.0f, -1.3f, -14.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Red.UseTexture();
		TicketBooth.RenderModel();

		//Coffee Shop
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-5.0f, -1.3f, -14.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		CoffeeShop.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-5.0f, -1.3f, 12.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		CoffeeShop.RenderModel();

		//MeatBall Cart
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(2.0f, -1.21f, -14.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MeatBallCart.RenderModel();

		//Cold Beverage Cart
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(2.0f, -1.2f, -10.0f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.015f, 0.015f, 0.015f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		ColdBeverage.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(2.0f, -1.2f, 12.0f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.015f, 0.015f, 0.015f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		ColdBeverage.RenderModel();

		//SnowBall cart
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.0f, -1.2f, -5.0f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		SnowBall.RenderModel();

		//Rejillas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-12.0f, -0.4f, 14.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Rejillas.RenderModel();

		//Table
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.8f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Table.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.0f, -0.8f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Table.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(2.0f, -0.8f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Table.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.0f, -0.8f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Table.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(4.0f, -0.8f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Table.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, -0.8f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Table.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(6.0f, -0.8f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Table.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(7.0f, -0.8f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Table.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.0f, -0.8f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Table.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-2.0f, -0.8f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Table.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-3.0f, -0.8f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Table.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.0f, -0.8f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Table.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-5.0f, -0.8f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Table.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-6.0f, -0.8f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Table.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-7.0f, -0.8f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Table.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-8.0f, -0.8f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Table.RenderModel();

		//Chair

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-2.0f, -0.3f, -2.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Chair.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.3f, -2.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Chair.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.0f, -0.3f, -2.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Chair.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-6.0f, -0.3f, -2.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Chair.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-8.0f, -0.3f, -2.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Chair.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(2.0f, -0.3f, -2.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Chair.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(4.0f, -0.3f, -2.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Chair.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(6.0f, -0.3f, -2.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Chair.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.3f, 2.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Chair.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(2.0f, -0.3f, 2.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Chair.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(4.0f, -0.3f, 2.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Chair.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(6.0f, -0.3f, 2.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Chair.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-2.0f, -0.3f, 2.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Chair.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.0f, -0.3f, 2.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Chair.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-6.0f, -0.3f, 2.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Chair.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-8.0f, -0.3f, 2.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Chair.RenderModel();

		//Tree

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-8.0f, -1.2f, 6.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(8.0f, -1.2f, 9.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.0f, -1.2f, 13.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.0f, -1.2f, -13.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(12.0f, -1.2f, 11.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(12.0f, -1.2f, -13.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(11.0f, -1.2f, -10.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(11.5f, -1.2f, -8.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(11.5f, -1.2f, 20.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.0f, -1.2f, 25.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(9.0f, -1.2f, 30.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.5f, -1.2f, 34.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Tree.RenderModel();

		//Calle
		
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -1.05f, -15.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -1.05f, -13.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -1.05f, -11.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -1.05f, -9.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -1.05f, -7.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();
		
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -1.05f, -5.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -1.05f, -3.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -1.05f, -1.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -1.05f, 1.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -1.05f, 3.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -1.05f, 5.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -1.05f, 7.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -1.05f, 9.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -1.05f, 11.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -1.05f, 13.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -1.05f, 15.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		//Segundo camino

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-13.0f, -1.05f, -7.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-11.0f, -1.05f, -7.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-9.0f, -1.05f, -7.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-7.0f, -1.05f, -7.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-5.0f, -1.05f, -7.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-3.0f, -1.05f, -7.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.0f, -1.05f, -7.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.0f, -1.05f, -7.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.0f, -1.05f, -7.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, -1.05f, -7.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(7.0f, -1.05f, -7.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		//Tercer camino

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-13.0f, -1.05f, 7.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-11.0f, -1.05f, 7.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-9.0f, -1.05f, 7.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-7.0f, -1.05f, 7.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-5.0f, -1.05f, 7.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-3.0f, -1.05f, 7.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.0f, -1.05f, 7.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.0f, -1.05f, 7.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.0f, -1.05f, 7.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, -1.05f, 7.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(7.0f, -1.05f, 7.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		//Cuarto camino

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -1.05f, 17.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -1.05f, 19.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -1.05f, 21.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -1.05f, 23.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -1.05f, 25.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -1.05f, 27.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -1.05f, 29.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -1.05f, 31.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -1.05f, 33.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		RockWall.RenderModel();

		//lamparas

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, -5.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Lamp.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 5.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Lamp.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, -1.0f, -5.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Lamp.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, -1.0f, 5.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Lamp.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-13.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Lamp.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-13.0f, -1.0f, 20.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Lamp.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-13.0f, -1.0f, 30.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Lamp.RenderModel();

		//Animales

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.3f, 20.0f));
		model = glm::scale(model, glm::vec3(0.04f, 0.04f, 0.04f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		dog.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.1f, 25.0f));
		model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Cat.RenderModel();

		//Animación Pacman

		if(caminoPacman1 >= 32.0f || caminoPacman1 <= -12.0f)
		{
			booleanoGiroPacman1 = 1;
		}
		if(booleanoGiroPacman1 == 1)
		{
			if(cuentaGiroPacman1 < 180.0f)
			{
				cuentaGiroPacman1 += deltaTime * 20;
				giroPacman1 += deltaTime * 20;
			}
			else
			{
				booleanoGiroPacman1 = 0;
			}
		}
		if(booleanoGiroPacman1 == 0)
		{
			cuentaGiroPacman1 = 0;

			if(caminoPacman1 <= -12.0f)
			{
				booleanoPacman1 = 0;
			}
			else if(caminoPacman1 >= 32.0f)
			{
				booleanoPacman1 = 1;
			}
			if(booleanoPacman1 == 0)
			{
				if(deltaTime <= 3.0f)
				{
					caminoPacman1 += deltaTime * 3; 
				}
			}
			else if(booleanoPacman1 == 1)
			{
				if(deltaTime <= 3.0f)
				{
					caminoPacman1 -= deltaTime * 3; 
				}
			}
		}

		//Pacman
		
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -1.0f, caminoPacman1));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		model = glm::rotate(model, giroPacman1 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PacMan.RenderModel();


		//Pacman puestos

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-5.0f, -1.3f, -14.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PacMan.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-5.0f, -1.3f, 12.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PacMan.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, -1.1f, 22.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Girafa.RenderModel();

		//Globos
		
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, counterGlobos, 28.0f));
		model = glm::scale(model, glm::vec3(0.04f, 0.04f, 0.04f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Globo.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-2.0f, counterGlobos, 25.0f));
		model = glm::scale(model, glm::vec3(0.04f, 0.04f, 0.04f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Globo.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.0f, counterGlobos, 20.0f));
		model = glm::scale(model, glm::vec3(0.04f, 0.04f, 0.04f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Globo.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-8.0f, counterGlobos, 30.0f));
		model = glm::scale(model, glm::vec3(0.04f, 0.04f, 0.04f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Globo.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, counterGlobos, 25.0f));
		model = glm::scale(model, glm::vec3(0.04f, 0.04f, 0.04f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Globo.RenderModel();

		//Animación globos

		positionCamara = camera.getCameraPosition();
		if(positionCamara.x >= -10.0f && positionCamara.x <= 0.0f && positionCamara.z >= 20.0f && positionCamara.z <= 30.0f)
		{
			if(counterGlobos >= 3.0)
			{
				booleanoGlobos = 0;
			}
			if(counterGlobos <= 0.0)
			{
				booleanoGlobos = 1;
			}
			if(booleanoGlobos == 0)
			{
				counterGlobos -= deltaTime;
			}
			if(booleanoGlobos == 1)
			{
				counterGlobos += deltaTime;
			}
		}

		// Animación Luces

		if(positionCamara.x >= 30.0f && positionCamara.x <= 80.0f)
		{
			if(counterLuz1 <= -10)
			{
				booleanoLuz = 0;
			}
			if(counterLuz1 >= 30)
			{
				booleanoLuz = 1;
			}
			if(booleanoLuz == 0)
			{
				counterLuz1 += deltaTime * 20;
			}
			if(booleanoLuz == 1)
			{
				counterLuz1 -= deltaTime * 20;
			}
		}
		spotLights[17].SetPos(glm::vec3(60.0f, 20.0f, counterLuz1));
		spotLights[18].SetPos(glm::vec3(60.0f, 20.0f, -counterLuz1 + 20));

		//Globo keyFrame

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(posXGlobo + movGlobo_x, posYGlobo + movGlobo_y, 0.0f));
		model = glm::scale(model, glm::vec3(0.04f, 0.04f, 0.04f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, giroGlobo * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Globo.RenderModel();

		//Rockas

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-7.0f, -1.5f, 28.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Red.UseTexture();
		Roca.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(13.0f, -1.0f, 4.0f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Bathroom.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(13.0f, -1.0f, 0.0f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Bathroom.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(13.0f, -1.0f, -4.0f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Bathroom.RenderModel();

		//Faro

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, -1.5f, 24.0f));
		// model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Faro.RenderModel();


		//Carro Camicase
		glm::mat4 temp(1.0);
		glm::mat4 temp1(1.0);

		bool *keys = mainWindow.getKeys();

		if (keys[GLFW_KEY_M])
		{
			animacion = false;
		}

		if (keys[GLFW_KEY_N])
		{
			animacion = true;
		}

		if (animacion != true){
			deltaTmp = deltaTime;
			deltaTime = 0.0f;
		}
		else {
			deltaTime = deltaTmp;
		}

		switch (posicion_kamikaze)
		{
			case 0:
				angulo_kamikaze = 30.0f;
				velocidad_kamikaze = 50;
				booleanoIda_o_Regreso_kamikaze = false;
			case 1:
				angulo_kamikaze = 75.0f;
				velocidad_kamikaze = 60;
				break;
			case 2:
				angulo_kamikaze = 90.0f;
				velocidad_kamikaze = 70;
				break;
			case 3:
				angulo_kamikaze = 120.0f;
				velocidad_kamikaze = 80;
				break;
			case 4:
				angulo_kamikaze = 170.0f;
				velocidad_kamikaze = 80;
				break;
			case 5:
				angulo_kamikaze = 360.0f;
				velocidad_kamikaze = 100;
				booleanoIda_o_Regreso_kamikaze = true;
				break;
		}

		if (booleanoKamikaze == 0)
		{
			if (deltaTime > 15)
			{
				deltaTime = 0.0f;
			}
			animacionKamikaze += deltaTime * velocidad_kamikaze;
			if (animacionKamikaze >= angulo_kamikaze)
			{
				booleanoKamikaze = 1;
			}
		}
		else if (booleanoKamikaze == 1)
		{
			animacionKamikaze -= deltaTime * velocidad_kamikaze;
			if (animacionKamikaze <= -angulo_kamikaze)
			{
				booleanoKamikaze = 0;
				if (booleanoIda_o_Regreso_kamikaze != true)
				{
					posicion_kamikaze += 1;
				}
				else
				{
					posicion_kamikaze -= 1;
				}
			}
		}

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 3.0f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Plataforma.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, 0.0f, 0.0f));
		temp = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Mastil.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(temp, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0, 1.0, 0.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Escenario.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(temp, glm::vec3(0.0f, 8.0f, 0.0f));
		model = glm::rotate(model, animacionKamikaze*toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MastilCanoa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(temp, glm::vec3(0.0f, 8.0f, 0.0f));
		temp1 = model;
		model = glm::rotate(model, 180*toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, animacionKamikaze * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MastilCanoa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(temp1, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, animacionKamikaze * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Canoa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(temp1, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, animacionKamikaze * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Canoa.RenderModel();

		x_kamikaze = 6*cos((-animacionKamikaze -90) * toRadians);
		y_kamikaze = 6*sin((-animacionKamikaze -90) * toRadians) + 8;
		camera.posicionCameraKamikaze(glm::vec3(29.0f, y_kamikaze, x_kamikaze), animacionKamikaze);

		// Rueda de la fortuna
		temp = glm::mat4(1.0);
		temp1 = glm::mat4(1.0);

		model = glm::mat4(1.0);
		model = glm::translate(temp, glm::vec3(30.0f, -1.0f, 20.0f));
		temp = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Sosten.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(temp, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Base.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(temp, glm::vec3(0.0f, 11.52f, 0.0f));
		temp1 = model;
		model = glm::rotate(model, animacionRueda * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Rueda.RenderModel();

		x_rueda = 9.8 * cos(animacionRueda * toRadians);
		y_rueda = 9.8 * sin(animacionRueda * toRadians) + 10;

		camera.posicionCameraRuleta(glm::vec3(x_rueda + 30.0f, y_rueda, 20.0f));

		for(int i = 0; i < 32; i++)
		{
			x_rueda = 9.8 * cos((animacionRueda + 11.25 * i) * toRadians);
			y_rueda = 9.8 * sin((animacionRueda + 11.25 * i) * toRadians) + 10;

			model = glm::mat4(1.0);
			model = glm::translate(temp1, glm::vec3(0.0f, -9.8f, 0.0f));
			model = glm::translate(model, glm::vec3(x_rueda, y_rueda, 0.0));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			Canasta.RenderModel();
		}
		 
		//Animación Rueda

		animacionRueda += deltaTime * 5;
	
		deltaTime = deltaTmp;

		//Montana Rusa

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(60.0f, -1.4f, 10.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MontanaRusa.RenderModel();

		//Juego de los patos

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-5.0f, -1.0f, 20.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		ParedPato.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.1f, -1.0f, 19.7f));
		model = glm::scale(model, glm::vec3(0.3f, 1.6f, 6.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Shelf.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-9.0f, -0.9f, 19.8f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.02f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Table.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-9.65f, -0.3f, 19.8f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -angulo_pistola * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Arma.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-9.65f, -0.3f, 17.8f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Arma.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-9.65f, -0.3f, 21.8f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Arma.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-5.0f, -1.0f, 16.0f));
		model = glm::scale(model, glm::vec3(0.04f, 0.04f, 0.04f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Globo.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-5.0f, -1.0f, 24.0f));
		model = glm::scale(model, glm::vec3(0.04f, 0.04f, 0.04f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Globo.RenderModel();

		//Fila media

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.0f, -0.1f, recorridoPato4));
		model = glm::scale(model, glm::vec3(escalaPato4, escalaPato4, escalaPato4));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Duck.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.0f, -0.1f, recorridoPato5));
		model = glm::scale(model, glm::vec3(escalaPato5, escalaPato5, escalaPato5));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Duck.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.0f, -0.1f, recorridoPato6));
		model = glm::scale(model, glm::vec3(escalaPato6, escalaPato6, escalaPato6));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Duck.RenderModel();

		//Fila alta

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.0f, 0.5f, recorridoPato2));
		model = glm::scale(model, glm::vec3(escalaPato2, escalaPato2, escalaPato2));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Duck.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.0f, 0.5f, recorridoPato1));
		model = glm::scale(model, glm::vec3(escalaPato1, escalaPato1, escalaPato1));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Duck.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.0f, 0.5f, recorridoPato3));
		model = glm::scale(model, glm::vec3(escalaPato3, escalaPato3, escalaPato3));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Duck.RenderModel();

		//Fila Baja

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.0f, -0.7f, recorridoPato8));
		model = glm::scale(model, glm::vec3(escalaPato8, escalaPato8, escalaPato8));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Duck.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.0f, -0.7f, recorridoPato7));
		model = glm::scale(model, glm::vec3(escalaPato7, escalaPato7, escalaPato7));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Duck.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.0f, -0.7f, recorridoPato9));
		model = glm::scale(model, glm::vec3(escalaPato9, escalaPato9, escalaPato9));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Duck.RenderModel();

		//Animacion de los patos

		//Fila Superior		
		if(recorridoPato1 >= 23.0f)
		{
			direccionPato1 = 0;			
		}
		else if(recorridoPato1 <= 20.0f)
		{
			direccionPato1 = 1;
		}
		if(recorridoPato2 >= 21.5f)
		{
			direccionPato2 = 0;			
		}
		else if(recorridoPato2 <= 18.5f)
		{
			direccionPato2 = 1;
		}
		if(recorridoPato3 >= 20.0f)
		{
			direccionPato3 = 0;			
		}
		else if(recorridoPato3 <= 17.0f)
		{
			direccionPato3 = 1;
		}

		//Fila media
		if(recorridoPato4 >= 23.0f)
		{
			direccionPato4 = 0;			
		}
		else if(recorridoPato4 <= 20.0f)
		{
			direccionPato4 = 1;
		}
		if(recorridoPato5 >= 21.5f)
		{
			direccionPato5 = 0;			
		}
		else if(recorridoPato5 <= 18.5f)
		{
			direccionPato5 = 1;
		}
		if(recorridoPato6 >= 20.0f)
		{
			direccionPato6 = 0;			
		}
		else if(recorridoPato6 <= 17.0f)
		{
			direccionPato6 = 1;
		}

		//Fila iferior
		if(recorridoPato7 >= 23.0f)
		{
			direccionPato7 = 0;			
		}
		else if(recorridoPato7 <= 20.0f)
		{
			direccionPato7 = 1;
		}
		if(recorridoPato8 >= 21.5f)
		{
			direccionPato8 = 0;			
		}
		else if(recorridoPato8 <= 18.5f)
		{
			direccionPato8 = 1;
		}
		if(recorridoPato9 >= 20.0f)
		{
			direccionPato9 = 0;			
		}
		else if(recorridoPato9 <= 17.0f)
		{
			direccionPato9 = 1;
		}

		//Pato 1

		if(direccionPato1 == 1)
		{
			if(deltaTime <= 0.1f && patoVivo1 == 1)
			{
				if(patoSeleccionado == 1 || animacionCorriendo1 == 1) //Entonce se efectua animación de explosion
				{
					animacionCorriendo1 = 1;
					if(escalaPato1 <= 0.10f && patoAumentando1 == 1)
					{
						escalaPato1 += deltaTime / 10.0f;
					}
					else
					{
						patoAumentando1 = 0;
						escalaPato1 -= deltaTime / 10.0f;
					}
					if(escalaPato1 <= 0.0f)	
					{
						animacionCorriendo1 = 0;
						patoVivo1 = 0;
					}		
				}
				else
				{
					recorridoPato1 += deltaTime;
				}
			}
		}
		else if(direccionPato1== 0)
		{
			if(deltaTime <= 0.1f && patoVivo1 == 1)
			{
				if(patoSeleccionado == 1 || animacionCorriendo1 == 1) //Entonce se efectua animación de explosion
				{
					animacionCorriendo1 = 1;
					if(escalaPato1 <= 0.10f && patoAumentando1 == 1)
					{
						escalaPato1 += deltaTime / 10.0f;
					}
					else
					{
						patoAumentando1 = 0;
						escalaPato1 -= deltaTime / 10.0f;
					}
					if(escalaPato1 <= 0.0f)	
					{
						animacionCorriendo1 = 0;
						patoVivo1 = 0;
					}	
				}
				else
				{
					recorridoPato1 -= deltaTime;
				}
			}
		}

		//Pato 2

		if(direccionPato2 == 1)
		{
			if(deltaTime <= 0.1f && patoVivo2 == 1)
			{
				if(patoSeleccionado == 2 || animacionCorriendo2 == 1) //Entonce se efectua animación de explosion
				{
					animacionCorriendo2 = 1;
					if(escalaPato2 <= 0.10f && patoAumentando2 == 1)
					{
						escalaPato2 += deltaTime / 10.0f;
					}
					else
					{
						patoAumentando2 = 0;
						escalaPato2 -= deltaTime / 10.0f;
					}
					if(escalaPato2 <= 0.0f)	
					{
						animacionCorriendo2 = 0;
						patoVivo2 = 0;
					}		
				}
				else
				{
					recorridoPato2 += deltaTime;
				}
			}
		}
		else if(direccionPato2 == 0)
		{
			if(deltaTime <= 0.1f && patoVivo2 == 1)
			{
				if(patoSeleccionado == 2 || animacionCorriendo2 == 1) //Entonce se efectua animación de explosion
				{
					animacionCorriendo2 = 1;
					if(escalaPato2 <= 0.10f && patoAumentando2 == 1)
					{
						escalaPato2 += deltaTime / 10.0f;
					}
					else
					{
						patoAumentando2 = 0;
						escalaPato2 -= deltaTime / 10.0f;
					}
					if(escalaPato2 <= 0.0f)	
					{
						animacionCorriendo2 = 0;
						patoVivo2 = 0;
					}	
				}
				else
				{
					recorridoPato2 -= deltaTime;
				}
			}
		}

		//Pato 3

		if(direccionPato3 == 1) 
		{
			if(deltaTime <= 0.1f && patoVivo3 == 1)
			{
				if(patoSeleccionado == 3 || animacionCorriendo3 == 1) //Entonce se efectua animación de explosion
				{
					animacionCorriendo3 = 1;
					if(escalaPato3 <= 0.10f && patoAumentando3 == 1)
					{
						escalaPato3 += deltaTime / 10.0f;
					}
					else
					{
						patoAumentando3 = 0;
						escalaPato3 -= deltaTime / 10.0f;
					}
					if(escalaPato3 <= 0.0f)	
					{
						animacionCorriendo3 = 0;
						patoVivo3 = 0;
					}		
				}
				else
				{
					recorridoPato3 += deltaTime;
				}
			}
		}
		else if(direccionPato3 == 0)
		{
			if(deltaTime <= 0.1f && patoVivo3 == 1)
			{
				if(patoSeleccionado == 3 || animacionCorriendo3 == 1) //Entonce se efectua animación de explosion
				{
					animacionCorriendo3 = 1;
					if(escalaPato3 <= 0.10f && patoAumentando3 == 1)
					{
						escalaPato3 += deltaTime / 10.0f;
					}
					else
					{
						patoAumentando3 = 0;
						escalaPato3 -= deltaTime / 10.0f;
					}
					if(escalaPato3 <= 0.0f)	
					{
						animacionCorriendo3 = 0;
						patoVivo3 = 0;
					}	
				}
				else
				{
					recorridoPato3 -= deltaTime;
				}
			}
		}

		//Pato 4

		if(direccionPato4 == 1) 
		{
			if(deltaTime <= 0.1f && patoVivo4 == 1)
			{
				if(patoSeleccionado == 4 || animacionCorriendo4 == 1) //Entonce se efectua animación de explosion
				{
					animacionCorriendo4 = 1;
					if(escalaPato4 <= 0.10f && patoAumentando4 == 1)
					{
						escalaPato4 += deltaTime / 10.0f;
					}
					else
					{
						patoAumentando4 = 0;
						escalaPato4 -= deltaTime / 10.0f;
					}
					if(escalaPato4 <= 0.0f)	
					{
						animacionCorriendo4 = 0;
						patoVivo4 = 0;
					}		
				}
				else
				{
					recorridoPato4 += deltaTime;
				}
			}
		}
		else if(direccionPato4 == 0)
		{
			if(deltaTime <= 0.1f && patoVivo4 == 1)
			{
				if(patoSeleccionado == 4 || animacionCorriendo4 == 1) //Entonce se efectua animación de explosion
				{
					animacionCorriendo4 = 1;
					if(escalaPato4 <= 0.10f && patoAumentando4 == 1)
					{
						escalaPato4 += deltaTime / 10.0f;
					}
					else
					{
						patoAumentando4 = 0;
						escalaPato4 -= deltaTime / 10.0f;
					}
					if(escalaPato4 <= 0.0f)	
					{
						animacionCorriendo4 = 0;
						patoVivo4 = 0;
					}	
				}
				else
				{
					recorridoPato4 -= deltaTime;
				}
			}
		}

		//Pato 5

		if(direccionPato5 == 1) 
		{
			if(deltaTime <= 0.1f && patoVivo5 == 1)
			{
				if(patoSeleccionado == 5 || animacionCorriendo5 == 1) //Entonce se efectua animación de explosion
				{
					animacionCorriendo5 = 1;
					if(escalaPato5 <= 0.10f && patoAumentando5 == 1)
					{
						escalaPato5 += deltaTime / 10.0f;
					}
					else
					{
						patoAumentando5 = 0;
						escalaPato5 -= deltaTime / 10.0f;
					}
					if(escalaPato5 <= 0.0f)	
					{
						animacionCorriendo5 = 0;
						patoVivo5 = 0;
					}		
				}
				else
				{
					recorridoPato5 += deltaTime;
				}
			}
		}
		else if(direccionPato5 == 0)
		{
			if(deltaTime <= 0.1f && patoVivo5 == 1)
			{
				if(patoSeleccionado == 5 || animacionCorriendo5 == 1) //Entonce se efectua animación de explosion
				{
					animacionCorriendo5 = 1;
					if(escalaPato5 <= 0.10f && patoAumentando5 == 1)
					{
						escalaPato5 += deltaTime / 10.0f;
					}
					else
					{
						patoAumentando5 = 0;
						escalaPato5 -= deltaTime / 10.0f;
					}
					if(escalaPato5 <= 0.0f)	
					{
						animacionCorriendo5 = 0;
						patoVivo5 = 0;
					}	
				}
				else
				{
					recorridoPato5 -= deltaTime;
				}
			}
		}

		//Pato 6
 
		if(direccionPato6 == 1) 
		{
			if(deltaTime <= 0.1f && patoVivo6 == 1)
			{
				if(patoSeleccionado == 6 || animacionCorriendo6 == 1) //Entonce se efectua animación de explosion
				{
					animacionCorriendo6 = 1;
					if(escalaPato6 <= 0.10f && patoAumentando6 == 1)
					{
						escalaPato6 += deltaTime / 10.0f;
					}
					else
					{
						patoAumentando6 = 0;
						escalaPato6 -= deltaTime / 10.0f;
					}
					if(escalaPato6 <= 0.0f)	
					{
						animacionCorriendo6 = 0;
						patoVivo6 = 0;
					}		
				}
				else
				{
					recorridoPato6 += deltaTime;
				}
			}
		}
		else if(direccionPato6 == 0)
		{
			if(deltaTime <= 0.1f && patoVivo6 == 1)
			{
				if(patoSeleccionado == 6 || animacionCorriendo6 == 1) //Entonce se efectua animación de explosion
				{
					animacionCorriendo6 = 1;
					if(escalaPato6 <= 0.10f && patoAumentando6 == 1)
					{
						escalaPato6 += deltaTime / 10.0f;
					}
					else
					{
						patoAumentando6 = 0;
						escalaPato6 -= deltaTime / 10.0f;
					}
					if(escalaPato6 <= 0.0f)	
					{
						animacionCorriendo6 = 0;
						patoVivo6 = 0;
					}	
				}
				else
				{
					recorridoPato6 -= deltaTime;
				}
			}
		}

		//Pato 7

		if(direccionPato7 == 1) 
		{
			if(deltaTime <= 0.1f && patoVivo7 == 1)
			{
				if(patoSeleccionado == 7 || animacionCorriendo7 == 1) //Entonce se efectua animación de explosion
				{
					animacionCorriendo7 = 1;
					if(escalaPato7 <= 0.10f && patoAumentando7 == 1)
					{
						escalaPato7 += deltaTime / 10.0f;
					}
					else
					{
						patoAumentando7 = 0;
						escalaPato7 -= deltaTime / 10.0f;
					}
					if(escalaPato7 <= 0.0f)	
					{
						animacionCorriendo7 = 0;
						patoVivo7 = 0;
					}		
				}
				else
				{
					recorridoPato7 += deltaTime;
				}
			}
		}
		else if(direccionPato7 == 0)
		{
			if(deltaTime <= 0.1f && patoVivo7 == 1)
			{
				if(patoSeleccionado == 7 || animacionCorriendo7 == 1) //Entonce se efectua animación de explosion
				{
					animacionCorriendo7 = 1;
					if(escalaPato7 <= 0.10f && patoAumentando7 == 1)
					{
						escalaPato7 += deltaTime / 10.0f;
					}
					else
					{
						patoAumentando7 = 0;
						escalaPato7 -= deltaTime / 10.0f;
					}
					if(escalaPato7 <= 0.0f)	
					{
						animacionCorriendo7 = 0;
						patoVivo7 = 0;
					}	
				}
				else
				{
					recorridoPato7 -= deltaTime;
				}
			}
		}

		//Pato 8

		if(direccionPato8 == 1) 
		{
			if(deltaTime <= 0.1f && patoVivo8 == 1)
			{
				if(patoSeleccionado == 8 || animacionCorriendo8 == 1) //Entonce se efectua animación de explosion
				{
					animacionCorriendo8 = 1;
					if(escalaPato8 <= 0.10f && patoAumentando8 == 1)
					{
						escalaPato8 += deltaTime / 10.0f;
					}
					else
					{
						patoAumentando8 = 0;
						escalaPato8 -= deltaTime / 10.0f;
					}
					if(escalaPato8 <= 0.0f)	
					{
						animacionCorriendo8 = 0;
						patoVivo8 = 0;
					}		
				}
				else
				{
					recorridoPato8 += deltaTime;
				}
			}
		}
		else if(direccionPato8 == 0)
		{
			if(deltaTime <= 0.1f && patoVivo8 == 1)
			{
				if(patoSeleccionado == 8 || animacionCorriendo8 == 1) //Entonce se efectua animación de explosion
				{
					animacionCorriendo8 = 1;
					if(escalaPato8 <= 0.10f && patoAumentando8 == 1)
					{
						escalaPato8 += deltaTime / 10.0f;
					}
					else
					{
						patoAumentando8 = 0;
						escalaPato8 -= deltaTime / 10.0f;
					}
					if(escalaPato8 <= 0.0f)	
					{
						animacionCorriendo8 = 0;
						patoVivo8 = 0;
					}	
				}
				else
				{
					recorridoPato8 -= deltaTime;
				}
			}
		}

		//Pato 9

		if(direccionPato9 == 1) 
		{
			if(deltaTime <= 0.1f && patoVivo9 == 1)
			{
				if(patoSeleccionado == 9 || animacionCorriendo9 == 1) //Entonce se efectua animación de explosion
				{
					animacionCorriendo9 = 1;
					if(escalaPato9 <= 0.10f && patoAumentando9 == 1)
					{
						escalaPato9 += deltaTime / 10.0f;
					}
					else
					{
						patoAumentando9 = 0;
						escalaPato9 -= deltaTime / 10.0f;
					}
					if(escalaPato9 <= 0.0f)	
					{
						animacionCorriendo9 = 0;
						patoVivo9 = 0;
					}		
				}
				else
				{
					recorridoPato9 += deltaTime;
				}
			}
		}
		else if(direccionPato9 == 0)
		{
			if(deltaTime <= 0.1f && patoVivo9 == 1)
			{
				if(patoSeleccionado == 9 || animacionCorriendo9 == 1) //Entonce se efectua animación de explosion
				{
					animacionCorriendo9 = 1;
					if(escalaPato9 <= 0.10f && patoAumentando9 == 1)
					{
						escalaPato9 += deltaTime / 10.0f;
					}
					else
					{
						patoAumentando9 = 0;
						escalaPato9 -= deltaTime / 10.0f;
					}
					if(escalaPato9 <= 0.0f)	
					{
						animacionCorriendo9 = 0;
						patoVivo9 = 0;
					}	
				}
				else
				{
					recorridoPato9 -= deltaTime;
				}
			}
		}
		

		if(camera.getCameraPosition().z >= 19.0f && camera.getCameraPosition().z <= 21.0f && camera.getCameraPosition().x <= -11.0f && camera.getCameraPosition().x >= -13.0f)
		{
			if (keys[GLFW_KEY_F] && tiempoDisparo >= 3.0f)
			{
				patoSeleccionado = rand() % 10;
				tiempoDisparo = 0.0f;
				angulo_pistola = 0.0f;
				subida_pistola = 0.0f;
				inicio_pistola = true;
			}
			else if(tiempoDisparo >= 2.0f) 
			{
				inicio_pistola = false;
			}
		}

		if(tiempoDisparo < 3.0f)
		{
			tiempoDisparo += deltaTime;
			camera.setCameraPosition(-12.0f, 0.0f, 20.0f);	
		}

		if(tiempoDisparo < 2.0f && angulo_pistola < 30.0f)
		{
			angulo_pistola += deltaTime*12.0f;
		}else if(angulo_pistola > 0.0f){
			angulo_pistola -= deltaTime*12.0f;
		}

		//printf("valor de inicio_pistola %d\n", inicio_pistola);
		musica3D(camera.getCameraPosition(), musica_3d);
		efecto_pistola(inicio_pistola, musica_pistola);

		// printf("Position %f, %f, %f",camera.getCameraPosition().x,camera.getCameraPosition().y,camera.getCameraPosition().z);

		glUseProgram(0);

		mainWindow.swapBuffers();
	}
	return 0;
}


