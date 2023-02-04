#include "CoreMinimal.h"

void SetTextPosition(Vector2& Location)
{
	static float valueX = 1.f;
	static float valueY = 1.f;

	size_t textSize = 400;
	if (Location.x + textSize >= GetScreenWidth()) {
		valueX = -1;
	}
	else if (Location.x <= 0) {
		valueX = 1;
	}

	if (Location.y + 20 >= GetScreenHeight()) {
		valueY = -1;
	}
	else if (Location.y <= 0) {
		valueY = 1;
	}

	Location.x += valueX;
	Location.y += valueY;
}

int main(int argc, char* argv[])
{
	InitWindow(1280, 720, GAME_NAME);
	SetTargetFPS(60);

	Vector2 TextLocation{100.f, 300.f};

	do {
		BeginDrawing();
		ClearBackground(DARKGRAY);
		
		// Demo
		SetTextPosition(TextLocation);
		DrawFPS(100, 100);
		DrawText("Game Template <Canal do Oliveira Dev>", (int)TextLocation.x, (int)TextLocation.y, 20, YELLOW);
		// Demo

		EndDrawing();
	} while (!WindowShouldClose());

	CloseWindow();

	return 0;
}