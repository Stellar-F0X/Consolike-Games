#include "Struct.h"
#include <cmath>

using namespace std;

Vector2 Vector2::operator+=(const Vector2& other) const
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator*(const float& multiply) const
{
	return Vector2(x * multiply, y * multiply);
}

bool Vector2::operator<(const Vector2& other) const
{
	return (x == other.x ? y < other.y : x < other.x);
}

float Vector2::magnitude()
{
	return sqrt(this->sqrmagnitude());
}

int Vector2::sqrmagnitude()
{
	return x * x + y * y;
}

void Vector2::Set(const float x, const float y)
{
	this->x = x;
	this->y = y;
}