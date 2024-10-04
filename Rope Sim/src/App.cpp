#include "App.h"


App::App(int w, int h, const char* title)
{
	InitWindow(w, h, title);
}

Rope rope(5, 20.f);
void App::Start()
{
	std::cout << rope.count() << '\n';
	rope.extend(45);
	std::cout << rope.count();
	for (int y = 0; y < GetScreenHeight(); y += GetScreenHeight() / 5.f)
	{
		for (int x = 0; x < GetScreenWidth(); x += GetScreenWidth() / 7.5f)
		{
			Pin* p = new Pin(x, y, 50.f);
			rope.pins.push_back(p);
		}
	}

	while (!WindowShouldClose())
	{	
		Update();
	}
}
void App::Update()
{
	//std::cout << &points[1] << '\n';
	//points[0].x = GetMouseX();
	//points[0].y = GetMouseY();
	rope.Update(GetFrameTime(), Vec2(GetMouseX(), GetMouseY()));

	
	Draw();
}
void App::Draw()
{
	BeginDrawing();

	// Draw
	ClearBackground(BLACK);

	// Rope
	Node* current = rope.head;
	while (current != nullptr)
	{
		DrawCircle(current->pos.x, current->pos.y, current->radius, WHITE);
		current = current->next;
	}
	// Pins
	for (const Pin* pin : rope.pins)
	{
		DrawCircle(pin->pos.x, pin->pos.y, pin->radius, LIGHTGRAY);
	}

	EndDrawing();
}