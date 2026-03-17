#include "Vec2.h"


double Vec2::dot(const Vec2& v1)
{
	return x * v1.x + y * v1.y;
}
double Vec2::mag()
{
	return sqrt(x * x + y * y);
}
Vec2 Vec2::norm()
{
	if (this->mag() == 0.f)
		return Vec2();

	return *this / this->mag();
}
Vec2 Vec2::lerp(const Vec2& v1, float t)
{
	return Vec2(x + (v1.x - x) * t, y + (v1.y - y) * t);
}
Vec2 Vec2::lerp(const Vec2& v0, const Vec2& v1, float t)
{
	return Vec2(v0.x + (v1.x - v0.x) * t, v0.y + (v1.y - v0.y) * t);
}
double Vec2::dist(const Vec2& v0, const Vec2& v1)
{
	Vec2 v2 = v1 - v0;
	return v2.mag();
}