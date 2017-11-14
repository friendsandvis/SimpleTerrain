
#include"SOMath.h"

using namespace somath;

double SO_PI = 3.1415926535897932384626433832795;



//VECTOR 4


vec4::vec4()
{
	x = y = z = w = 0.0;
}

vec4::vec4(const vec4& tocopy)
{
	x = tocopy.x;
	y = tocopy.y;
	z = tocopy.z;
	w = tocopy.w;
}


vec4::~vec4()
{
	x = y = z = w = (double)0.0;
}


vec4 vec4::addition(vec4 operator2)
{
	vec4 result = *this;

	result.x += operator2.x;
	result.y += operator2.y;
	result.z += operator2.z;
	result.w += operator2.w;
	return result;
}


vec4 vec4::subtraction(vec4 operator2)
{
	vec4 result = *this;

	result.x -= operator2.x;
	result.y -= operator2.y;
	result.z -= operator2.z;
	result.w -= operator2.w;
	return result;
}


vec4 vec4::multiplication(vec4 operator2)
{
	vec4 result = *this;

	result.x *= operator2.x;
	result.y *= operator2.y;
	result.z *= operator2.z;
	result.w *= operator2.w;
	return result;
}

vec4 vec4::multiplication(mat4& opprend2)
{
	vec4 result(0.0);
	double *vecarr[4], vecarrop[4];
	vecarr[0] = &result.x;vecarr[1] = &result.y;vecarr[2] = &result.z;vecarr[3] = &result.w;
	vecarrop[0] = x;vecarrop[1] = y;vecarrop[2] = z;vecarrop[3] = w;

	for (int z = 0;z < 4;z++)
		for (int z1 = 0;z1 < 4;z1++)
			(*(vecarr[z])) += vecarrop[z1] * opprend2.matrix[z1][z];

	return result;
}


vec4 vec4::division(vec4 denominator)
{
	if (denominator.x == 0.0 || denominator.y == 0.0 || denominator.z == 0.0 || denominator.w == 0.0)
		return *this;
	vec4 result = *this;
	result.x /= denominator.x;
	result.y /= denominator.y;
	result.z /= denominator.z;
	result.w /= denominator.w;
	return result;
}

vec4 vec4::operator+(vec4 opprend2)
{
	return addition(opprend2);
}
vec4 vec4::operator-()
{
	return multiplication(vec4(-1));
}
vec4 vec4::operator-(vec4 opprend2)
{
	return subtraction(opprend2);
}
vec4 vec4::operator*(vec4 opprend2)
{
	return multiplication(opprend2);
}
vec4 vec4::operator*(mat4& opprend2)
{
	return multiplication(opprend2);
}
vec4 vec4::operator/(vec4 denominator)
{
	return division(denominator);
}

vec4 somath::operator*(double opprend1, vec4 opprend2)
{
	return opprend2.multiplication(somath::vec4(opprend1));
}

vec4 somath::operator*(vec4 opprend1, double opprend2)
{
	return opprend1.multiplication(somath::vec4(opprend2));
}
vec4 somath::operator/(double opprend1, vec4 opprend2)
{
	return opprend2.division(somath::vec4(opprend1));
}

vec4 somath::operator/(vec4 opprend1, double opprend2)
{
	return opprend1.division(somath::vec4(opprend2));
}
vec4 somath::operator-(double opprend1, vec4 opprend2)
{
	return opprend2.subtraction(somath::vec4(opprend1));
}

vec4 somath::operator-(vec4 opprend1, double opprend2)
{
	return opprend1.subtraction(somath::vec4(opprend2));
}
vec4 somath::operator+(double opprend1, vec4 opprend2)
{
	return opprend2.addition(somath::vec4(opprend1));
}

vec4 somath::operator+(vec4 opprend1, double opprend2)
{
	return opprend1.addition(somath::vec4(opprend2));
}

std::ostream& somath::operator<<(std::ostream& outputstr, vec4 operand)
{
	outputstr << '\n' << operand.x << '\t' << operand.y << '\t' << operand.z << '\t' << operand.w << '\n';
	return outputstr;
}


double vec4::dot(vec4 opperand2)
{
	return (x*opperand2.x + y*opperand2.y + z*opperand2.z + w*opperand2.w);
}

vec4 vec4::normalize()
{
	double normalizer = std::sqrt(x*x + y*y + z*z + w*w);
	if (normalizer == 0)
		return *this;

	vec4 normalizedcopy = *this;
	normalizedcopy.x /= normalizer;
	normalizedcopy.y /= normalizer;
	normalizedcopy.z /= normalizer;
	normalizedcopy.w /= normalizer;

	return normalizedcopy;
}

double vec4::length()
{
	return std::sqrt(x*x + y*y + z*z + w*w);
}

double vec4::distancefrom(vec4 point2)
{
	return std::sqrt(pow(point2.x - x, 2) + pow(point2.y - y, 2) + pow(point2.z - z, 2) + pow(point2.w - w, 2));
}










//VECTOR 3


vec3::vec3()
{
	x = y = z = 0.0;
}

vec3::vec3(const vec3& tocopy)
{
	x = tocopy.x;
	y = tocopy.y;
	z = tocopy.z;
}
vec3::vec3(const vec4& tocopy)
{
	x = tocopy.x;
	y = tocopy.y;
	z = tocopy.z;
}

vec3::~vec3()
{
	x = y = z = (double)0.0;
}


vec3 vec3::addition(vec3 operator2)
{
	vec3 result = *this;
	result.x += operator2.x;
	result.y += operator2.y;
	result.z += operator2.z;
	return result;
}


vec3 vec3::subtraction(vec3 operator2)
{
	vec3 result = *this;
	result.x -= operator2.x;
	result.y -= operator2.y;
	result.z -= operator2.z;
	return result;
}


vec3 vec3::multiplication(vec3 operator2)
{
	vec3 result = *this;
	result.x *= operator2.x;
	result.y *= operator2.y;
	result.z *= operator2.z;
	return result;
}

vec3 vec3::multiplication(mat3& opprend2)
{
	vec3 result(0.0);
	double *vecarr[3], vecarrop[3];
	vecarr[0] = &result.x;vecarr[1] = &result.y;vecarr[2] = &result.z;
	vecarrop[0] = x;vecarrop[1] = y;vecarrop[2] = z;

	for (int z = 0;z < 3;z++)
		for (int z1 = 0;z1 < 3;z1++)
			(*(vecarr[z])) += vecarrop[z1] * opprend2.matrix[z1][z];

	return result;
}


