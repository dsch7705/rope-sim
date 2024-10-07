#pragma once
#include <string>
#include <chrono>
#include <fstream>
#include "Rope.h"


namespace Serial
{
	struct LEVELData
	{
		const std::vector<Pin*>& pins;
		const std::vector<Shape*>& shapes;

		LEVELData(const std::vector<Pin*>& pins, const std::vector<Shape*>& shapes) : pins(pins), shapes(shapes) {}
	};

	void SerializeLEVEL(LEVELData& data, const std::string& directory, const std::string& filename);
	size_t LoadFile(const std::string& location, void* dest);

	bool charCmp(char* data, size_t len, const char* lit);;
}