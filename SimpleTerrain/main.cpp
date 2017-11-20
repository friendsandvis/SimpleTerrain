
#include"support.h"
#include"socamera.h"
#include"modelloader.h"


//---------------------------data------------------------------------
float NEARPLANE = 0.1f, FARPLANE = 1000.0f;
Window window;
socamera::FPSCamera maincamera, recam;
socamera::Camera reflectcamera;
somath::mat4 basicprojectionmat, model;
float distorsiontime = 0.0;
float speedofdis = 0.05;
somath::vec3 lightpos(10, 10, 10);

//meshes
Plane plane1;
TerrainMesh terrain2;

//programs
soprogram::Program pwaterplane, pviewplane, pterrainplane, pskybox, pblur,ptree;
Skybox sky;

//framebuffers
FrameBuffer fborefract, fboreflect, fboscene, fboblurH, fboblurV;

//buffer and image pointers
GLuint dvmapid, normalmapid, hmapid;
GLuint64 dvmapidbindless, normalmapidbindless, hmapidbindless;

//Models
Model tree("textures/");




//------------------------------functions-----------------------------

void glfwMouseButtoncallback(GLFWwindow*, int, int, int);
void keyListener(GLFWwindow*, int, int, int, int);
void mouseListener(GLFWwindow*, double, double);




void init()
{
	//camera setup and matricies
	maincamera.set(somath::vec3(5.0, 5.0, -5.0), somath::vec3(0.0), false);
	recam.set(somath::vec3(5.0, -5.0, -5.0), somath::vec3(0.0), false);
	maincamera.setSpeed(30.0);
	recam.setSpeed(30.0);
	somath::vec3 maincampos = maincamera.getPos();
	maincampos = somath::vec3(maincampos.x, -maincampos.y, maincampos.z);
	reflectcamera.set(maincampos, somath::vec3(0.0), false);
	maincamera.setProjectionMatrix(window.getWidth() / (float)window.getHeight(), (float)(somath::toRadians(45.0f)), NEARPLANE, FARPLANE);



	//program initialization
	pviewplane.makeProgram("Shaders/vplanesimple.txt", "Shaders/fplanesimple.txt");
	pwaterplane.makeProgram("Shaders/vplane.txt", "Shaders/fplanewater.txt");
	pterrainplane.makeProgram("Shaders/vterrain.txt","Shaders/gterrain.txt", "Shaders/fterrain.txt");
	pskybox.makeProgram("Shaders/vskybox.txt", "Shaders/fskybox.txt");
	pblur.makeProgram("Shaders/vblur.txt","shaders/fblur.txt");
	ptree.makeProgram("Shaders/vtree.txt", "shaders/ftree.txt");

	//mesh initialization
	plane1.setPlane();
	terrain2.setTerrainMesh(1000, 1000,1.0,1.0, 5,30.0);
	terrain2.setHeightMap(10.0f);

	//Models
	tree.setModel("Models/Tree.obj");
	tree.makeBuffers();



	//framebuffer initialization
	fborefract.makeFrameBuffer(window.getWidth(),window.getHeight(),true);
	fboreflect.makeFrameBuffer(window.getWidth(), window.getHeight(), true);
	fboscene.makeFrameBuffer(window.getWidth(), window.getHeight(), true);
	fboblurH.makeFrameBuffer(window.getWidth(), window.getHeight(), false);
	fboblurV.makeFrameBuffer(window.getWidth(), window.getHeight(), false);

	//textures and skybox initialization
	const char* files[6] = { "textures/skyright.jpg","textures/skyleft.jpg","textures/skyup.jpg","textures/skydown.jpg","textures/skyback.jpg","textures/skyfront.jpg" };
	sky.setSkybox(files);
	dvmapid = getTexture("textures/dudv.png",5);
	normalmapid = getTexture("textures/normalmap.png",5);

	//make texture bindless
	dvmapidbindless = glGetTextureHandleARB(dvmapid);
	normalmapidbindless = glGetTextureHandleARB(normalmapid);
	hmapidbindless = glGetTextureHandleARB(hmapid);
	glMakeTextureHandleResidentARB(dvmapidbindless);
	glMakeTextureHandleResidentARB(normalmapidbindless);
	glMakeTextureHandleResidentARB(hmapidbindless);

}

