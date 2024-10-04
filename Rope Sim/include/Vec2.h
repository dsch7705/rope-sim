#pragma once
#include <math.h>
#include <iostream>
#include <stdexcept>


struct Vec2
{
	double x;
	double y;

	Vec2() : x(0.f), y(0.f) {}
	Vec2(double x, double y) : x(x), y(y) {}
	const Vec2 operator+(const Vec2& v1) const { return Vec2(x + v1.x, y + v1.y); }
	const Vec2 operator-(const Vec2& v1) const { return Vec2(x - v1.x, y - v1.y); }
	Vec2 operator+(const Vec2& v1) { return Vec2(x + v1.x, y + v1.y); }
	Vec2 operator-(const Vec2& v1) { return Vec2(x - v1.x, y - v1.y); }
	const Vec2 operator*(double s) const { return Vec2(x * s, y * s); }
	const Vec2 operator/(double s) const { return Vec2(x / s, y / s); }
	Vec2 operator*(double s) { return Vec2(x * s, y * s); }
	Vec2 operator/(double s) { return Vec2(x / s, y / s); }
	void operator+=(const Vec2& v1) { x += v1.x; y += v1.y; }
	void operator-=(const Vec2& v1) { x -= v1.x; y -= v1.y; }
	void operator*=(double s) { x *= s; y *= s; }
	void operator/=(double s) { x /= s; y /= s; }
	const Vec2 operator-() const { return Vec2(-x, -y); }
	Vec2 operator-() { return Vec2(-x, -y); }
	bool operator==(const Vec2& v1) { return (x == v1.x && y == v1.y); }

	Vec2 dot(const Vec2& v1);
	double mag();
	Vec2 norm();
	Vec2 lerp(const Vec2& v1, float t);

	static Vec2 lerp(const Vec2& v0, const Vec2& v1, float t);
	static double dist(const Vec2& v0, const Vec2& v1);
};