vec3 vec3::division(vec3 denominator)
{
	if (denominator.x == 0.0 || denominator.y == 0.0 || denominator.z == 0.0)
		return *this;
	vec3 result = *this;
	result.x /= denominator.x;
	result.y /= denominator.y;
	result.z /= denominator.z;
	return result;
}

vec3 vec3::operator+(vec3 opprend2)
{
	return addition(opprend2);
}
vec3 vec3::operator-(vec3 opprend2)
{
	return subtraction(opprend2);
}
vec3 vec3::operator-()
{
	return multiplication(vec3(-1.0));
}
vec3 vec3::operator*(vec3 opprend2)
{
	return multiplication(opprend2);
}
vec3 vec3::operator*(mat3& opprend2)
{
	return multiplication(opprend2);
}
vec3 vec3::operator/(vec3 denominator)
{
	return division(denominator);
}
vec3 somath::operator*(double opprend1, vec3 opprend2)
{
	return opprend2.multiplication(somath::vec3(opprend1));
}

vec3 somath::operator*(vec3 opprend1, double opprend2)
{
	return opprend1.multiplication(somath::vec3(opprend2));
}
vec3 somath::operator/(double opprend1, vec3 opprend2)
{
	return opprend2.division(somath::vec3(opprend1));
}

vec3 somath::operator/(vec3 opprend1, double opprend2)
{
	return opprend1.division(somath::vec3(opprend2));
}
vec3 somath::operator-(double opprend1, vec3 opprend2)
{
	return opprend2.subtraction(somath::vec3(opprend1));
}

vec3 somath::operator-(vec3 opprend1, double opprend2)
{
	return opprend1.subtraction(somath::vec3(opprend2));
}
vec3 somath::operator+(double opprend1, vec3 opprend2)
{
	return opprend2.addition(somath::vec3(opprend1));
}

vec3 somath::operator+(vec3 opprend1, double opprend2)
{
	return opprend1.addition(somath::vec3(opprend2));
}
std::ostream& somath::operator<<(std::ostream& outputstr, vec3 operand)
{
	outputstr << '\n' << operand.x << '\t' << operand.y << '\t' << operand.z << '\n';
	return outputstr;
}

double vec3::dot(vec3 opperand2)
{
	return (x*opperand2.x + y*opperand2.y + z*opperand2.z);
}

vec3 vec3::cross(vec3 opprend2)
{
	vec3 crossp;
	crossp.x = (y*opprend2.z - z*opprend2.y);
	crossp.y = (z*opprend2.x) - (x*opprend2.z);
	crossp.z = (x*opprend2.y) - (y*opprend2.x);

	return crossp;
}

vec3 vec3::normalize()
{
	double normalizer = std::sqrt(x*x + y*y + z*z);
	if (normalizer == 0)
		return *this;

	vec3 normalizedcopy = *this;
	normalizedcopy.x /= normalizer;
	normalizedcopy.y /= normalizer;
	normalizedcopy.z /= normalizer;

	return normalizedcopy;
}

double vec3::length()
{
	return std::sqrt(x*x + y*y + z*z);
}

double vec3::distancefrom(vec3 point2)
{
	return std::sqrt(pow(point2.x - x, 2) + pow(point2.y - y, 2) + pow(point2.z - z, 2));
}













//VECTOR 2


vec2::vec2()
{
	x = y = 0.0;
}

vec2::vec2(const vec2& tocopy)
{
	x = tocopy.x;
	y = tocopy.y;
}

vec2::~vec2()
{
	x = y = (double)0.0;
}


vec2 vec2::addition(vec2 operator2)
{
	vec2 result = *this;
	result.x += operator2.x;
	result.y += operator2.y;
	return result;
}


vec2 vec2::subtraction(vec2 operator2)
{
	vec2 result = *this;
	result.x -= operator2.x;
	result.y -= operator2.y;
	return result;
}


vec2 vec2::multiplication(vec2 operator2)
{
	vec2 result = *this;
	result.x *= operator2.x;
	result.y *= operator2.y;
	return result;
}


vec2 vec2::division(vec2 denominator)
{
	if (denominator.x == 0.0 || denominator.y == 0.0)
		return *this;
	vec2 result = *this;
	result.x /= denominator.x;
	result.y /= denominator.y;
	return result;
}

vec2 vec2::operator+(vec2 opprend2)
{
	return addition(opprend2);
}
vec2 vec2::operator-(vec2 opprend2)
{
	return subtraction(opprend2);
}
vec2 vec2::operator-()
{
	return multiplication(-1.0);
}
vec2 vec2::operator*(vec2 opprend2)
{
	return multiplication(opprend2);
}
vec2 vec2::operator/(vec2 denominator)
{
	return division(denominator);
}

vec2 somath::operator*(double opprend1, vec2 opprend2)
{
	return opprend2.multiplication(somath::vec2(opprend1));
}

vec2 somath::operator*(vec2 opprend1, double opprend2)
{
	return opprend1.multiplication(somath::vec2(opprend2));
}
vec2 somath::operator/(double opprend1, vec2 opprend2)
{
	return opprend2.division(somath::vec2(opprend1));
}

vec2 somath::operator/(vec2 opprend1, double opprend2)
{
	return opprend1.division(somath::vec2(opprend2));
}
vec2 somath::operator-(double opprend1, vec2 opprend2)
{
	return opprend2.subtraction(somath::vec2(opprend1));
}

vec2 somath::operator-(vec2 opprend1, double opprend2)
{
	return opprend1.subtraction(somath::vec2(opprend2));
}
vec2 somath::operator+(double opprend1, vec2 opprend2)
{
	return opprend2.addition(somath::vec2(opprend1));
}

vec2 somath::operator+(vec2 opprend1, double opprend2)
{
	return opprend1.addition(somath::vec2(opprend2));
}

std::ostream& somath::operator<<(std::ostream& outputstr, vec2 operand)
{
	outputstr << '\n' << operand.x << '\t' << operand.y << '\n';
	return outputstr;
}

double vec2::dot(vec2 opperand2)
{
	return (x*opperand2.x + y*opperand2.y);
}

vec2 vec2::normalize()
{
	double normalizer = std::sqrt(x*x + y*y);
	if (normalizer == 0)
		return *this;

	vec2 normalizedcopy = *this;
	normalizedcopy.x /= normalizer;
	normalizedcopy.y /= normalizer;

	return normalizedcopy;
}

double vec2::length()
{
	return std::sqrt(x*x + y*y);
}

