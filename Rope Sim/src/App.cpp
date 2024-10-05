#include "App.h"


App::App(int w, int h, const char* title)
{
	InitWindow(w, h, title);
	center.x = w / 2.f;
	center.y = h / 2.f;
}

void App::Start()
{
	rope = new Rope(10, 20.f);

	int numPins = 0;
	double pinCircleRadius = 275.f;
	double pinRadius = 15.f;
	for (int i = 0; i < numPins; i++)
	{
		double theta = ((2.f * PI) / numPins) * i;
		Pin* p = new Pin(center.x + cos(theta) * pinCircleRadius, center.y + sin(theta) * pinCircleRadius, pinRadius);
		rope->pins.push_back(p);
		p = new Pin(center.x + cos(theta) * pinCircleRadius*.5f, center.y + sin(theta) * pinCircleRadius*.5f, pinRadius - 10);
		rope->pins.push_back(p);
	}

	Serial::PINSData data(rope->pins, BLACK);
	//Serial::SerializePINS(data, "res/save/", "double_circle");
	Serial::LoadFile("res/save/double_circle.pins", rope);

	while (!WindowShouldClose())
	{
		Update();
	}
}
void App::RecordGIF()
{
	gifHandle = new GIF(GetScreenWidth(), GetScreenHeight(), GIFMSPerFrame / 10);
	GIFStartTime = GetTime();
	timeSinceLastFrameMS = 0.f;
	recordingGIF = true;
}
void App::GetFileName(std::string& filename)
{
	std::cout << "\nEnter file name: ";
	std::cin >> filename;
}

void App::Update()
{
	rope->Update(GetFrameTime(), Vec2(GetMouseX(), GetMouseY()));
	Draw();

	// Input
	if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S))
		RecordGIF();

	// GIF
	if (recordingGIF)
	{
		timeSinceLastFrameMS += (GetTime() - GIFStartTime);

		// Record frame
		if (timeSinceLastFrameMS / 10 > gifHandle->frameTimeCS)
		{
			uint8_t* img = (uint8_t*)LoadImageFromScreen().data;
			gifHandle->RecordFrame(img);
			timeSinceLastFrameMS = 0.f;
		}
		// Stop recording
		if (GetTime() - GIFStartTime > gifHandle->lengthS)
		{
			std::string filename;
			App::GetFileName(filename);
			gifHandle->SaveGIF(filename.c_str());

			delete(gifHandle);

			timeSinceLastFrameMS = 0.f;
			GIFStartTime = 0.f;
			recordingGIF = false;
		}
	}
}
void App::Draw()
{
	BeginDrawing();

	// Draw
	ClearBackground(BLACK);

	// Rope
	Node* current = rope->head;
	while (current != nullptr)
	{
		DrawCircle(current->pos.x, current->pos.y, current->radius, WHITE);
		current = current->next;
	}
	// Pins
	for (const Pin* pin : rope->pins)
	{
		DrawCircle(pin->pos.x, pin->pos.y, pin->radius, LIGHTGRAY);
	}

	EndDrawing();
}