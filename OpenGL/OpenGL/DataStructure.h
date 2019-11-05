#pragma once

#include <string>

struct Color
{
	int r;
	int g;
	int b;
	int a;

	Color() = default;

	Color(int _r, int _g, int _b, int _a)
	{
		r = _r; g = _g; b = _b; a = _a;
	}

	Color(const Color& _color)
	{
		r = _color.r;
		g = _color.g;
		b = _color.b;
		a = _color.a;
	}

	Color& operator=(Color _color)
	{
		r = _color.r;
		g = _color.g;
		b = _color.b;
		a = _color.a;
		return *this;
	}

	float* data()
	{
		float arr[4] = { r, g, b, a };
		return arr;
	}
};

struct Origin
{
	int x;
	int y;
	int z;

	Origin() = default;

	Origin(int _x, int _y, int _z)
	{
		x = _x; y = _y; z = _z;
	}

	Origin(const Origin& _origin)
	{
		x = _origin.x;
		y = _origin.y;
		z = _origin.z;
	}

	Origin& operator=(Origin _origin)
	{
		x = _origin.x;
		y = _origin.y;
		z = _origin.z;
		return *this;
	}
};

struct Size
{
	int width;
	int height;
	int depth;

	Size() = default;

	Size(int _width, int _height, int _depth)
	{
		width = _width;
		height = _height;
		depth = _depth;
	}

	Size(const Size& _size)
	{
		width = _size.width;
		height = _size.height;
		depth = _size.depth;
	}

	Size& operator=(Size _size)
	{
		width = _size.width;
		height = _size.height;
		depth = _size.depth;
		return *this;
	}
};

struct Coordinate2D
{
	float x;
	float y;
	Coordinate2D(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	Coordinate2D(const Coordinate2D& _coordinate)
	{
		x = _coordinate.x;
		y = _coordinate.y;
	}

	Coordinate2D& operator=(Coordinate2D _coordinate)
	{
		x = _coordinate.x;
		y = _coordinate.y;
		return *this;
	}
};

struct Region
{
	Origin           origin;           // The coordinates for the front lower-left corner of a region.
	Size             size;             // The dimensions of an object.

	Region() = default;

	Region(Origin _origin, Size _size)
	{
		origin = _origin;
		size = _size;
	}

	Region(const Region& _region)
	{
		origin = _region.origin;
		size = _region.size;
	}

	Region& operator=(Region rhs)
	{
		origin = rhs.origin;
		size = rhs.size;
		return *this;
	}

	// @Return : A region whose x and width values are as specified.
	// The y and z coordinates of the region's origin are set to 0, 
	// and the region's height and depth are set to 1.
	static  Region regionMake1D(int x, int width)
	{
		Origin origin(x, 0, 0);
		Size size(width, 1, 1);
		return Region(origin, size);
	}

	// @Return : A region whose x, y, width, and height values are as specified. 
	// The z coordinate of the region's origin is set to 0,
	// and the region's depth is set to 1.
	static Region regionMake2D(int x, int y, int width, int height)
	{
		Origin origin(x, y, 0);
		Size size(width, height, 1);
		return Region(origin, size);
	}

	// @ Return : A 3D region with the specified values.
	static Region regionMake3D(int x, int y, int z, int width, int height, int depth)
	{
		Origin origin(x, y, z);
		Size size(width, height, depth);
		return Region(origin, size);
	}

};

struct PixelData
{
	uint8_t*    data;
	PixelFormat format;
	DataType    type;

	PixelData(uint8_t*  _data, PixelFormat _format, DataType _dataType)
	{
		data = _data;
		format = _format;
		type = _dataType;
	}

	PixelData(const PixelData& _pixelData)
	{
		data = _pixelData.data;
		format = _pixelData.format;
		type = _pixelData.type;
	}

	PixelData& operator=(PixelData _pixelData)
	{
		data = _pixelData.data;
		format = _pixelData.format;
		type = _pixelData.type;
		return *this;
	}
};

struct VertexAttribute
{
	int          count;
	Type         type;
	int          bufferIndex;
	int          offset;
	std::string  name;
	bool         normalized { false };
};

struct VertexLayout
{
	int stride;
};

template<MemoryFormat T>
struct MemoryLayout
{
	static int stride()
	{
		switch (T)
		{
		case MemoryFormat::FLOAT1:
			return sizeof(float);
			break;
		case MemoryFormat::FLOAT2:
			return 2 * sizeof(float);
			break;
		case MemoryFormat::FLOAT3:
			return 3 * sizeof(float);
			break;
		case MemoryFormat::FLOAT4:
			return 4 * sizeof(float);
			break;
		case MemoryFormat::INT1:
			return sizeof(int);
			break;
		case MemoryFormat::INT2:
			return 2 * sizeof(int);
			break;
		case MemoryFormat::INT3:
			return 3 * sizeof(int);
			break;
		case MemoryFormat::INT4:
			return 4 * sizeof(int);
			break;
		case MemoryFormat::UINT1:
			return sizeof(unsigned int);
			break;
		case MemoryFormat::UNIT2:
			return 2 * sizeof(unsigned int);
			break;
		case MemoryFormat::UNIT3:
			return 3 * sizeof(unsigned int);
			break;
		case MemoryFormat::UNIT4:
			return 4 * sizeof(unsigned int);
			break;
		default:
			break;
		}
	}

	static Type type()
	{
		switch (T)
		{
		case MemoryFormat::FLOAT1:
		case MemoryFormat::FLOAT2:
		case MemoryFormat::FLOAT3:
		case MemoryFormat::FLOAT4:
			return Type::FLOAT;
			break;
		case MemoryFormat::INT1:
		case MemoryFormat::INT2:
		case MemoryFormat::INT3:
		case MemoryFormat::INT4:
			return Type::INT;
		case MemoryFormat::UINT1:
		case MemoryFormat::UNIT2:
		case MemoryFormat::UNIT3:
		case MemoryFormat::UNIT4:
			return Type::UNSIGNED_INT;
			break;
		default:
			break;
		}
	}
};