double vec2::distancefrom(vec2 point2)
{
	return std::sqrt(pow(point2.x - x, 2) + pow(point2.y - y, 2));
}










//mat4
mat4::mat4()
{
	for (int z = 0;z < 4;z++)
		for (int z1 = 0;z1 < 4;z1++)
		{
			if (z1 == z)
				matrix[z][z1] = 1;
			else
				matrix[z][z1] = 0;
		}
}

mat4::mat4(double scalervalueforall)
{
	for (int z = 0;z < 4;z++)
		for (int z1 = 0;z1 < 4;z1++)
			matrix[z][z1] = scalervalueforall;
}

mat4::mat4(const mat4& tocopy)
{
	for (int z = 0;z < 4;z++)
		for (int z1 = 0;z1 < 4;z1++)
		{
			matrix[z][z1] = tocopy.matrix[z][z1];
		}
}
mat4::mat4(const mat3& tocopy)
{
	for (int z = 0;z < 3;z++)
		for (int z1 = 0;z1 < 3;z1++)
		{
			matrix[z][z1] = tocopy.matrix[z][z1];
		}
	matrix[0][3] = 0;
	matrix[1][3] = 0;
	matrix[2][3] = 0;
	matrix[3][3] = 1;
	matrix[3][2] = 0;
	matrix[3][1] = 0;
	matrix[3][0] = 0;

}
mat4::~mat4()
{

}

void mat4::showMatrix()
{
	std::cout << '\n';
	for (int z = 0;z < 4;z++)
	{
		for (int z1 = 0;z1 < 4;z1++)
			std::cout << matrix[z][z1] << '\t';
		std::cout << '\n';
	}
}

mat4 mat4::transpose()
{
	mat4 transpose;

	for (int z = 0;z < 4;z++)
		for (int z1 = 0;z1 < 4;z1++)
			transpose.matrix[z][z1] = matrix[z1][z];

	return transpose;
}


mat4 mat4::addition(const mat4& opprend2)
{
	mat4 result;

	for (int z = 0;z < 4;z++)
		for (int z1 = 0;z1 < 4;z1++)
			result.matrix[z][z1] = matrix[z][z1] + opprend2.matrix[z][z1];

	return result;

}
mat4 mat4::subtract(const mat4& opprend2)
{
	mat4 result;

	for (int z = 0;z < 4;z++)
		for (int z1 = 0;z1 < 4;z1++)
			result.matrix[z][z1] = matrix[z][z1] - opprend2.matrix[z][z1];

	return result;

}
mat4 mat4::multiply(const mat4& opprend2)
{
	mat4 result(0.0);

	for (int z = 0;z < 4;z++)
		for (int z1 = 0;z1 < 4;z1++)
			for (int z2 = 0;z2 < 4;z2++)
				result.matrix[z][z1] += matrix[z][z2] * opprend2.matrix[z2][z1];

	return result;

}

vec4 mat4::multiply(const vec4& opprend2)
{
	vec4 result(0.0);
	double *vecarr[4], vecarrop[4];
	vecarr[0] = &result.x;vecarr[1] = &result.y;vecarr[2] = &result.z;vecarr[3] = &result.w;
	vecarrop[0] = opprend2.x;vecarrop[1] = opprend2.y;vecarrop[2] = opprend2.z;vecarrop[3] = opprend2.w;

	for (int z = 0;z < 4;z++)
		for (int z1 = 0;z1 < 4;z1++)
			(*(vecarr[z])) += vecarrop[z1] * matrix[z][z1];

	return result;

}

mat4 mat4::division(const mat4& opprend2)
{
	mat4 result;

	for (int z = 0;z < 4;z++)
		for (int z1 = 0;z1 < 4;z1++)
			result.matrix[z][z1] = matrix[z][z1] / opprend2.matrix[z][z1];

	return result;

}

mat4 mat4::operator+(const mat4& opprend2)
{
	return this->addition(opprend2);
}
mat4 mat4::operator-(const mat4& opprend2)
{
	return this->subtract(opprend2);
}
mat4 mat4::operator-()
{
	return this->multiply(mat4(-1.0));
}
mat4 mat4::operator*(const mat4& opprend2)
{
	return this->multiply(opprend2);
}
vec4 mat4::operator*(const vec4& opprend2)
{
	return multiply(opprend2);
}
mat4 mat4::operator/(const mat4& opprend2)
{
	return this->division(opprend2);
}

mat4 somath::operator*(double scalervalue, mat4& mat)
{
	return mat.multiply(mat4(scalervalue));
}
mat4 somath::operator*(mat4& mat, double scalervalue)
{
	return mat.multiply(mat4(scalervalue));
}
mat4 somath::operator/(double scalervalue, mat4& mat)
{
	return mat.division(mat4(scalervalue));
}
mat4 somath::operator/(mat4& mat, double scalervalue)
{
	return mat.division(mat4(scalervalue));
}
mat4 somath::operator-(double scalervalue, mat4& mat)
{
	return mat.subtract(mat4(scalervalue));
}
mat4 somath::operator-(mat4& mat, double scalervalue)
{
	return mat.subtract(mat4(scalervalue));
}
mat4 somath::operator+(double scalervalue, mat4& mat)
{
	return mat.addition(mat4(scalervalue));
}
mat4 somath::operator+(mat4& mat, double scalervalue)
{
	return mat.addition(mat4(scalervalue));
}
std::ostream & somath::operator<<(std::ostream & outputstr, mat4 operand)
{
	outputstr << '\n';
	for (int z = 0;z < 4;z++)
	{
		for (int z1 = 0;z1 < 4;z1++)
			outputstr << operand.matrix[z][z1] << '\t';
		outputstr << '\n';
	}

	return outputstr;
}


double somath::toRadians(double angleindegree)
{
	return (SO_PI*angleindegree) / 180.0;
}


