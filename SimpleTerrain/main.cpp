
#include"support.h"
#include"socamera.h"



//----------------------------data---------------------------------
//position of trees
GLfloat treepositions[] =
{
	5.0,0.0,5.0,
	10.0,0.0,10.0,
	0.0,0.0,0.0,
	70.0,0.0,5.0,
	100.0,0.0,150.0
};


//------------------------------functions-----------------------------
float NEARPLANE = 0.1f, FARPLANE = 1000.0f;
Window window;


void glfwMouseButtoncallback(GLFWwindow*, int, int, int);
void keyListener(GLFWwindow*, int, int, int, int);
void mouseListener(GLFWwindow*, double, double);


Plane plane1;
TerrainMesh terrain2;
soprogram::Program pplane,pplanesimple, terrainplane, pskybox, pblur,pcube1;
Skybox sky;

FrameBuffer fborefract, fboreflect, fboscene, fboblur1, fboblur2;

socamera::FPSCamera maincamera, recam;
socamera::Camera reflectcamera;
somath::mat4 basicprojectionmat, model;

GLuint dvmapid, normalmapid,hmapid;
GLuint64 dvmapidbindless, normalmapidbindless,hmapidbindless;
float distorsiontime = 0.0;
float speedofdis = 0.05;

somath::vec3 lightpos(0, 10, 10);
/*
Model* cube1;
Materials* materialscube1;

ImageLoader loader1;
*/

void init()
{
	maincamera.set(somath::vec3(5.0, 5.0, -5.0), somath::vec3(0.0), false);
	recam.set(somath::vec3(5.0, -5.0, -5.0), somath::vec3(0.0), false);
	maincamera.setSpeed(30.0);
	recam.setSpeed(30.0);

	somath::vec3 maincampos = maincamera.getPos();
	maincampos = somath::vec3(maincampos.x, -maincampos.y, maincampos.z);
	reflectcamera.set(maincampos, somath::vec3(0.0), false);


	//basicprojectionmat= glm::perspective((float)(glm::radians(45.0f)), WIDTHOFWINDOW / (float)HEIGHTOFWINDOW, NEARPLANE,FARPLANE);
	//basicprojectionmat = glm::ortho(-50.0,50.0,-50.0,50.0,(double)(-1.0*50.0),(double)50.0);
	maincamera.setProjectionMatrix(window.getWidth() / (float)window.getHeight(), (float)(somath::toRadians(45.0f)), NEARPLANE, FARPLANE);
	//basicprojectionmat = makeOrthogonalProjectionMatrix(-50.0, 50.0, -50.0, 50.0, (double)(-1.0*50.0), (double)50.0);

	pplanesimple.makeProgram("Shaders/vplanesimple.txt", "Shaders/fplanesimple.txt");
	pplane.makeProgram("Shaders/vplane.txt", "Shaders/fplanewater.txt");
	terrainplane.makeProgram("Shaders/vterrain.txt","Shaders/gterrain.txt", "Shaders/fterrain.txt");
	pskybox.makeProgram("Shaders/vskybox.txt", "Shaders/fskybox.txt");
	//pblur.makeProgram("Shaders/vplanebluring.txt", "Shaders/fplanebluring.txt");
	//pcube1.makeProgram("Shaders/vcube1.txt", "Shaders/fcube1.txt");

	plane1.setPlane();
	terrain2.setTerrainMesh(1000, 1000,0.5,0.5, 5,30.0);
	terrain2.setHeightMap(10.0f);

	/*
	vbotreepos = new VBO();
	glBindBuffer(GL_ARRAY_BUFFER, vbotreepos->getVBO());
	glBufferData(GL_ARRAY_BUFFER, sizeof(treepositions), treepositions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	*/

	fborefract.makeFrameBuffer(window.getWidth(),window.getHeight(),true);
	fboreflect.makeFrameBuffer(window.getWidth(), window.getHeight(), true);
	fboscene.makeFrameBuffer(window.getWidth(), window.getHeight(), true);
	fboblur1.makeFrameBuffer(window.getWidth(), window.getHeight(), false);
	fboblur2.makeFrameBuffer(window.getWidth(), window.getHeight(), false);

	const char* files[6] = { "textures/skyright.jpg","textures/skyleft.jpg","textures/skyup.jpg","textures/skydown.jpg","textures/skyback.jpg","textures/skyfront.jpg" };
	sky.setSkybox(files);
	dvmapid = getTexture("textures/dudv.png",5);
	normalmapid = getTexture("textures/normalmap.png",5);
	hmapid=getTextureGreyScale("textures/hmap.png", 1);

	dvmapidbindless = glGetTextureHandleARB(dvmapid);
	normalmapidbindless = glGetTextureHandleARB(normalmapid);
	hmapidbindless = glGetTextureHandleARB(hmapid);

	glMakeTextureHandleResidentARB(dvmapidbindless);
	glMakeTextureHandleResidentARB(normalmapidbindless);
	glMakeTextureHandleResidentARB(hmapidbindless);

	/*
	materialscube1 = new Materials("tree.mtl", &loader1);
	cube1 = new Model("tree.obj", 0.95f, materialscube1);

	pcube1->useProgram();
	for (int z = 0;z < materialscube1->getMaterialCount();z++)
	{
		stringstream ss;
		ss << "materials[" << z << "]";

		stringstream ss2;
		ss2 << ss.str() << ".diffuse";
		pcube1->setUniformVec3(ss2.str().c_str(), materialscube1->getMaterial(z)->diffuse);
		ss2.str("");
		ss2.clear();

		ss2 << ss.str() << ".ambient";
		pcube1->setUniformVec3(ss2.str().c_str(), materialscube1->getMaterial(z)->ambient);
		ss2.str("");
		ss2.clear();

		ss2 << ss.str() << ".specular";
		pcube1->setUniformVec3(ss2.str().c_str(), materialscube1->getMaterial(z)->specular);
		ss2.str("");
		ss2.clear();

		ss2 << ss.str() << ".specularexp";
		pcube1->setUniformFloat(ss2.str().c_str(), materialscube1->getMaterial(z)->specularexp);
	}
	*/
}

