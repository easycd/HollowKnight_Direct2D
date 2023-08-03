#pragma once
#include <math.h>
#define PI 3.141592

namespace km
{
	struct VectorR
	{
		static VectorR Up;
		static VectorR Right;

		static VectorR One;
		static VectorR Zero;

		float x;
		float y;

		VectorR()
			: x(0.0f)
			, y(0.0f)
		{

		}
		VectorR(float x, float y)
			: x(x)
			, y(y)
		{

		}
		VectorR(int x, int y)
			: x(x)
			, y(y)
		{

		}
		VectorR(const VectorR&) = default;
		VectorR& operator=(const VectorR&) = default;

		VectorR(VectorR&&) = default;
		VectorR& operator=(VectorR&&) = default;

		VectorR operator+(const VectorR& other)
		{
			VectorR temp;
			temp.x = x + other.x;
			temp.y = y + other.y;

			return temp;
		}

		VectorR operator-(const VectorR& other)
		{
			VectorR temp;
			temp.x = x - other.x;
			temp.y = y - other.y;

			return temp;
		}

		VectorR operator*(const VectorR& other)
		{
			VectorR temp;
			temp.x = x * other.x;
			temp.y = y * other.y;

			return temp;
		}

		VectorR operator*(const float ratio)
		{
			VectorR temp;
			temp.x = x * ratio;
			temp.y = y * ratio;

			return temp;
		}

		VectorR operator/(const float ratio)
		{
			VectorR temp;
			temp.x = x / ratio;
			temp.y = y / ratio;

			return temp;
		}

		VectorR operator-()
		{
			return VectorR(-x, -y);
		}

		void operator+=(const VectorR& other)
		{
			x += other.x;
			y += other.y;
		}

		void operator-=(const VectorR& other)
		{
			x -= other.x;
			y -= other.y;
		}

		void operator*=(const VectorR& other)
		{
			x *= other.x;
			y *= other.y;
		}

		void operator*=(const float& value)
		{
			x *= value;
			y *= value;
		}

		bool operator==(const VectorR& other)
		{
			return (x == other.x && y == other.y);
		}

		bool operator!=(const VectorR& other)
		{
			return (x != other.x && y != other.y);
		}

		void operator-=(const float& value)
		{
			x -= value;
			y -= value;
		}

		void operator=(const float& value)
		{
			x = value;
			y = value;
		}

		float Length()
		{
			return sqrtf(x * x + y * y);
		}

		void Clear()
		{
			x = 0.0f;
			y = 0.0f;
		}

		//길이가 1인 단위 벡터로 만들어줌
		VectorR& Normalize()
		{
			float length = Length();

			if (Length() == 0.0f)
				return *this;

			x /= length;
			y /= length;

			return *this;
		}

	};

	namespace rigidmath
	{
		//float x = dir.x * cosf(PI / 5.0f) - dir.y * sinf(PI / 5.0f);
		//float y = dir.x * sinf(PI / 5.0f) + dir.y * cosf(PI / 5.0f);

		inline static VectorR Rotate(VectorR vector, float degree)
		{
			float radian = (degree / 180.0f) * PI;
			vector.Normalize();

			float x = vector.x * cosf(radian) - vector.y * sinf(radian);
			float y = vector.x * sinf(radian) + vector.y * cosf(radian);
			//atan
			//atan();
			return VectorR(x, y);
		}

		//내적
		inline static float Dot(VectorR& v1, VectorR& v2)
		{
			return v1.x * v2.x + v1.y * v2.y;
		}
		//외적
		inline static float Cross(VectorR& v1, VectorR& v2)
		{
			return v1.x * v2.y - v1.y * v2.x;
		}

		static VectorR Direction(VectorR v1, VectorR v2)
		{
			VectorR Dir = v2 - v1;
			Dir.Normalize();

			return Dir;
		}

	};
}