//projection matrix acomplishes task by taking following constants
//1. field of view is horizontal fov in radians
//2. aspectratio=WIDTH/HEIGHT
//3. nearplane and farplane can be + only
//4. finally we place z(eye space)[note z not -z] in w of clip space coordinates for correct perspective devide
mat4 somath::makePerspectiveProjectionMatrix(double aspectratio, double fieldofview, double nearplane, double farplane)
{
	double tantheta = std::tan(fieldofview / 2.0);
	double distancebetweenplanes = std::abs(nearplane);

	double n = nearplane, f = farplane;
	double l = tantheta*distancebetweenplanes;
	double b = l / aspectratio;

	mat4 projectionmatrix;

	projectionmatrix.matrix[0][0] = (n / l);
	projectionmatrix.matrix[0][1] = 0;
	projectionmatrix.matrix[0][2] = 0;
	projectionmatrix.matrix[0][3] = 0;

	projectionmatrix.matrix[1][0] = 0;
	projectionmatrix.matrix[1][1] = (n / b);
	projectionmatrix.matrix[1][2] = 0;
	projectionmatrix.matrix[1][3] = 0;

	projectionmatrix.matrix[2][0] = 0;
	projectionmatrix.matrix[2][1] = 0;
	projectionmatrix.matrix[2][2] = -1.0*(f + n) / (f - n);
	projectionmatrix.matrix[2][3] = -2.0*n*f / (f - n);

	projectionmatrix.matrix[3][0] = 0;
	projectionmatrix.matrix[3][1] = 0;
	projectionmatrix.matrix[3][2] = -1;
	projectionmatrix.matrix[3][3] = 0;

	return projectionmatrix;
}


/*
simple orthogonal projection matrix for the purpose of symetric fructums
(right and up must be +)

Symitric fructums include the onses that have x and y lengths symmitric
i.e.|left|=|right| and |top|=|bottom|
*/
mat4 somath::makeOrthogonalProjectionMatrixSymetric(double right, double up, double near, double far)
{
	mat4 projectionmatrix;

	projectionmatrix.matrix[0][0] = (1.0 / right);
	projectionmatrix.matrix[0][1] = 0;
	projectionmatrix.matrix[0][2] = 0;
	projectionmatrix.matrix[0][3] = 0;

	projectionmatrix.matrix[1][0] = 0;
	projectionmatrix.matrix[1][1] = (1.0 / up);
	projectionmatrix.matrix[1][2] = 0;
	projectionmatrix.matrix[1][3] = 0;

	projectionmatrix.matrix[2][0] = 0;
	projectionmatrix.matrix[2][1] = 0;
	projectionmatrix.matrix[2][2] = 2.0 / (near - far);
	projectionmatrix.matrix[2][3] = (near + far) / (near - far);

	projectionmatrix.matrix[3][0] = 0;
	projectionmatrix.matrix[3][1] = 0;
	projectionmatrix.matrix[3][2] = 0;
	projectionmatrix.matrix[3][3] = 1;

	return projectionmatrix;
}





/*
generic orthogonal projectionmatrix for any case scenetrio
*/
mat4 somath::makeOrthogonalProjectionMatrix(double left, double right, double down, double up, double near, double far)
{
	mat4 projectionmatrix;

	projectionmatrix.matrix[0][0] = -2.0 / (left - right);
	projectionmatrix.matrix[0][1] = 0;
	projectionmatrix.matrix[0][2] = 0;
	projectionmatrix.matrix[0][3] = (left + right) / (left - right);

	projectionmatrix.matrix[1][0] = 0;
	projectionmatrix.matrix[1][1] = -2.0 / (down - up);
	projectionmatrix.matrix[1][2] = 0;
	projectionmatrix.matrix[1][3] = (down + up) / (down - up);

	projectionmatrix.matrix[2][0] = 0;
	projectionmatrix.matrix[2][1] = 0;
	projectionmatrix.matrix[2][2] = 2.0 / (near - far);
	projectionmatrix.matrix[2][3] = (near + far) / (near - far);

	projectionmatrix.matrix[3][0] = 0;
	projectionmatrix.matrix[3][1] = 0;
	projectionmatrix.matrix[3][2] = 0;
	projectionmatrix.matrix[3][3] = 1;

	return projectionmatrix;
}


mat4 somath::translateMatrix(mat4 matrixtotranslate, vec3 translatebyvector)
{
	mat4 translate;

	translate.matrix[0][3] = translatebyvector.x;
	translate.matrix[1][3] = translatebyvector.y;
	translate.matrix[2][3] = translatebyvector.z;

	return matrixtotranslate*translate;
}

mat4 somath::scaleMarix(mat4 matrixtoscale, vec3 scalefactorperaxis)
{
	mat4 scale;

	scale.matrix[0][0] = scalefactorperaxis.x;
	scale.matrix[1][1] = scalefactorperaxis.y;
	scale.matrix[2][2] = scalefactorperaxis.z;

	return matrixtoscale*scale;
}


mat4 somath::lookat(vec3 positionofcamera, vec3 directionortarget, vec3 worldup, bool givenvectorisdirection)
{
	mat4 lookat;

	vec3 axis1, axis2, axis3;

	//opposit to camera looking direction (represents new + z axis because camera must look down at negive z axis)
	if (givenvectorisdirection)
		axis1 = normalize(-directionortarget);
	else
		axis1 = normalize(positionofcamera - directionortarget);

	//our new + x axis
	axis2 = worldup.cross(axis1);
	if (axis2.length() == 0.0)
		axis2 = vec3(1.0, 0.0, 0.0);
	else
		axis2 = normalize(axis2);

	//our new +y axis
	axis3 = normalize(axis1.cross(axis2));


	//orientation matrix replaces look at identity matrix
	lookat.matrix[0][0] = axis2.x;
	lookat.matrix[0][1] = axis2.y;
	lookat.matrix[0][2] = axis2.z;

	lookat.matrix[1][0] = axis3.x;
	lookat.matrix[1][1] = axis3.y;
	lookat.matrix[1][2] = axis3.z;

	lookat.matrix[2][0] = axis1.x;
	lookat.matrix[2][1] = axis1.y;
	lookat.matrix[2][2] = axis1.z;

	//finally add translation by - of camera position
	lookat = translateMatrix(lookat, -positionofcamera);

	return lookat;

}

vec4 somath::normalize(vec4 tonormalize)
{
	double x = tonormalize.x, y = tonormalize.y, z = tonormalize.z, w = tonormalize.w;

	double normalizer = std::sqrt(x*x + y*y + z*z + w*w);
	if (normalizer == 0)
		return tonormalize;

	vec4 normalizedcopy = tonormalize;
	normalizedcopy.x /= normalizer;
	normalizedcopy.y /= normalizer;
	normalizedcopy.z /= normalizer;
	normalizedcopy.w /= normalizer;

	return normalizedcopy;
}

vec3 somath::normalize(vec3 tonormalize)
{
	double x = tonormalize.x, y = tonormalize.y, z = tonormalize.z;

	double normalizer = std::sqrt(x*x + y*y + z*z);
	if (normalizer == 0)
		return tonormalize;

	vec3 normalizedcopy = tonormalize;
	normalizedcopy.x /= normalizer;
	normalizedcopy.y /= normalizer;
	normalizedcopy.z /= normalizer;

	return normalizedcopy;
}

