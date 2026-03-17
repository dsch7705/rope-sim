#include "Shape.h"


Shape::Shape(const unsigned int sides, const Vec2& center) : sides(sides), center(center)
{
	vertices = (Vec2*)malloc(sizeof(Vec2) * sides);
	normals = (Vec2*)malloc(sizeof(Vec2) * sides);
}
Shape::~Shape()
{
	free(vertices);
	free(normals);
}
void Shape::GenerateNormals(bool invert)
{
	for (int i = 0; i < sides; i++)
	{
		int nextI = (i + 1) % sides;

		Vec2 edge = vertices[nextI] - vertices[i];
		if (invert)
			edge = -edge;
		normals[i] = edge.perp().norm();
	}
}

Shape Shape::Star(float radius, const Vec2& center)
{
	Shape star(5, center);

	const double PI = 3.141592;
	for (int i = 0; i < star.sides; i++)
	{
		double theta = (-PI / 2.) + i * (4. * PI / star.sides);
		star.vertices[i] = Vec2(cos(theta) * radius, sin(theta) * radius);
	}

	star.GenerateNormals(false);
	return star;
}
Shape Shape::Box(const Vec2& size, const Vec2& center)
{
	Shape box(4, center);
	box.vertices[0] = size / 2;
	box.vertices[1] = Vec2(size.x / 2, -size.y / 2);
	box.vertices[2] = -size / 2;
	box.vertices[3] = -Vec2(size.x / 2, -size.y / 2);

	box.GenerateNormals(true);
	return box;
}