#ifndef SOMATHUSED
#define SOMATHUSED
/*
ALL THE CLASSES ARE UNDER THE NAMESPACE somath

Vector notes
------Vector classes donot have cross product except for vec3 as cross for others is useless
------Vector is not an array so no one pointer access

Matrices notes
NOTE----------------MATRIX IS IN COLUMN MAJOR AS PER OPENGL STANDERD AND AS GLSL LIKES IT
------Matrices are only square
*/

#include<iostream>
#include<cmath>

namespace somath
{
	


	//-------------------------------------vectors-------------------------------------
	//forward declaration
	class vec3;
	class vec4;
	class vec2;
	class mat3;
	class mat4;

	//vector4 class

	class vec4
	{
	private:
	public:
		double x, y, z, w;

		vec4();
		vec4(const vec4& tocopy);
		template<class A>
		vec4(A x);
		template<class A>
		vec4(A x, A y, A z, A w);
		template<class A>
		vec4(vec3 xyz, A w);
		~vec4();

		vec4 addition(vec4 opprend2);
		vec4 subtraction(vec4 opprand2);
		vec4 multiplication(vec4 opprend2);
		vec4 multiplication(mat4& opprend2);
		vec4 division(vec4 denominator);

		double dot(vec4 opprend2);
		vec4 normalize();
		double length();
		double distancefrom(vec4 point2);

		vec4 operator+(vec4 opprend2);
		vec4 operator-(vec4 opprend2);
		vec4 operator-();
		vec4 operator*(vec4 opprend2);
		vec4 operator*(mat4& opprend2);
		vec4 operator/(vec4 denominator);

		friend std::ostream& operator<<(std::ostream& outputstr, vec4 operand);
		friend vec4 operator*(vec4 opprend1, double opprend2);
		friend vec4 operator*(double opprend1, vec4 oprend2);
		friend vec4 operator/(vec4 opprend1, double opprend2);
		friend vec4 operator/(double opprend1, vec4 oprend2);
		friend vec4 operator-(vec4 opprend1, double opprend2);
		friend vec4 operator-(double opprend1, vec4 oprend2);
		friend vec4 operator+(vec4 opprend1, double opprend2);
		friend vec4 operator+(double opprend1, vec4 oprend2);
	};

	//template function defined in heder to make it visible to user files

	template<class A>
	vec4::vec4(A x, A y, A z, A w)
	{
		this->x = (double)x;
		this->y = (double)y;
		this->z = (double)z;
		this->w = (double)w;
	}

	template<class A>
	vec4::vec4(vec3 xyz, A w)
	{
		this->x = (double)xyz.x;
		this->y = (double)xyz.y;
		this->z = (double)xyz.z;
		this->w = (double)w;
	}

	template<class A>
	vec4::vec4(A x)
	{
		this->x = y = z = w = (double)x;
	}



	//vector3 class

	class vec3
	{
	private:
	public:
		double x, y, z;

		vec3();
		vec3(const vec3& tocopy);
		vec3(const vec4& tocopy);
		template<class A>
		vec3(A x);
		template<class A>
		vec3(A x, A y, A z);
		~vec3();

		vec3 addition(vec3 opprend2);
		vec3 subtraction(vec3 opprand2);
		vec3 multiplication(vec3 opprend2);
		vec3 multiplication(mat3& opprend2);
		vec3 division(vec3 denominator);

		double dot(vec3 opprend2);
		vec3 vec3::cross(vec3 opprend2);
		vec3 normalize();
		double length();
		double distancefrom(vec3 point2);

		vec3 operator+(vec3 opprend2);
		vec3 operator-(vec3 opprend2);
		vec3 operator-();
		vec3 operator*(vec3 opprend2);
		vec3 operator*(mat3& opprend2);
		vec3 operator/(vec3 denominator);
		friend std::ostream& operator<<(std::ostream& outputstr, vec3 operand);
		friend std::ostream& operator<<(std::ostream& outputstr, vec4 operand);
		friend vec3 operator*(vec3 opprend1, double opprend2);
		friend vec3 operator*(double opprend1, vec3 oprend2);
		friend vec3 operator/(vec3 opprend1, double opprend2);
		friend vec3 operator/(double opprend1, vec3 oprend2);
		friend vec3 operator-(vec3 opprend1, double opprend2);
		friend vec3 operator-(double opprend1, vec3 oprend2);
		friend vec3 operator+(vec3 opprend1, double opprend2);
		friend vec3 operator+(double opprend1, vec3 oprend2);
	};