vec2 somath::normalize(vec2 tonormalize)
{
	double x = tonormalize.x, y = tonormalize.y;

	double normalizer = std::sqrt(x*x + y*y);
	if (normalizer == 0)
		return tonormalize;

	vec2 normalizedcopy = tonormalize;
	normalizedcopy.x /= normalizer;
	normalizedcopy.y /= normalizer;

	return normalizedcopy;
}


/*
for rotation matrix-
angle  order:   looking at - axis rotation along anticlockwise direction
*/

mat4 somath::rotateMatrixByX(mat4 matrixtorotate, double angle)
{
	double cosT = std::cos(angle);
	double sinT = std::sin(angle);

	mat4 rotation;

	rotation.matrix[1][1] = cosT;
	rotation.matrix[1][2] = -sinT;
	rotation.matrix[2][1] = sinT;
	rotation.matrix[2][2] = cosT;

	return matrixtorotate*rotation;
}

mat4 somath::rotateMatrixByY(mat4 matrixtorotate, double angle)
{
	double cosT = std::cos(angle);
	double sinT = std::sin(angle);

	mat4 rotation;

	rotation.matrix[0][0] = cosT;
	rotation.matrix[0][2] = sinT;
	rotation.matrix[2][0] = -sinT;
	rotation.matrix[2][2] = cosT;

	return matrixtorotate*rotation;
}

mat4 somath::rotateMatrixByZ(mat4 matrixtorotate, double angle)
{
	double cosT = std::cos(angle);
	double sinT = std::sin(angle);

	mat4 rotation;

	rotation.matrix[0][0] = cosT;
	rotation.matrix[0][1] = -sinT;
	rotation.matrix[1][0] = sinT;
	rotation.matrix[1][1] = cosT;

	return matrixtorotate*rotation;
}

mat4 somath::rotateMatrix(mat4 matrixtorotate, double angle, vec3 axis)
{
	mat4 rotation;

	//simplified cases if axis is any one of base axis
	//METHORD TO FIND IF ALIGNED FOR A AXIS:      take vec2 of remaining coordinates and calculate the length if 0 then means that axis is aligned
	if (!vec2(axis.x, axis.y).length())
		return rotateMatrixByZ(matrixtorotate, angle);
	else if (!vec2(axis.x, axis.z).length())
		return rotateMatrixByY(matrixtorotate, angle);
	else if (!vec2(axis.z, axis.y).length())
		return rotateMatrixByX(matrixtorotate, angle);

	axis = normalize(axis);
	vec3 axis2 = axis*axis;
	double sinT = std::sin(angle), cosT = std::cos(angle);


	rotation.matrix[0][0] = cosT + axis2.x*(1.0 - cosT);
	rotation.matrix[0][1] = axis.x*axis.y*(1.0 - cosT) - axis.z*sinT;
	rotation.matrix[0][2] = axis.x*axis.z*(1.0 - cosT) + axis.y*sinT;
	rotation.matrix[0][3] = 0;
	rotation.matrix[1][0] = axis.y*axis.x*(1.0 - cosT) + axis.z*sinT;
	rotation.matrix[1][1] = cosT + axis2.y*(1.0 - cosT);
	rotation.matrix[1][2] = axis.y*axis.z*(1.0 - cosT) - axis.x*sinT;
	rotation.matrix[1][3] = 0;
	rotation.matrix[2][0] = axis.z*axis.x*(1.0 - cosT) - axis.y*sinT;
	rotation.matrix[2][1] = axis.z*axis.y*(1.0 - cosT) + axis.x*sinT;
	rotation.matrix[2][2] = cosT + axis2.z*(1.0 - cosT);
	rotation.matrix[2][3] = 0;
	rotation.matrix[3][0] = 0;
	rotation.matrix[3][1] = 0;
	rotation.matrix[3][2] = 0;
	rotation.matrix[3][3] = 1;

	//above is in column major order so transpose;
	return matrixtorotate*rotation;
}


double somath::dot(vec4 opprend1, vec4 opprend2)
{
	return opprend1.dot(opprend2);
}
double somath::dot(vec3 opprend1, vec3 opprend2)
{
	return opprend1.dot(opprend2);
}
double somath::dot(vec2 opprend1, vec2 opprend2)
{
	return opprend1.dot(opprend2);
}
vec3 somath::cross(vec3 opprend1, vec3 opprend2)
{
	return opprend1.cross(opprend2);
}





//mat3
mat3::mat3()
{
	for (int z = 0;z < 3;z++)
		for (int z1 = 0;z1 < 3;z1++)
		{
			if (z1 == z)
				matrix[z][z1] = 1;
			else
				matrix[z][z1] = 0;
		}
}

mat3::mat3(double scalervalueforall)
{
	for (int z = 0;z < 3;z++)
		for (int z1 = 0;z1 < 3;z1++)
			matrix[z][z1] = scalervalueforall;
}

mat3::mat3(const mat3& tocopy)
{
	for (int z = 0;z < 3;z++)
		for (int z1 = 0;z1 < 3;z1++)
		{
			matrix[z][z1] = tocopy.matrix[z][z1];
		}
}
mat3::mat3(const mat4& tocopy)
{
	for (int z = 0;z < 3;z++)
		for (int z1 = 0;z1 < 3;z1++)
		{
			matrix[z][z1] = tocopy.matrix[z][z1];
		}
}
mat3::~mat3()
{

}

void mat3::showMatrix()
{
	std::cout << '\n';
	for (int z = 0;z < 3;z++)
	{
		for (int z1 = 0;z1 < 3;z1++)
			std::cout << matrix[z][z1] << '\t';
		std::cout << '\n';
	}
}

mat3 mat3::transpose()
{
	mat3 transpose;

	for (int z = 0;z < 3;z++)
		for (int z1 = 0;z1 < 3;z1++)
			transpose.matrix[z][z1] = matrix[z1][z];

	return transpose;
}


mat3 mat3::addition(const mat3& opprend2)
{
	mat3 result;

	for (int z = 0;z < 3;z++)
		for (int z1 = 0;z1 < 3;z1++)
			result.matrix[z][z1] = matrix[z][z1] + opprend2.matrix[z][z1];

	return result;

}
mat3 mat3::subtract(const mat3& opprend2)
{
	mat3 result;

	for (int z = 0;z < 3;z++)
		for (int z1 = 0;z1 < 3;z1++)
			result.matrix[z][z1] = matrix[z][z1] - opprend2.matrix[z][z1];

	return result;

}
mat3 mat3::multiply(const mat3& opprend2)
{
	mat3 result(0.0);

	for (int z = 0;z < 3;z++)
		for (int z1 = 0;z1 < 3;z1++)
			for (int z2 = 0;z2 < 3;z2++)
				result.matrix[z][z1] += matrix[z][z2] * opprend2.matrix[z2][z1];

	return result;

}

