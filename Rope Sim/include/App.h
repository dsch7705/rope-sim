#pragma once
#include <iostream>
#include <array>
#include <string>
#include <chrono>
#include "raylib/raylib.h"
#include "Serial.h"
#include "GIF.h"
#include "Rope.h"


class App
{
public:
	inline static Vec2 center;

	App(int w, int h, const char* title);
	void Start();
	void RecordGIF();

private:
	Rope* rope;

	// GIF
	GIF* gifHandle;
	bool recordingGIF = false;
	float GIFStartTime = 0.f;

	float timeSinceLastFrameMS = 0.f;
	float GIFMSPerFrame = 50.f;

	// Core
	void Update();
	void Draw();
	void DrawShape(const Shape& shape);

	static void GetFileName(std::string& filename);
};