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

enum class PixelFormat
{
	RGB,
	RGBA
};

enum class DataType
{
	BYTE,
	UNSIGNED_BYTE,
	SHORT,
	UNSIGNED_SHORT,
	INT,
	UNSIGNED_INT,
	FLOAT
};

enum TextureType
{
	TEXTURE_1D,
	TEXTURE_2D,
	TEXTURE_3D
};

enum class TextureWrap
{
	REPEAT,          // The default behavior for textures.Repeats the texture image.
	MIRRORED_REPEAT, // Same as GL_REPEAT but mirrors the image with each repeat.
	CLAMP_TO_EDGE,   // Clamps the coordinates between 0 and 1. The result is that higher coordinates become clamped to the edge, resulting in a stretched edge pattern.
	CLAMP_TO_BORDER  // Coordinates outside the range are now given a user - specified border color.
};

enum class TextureFilter
{
	NEAREST,
	LINEAR
};

enum class MipmapSwitchingFilter
{
	NEAREST_MIPMAP_NEAREST,     //  takes the nearest mipmap to match the pixel size and uses nearest neighbor interpolation for texture sampling.
	LINEAR_MIPMAP_NEAREST,      //  takes the nearest mipmap level and samples using linear interpolation.
	NEAREST_MIPMAP_LINEAR,      //  linearly interpolates between the two mipmaps that most closely match the size of a pixel and samples via nearest neighbor interpolation.
	LINEAR_MIPMAP_LINEAR        //  linearly interpolates between the two closest mipmaps and samples the texture via linear interpolation.
};

enum class MemoryFormat
{
	FLOAT1,
	FLOAT2,
	FLOAT3,
	FLOAT4,
	INT1,
	INT2,
	INT3,
	INT4,
	UINT1,
	UNIT2,
	UNIT3,
	UNIT4,
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


enum class TextureUnit
{
	TEXTURE0,
	TEXTURE1,
	TEXTURE2,
	TEXTURE3,
	TEXTURE4,
	TEXTURE5,
	TEXTURE6,
	TEXTURE7,
	TEXTURE8,
	TEXTURE9,
	TEXTURE10,
	TEXTURE11,
	TEXTURE12,
	TEXTURE13,
	TEXTURE14,
	TEXTURE15,
	TEXTURE16
};