	//template function defined in heder to make it visible to user files

	template<class A>
	vec3::vec3(A x, A y, A z)
	{
		this->x = (double)x;
		this->y = (double)y;
		this->z = (double)z;
	}

	template<class A>
	vec3::vec3(A x)
	{
		this->x = y = z = (double)x;
	}




	//vector2 class

	class vec2
	{
	private:
	public:
		double x, y, z;

		vec2();
		vec2(const vec2& tocopy);
		template<class A>
		vec2(A x);
		template<class A>
		vec2(A x, A y);
		~vec2();

		vec2 addition(vec2 opprend2);
		vec2 subtraction(vec2 opprand2);
		vec2 multiplication(vec2 opprend2);
		vec2 division(vec2 denominator);

		double dot(vec2 opprend2);
		vec2 normalize();
		double length();
		double distancefrom(vec2 point2);

		vec2 operator+(vec2 opprend2);
		vec2 operator-(vec2 opprend2);
		vec2 operator-();
		vec2 operator*(vec2 opprend2);
		vec2 operator/(vec2 denominator);
		friend std::ostream& operator<<(std::ostream& outputstr, vec2 operand);
		friend vec2 operator*(vec2 opprend1, double opprend2);
		friend vec2 operator*(double opprend1, vec2 oprend2);
		friend vec2 operator/(vec2 opprend1, double opprend2);
		friend vec2 operator/(double opprend1, vec2 oprend2);
		friend vec2 operator-(vec2 opprend1, double opprend2);
		friend vec2 operator-(double opprend1, vec2 oprend2);
		friend vec2 operator+(vec2 opprend1, double opprend2);
		friend vec2 operator+(double opprend1, vec2 oprend2);
	};

	//template function defined in heder to make it visible to user files

	template<class A>
	vec2::vec2(A x, A y)
	{
		this->x = (double)x;
		this->y = (double)y;
	}

	template<class A>
	vec2::vec2(A x)
	{
		this->x = y = (double)x;
	}









	//-------------------------Matrix------------------------

	//forwoard declare
	class mat3;

	//mat4
	class mat4
	{
	public:
		double matrix[4][4];

		mat4();
		mat4(double scalervalueforall);
		mat4(const mat4& tocopy);
		mat4(const mat3& tocopy);
		~mat4();

		void showMatrix();
		mat4 transpose();

		mat4 addition(const mat4& opprend2);
		mat4 subtract(const mat4& opprend2);
		mat4 multiply(const mat4& opprend2);
		vec4 multiply(const vec4& opprend2);
		mat4 division(const mat4& opprend2);


		mat4 operator+(const mat4& opprend2);
		mat4 operator-(const mat4& opprend2);
		mat4 operator-();
		mat4 operator*(const mat4& opprend2);
		vec4 operator*(const vec4& opprend2);
		mat4 operator/(const mat4& opprend2);

		friend mat4 operator*(double scalervalue, mat4& mat);
		friend mat4 operator*(mat4& mat, double scalervalue);
		friend mat4 operator/(double scalervalue, mat4& mat);
		friend mat4 operator/(mat4& mat, double scalervalue);
		friend mat4 operator+(double scalervalue, mat4& mat);
		friend mat4 operator+(mat4& mat, double scalervalue);
		friend mat4 operator-(double scalervalue, mat4& mat);
		friend mat4 operator-(mat4& mat, double scalervalue);
		friend std::ostream& operator<<(std::ostream& outputstr, mat4 operand);
	};

	//mat3
	class mat3
	{
	public:
		double matrix[3][3];

		mat3();
		mat3(double scalervalueforall);
		mat3(const mat3& tocopy);
		mat3(const mat4& tocopy);
		~mat3();

		void showMatrix();
		mat3 transpose();

		mat3 addition(const mat3& opprend2);
		mat3 subtract(const mat3& opprend2);
		mat3 multiply(const mat3& opprend2);
		vec3 multiply(const vec3& opprend2);
		mat3 division(const mat3& opprend2);


		mat3 operator+(const mat3& opprend2);
		mat3 operator-(const mat3& opprend2);
		mat3 operator-();
		mat3 operator*(const mat3& opprend2);
		vec3 operator*(const vec3& opprend2);
		mat3 operator/(const mat3& opprend2);

