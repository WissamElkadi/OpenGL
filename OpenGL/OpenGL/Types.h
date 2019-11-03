#pragma once

enum class Type
{
	BYTE,
	UNSIGNED_BYTE,
	SHORT,
	UNSIGNED_SHORT,
	INT,
	UNSIGNED_INT,
	FLOAT
};

enum class ShaderType
{
	VERTEX,
	GEOMETRY,
	FRAGMENT
};

enum class DrawingPrimitive
{
	POINTS,
	LINES,
	LINE_LOOP,
	LINE_STRIP,
	TRIANGLES,
	TRIANGLE_STRIP,
	TRIANGLE_FAN
};

enum class UniformType
{
	FLOAT_1,
	FLOAT_2,
	FLOAT_3,
	FLOAT_4,
	INT_1,
	INT_2,
	INT_3,
	INT_4,
	VEC_FLOAT_1,
	VEC_FLOAT_2,
	VEC_FLOAT_3,
	VEC_FLOAT_4,
	VEC_INT_1,
	VEC_INT_2,
	VEC_INT_3,
	VEC_INT_4,
	MAT_FLOAT_2X2,
	MAT_FLOAT_3X3,
	MAT_FLOAT_4X4
};