vec3 mat3::multiply(const vec3& opprend2)
{
	vec3 result(0.0);
	double *vecarr[3], vecarrop[3];
	vecarr[0] = &result.x;vecarr[1] = &result.y;vecarr[2] = &result.z;
	vecarrop[0] = opprend2.x;vecarrop[1] = opprend2.y;vecarrop[2] = opprend2.z;

	for (int z = 0;z < 3;z++)
		for (int z1 = 0;z1 < 3;z1++)
			(*(vecarr[z])) += vecarrop[z1] * matrix[z][z1];

	return result;

}

mat3 mat3::division(const mat3& opprend2)
{
	mat3 result;

	for (int z = 0;z < 3;z++)
		for (int z1 = 0;z1 < 3;z1++)
			result.matrix[z][z1] = matrix[z][z1] / opprend2.matrix[z][z1];

	return result;
}
mat3 mat3::operator+(const mat3& opprend2)
{
	return this->addition(opprend2);
}
mat3 mat3::operator-(const mat3& opprend2)
{
	return this->subtract(opprend2);
}
mat3 mat3::operator-()
{
	return this->multiply(mat3(-1.0));
}
mat3 mat3::operator*(const mat3& opprend2)
{
	return this->multiply(opprend2);
}
vec3 mat3::operator*(const vec3& opprend2)
{
	return multiply(opprend2);
}
mat3 mat3::operator/(const mat3& opprend2)
{
	return division(opprend2);
}

mat3 somath::operator*(double scalervalue, mat3& mat)
{
	return mat.multiply(mat3(scalervalue));
}
mat3 somath::operator*(mat3& mat, double scalervalue)
{
	return mat.multiply(mat3(scalervalue));
}
mat3 somath::operator/(double scalervalue, mat3& mat)
{
	return mat.division(mat3(scalervalue));
}
mat3 somath::operator/(mat3& mat, double scalervalue)
{
	return mat.division(mat3(scalervalue));
}
mat3 somath::operator-(double scalervalue, mat3& mat)
{
	return mat.subtract(mat3(scalervalue));
}
mat3 somath::operator-(mat3& mat, double scalervalue)
{
	return mat.subtract(mat3(scalervalue));
}
mat3 somath::operator+(double scalervalue, mat3& mat)
{
	return mat.addition(mat3(scalervalue));
}
mat3 somath::operator+(mat3& mat, double scalervalue)
{
	return mat.addition(mat3(scalervalue));
}
std::ostream & somath::operator<<(std::ostream & outputstr, mat3 operand)
{
	outputstr << '\n';
	for (int z = 0;z < 3;z++)
	{
		for (int z1 = 0;z1 < 3;z1++)
			outputstr << operand.matrix[z][z1] << '\t';
		outputstr << '\n';
	}

	return outputstr;
}




//Convert any other entity to a narray of floats for use to give to opengl(G.P.U)
linearFormation::linearFormation()
{
	arr = nullptr;
	type = NONE;
}

linearFormation::linearFormation(vec3 tomakearrayof)
{
	arr = nullptr;
	type = NONE;
	setlinearFormation(tomakearrayof);
}

linearFormation::linearFormation(vec4 tomakearrayof)
{
	arr = nullptr;
	type = NONE;
	setlinearFormation(tomakearrayof);
}

linearFormation::linearFormation(vec2 tomakearrayof)
{
	arr = nullptr;
	type = NONE;
	setlinearFormation(tomakearrayof);
}

linearFormation::linearFormation(mat4 tomakearrayof)
{
	arr = nullptr;
	type = NONE;
	setlinearFormation(tomakearrayof);
}


linearFormation::linearFormation(mat3 tomakearrayof)
{
	arr = nullptr;
	type = NONE;
	setlinearFormation(tomakearrayof);
}

linearFormation::~linearFormation()
{
	delete[] arr;
}

void linearFormation::setlinearFormation(vec3 tomakearrayof)
{
	delete[] arr;

	arr = new float[3];
	arr[0] = tomakearrayof.x;
	arr[1] = tomakearrayof.y;
	arr[2] = tomakearrayof.z;

	type = VECTOR3;

}
void linearFormation::setlinearFormation(vec4 tomakearrayof)
{
	delete[] arr;

	arr = new float[4];
	arr[0] = tomakearrayof.x;
	arr[1] = tomakearrayof.y;
	arr[2] = tomakearrayof.z;
	arr[3] = tomakearrayof.w;

	type = VECTOR4;
}
void linearFormation::setlinearFormation(vec2 tomakearrayof)
{
	delete[] arr;

	arr = new float[2];
	arr[0] = tomakearrayof.x;
	arr[1] = tomakearrayof.y;

	type = VECTOR2;
}
void linearFormation::setlinearFormation(mat4 tomakearrayof)
{
	delete[] arr;

	arr = new float[16];
	arr[0] = tomakearrayof.matrix[0][0];
	arr[1] = tomakearrayof.matrix[1][0];
	arr[2] = tomakearrayof.matrix[2][0];
	arr[3] = tomakearrayof.matrix[3][0];
	arr[4] = tomakearrayof.matrix[0][1];
	arr[5] = tomakearrayof.matrix[1][1];
	arr[6] = tomakearrayof.matrix[2][1];
	arr[7] = tomakearrayof.matrix[3][1];
	arr[8] = tomakearrayof.matrix[0][2];
	arr[9] = tomakearrayof.matrix[1][2];
	arr[10] = tomakearrayof.matrix[2][2];
	arr[11] = tomakearrayof.matrix[3][2];
	arr[12] = tomakearrayof.matrix[0][3];
	arr[13] = tomakearrayof.matrix[1][3];
	arr[14] = tomakearrayof.matrix[2][3];
	arr[15] = tomakearrayof.matrix[3][3];

	type = MATRIX4;
}

