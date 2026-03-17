#pragma once
#include "Vec2.h"


typedef struct Shape
{
	const unsigned int sides;
	Vec2 center;
	Vec2* vertices;
	Vec2* normals;

	Shape(const unsigned int sides, const Vec2& center);
	~Shape();
	void GenerateNormals(bool invert);

	static Shape Star(float radius, const Vec2& center);
	static Shape Box(const Vec2& size, const Vec2& center);
};