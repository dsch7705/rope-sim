#pragma once
#include <iostream>
#include <array>
#include <string>
#include "raylib/raylib.h"
#include "Rope.h"


class App
{
public:
	App(int w, int h, const char* title);
	void Start();

private:
	void Update();
	void Draw();
};