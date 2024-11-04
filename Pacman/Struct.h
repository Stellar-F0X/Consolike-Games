#pragma once
struct Vector2
{
public:
	Vector2(const float x = 0, const float y = 0) : x(x), y(y) {}
	Vector2 operator+=(const Vector2& other) const;
	Vector2 operator+(const Vector2& other) const;
	bool operator<(const Vector2& other) const;
	Vector2 operator*(const float& other) const;

public:
	float magnitude();
	int sqrmagnitude();
	void Set(float x, float y);

public:
	float x;
	float y;
};