void linearFormation::setlinearFormation(mat3 tomakearrayof)
{
	delete[] arr;

	arr = new float[9];
	arr[0] = tomakearrayof.matrix[0][0];
	arr[1] = tomakearrayof.matrix[1][0];
	arr[2] = tomakearrayof.matrix[2][0];
	arr[3] = tomakearrayof.matrix[0][1];
	arr[4] = tomakearrayof.matrix[1][1];
	arr[5] = tomakearrayof.matrix[2][1];
	arr[6] = tomakearrayof.matrix[0][2];
	arr[7] = tomakearrayof.matrix[1][2];
	arr[8] = tomakearrayof.matrix[2][2];

	type = MATRIX3;
}


const float* linearFormation::getArray()
{
	return arr;
}






linearFormationLinked::linearFormationLinked()
{
	arr = nullptr;
	floatarr = nullptr;
	type = NONE;
	sizeofarray = 0;
}
linearFormationLinked::linearFormationLinked(vec3 tomakearrayof)
{
	arr = nullptr;
	floatarr = nullptr;
	type = NONE;
	sizeofarray = 0;
	setlinearFormation(tomakearrayof);
}
linearFormationLinked::linearFormationLinked(vec4 tomakearrayof)
{
	arr = nullptr;
	floatarr = nullptr;
	type = NONE;
	sizeofarray = 0;
	setlinearFormation(tomakearrayof);
}
linearFormationLinked::linearFormationLinked(vec2 tomakearrayof)
{
	arr = nullptr;
	floatarr = nullptr;
	type = NONE;
	sizeofarray = 0;
	setlinearFormation(tomakearrayof);
}
linearFormationLinked::linearFormationLinked(mat4 tomakearrayof)
{
	arr = nullptr;
	floatarr = nullptr;
	type = NONE;
	sizeofarray = 0;
	setlinearFormation(tomakearrayof);
}
linearFormationLinked::linearFormationLinked(mat3 tomakearrayof)
{
	arr = nullptr;
	floatarr = nullptr;
	type = NONE;
	sizeofarray = 0;
	setlinearFormation(tomakearrayof);
}
void linearFormationLinked::setlinearFormation(vec3 tomakearrayof)
{
	delete[] arr;

	arr = new double*[3];
	arr[0] = &tomakearrayof.x;
	arr[1] = &tomakearrayof.y;
	arr[2] = &tomakearrayof.z;

	type = VECTOR3;

	delete[] floatarr;
	floatarr = new float[3];

	sizeofarray = 3;
}
void linearFormationLinked::setlinearFormation(vec4 tomakearrayof)
{
	delete[] arr;

	arr = new double*[4];
	arr[0] = &tomakearrayof.x;
	arr[1] = &tomakearrayof.y;
	arr[2] = &tomakearrayof.z;
	arr[2] = &tomakearrayof.w;

	type = VECTOR4;

	delete[] floatarr;
	floatarr = new float[4];

	sizeofarray = 4;
}
void linearFormationLinked::setlinearFormation(vec2 tomakearrayof)
{
	delete[] arr;

	arr = new double*[2];
	arr[0] = &tomakearrayof.x;
	arr[1] = &tomakearrayof.y;

	type = VECTOR2;

	delete[] floatarr;
	floatarr = new float[2];

	sizeofarray = 2;
}
void linearFormationLinked::setlinearFormation(mat4 tomakearrayof)
{
	delete[] arr;

	arr = new double*[16];
	arr[0] = &tomakearrayof.matrix[0][0];
	arr[1] = &tomakearrayof.matrix[1][0];
	arr[2] = &tomakearrayof.matrix[2][0];
	arr[3] = &tomakearrayof.matrix[3][0];
	arr[4] = &tomakearrayof.matrix[0][1];
	arr[5] = &tomakearrayof.matrix[1][1];
	arr[6] = &tomakearrayof.matrix[2][1];
	arr[7] = &tomakearrayof.matrix[3][1];
	arr[8] = &tomakearrayof.matrix[0][2];
	arr[9] = &tomakearrayof.matrix[1][2];
	arr[10] = &tomakearrayof.matrix[2][2];
	arr[11] = &tomakearrayof.matrix[3][2];
	arr[12] = &tomakearrayof.matrix[0][3];
	arr[13] = &tomakearrayof.matrix[1][3];
	arr[14] = &tomakearrayof.matrix[2][3];
	arr[15] = &tomakearrayof.matrix[3][3];

	type = MATRIX4;

	delete[] floatarr;
	floatarr = new float[16];

	sizeofarray = 16;
}
void linearFormationLinked::setlinearFormation(mat3 tomakearrayof)
{
	delete[] arr;

	arr = new double*[9];
	arr[0] = &tomakearrayof.matrix[0][0];
	arr[1] = &tomakearrayof.matrix[1][0];
	arr[2] = &tomakearrayof.matrix[2][0];
	arr[3] = &tomakearrayof.matrix[0][1];
	arr[4] = &tomakearrayof.matrix[1][1];
	arr[5] = &tomakearrayof.matrix[2][1];
	arr[6] = &tomakearrayof.matrix[0][2];
	arr[7] = &tomakearrayof.matrix[1][2];
	arr[8] = &tomakearrayof.matrix[2][2];

	type = MATRIX3;

	delete[] floatarr;
	floatarr = new float[9];

	sizeofarray = 9;
}
linearFormationLinked::~linearFormationLinked()
{
	delete[] arr;
	delete[] floatarr;
}

const float* linearFormationLinked::getArray()
{
	for (int z = 0;z < sizeofarray;z++)
		floatarr[z] = (float)(*arr[z]);

	return floatarr;
}




//--------------------------------Noise----------------------------

//Perlin's simple noise

