#include "Serial.h"


void Serial::SerializePINS(PINSData& data, const std::string& directory, const std::string& filename)
{
	std::string path = directory + filename + ".pins";
	std::ofstream file(path, std::ios::binary);
	if (!file.is_open())
	{
		std::string msg = "Cannot open file '" + path + "'";
		perror(msg.c_str());
		return;
	}

	file.write("PINS", 4);
	int numPins = data.pins.size();
	file.write((char*)&numPins, sizeof(int));

	for (const Pin* pin : data.pins)
	{
		file.write((char*)pin, sizeof(Pin));
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
		return 0;
	}

	// Read first 4 identifying bytes
	char type[4];
	file.read(type, 4);

	if (!charCmp(type, 4, "PINS"))
	{
		std::cout << "File at " << location << " formatted incorrectly.";
		return 0;
	}

	// Level data file
	Rope* destRope = (Rope*)dest;

	// Read next byte for # of pins
	int* nPins = new int;
	file.read((char*)nPins, sizeof(int));
	std::cout << *nPins << '\n';
	Pin* p = (Pin*)malloc(sizeof(Pin) * *nPins);
	
	for (int offset = 0; offset < *nPins; offset++)
	{
		Pin* loc = p + offset;
		file.read((char*)loc, sizeof(Pin));
		destRope->pins.push_back(loc);
	}
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