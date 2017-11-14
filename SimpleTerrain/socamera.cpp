
#include"socamera.h"

socamera::Camera::Camera()
{
	worldup = somath::vec3(0.0, 1.0, 0.0);
	position = somath::vec3(0.0);
	targetvector = somath::vec3(0.0);
}
void socamera::Camera::set(somath::vec3 pos, somath::vec3 target, bool targetisvector)
{
	position = pos;
	if (!targetisvector)
		this->targetvector = somath::normalize(target - pos);
	else
		this->targetvector = somath::normalize(target);

	viewmatrix = somath::lookat(pos, this->targetvector, worldup, true);
}
void socamera::Camera::setWorldUp(somath::vec3 worldup)
{
	this->worldup = worldup;
}
void socamera::Camera::lookAt(somath::vec3 target, bool targetisvector)
{
	if (!targetisvector)
		this->targetvector = target - position;
	else
		this->targetvector = target;

	viewmatrix = somath::lookat(position, this->targetvector, worldup, true);
}

void socamera::Camera::setProjectionMatrix(double aspectratio, double fieldofview, double nearplane, double farplane)
{
	pmatrix.nearplane=nearplane;
	pmatrix.farplane=farplane;
	pmatrix.projectionmatrix=somath::makePerspectiveProjectionMatrix(aspectratio, fieldofview, nearplane, farplane);
}

socamera::ProjectionMatrix& socamera::Camera::getProjectionMatrix()
{
	return pmatrix;
}

somath::mat4& socamera::Camera::getViewMatrix()
{
	return viewmatrix;
}

somath::vec3 socamera::Camera::getPos()
{
	return position;
}

somath::vec3 socamera::Camera::getTargetDirection()
{
	return targetvector;
}










socamera::FPSCamera::FPSCamera()
{
	Camera();

	for (int z = 0;z<4;z++)
		RLDUpressed[z] = false;

	speed = 2.5;
	strafdir = somath::vec3(0);
	xposprev = yposprev = 0;
	sensitivity = 0.1;
	yaw = pitch = 0.0;
	PI = 3.1415926535897932384626433832795;

}
void socamera::FPSCamera::setSensitivity(double sensitivity)
{
	this->sensitivity = sensitivity;
}
void socamera::FPSCamera::setSpeed(double speed)
{
	this->speed = speed;
}
void socamera::FPSCamera::set(somath::vec3 pos, somath::vec3 target, bool targetisvector)
{
	Camera::set(pos, target, targetisvector);

	strafdir = somath::normalize(somath::cross(worldup, targetvector*-1.0));
}

void socamera::FPSCamera::keyListener(GLFWwindow* win, int key, int scancode, int action, int modifier)
{
	if (action == GLFW_PRESS)
		for (int z = 0;z < 4;z++)
		{
			if (GLFW_KEY_RIGHT + z == key)
				RLDUpressed[z] = true;
		}

	else if (action == GLFW_RELEASE)
		for (int z = 0;z < 4;z++)
		{
			if (GLFW_KEY_RIGHT + z == key)
				RLDUpressed[z] = false;
		}
}

void socamera::FPSCamera::mouseListener(GLFWwindow* window, double xpos, double ypos)
{
	double xdelta = xpos - xposprev;
	xposprev = xpos;

	double ydelta = ypos - yposprev;
	yposprev = ypos;

	ydelta = somath::toRadians(ydelta*sensitivity);
	pitch -= ydelta;
	if (pitch<-(PI / 2.5))
		pitch = -(PI / 2.5);
	else if (pitch>(PI / 2.5))
		pitch = (PI / 2.5);

	xdelta = somath::toRadians(xdelta*sensitivity);
	yaw -= xdelta;


	double y = std::sin(pitch);
	double x = std::cos(pitch);
	somath::vec3 targettem(x*std::sin(yaw), y, x* std::cos(yaw));

	targetvector = somath::normalize(targettem);
	strafdir = somath::normalize(somath::cross(worldup, targetvector*-1.0));
}

void socamera::FPSCamera::update(float delta)
{

	if (RLDUpressed[2])
		position = position - targetvector*(speed*delta);
	else if (RLDUpressed[3])
		position = position + targetvector*(speed*delta);

	if (RLDUpressed[0])
		position = position + strafdir*(speed*delta);
	else if (RLDUpressed[1])
		position = position - strafdir*(speed*delta);

	viewmatrix = somath::lookat(position, targetvector, worldup, true);
}




