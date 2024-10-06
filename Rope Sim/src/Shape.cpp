#include "Shape.h"


Shape::Shape(const unsigned int sides, const Vec2& center) : sides(sides), center(center), normals(nullptr)
{
	vertices = (Vec2*)malloc(sizeof(Vec2) * sides);
	normals = (Vec2*)malloc(sizeof(Vec2) * sides);
}
Shape::~Shape()
{
	free(vertices);
	free(normals);
}

Shape Shape::Star(float radius, const Vec2& center)
{
	Shape star(5, center);

	const double PI = 3.141592;
	for (int i = 0; i < star.sides; i++)
	{
		double theta = (-PI / 2.) + i * (4. * PI / star.sides);
		star.vertices[i] = star.center + Vec2(cos(theta) * radius, sin(theta) * radius);
	}
	CalculateNormals(star);

	return star;
}

void Shape::CalculateNormals(Shape& shape)
{
	for (int i = 0; i < shape.sides; i++)
	{
		int nextI = (i + 1) % shape.sides;
		shape.normals[i] = (shape.vertices[nextI] - shape.vertices[i]).perp().norm();
	}
}