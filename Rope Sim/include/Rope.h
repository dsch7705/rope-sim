#pragma once
#include <vector>
#include <cmath>
#include "Vec2.h"
#include "Shape.h"
#include "raylib/raylib.h"


struct Pin
{
	Vec2 pos;
	double radius;

	Pin() : pos(Vec2(0.f, 0.f)), radius(10.f) {}
	Pin(double x, double y, double radius) : pos(Vec2(x, y)), radius(radius) {}
};

struct Node
{
	Vec2 pos;
	double radius;
	Node* next;

	Node() : pos(Vec2()), radius(0.f), next(nullptr) {}
	Node(const Vec2& pos, double radius) : pos(pos), radius(radius), next(nullptr) {}
};
class Rope
{
public:
	std::vector<Pin*> pins;
	std::vector<Shape*> shapes;

public:
	Node* head;

	Rope(int size, double thickness);
	void Update(float dT, const Vec2& follow);
	void extend(int n);
	void shrink(int n);
	int count();

private:
	void Collisions(Node* node);
};