//a hard coded randomvalue array for quick functionning of the noise function
//contains values between 0-256(inclusive) twice
unsigned randomvalues[512] =
{
	77,8,191,254,204,76,32,99,86,59,56,114,160,203,245,45,159,223,195,127,36,165,58,94,153,23,101,232,68,5,154,123,251,104,209,220,150,168,102,34,213,246,79,182,216,140,133,113,208,92,233,121,227,148,163,124,70,132,135,93,155,17,247,198,252,215,51,136,98,64,152,47,173,205,149,157,26,218,200,194,96,138,111,10,25,66,6,249,147,27,110,250,239,189,53,65,80,146,244,131,193,69,29,116,33,84,55,42,221,73,63,41,61,126,44,24,9,171,60,196,192,137,188,225,211,0,83,178,4,119,144,197,54,172,52,120,174,21,100,143,240,75,207,37,236,19,179,87,253,85,219,201,40,14,38,224,72,12,43,74,237,82,95,130,210,128,242,186,176,229,238,108,13,81,226,48,248,228,90,78,170,167,15,30,141,71,199,217,177,241,89,112,97,91,122,161,117,118,255,175,103,18,139,20,109,28,231,22,187,35,115,105,202,129,166,50,190,2,142,169,67,1,57,235,185,145,181,62,31,180,7,156,162,212,107,3,39,46,222,151,49,183,164,11,158,134,125,88,106,16,206,230,214,243,234,184,77,8,191,254,204,76,32,99,86,59,56,114,160,203,245,45,159,223,195,127,36,165,58,94,153,23,101,232,68,5,154,123,251,104,209,220,150,168,102,34,213,246,79,182,216,140,133,113,208,92,233,121,227,148,163,124,70,132,135,93,155,17,247,198,252,215,51,136,98,64,152,47,173,205,149,157,26,218,200,194,96,138,111,10,25,66,6,249,147,27,110,250,239,189,53,65,80,146,244,131,193,69,29,116,33,84,55,42,221,73,63,41,61,126,44,24,9,171,60,196,192,137,188,225,211,0,83,178,4,119,144,197,54,172,52,120,174,21,100,143,240,75,207,37,236,19,179,87,253,85,219,201,40,14,38,224,72,12,43,74,237,82,95,130,210,128,242,186,176,229,238,108,13,81,226,48,248,228,90,78,170,167,15,30,141,71,199,217,177,241,89,112,97,91,122,161,117,118,255,175,103,18,139,20,109,28,231,22,187,35,115,105,202,129,166,50,190,2,142,169,67,1,57,235,185,145,181,62,31,180,7,156,162,212,107,3,39,46,222,151,49,183,164,11,158,134,125,88,106,16,206,230,214,243,234,184
};


//the direction vector to be taken 
int randomgradiants[12][3] =
{
	{ 1,1,0 },
	{ -1,-1,0 },
	{ -1,1,0 },
	{ 1,-1,0 },
	{ 0,1,1 },
	{ 0,-1,-1 },
	{ 0,1,-1 },
	{ 0,-1,1 },
	{ 1,0,1 },
	{ -1,0,-1 },
	{ -1,0,1 },
	{ 1,0,-1 }
};


//returns value between 0.0-1.0 (inclusive)
float somath::getNoise(double x, double y, double z)
{
	unsigned xfloor = unsigned(x);
	unsigned yfloor = unsigned(y);
	unsigned zfloor = unsigned(z);

	double xrem = x - xfloor;
	double yrem = y - yfloor;
	double zrem = z - zfloor;

	xfloor %= 256;
	yfloor %= 256;
	zfloor %= 256;

	int temnum = (randomvalues[xfloor + randomvalues[yfloor + randomvalues[zfloor]]]) % 12;
	somath::vec3 grad000 = somath::vec3(randomgradiants[temnum][0], randomgradiants[temnum][1], randomgradiants[temnum][2]);

	temnum = (randomvalues[xfloor + randomvalues[yfloor + randomvalues[zfloor + 1]]]) % 12;
	somath::vec3 grad001 = somath::vec3(randomgradiants[temnum][0], randomgradiants[temnum][1], randomgradiants[temnum][2]);

	temnum = (randomvalues[xfloor + randomvalues[yfloor + 1 + randomvalues[zfloor]]]) % 12;
	somath::vec3 grad010 = somath::vec3(randomgradiants[temnum][0], randomgradiants[temnum][1], randomgradiants[temnum][2]);

	temnum = (randomvalues[xfloor + randomvalues[yfloor + 1 + randomvalues[zfloor + 1]]]) % 12;
	somath::vec3 grad011 = somath::vec3(randomgradiants[temnum][0], randomgradiants[temnum][1], randomgradiants[temnum][2]);

	temnum = (randomvalues[xfloor + 1 + randomvalues[yfloor + randomvalues[zfloor]]]) % 12;
	somath::vec3 grad100 = somath::vec3(randomgradiants[temnum][0], randomgradiants[temnum][1], randomgradiants[temnum][2]);

	temnum = (randomvalues[xfloor + 1 + randomvalues[yfloor + randomvalues[zfloor + 1]]]) % 12;
	somath::vec3 grad101 = somath::vec3(randomgradiants[temnum][0], randomgradiants[temnum][1], randomgradiants[temnum][2]);

	temnum = (randomvalues[xfloor + 1 + randomvalues[yfloor + 1 + randomvalues[zfloor]]]) % 12;
	somath::vec3 grad110 = somath::vec3(randomgradiants[temnum][0], randomgradiants[temnum][1], randomgradiants[temnum][2]);

	temnum = (randomvalues[xfloor + 1 + randomvalues[yfloor + 1 + randomvalues[zfloor + 1]]]) % 12;
	somath::vec3 grad111 = somath::vec3(randomgradiants[temnum][0], randomgradiants[temnum][1], randomgradiants[temnum][2]);

	double dot000 = somath::dot(grad000, somath::vec3(xrem, yrem, zrem));
	double dot001 = somath::dot(grad001, somath::vec3(xrem, yrem, zrem - 1));
	double dot010 = somath::dot(grad010, somath::vec3(xrem, yrem - 1, zrem));
	double dot011 = somath::dot(grad011, somath::vec3(xrem, yrem - 1, zrem - 1));
	double dot100 = somath::dot(grad100, somath::vec3(xrem - 1, yrem, zrem));
	double dot101 = somath::dot(grad101, somath::vec3(xrem - 1, yrem, zrem - 1));
	double dot110 = somath::dot(grad110, somath::vec3(xrem - 1, yrem - 1, zrem));
	double dot111 = somath::dot(grad111, somath::vec3(xrem - 1, yrem - 1, zrem - 1));

	double xfadecompo = xrem*xrem*(3 - 2 * xrem);
	double yfadecompo = yrem*yrem*(3 - 2 * yrem);
	double zfadecompo = zrem*zrem*(3 - 2 * zrem);


	double xip1 = (1 - xfadecompo)*dot000 + xfadecompo*dot100;
	double xip2 = (1 - xfadecompo)*dot001 + xfadecompo*dot101;
	double xip3 = (1 - xfadecompo)*dot010 + xfadecompo*dot110;
	double xip4 = (1 - xfadecompo)*dot011 + xfadecompo*dot111;

	double yip1 = (1 - yfadecompo)*xip1 + yfadecompo*xip3;
	double yip2 = (1 - yfadecompo)*xip2 + yfadecompo*xip4;

	double zip1 = (1 - zfadecompo)*yip1 + zfadecompo*yip2;

	return zip1;
}