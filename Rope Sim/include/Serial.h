#pragma once
#include <string>
#include "Rope.h"


namespace Serial
{
	struct PINSData
	{
		const std::vector<Pin*>& pins;
		Color backColor;

		PINSData(const std::vector<Pin*>& pins, Color backColor) : pins(pins), backColor(backColor) {}
	};

	void SerializePINS(PINSData& data, const std::string& directory, const std::string& filename);
	void LoadFile(const std::string& location, void* dest);

	bool charCmp(char* data, size_t len, const char* lit);;
}