#include "Serial.h"


void Serial::SerializePINS(PINSData& data, const std::string& directory, const std::string& filename)
{
	FILE* fp;
	std::string path = directory + filename + ".pins";
	fopen_s(&fp, path.c_str(), "wb");
	if (fp == nullptr)
	{
		std::string msg = "Cannot open file '" + path + "'";
		perror(msg.c_str());
		return;
	}


	fwrite("PINS", 4, 1, fp);
	size_t numPins = data.pins.size();
	fwrite(&numPins, sizeof(size_t), 1, fp);

	for (const Pin* pin : data.pins)
	{
		fwrite(pin, sizeof(Pin), 1, fp);
	}

	fclose(fp);
}
void Serial::LoadFile(const std::string& location, void* dest)
{
	FILE* fp;
	fopen_s(&fp, location.c_str(), "rb");
	if (fp == nullptr)
	{
		std::string msg = "Cannot open file '" + location + "'";
		perror(msg.c_str());
		return;
	}

	char type[4];
	fread_s(type, 4, 1, 4, fp);

	if (!charCmp(type, 4, "PINS"))
	{
		std::cout << "File at " << location << " formatted incorrectly.";
		return;
	}
	Rope* destRope = (Rope*)dest;

	size_t* nPins = new size_t;
	fread_s(nPins, sizeof(size_t), sizeof(size_t), 1, fp);

	for (int i = 0; i < *nPins; i++)
	{
		Pin* p = (Pin*)malloc(sizeof(Pin));
		if (p == nullptr)
			continue;

		fread_s(p, sizeof(Pin), sizeof(Pin), 1, fp);
		destRope->pins.push_back(p);
	}
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