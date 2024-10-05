#pragma once
#include <iostream>
#include "raylib/msf_gif.h"


struct Frame
{
	uint8_t* data = nullptr;
	Frame* next = nullptr;

	Frame(uint8_t* data, size_t bufferSize) : data(data) {}
	~Frame();
};
class GIF
{
	inline static const std::string saveDirectory = "res/gifs/";

	Frame* first = nullptr;
	Frame* last = nullptr;
	int w;
	int h;

public:
	float lengthS = 5.f;
	int frameTimeCS;

	GIF(int w, int h, int frameTimeCS) : w(w), h(h), frameTimeCS(frameTimeCS) {}
	~GIF();
	void RecordFrame(uint8_t* data);
	void SaveGIF(const std::string& filename);

};