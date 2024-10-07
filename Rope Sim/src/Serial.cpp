#include "Serial.h"


void Serial::SerializeLEVEL(Serial::LEVELData& data, const std::string& directory, const std::string& filename)
{
	std::string path = directory + filename + ".pins";
	std::ofstream file(path, std::ios::binary);
	if (!file.is_open())
	{
		std::string msg = "Cannot open file '" + path + "'";
		perror(msg.c_str());
		return;
	}

	// File header
	int headerLen = 5;
	file.write((char*)&headerLen, sizeof(int));
	file.write("LEVEL", headerLen);					// type
	int numPins = data.pins.size();
	file.write((char*)&numPins, sizeof(int));		// # pins
	int numShapes = data.shapes.size();
	file.write((char*)&numShapes, sizeof(int));		// # shapes

	// Pins
	for (const Pin* pin : data.pins)
	{
		file.write((char*)pin, sizeof(Pin));
	}

	// Shapes
	for (const Shape* shape : data.shapes)
	{
		int vertBufferSize = sizeof(Vec2) * shape->sides;
		int fullBufferSize = sizeof(shape->sides) + sizeof(shape->center) + vertBufferSize;
		char* buffer = (char*)malloc(sizeof(shape->sides) + sizeof(shape->center) + vertBufferSize);
		if (buffer == nullptr)
			continue;

		char* ptr = buffer;
		memcpy(ptr, &shape->sides, sizeof(shape->sides));		// # sides
		ptr += sizeof(shape->sides);
		memcpy(ptr, &shape->center, sizeof(shape->center));		// center
		ptr += sizeof(shape->center);
		memcpy(ptr, shape->vertices, vertBufferSize);			// vertices

		file.write(buffer, fullBufferSize);

		free(buffer);
		ptr = nullptr;
	}

	file.close();
}
size_t Serial::LoadFile(const std::string& location, void* dest)
{
	// Self timing
	using namespace std::chrono;
	auto start = high_resolution_clock::now();

	// Open file
	std::ifstream file(location, std::ios::binary);
	if (!file.is_open())
	{
		std::string msg = "Cannot open file '" + location + "'";
		perror(msg.c_str());
		return -1;
	}

	// Header
	int headerLen;
	file.read((char*)&headerLen, sizeof(int));
	char* type = new char[5];
	file.read(type, headerLen);							// type

	if (charCmp(type, 5, "LEVEL"))
	{
		// Level handle
		Rope* level = (Rope*)dest;

		// Read # of objects
		int nPins, nShapes;
		file.read((char*)&nPins, sizeof(int));			// # pins
		file.read((char*)&nShapes, sizeof(int));		// # shapes

		Pin* pinBuf = (Pin*)malloc(sizeof(Pin) * nPins);
		Shape* shapeBuf = (Shape*)malloc(sizeof(Shape) * nShapes);
		if (pinBuf == nullptr || shapeBuf == nullptr)
			return -1;

		// Pins
		for (int offset = 0; offset < nPins; offset++)
		{
			Pin* loc = pinBuf + offset;
			file.read((char*)loc, sizeof(Pin));
			level->pins.push_back(loc);
		}

		// Shapes
		for (int i = 0; i < nShapes; i++)
		{
			Shape* loc = shapeBuf + i;									// Address to write to
			file.read((char*)&loc->sides, sizeof(loc->sides));			// # sides
			loc->vertices = (Vec2*)malloc(sizeof(Vec2) * loc->sides);
			loc->normals = (Vec2*)malloc(sizeof(Vec2) * loc->sides);
			file.read((char*)&loc->center, sizeof(loc->center));		// center
			file.read((char*)loc->vertices, sizeof(Vec2) * loc->sides); // vertices

			loc->GenerateNormals(false);
			level->shapes.push_back(loc);
		}
	}

	delete[] type;
	file.close();

	// Self timing
	auto stop = high_resolution_clock::now();
	duration time = duration_cast<microseconds>(stop - start);
	return time.count();
}

bool Serial::charCmp(char* data, size_t len, const char* lit)
{
	for (int i = 0; i < len; i++)
	{
		if (data[i] != lit[i])
			return false;
	}

	return true;
}