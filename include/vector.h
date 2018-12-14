#pragma once

#define M_PI 3.1415926535897931

class vec2_t {
public:
	float x, y;

	//constructors
	vec2_t();
	~vec2_t();
	vec2_t(float x);
	vec2_t(float x, float y);
	vec2_t(float x, float y, float z);
	vec2_t(float vect[2]);

	//operators
	vec2_t operator+(const vec2_t vec);
	vec2_t operator+(const float* vec);
	vec2_t operator-(const vec2_t vec);
	vec2_t operator-(const float* vec);
	vec2_t operator*=(const vec2_t vec);
	vec2_t operator*=(const float scalar);
	bool operator==(const vec2_t vec);
	bool operator==(const float value);
	bool operator!=(const vec2_t vec);
	bool operator!=(const float value);
	operator float*();

	//functions
	float* convert();
	void print();
};

class vec3_t {
public:
	float x, y, z;

	//constructors
	vec3_t();
	~vec3_t();
	vec3_t(float x);
	vec3_t(float x, float y);
	vec3_t(float x, float y, float z);
	vec3_t(float* vec);
	vec3_t(int null);

	//operators
	vec3_t operator+(const vec3_t vec);
	vec3_t operator+(const float* vec);
	vec3_t operator-(const vec3_t vec);
	vec3_t operator-(const float* vec);
	vec3_t operator-() const;
	vec3_t operator-=(const vec3_t vec);
	vec3_t operator+=(const vec3_t vec);
	vec3_t operator*=(const vec3_t vec);
	vec3_t operator*=(const float scalar);
	vec3_t operator *(const float scalar);
	bool operator==(const vec3_t vec);
	bool operator==(const float value);
	bool operator!=(const vec3_t vec);
	bool operator!=(const float value);
	operator float*();

	//functions
	vec3_t forward(float distance = 1.0f);
	vec3_t normalize();
	float Vec3DistanceSq(vec3_t vec);
	float length();
	float* convert();
	void print();
};

void AngleVectors(vec3_t angles, vec3_t *forward, vec3_t *right, vec3_t *up);
void VectorToAngles(vec3_t *input, vec3_t *output);