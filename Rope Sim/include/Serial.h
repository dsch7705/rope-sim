#pragma once
#include <string>
#include <chrono>
#include <fstream>
#include "Rope.h"


namespace Serial
{
	struct PINSData
	{
		const std::vector<Pin*>& pins;

		PINSData(const std::vector<Pin*>& pins) : pins(pins) {}
	};

	void SerializePINS(PINSData& data, const std::string& directory, const std::string& filename);
	size_t LoadFile(const std::string& location, void* dest);

	bool charCmp(char* data, size_t len, const char* lit);;
}