void update(double delta)
{

	maincamera.update(delta);
	somath::vec3 tem = maincamera.getPos();
	tem.y = -tem.y;
	somath::vec3 tem2 = maincamera.getTargetDirection();
	tem2.y = -tem2.y;
	recam.set(tem, tem2,true);


	distorsiontime += speedofdis*delta;
	distorsiontime = fmod(distorsiontime, 1.0);

}

void render()
{
	
	fborefract.bind();
	glClearColor(0.1, 0.5, 0.65, 1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	terrainplane.useProgram();
	terrainplane.setUniformMat4("project", maincamera.getProjectionMatrix().projectionmatrix);
	terrainplane.setUniformMat4("view", maincamera.getViewMatrix());
	terrainplane.setUniformFloat("clipactive", 0.0);
	terrainplane.setUniformVec3("lightpos", lightpos);
	terrainplane.setUniformVec2("worldsize", terrain2.getWorldSize());
	terrainplane.setUniformVec2("worldscale", terrain2.getWorldScale());
	glUniformHandleui64ARB(glGetUniformLocation(terrainplane.getProgram(), "heightmap"), terrain2.getHmapBindless());
	terrain2.render();

	pskybox.useProgram();
	pskybox.setUniformMat4("project", maincamera.getProjectionMatrix().projectionmatrix);
	pskybox.setUniformMat4("view", somath::mat4(somath::mat3(maincamera.getViewMatrix())));
	glUniformHandleui64ARB(glGetUniformLocation(pskybox.getProgram(), "cubeimage"), sky.getSkyboxTexBindLess());
	sky.render();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	/*
	glEnable(GL_BLEND);
	pcube1->useProgram();
	pcube1->setUniformMat4("project", basicprojectionmat);
	pcube1->setUniformMat4("view", maincamera.getViewMatrix());
	pcube1->setUniformVec3("camerapos", maincamera.getPos());
	pcube1->setUniformVec3("lightpos", lightpos);
	pcube1->setUniformInteger("teximages[0]", 0);
	pcube1->setUniformInteger("teximages[1]", 1);
	pcube1->setUniformInteger("teximages[2]", 2);


	materialscube1->getModelImages()->BindTextures();
	cube1->bindVAO();
	glBindBuffer(GL_ARRAY_BUFFER, vbotreepos->getVBO());
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(4);
	glVertexAttribDivisor(4, 1);
	cube1->renderInstances(5);
	glDisable(GL_BLEND);
	*/


	fboreflect.bind();
	glClearColor(0.1, 0.5, 0.65, 1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	terrainplane.useProgram();
	terrainplane.setUniformMat4("project", maincamera.getProjectionMatrix().projectionmatrix);
	terrainplane.setUniformMat4("view", recam.getViewMatrix());
	terrainplane.setUniformFloat("clipactive", 1.0);
	terrainplane.setUniformVec3("lightpos", lightpos);
	terrainplane.setUniformVec2("worldsize", terrain2.getWorldSize());
	terrainplane.setUniformVec2("worldscale", terrain2.getWorldScale());
	glUniformHandleui64ARB(glGetUniformLocation(terrainplane.getProgram(), "heightmap"), terrain2.getHmapBindless());
	terrain2.render();

	pskybox.useProgram();
	pskybox.setUniformMat4("project", maincamera.getProjectionMatrix().projectionmatrix);
	pskybox.setUniformMat4("view", somath::mat4(somath::mat3(recam.getViewMatrix())));
	glUniformHandleui64ARB(glGetUniformLocation(pskybox.getProgram(), "cubeimage"), sky.getSkyboxTexBindLess());
	sky.render();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	/*
	glEnable(GL_BLEND);
	pcube1->useProgram();
	pcube1->setUniformMat4("project", basicprojectionmat);
	pcube1->setUniformMat4("view", recam.getViewMatrix());
	pcube1->setUniformVec3("camerapos", recam.getPos());
	pcube1->setUniformVec3("lightpos", lightpos);
	pcube1->setUniformInteger("teximages[0]", 0);
	pcube1->setUniformInteger("teximages[1]", 1);
	pcube1->setUniformInteger("teximages[2]", 2);


	materialscube1->getModelImages()->BindTextures();
	cube1->bindVAO();
	glBindBuffer(GL_ARRAY_BUFFER, vbotreepos->getVBO());
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(4);
	glVertexAttribDivisor(4, 1);
	cube1->renderInstances(5);
	glDisable(GL_BLEND);

	fboscene->unbind();

	fboreflect->unbind();
	*/

	fboscene.bind();

	glClearColor(0.0, 1.0, 0.0, 1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);




	pplane.useProgram();
	pplane.setUniformMat4("project", maincamera.getProjectionMatrix().projectionmatrix);
	pplane.setUniformMat4("view", maincamera.getViewMatrix());
	pplane.setUniformMat4("model", somath::mat4());
	pplane.setUniformVec3("camerapos", maincamera.getPos());
	pplane.setUniformFloat("scale", 2 * 25 * 3*5);
	pplane.setUniformFloat("tiles", 8);
	pplane.setUniformFloat("distortionoffset", distorsiontime);
	pplane.setUniformVec3("lightpos", lightpos);
	pplane.setUniformFloat("np", NEARPLANE);
	pplane.setUniformFloat("fp", FARPLANE);
	glUniformHandleui64ARB(glGetUniformLocation(pplane.getProgram(), "tex1"), fboreflect.getTextureBindLess());
	glUniformHandleui64ARB(glGetUniformLocation(pplane.getProgram(), "tex2"), fborefract.getTextureBindLess());
	glUniformHandleui64ARB(glGetUniformLocation(pplane.getProgram(), "dvmap"), dvmapidbindless);
	glUniformHandleui64ARB(glGetUniformLocation(pplane.getProgram(), "normalmap"), normalmapidbindless);
	glEnable(GL_BLEND);
	plane1.render();
	glDisable(GL_BLEND);
	
	
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	terrainplane.useProgram();
	terrainplane.setUniformMat4("project", maincamera.getProjectionMatrix().projectionmatrix);
	terrainplane.setUniformMat4("view", maincamera.getViewMatrix());
	terrainplane.setUniformFloat("clipactive", 0.0);
	terrainplane.setUniformVec3("lightpos", lightpos);
	terrainplane.setUniformVec2("worldsize",terrain2.getWorldSize());
	terrainplane.setUniformVec2("worldscale",terrain2.getWorldScale());
	glUniformHandleui64ARB(glGetUniformLocation(terrainplane.getProgram(), "heightmap"), terrain2.getHmapBindless());
	terrain2.render();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	
	pskybox.useProgram();
	pskybox.setUniformMat4("project", maincamera.getProjectionMatrix().projectionmatrix);
	pskybox.setUniformMat4("view", somath::mat4(somath::mat3(maincamera.getViewMatrix())));
	glUniformHandleui64ARB(glGetUniformLocation(pskybox.getProgram(), "cubeimage"), sky.getSkyboxTexBindLess());
	sky.render();
	
	/*
	pcube1->useProgram();
	pcube1->setUniformMat4("project", basicprojectionmat);
	pcube1->setUniformMat4("view", maincamera.getViewMatrix());
	pcube1->setUniformVec3("camerapos", maincamera.getPos());
	pcube1->setUniformVec3("lightpos", lightpos);
	pcube1->setUniformInteger("teximages[0]", 0);
	pcube1->setUniformInteger("teximages[1]", 1);
	pcube1->setUniformInteger("teximages[2]", 2);


	materialscube1->getModelImages()->BindTextures();
	cube1->bindVAO();
	glBindBuffer(GL_ARRAY_BUFFER, vbotreepos->getVBO());
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(4);
	glVertexAttribDivisor(4, 1);
	glEnable(GL_BLEND);
	cube1->renderInstances(5);
	glDisable(GL_BLEND);
	
	fboscene->unbind();
	*/

	/*
	for (int z = 0;z < 4;z++)
	{
		fboblur1->bind();

		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		pblur->useProgram();
		pblur->setUniformVec2("sizeofscreen", glm::vec2(WIDTHOFWINDOW / 2.0, HEIGHTOFWINDOW / 2.0));
		pblur->setUniformFloat("horizontalblur", 1.0);
		pblur->setUniformMat4("project", glm::mat4());
		pblur->setUniformMat4("view", glm::mat4());
		model = glm::mat4();
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
		pblur->setUniformMat4("model", model);
		pblur->setUniformFloat("scale", 1);
		glActiveTexture(GL_TEXTURE0);
		if (z == 0)
			glBindTexture(GL_TEXTURE_2D, fboscene->getTexture());
		else
			glBindTexture(GL_TEXTURE_2D, fboblur2->getTexture());

		plane1.render();

		fboblur1->unbind();

		fboblur2->bind();

		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		pblur->useProgram();
		pblur->setUniformVec2("sizeofscreen", glm::vec2(WIDTHOFWINDOW / 2.0, HEIGHTOFWINDOW / 2.0));
		pblur->setUniformFloat("horizontalblur", 0.0);
		pblur->setUniformMat4("project", glm::mat4());
		pblur->setUniformMat4("view", glm::mat4());
		model = glm::mat4();
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
		pblur->setUniformMat4("model", model);
		pblur->setUniformFloat("scale", 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, fboblur1->getTexture());
		plane1.render();

		fboblur2->unbind();
	}
	*/
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	pplanesimple.useProgram();
	pplanesimple.setUniformMat4("project", somath::mat4());
	pplanesimple.setUniformMat4("view", somath::mat4());
	pplanesimple.setUniformMat4("model", somath::mat4());
	glUniformHandleui64ARB(glGetUniformLocation(pplanesimple.getProgram(),"image"), fboscene.getTextureBindLess());
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, fboscene.getTexture());

	/*
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fboblur2->getTexture());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, fboscene->getTexture());
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, fboscene->getDepthTexture());
	*/
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
	window.getWindowID();
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



