#pragma once

#include "SOMath.h"
#include<GLFW\glfw3.h>


namespace socamera
{
	struct ProjectionMatrix
	{
		somath::mat4 projectionmatrix;
		double nearplane, farplane;
	};



	class Camera
	{
	protected:
		somath::vec3 position, targetvector, worldup;
		somath::mat4 viewmatrix;
		ProjectionMatrix pmatrix;
	public:
		Camera();
		void set(somath::vec3 pos, somath::vec3 target,bool targetisdirectionvector);
		void lookAt(somath::vec3 target, bool targetisdirectionvector);
		void setProjectionMatrix(double aspectratio, double fieldofview, double nearplane, double farplane);
		somath::mat4& getViewMatrix();
		ProjectionMatrix& getProjectionMatrix();
		somath::vec3 getPos();
		somath::vec3 getTargetDirection();
		void setWorldUp(somath::vec3);
	};



	class FPSCamera :public Camera
	{
		bool RLDUpressed[4];
		double PI ;
		float speed;
		somath::vec3 strafdir;
		double xposprev, yposprev;
		double sensitivity;
		double yaw, pitch;
	public:
		FPSCamera();
		void setSensitivity(double sensitivity);
		void setSpeed(double speed);
		virtual void set(somath::vec3 pos, somath::vec3 target, bool targetisdirectionvector);
		void keyListener(GLFWwindow* win, int key, int scancode, int action, int modifier);
		void mouseListener(GLFWwindow* window, double xpos, double ypos);
		void update(float delta);
	};
}
