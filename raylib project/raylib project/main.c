#include "raylib.h"

int main()
{
	// Tell the window to use vsync and work on high DPI displays
	//SetConfigFlags(FLAG_WINDOW_HIGHDPI);

	int windowW = 800;
	int windowH = 600;

	// Create the window and OpenGL context
	InitWindow(windowW, windowH, "Hello Raylib");

	Font font = LoadFontEx("arial.ttf", 36, NULL, 0);

	SetTargetFPS(60);
	
	int posX = 0;
	int posY = 0;

	Vector2 textPos = { 0.0f, 0.0f };

	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{

		if (IsKeyDown(KEY_D)) {
			textPos.x += 10;
		}
		if (IsKeyDown(KEY_A)) {
			textPos.x -= 10;
		}
		if (IsKeyDown(KEY_W)) {
			textPos.y -= 10;
		}
		if (IsKeyDown(KEY_S)) {
			textPos.y += 10;
		}
		
		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		// draw some text using the default font
		//DrawText("Hello Raylib!", posX, posY, 36, WHITE);
		DrawTextEx(font, "Hello Raylib", textPos, 36, 1, WHITE);
		DrawText(TextFormat("%2d", GetFPS()), 0, 0, 36, ORANGE);
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