void update(double delta)
{
	//camera update
	maincamera.update(delta);
	somath::vec3 tem = maincamera.getPos();
	tem.y = -tem.y;
	somath::vec3 tem2 = maincamera.getTargetDirection();
	tem2.y = -tem2.y;
	recam.set(tem, tem2,true);


	//distortion in uv map(rather offset in texcoord)
	distorsiontime += speedofdis*delta;
	distorsiontime = fmod(distorsiontime, 1.0);

}

void destroy()
{

	//meshes
	plane1.destroy();
	terrain2.destroyTerrain();

	//skybox
	sky.destroy();

	//framebuffers
	fborefract.destroy();
	fboreflect.destroy();
	fboscene.destroy();
	fboblurH.destroy();
	fboblurV.destroy();

	//buffer and image pointers
	glDeleteTextures(1, &dvmapid);
	glDeleteTextures(1, &normalmapid);
	glDeleteTextures(1, &hmapid);

	//Models
	tree.destroy();
}

void render()
{
	//------------------------------------refraction render scene-------------------------------------------

	//framebuffer for refraction
	fborefract.bind();									
	glClearColor(0.1, 0.5, 0.65, 1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//terrain plane render
	pterrainplane.useProgram();
	pterrainplane.setUniformMat4("project", maincamera.getProjectionMatrix().projectionmatrix);
	pterrainplane.setUniformMat4("view", maincamera.getViewMatrix());
	pterrainplane.setUniformInteger("clipactive", 0.0);
	pterrainplane.setUniformVec3("lightpos", lightpos);
	pterrainplane.setUniformVec2("worldsize", terrain2.getWorldSize());
	pterrainplane.setUniformVec2("worldscale", terrain2.getWorldScale());
	glUniformHandleui64ARB(glGetUniformLocation(pterrainplane.getProgram(), "heightmap"), terrain2.getHmapBindless());
	terrain2.render();


	ptree.useProgram();
	ptree.setUniformMat4("project", maincamera.getProjectionMatrix().projectionmatrix);
	ptree.setUniformMat4("view", maincamera.getViewMatrix());
	ptree.setUniformMat4("model", somath::mat4());
	ptree.setUniformVec3("light1.lightpos", somath::vec3(1.0));
	ptree.setUniformVec3("light1.lightcolor", somath::vec3(1.0, 1.0, 1.0));
	ptree.setUniformVec3("camerapos", maincamera.getPos());
	tree.render(ptree);

	
	//render skybox
	pskybox.useProgram();
	pskybox.setUniformMat4("project", maincamera.getProjectionMatrix().projectionmatrix);
	pskybox.setUniformMat4("view", somath::mat4(somath::mat3(maincamera.getViewMatrix())));
	glUniformHandleui64ARB(glGetUniformLocation(pskybox.getProgram(), "cubeimage"), sky.getSkyboxTexBindLess());
	sky.render();


	
	//------------------------------------reflection render scene-------------------------------------------

	//framebuffer for reflection
	fboreflect.bind();
	glClearColor(0.1, 0.5, 0.65, 1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//render terrain
	pterrainplane.useProgram();
	pterrainplane.setUniformMat4("project", maincamera.getProjectionMatrix().projectionmatrix);
	pterrainplane.setUniformMat4("view", recam.getViewMatrix());
	pterrainplane.setUniformInteger("clipactive", 1.0);
	pterrainplane.setUniformVec3("lightpos", lightpos);
	pterrainplane.setUniformVec2("worldsize", terrain2.getWorldSize());
	pterrainplane.setUniformVec2("worldscale", terrain2.getWorldScale());
	glUniformHandleui64ARB(glGetUniformLocation(pterrainplane.getProgram(), "heightmap"), terrain2.getHmapBindless());
	terrain2.render();

	ptree.useProgram();
	ptree.setUniformMat4("project", maincamera.getProjectionMatrix().projectionmatrix);
	ptree.setUniformMat4("view", recam.getViewMatrix());
	ptree.setUniformMat4("model", somath::mat4());
	ptree.setUniformVec3("light1.lightpos", somath::vec3(1.0));
	ptree.setUniformVec3("light1.lightcolor", somath::vec3(1.0, 1.0, 1.0));
	ptree.setUniformVec3("camerapos", maincamera.getPos());
	tree.render(ptree);

	//render skybox
	pskybox.useProgram();
	pskybox.setUniformMat4("project", maincamera.getProjectionMatrix().projectionmatrix);
	pskybox.setUniformMat4("view", somath::mat4(somath::mat3(recam.getViewMatrix())));
	glUniformHandleui64ARB(glGetUniformLocation(pskybox.getProgram(), "cubeimage"), sky.getSkyboxTexBindLess());
	sky.render();




	//-------------------------------------render the main scene-----------------------------

	//using a seperate FBO for postprocessing
	fboscene.bind();

	glClearColor(0.0, 1.0, 0.0, 1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	
	//render terrain
	pterrainplane.useProgram();
	pterrainplane.setUniformMat4("project", maincamera.getProjectionMatrix().projectionmatrix);
	pterrainplane.setUniformMat4("view", maincamera.getViewMatrix());
	pterrainplane.setUniformInteger("clipactive", 0.0);
	pterrainplane.setUniformVec3("lightpos", lightpos);
	pterrainplane.setUniformVec2("worldsize",terrain2.getWorldSize());
	pterrainplane.setUniformVec2("worldscale",terrain2.getWorldScale());
	glUniformHandleui64ARB(glGetUniformLocation(pterrainplane.getProgram(), "heightmap"), terrain2.getHmapBindless());
	terrain2.render();

	ptree.useProgram();
	ptree.setUniformMat4("project", maincamera.getProjectionMatrix().projectionmatrix);
	ptree.setUniformMat4("view", maincamera.getViewMatrix());
	ptree.setUniformMat4("model", somath::mat4());
	ptree.setUniformVec3("light1.lightpos", somath::vec3(1.0));
	ptree.setUniformVec3("light1.lightcolor", somath::vec3(1.0, 1.0, 1.0));
	ptree.setUniformVec3("camerapos", maincamera.getPos());
	tree.render(ptree);

	//render waterplane with both the textures of reflection and refraction part
	pwaterplane.useProgram();
	pwaterplane.setUniformMat4("project", maincamera.getProjectionMatrix().projectionmatrix);
	pwaterplane.setUniformMat4("view", maincamera.getViewMatrix());
	pwaterplane.setUniformMat4("model", somath::mat4());
	pwaterplane.setUniformVec3("camerapos", maincamera.getPos());
	pwaterplane.setUniformFloat("scale", 2 * 25 * 3 * 5);
	pwaterplane.setUniformFloat("tiles", 8);
	pwaterplane.setUniformFloat("distortionoffset", distorsiontime);
	pwaterplane.setUniformVec3("lightpos", lightpos);
	pwaterplane.setUniformFloat("np", NEARPLANE);
	pwaterplane.setUniformFloat("fp", FARPLANE);
	glUniformHandleui64ARB(glGetUniformLocation(pwaterplane.getProgram(), "tex1"), fboreflect.getTextureBindLess());
	glUniformHandleui64ARB(glGetUniformLocation(pwaterplane.getProgram(), "tex2"), fborefract.getTextureBindLess());
	glUniformHandleui64ARB(glGetUniformLocation(pwaterplane.getProgram(), "dvmap"), dvmapidbindless);
	glUniformHandleui64ARB(glGetUniformLocation(pwaterplane.getProgram(), "normalmap"), normalmapidbindless);
	glUniformHandleui64ARB(glGetUniformLocation(pwaterplane.getProgram(), "depthmap"), fborefract.getDepthTextureBindLess());
	glEnable(GL_BLEND);
	plane1.render();
	glDisable(GL_BLEND);

	//render skybox
	pskybox.useProgram();
	pskybox.setUniformMat4("project", maincamera.getProjectionMatrix().projectionmatrix);
	pskybox.setUniformMat4("view", somath::mat4(somath::mat3(maincamera.getViewMatrix())));
	glUniformHandleui64ARB(glGetUniformLocation(pskybox.getProgram(), "cubeimage"), sky.getSkyboxTexBindLess());
	sky.render();
	
	



	
	//--------------------------------------------------post processing---------------------------------------------

	//bluring(2 pass gaussian blur)    *4 times
	for (int z = 0;z < 3;z++)
	{

		//-----------------horizontal bluring----------------
		fboblurH.bind();

		glClearColor(0.0, 1.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);

		pblur.useProgram();
		pblur.setUniformVec2("sizeofscreen", somath::vec2(window.getWidth() , window.getHeight() ));
		pblur.setUniformInteger("horizontalblur", 1);
		if (z == 0)
			glUniformHandleui64ARB(glGetUniformLocation(pblur.getProgram(), "image"), fboscene.getTextureBindLess());
		else
			glUniformHandleui64ARB(glGetUniformLocation(pblur.getProgram(), "image"), fboblurV.getTextureBindLess());

		plane1.render();



		//--------------vertical bluring------------------
		fboblurV.bind();

		glClearColor(1.0, 0.0, 0.0, 0.0);
		glClear( GL_COLOR_BUFFER_BIT);

		pblur.useProgram();
		pblur.setUniformVec2("sizeofscreen", somath::vec2(window.getWidth(), window.getHeight()));
		pblur.setUniformInteger("horizontalblur", 0);

		glUniformHandleui64ARB(glGetUniformLocation(pblur.getProgram(), "image"), fboblurH.getTextureBindLess());

		plane1.render();

	}
	


	//render the final mainterrain fbo texture with poost pocessing
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	pviewplane.useProgram();
	pviewplane.setUniformFloat("np", NEARPLANE);
	pviewplane.setUniformFloat("fp", FARPLANE);
	glUniformHandleui64ARB(glGetUniformLocation(pviewplane.getProgram(),"image"), fboscene.getTextureBindLess());
	glUniformHandleui64ARB(glGetUniformLocation(pviewplane.getProgram(), "imageblured"), fboblurV.getTextureBindLess());
	glUniformHandleui64ARB(glGetUniformLocation(pviewplane.getProgram(), "imagedepth"), fboscene.getDepthTextureBindLess());
	plane1.render();
	

}


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);

	window.setWindow(1920, 1080,"Simple Terrain");
	//-------------------callbacks---------------------
	glfwSetMouseButtonCallback(window.getWindowID(), glfwMouseButtoncallback);
	glfwSetKeyCallback(window.getWindowID(), keyListener);
	glfwSetCursorPosCallback(window.getWindowID(), mouseListener);

	glfwSetInputMode(window.getWindowID(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwMakeContextCurrent(window.getWindowID());

	glewExperimental = GL_TRUE;
	glewInit();

	glViewport(0, 0, window.getWidth(), window.getHeight());

	init();
	

	double prevtime = 0, currenttime, delta;

	glClearColor(0.1, 0.5, 0.65, 1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CLIP_PLANE0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);


	while (glfwWindowShouldClose(window.getWindowID()) == GL_FALSE)
	{
		glfwPollEvents();
		glClearColor(0.1, 0.5, 0.65, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		currenttime = glfwGetTime();
		delta = currenttime - prevtime;
		prevtime = currenttime;
		update(delta);

		render();

		glfwSwapBuffers(window.getWindowID());
	}
	//-------------------------game resource clearing------------------------------
	
	destroy();
	window.getWindowID();
	window.destroyWindow();
	glfwTerminate();

	return 0;
}

void glfwMouseButtoncallback(GLFWwindow* window, int button, int action, int mod)
{

}

void mouseListener(GLFWwindow* window, double xpos, double ypos)
{
	maincamera.mouseListener(window, xpos, ypos);
	recam.mouseListener(window, xpos, ypos);
}

void keyListener(GLFWwindow* win, int key, int mod, int action, int unknown)
{
	maincamera.keyListener(win, key, mod, action, unknown);
	recam.keyListener(win, key, mod, action, unknown);
	if (key == GLFW_KEY_ESCAPE)
		glfwSetWindowShouldClose(window.getWindowID(), GLFW_TRUE);
}



