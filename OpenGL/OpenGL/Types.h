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