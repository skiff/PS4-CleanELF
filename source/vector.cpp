#include "../include/utility.h"
#include "../include/imports.h"
#include "../include/vector.h"

//Vector2
vec2_t::vec2_t() {
	this->x = this->y = 0;
}

vec2_t::~vec2_t() {

}

vec2_t::vec2_t(float x) {
	this->x = x; this->y = 0;
}

vec2_t::vec2_t(float x, float y) {
	this->x = x; this->y = y;
}

vec2_t::vec2_t(float x, float y, float z) {
	this->x = x; this->y = y;
}

vec2_t::vec2_t(float vec[2]) {
	this->x = vec[0]; this->y = vec[1];
}

vec2_t vec2_t::operator+(const vec2_t vec) {
	return vec2_t(this->x + vec.x, this->y + vec.y);
}

vec2_t vec2_t::operator+(const float* vec) {
	return vec2_t(this->x + vec[0], this->y + vec[1]);
}

vec2_t vec2_t::operator-(const vec2_t vec) {
	return vec2_t(this->x - vec.x, this->y - vec.y);
}

vec2_t vec2_t::operator-(const float* vec) {
	return vec2_t(this->x - vec[0], this->y - vec[1]);
}

vec2_t vec2_t::operator*=(const vec2_t vec) {
	return vec2_t(this->x * vec.x, this->y * vec.y);
}

vec2_t vec2_t::operator*=(const float scalar) {
	return vec2_t(this->x * scalar, this->y * scalar);
}

bool vec2_t::operator==(const vec2_t vec) {
	return (this->x == vec.x && this->y == vec.y);
}

bool vec2_t::operator==(const float value) {
	return (this->x == value && this->y == value);
}

bool vec2_t::operator!=(const vec2_t vec) {
	return (this->x != vec.x && this->y != vec.y);
}

bool vec2_t::operator!=(const float value) {
	return (this->x != value && this->y != value);
}

vec2_t::operator float*() {
	return this->convert();
}

float* vec2_t::convert() {
	return (float*)&this[0];
}

void vec2_t::print() {
	printf("%.3f %.3f\n", this->x, this->y);
}



//Vector3
vec3_t::vec3_t() {
	this->x = this->y = this->z = 0;
}

vec3_t::~vec3_t() {
}

vec3_t::vec3_t(float x) {
	this->x = x; this->y = this->z = 0;
}

vec3_t::vec3_t(float x, float y) {
	this->x = x; this->y = y; this->z = 0;
}

vec3_t::vec3_t(float x, float y, float z) {
	this->x = x; this->y = y; this->z = z;
}