		friend mat3 operator*(double scalervalue, mat3& mat);
		friend mat3 operator*(mat3& mat, double scalervalue);
		friend mat3 operator/(double scalervalue, mat3& mat);
		friend mat3 operator/(mat3& mat, double scalervalue);
		friend mat3 operator+(double scalervalue, mat3& mat);
		friend mat3 operator+(mat3& mat, double scalervalue);
		friend mat3 operator-(double scalervalue, mat3& mat);
		friend mat3 operator-(mat3& mat, double scalervalue);
		friend std::ostream& operator<<(std::ostream& outputstr, mat3 operand);
	};

	//--------------------general functions---------------------------

	double toRadians(double angleindegree);
	vec4 normalize(vec4 tonormalize);
	vec3 normalize(vec3 tonormalize);
	vec2 normalize(vec2 tonormalize);
	double dot(vec4 opprend1, vec4 opprend2);
	double dot(vec3 opprend1, vec3 opprend2);
	double dot(vec2 opprend1, vec2 opprend2);
	vec3 cross(vec3 opprend1, vec3 opprend2);



	//------------------projection matrix---------------------

	/*
	projection matrix acomplishes task by taking following constants
	1. field of view is horizontal fov in radians
	2. aspectratio=WIDTH/HEIGHT
	3. nearplane and farplane can be +/- but must represent planes in cameraspace
	4. finally we place z(eye space)[note z not -z] in w of clip space coordinates for correct perspective devide
	*/
	mat4 makePerspectiveProjectionMatrix(double aspectratio, double fieldofview, double nearplane, double farplane);

	mat4 makeOrthogonalProjectionMatrix(double left, double right, double down, double up, double near, double far);

	mat4 makeOrthogonalProjectionMatrixSymetric(double right, double up, double near, double far);


	//---------------------transformation matrix------------------------
	/*
	for rotation matrix-
	angle  order:   looking at - axis rotation along anticlockwise direction
	*/

	mat4 rotateMatrixByX(mat4 matrixtorotate, double angle);

	mat4 rotateMatrixByY(mat4 matrixtorotate, double angle);

	mat4 rotateMatrixByZ(mat4 matrixtorotate, double angle);

	mat4 rotateMatrix(mat4 matrixtorotate, double angle, vec3 axis);

	mat4 translateMatrix(mat4 matrixtotranslate, vec3 translatebyvector);

	mat4 scaleMarix(mat4 matrixtoscale, vec3 scalefactorperaxis);



	//-----------------view matrix--------------------------
	mat4 lookat(vec3 positionofcamera, vec3 directionortarget, vec3 worldup, bool givenvectorisdirection);


	enum TypeOfLinearFormation
	{
		VECTOR2 = 1, VECTOR3 = 2, VECTOR4 = 3, MATRIX3 = 4, MATRIX4 = 5, NONE = 0
	};

	class linearFormation
	{
		float *arr;
		TypeOfLinearFormation type;

	public:
		linearFormation();
		linearFormation(vec3 tomakearrayof);
		linearFormation(vec4 tomakearrayof);
		linearFormation(vec2 tomakearrayof);
		linearFormation(mat4 tomakearrayof);
		linearFormation(mat3 tomakearrayof);
		void setlinearFormation(vec3 tomakearrayof);
		void setlinearFormation(vec4 tomakearrayof);
		void setlinearFormation(vec2 tomakearrayof);
		void setlinearFormation(mat4 tomakearrayof);
		void setlinearFormation(mat3 tomakearrayof);
		~linearFormation();

		const float* getArray();
	};

	class linearFormationLinked
	{
		double **arr;
		float *floatarr;
		unsigned sizeofarray;
		TypeOfLinearFormation type;

	public:
		linearFormationLinked();
		linearFormationLinked(vec3 tomakearrayof);
		linearFormationLinked(vec4 tomakearrayof);
		linearFormationLinked(vec2 tomakearrayof);
		linearFormationLinked(mat4 tomakearrayof);
		linearFormationLinked(mat3 tomakearrayof);
		void setlinearFormation(vec3 tomakearrayof);
		void setlinearFormation(vec4 tomakearrayof);
		void setlinearFormation(vec2 tomakearrayof);
		void setlinearFormation(mat4 tomakearrayof);
		void setlinearFormation(mat3 tomakearrayof);
		~linearFormationLinked();

		const float* getArray();
	};



	//-------------------------------Noise ---------------------------------

	//Perlins simple 3D noise function
	float getNoise(double x, double y, double z);

}



#endif SOMATHUSED

