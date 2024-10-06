#pragma once
#include "Vec2.h"


struct Shape
{
	const unsigned int sides;
	Vec2 center;
	Vec2* vertices;
	Vec2* normals;

	Shape(const unsigned int sides, const Vec2& center);
	~Shape();

	static Shape Star(float radius, const Vec2& center);
	static void CalculateNormals(Shape& shape);
};