vec3_t::vec3_t(float* vec) {
	if (vec != 0) {
		this->x = vec[0];
		this->y = vec[1];
		this->z = vec[2];
	}
	else {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
}

vec3_t::vec3_t(int null) {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

vec3_t vec3_t::operator+(const vec3_t vec) {
	return vec3_t(this->x + vec.x, this->y + vec.y, this->z + vec.z);
}

vec3_t vec3_t::operator+(const float* vec) {
	return operator+(vec3_t(vec[0], vec[1], vec[2]));
}

vec3_t vec3_t::operator-(const vec3_t vec) {
	return vec3_t(this->x - vec.x, this->y - vec.y, this->z - vec.z);
}

vec3_t vec3_t::operator-(const float* vec) {
	return vec3_t(this->x - vec[0], this->y - vec[1], this->z - vec[2]);
}

vec3_t vec3_t::operator-() const {
	return vec3_t(-x, -y, -z);
}

vec3_t vec3_t::operator-=(const vec3_t vec) {
	return this->operator-(vec);
}

vec3_t vec3_t::operator+=(const vec3_t vec)
{
	return this->operator+(vec);
}

vec3_t vec3_t::operator*=(const vec3_t vec) {
	return vec3_t(this->x * vec.x, this->y * vec.y, this->z * vec.z);
}

vec3_t vec3_t::operator*=(const float scalar) {
	return vec3_t(this->x * scalar, this->y * scalar, this->z * scalar);
}

vec3_t vec3_t::operator*(const float scalar) {
	return vec3_t(this->x * scalar, this->y * scalar, this->z * scalar);
}

bool vec3_t::operator==(const vec3_t vec) {
	return (this->x == vec.x && this->y == vec.y && this->z == vec.z);
}

bool vec3_t::operator==(const float value) {
	return (this->x == value && this->y == value && this->z == value);
}

bool vec3_t::operator!=(const vec3_t vec) {
	return (this->x != vec.x && this->y != vec.y && this->z != vec.z);
}

bool vec3_t::operator!=(const float value) {
	return (this->x != value && this->y != value && this->z != value);
}

vec3_t::operator float*() {
	return this->convert();
}

vec3_t vec3_t::forward(float distance) {
	float angle, sp, sy, cp, cy, PiDiv;
	PiDiv = M_PI / 180.0f;
	angle = this->y * PiDiv;
	sy = sin(angle);
	cy = cos(angle);
	angle = this->x * PiDiv;
	sp = sin(angle);
	cp = cos(angle);
	vec3_t temp(cp * cy * distance, cp * sy * distance, -sp * distance);
	return temp;
}

vec3_t vec3_t::normalize() {
	vec3_t newvec;
	newvec.x = this->x / length();
	newvec.y = this->y / length();
	newvec.z = this->z / length();
	return newvec;
}

float vec3_t::Vec3DistanceSq(vec3_t vec) {
	float _x = this->x - vec.x;
	float _y = this->y - vec.y;
	float _z = this->z - vec.z;
	return sqrt((_x * _x) + (_y * _y) + (_z * _z));
}

float vec3_t::length() {
	return (float)sqrt(x*x + y * y + z * z);
}

float* vec3_t::convert() {
	return (float*)&this[0];
}

void vec3_t::print() {
	printf("%.3f %.3f %.3f\n", this->x, this->y, this->z);
}

void AngleVectors(vec3_t angles, vec3_t *forward, vec3_t *right, vec3_t *up) {
	float angle;
	float sr, sp, sy, cr, cp, cy;
	angle = angles.y * (M_PI * 2.0f / 360.0f);
	sy = sin(angle);
	cy = cos(angle);
	angle = angles.x * (M_PI * 2.0f / 360.0f);
	sp = sin(angle);
	cp = cos(angle);
	angle = angles.z * (M_PI * 2.0f / 360.0f);
	sr = sin(angle);
	cr = cos(angle);
	if (forward) {
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}
	if (right) {
		right->x = (-1 * sr*sp*cy + -1 * cr*-sy);
		right->y = (-1 * sr*sp*sy + -1 * cr*cy);
		right->z = -1 * sr*cp;
	}
	if (up) {
		up->x = (cr*sp*cy + -sr * -sy);
		up->y = (cr*sp*sy + -sr * cy);
		up->z = cr * cp;
	}
}

void VectorToAngles(vec3_t *input, vec3_t *output) {
	float forward;
	float yaw, pitch;
	float PI = 3.1415926535897931;
	if (input->x == 0 && input->y == 0) {
		yaw = 0;
		if (input->z > 0) pitch = 90.00;
		else pitch = 270.00;
	}
	else {
		if (input->x != -1)
			yaw = (float)(atan2((double)input->y, (double)input->x) * 180.00 / PI);
		else if (input->y > 0)
			yaw = 90.00;
		else
			yaw = 270;
		if (yaw < 0)
			yaw += 360.00;

		forward = (float)sqrt((double)(input->x * input->x + input->y * input->y));
		pitch = (float)(atan2((double)input->z, (double)forward) * 180.00 / PI);
		if (pitch < 0) pitch += 360.00;
	}

	output->x = -pitch;
	output->y = yaw;
	output->z = 0;
}