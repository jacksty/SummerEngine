#pragma once

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef float_t float32;
typedef double_t float64;


// VECTOR4

#pragma pack(push, 1)
typedef struct {
	float32 x;
	float32 y;
	float32 z;
	float32 w;
} vector4;
#pragma pack(pop)

vector4 operator+(vector4 a, vector4 b)
{
	return vector4{ a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
}
vector4 operator-(vector4 a)
{
	return vector4{ -a.x, -a.y, -a.z, -a.w };
}
vector4 operator-(vector4 a, vector4 b)
{
	return vector4{ a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
}
void operator+=(vector4& a, vector4 b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	a.w += b.w;
}
void operator-=(vector4& a, vector4 b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	a.w -= b.w;
}
vector4 operator*(vector4 a, float32 b)
{
	return vector4{ a.x * b, a.y * b, a.z * b, a.w * b };
}
vector4 operator/(vector4 a, float32 b)
{
	return vector4{ a.x / b, a.y / b, a.z / b, a.w / b };
}
void operator*=(vector4& a, float32 b)
{
	a.x *= b;
	a.y *= b;
	a.z *= b;
	a.w *= b;
}
void operator/=(vector4& a, float32 b)
{
	a.x /= b;
	a.y /= b;
	a.z /= b;
	a.w /= b;
}
/// Dot product
float32 operator*(vector4 a, vector4 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}
/// Cross product
vector4 operator/(vector4 a, vector4 b)
{
	return vector4{ a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x, a.w * b.w };
}
float32 magnitude(vector4 a)
{
	return sqrtf(a * a);
}
void normalize(vector4& a)
{
	a /= magnitude(a);
}
/// Returns a normalized copy of this vector.
vector4 operator!(vector4 a)
{
	return a / magnitude(a);
}

#define VEC4_ZERO vector4{0.f, 0.f, 0.f, 0.f}



// MATRIX4X4

typedef struct{
	float32 data[16];

	inline float32 operator[](int index)
	{
		return data[index];
	}

	inline float32 get(int row, int column)
	{
		return data[row * 4 + column];
	}

	inline vector4 getRow(int row)
	{
		return (*reinterpret_cast<vector4*>(&data[row * 4]));
	}

	inline void set(int index, float32 value)
	{
		data[index] = value;
	}

	inline void setRow(int row, vector4 value)
	{
		(*reinterpret_cast<vector4*>(&data[row * 4])) = value;
	}
} matrix4x4;

matrix4x4 operator*(matrix4x4& a, matrix4x4& b)
{
	matrix4x4 c;

	for (int i = 0; i < 16; ++i)
	{
		int rowVals = i / 4;
		int colVals = i % 4 - 4;
		float32 val = 0.f;

		for (int j = 0; j < 4; ++j)
			val += a[rowVals++] * b[colVals += 4];

		c.set(i, val);
	}
	return c;
}
void operator*=(matrix4x4& a, matrix4x4& b)
{
	matrix4x4 c(a);

	for (int i = 0; i < 16; ++i)
	{
		int rowv = i / 4;
		int colv = i % 4 - 4;
		float32 val = 0.f;

		for (int j = 0; j < 4; ++j)
			val += c[rowv++] * b[colv += 4];

		a.set(i, val);
	}
}

#define MAT4_IDENTITY matrix4x4{{1.f, 0.f, 0.f, 0.f,   0.f, 1.f, 0.f, 0.f,   0.f, 0.f, 1.f, 0.f,   0.f, 0.f, 0.f, 1.f}}