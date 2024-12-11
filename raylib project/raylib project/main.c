#include <stdio.h>
#include "raylib.h"
#include "raymath.h"

int main()
{
	// Tell the window to work on high DPI displays
	//SetConfigFlags(FLAG_WINDOW_HIGHDPI);

	int CanvasW = 1280;
	int CanvasH = 800;

	char text[] = "Hello Raylib";

	// Create the window and OpenGL context
	InitWindow(CanvasW, CanvasH, text);

	Font font = LoadFontEx("NotoSans-Regular.ttf", 90, NULL, 0);
	SetTextureFilter(font.texture , TEXTURE_FILTER_BILINEAR);

	SetTargetFPS(60);
	
	int posX = CanvasW / 2;
	int posY = CanvasH / 2;

	Vector2 textPos = { CanvasW / 2.0f - MeasureTextEx(font, text, (float)font.baseSize, 1).x / 2, CanvasH / 2.0f - (float)font.baseSize };
	Vector2 textVel = { 0, 0 };

	float dt; // delta time

	float speed = 300.0f;

	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		dt = GetFrameTime();

		if (IsKeyDown(KEY_D)) {
			textVel.x = speed;
		} 
		else if (IsKeyDown(KEY_A)) {
			textVel.x = -speed;
		}
		else {
			textVel.x = 0;
		}

		if (IsKeyDown(KEY_W)) {
			textVel.y = -speed;
		} 
		else if (IsKeyDown(KEY_S)) {
			textVel.y = speed;
		}
		else {
			textVel.y = 0;
		}

		textPos = Vector2Add(textPos, Vector2Scale(textVel, dt));
		
		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		// draw some text using the default font
		//DrawText("Hello Raylib!", posX, posY, 36, WHITE);
		DrawTextEx(font, text, textPos, (float)font.baseSize, 1, WHITE);

		//DrawFPS(0, 0);
		DrawText(TextFormat("%2d FPS", GetFPS()), 0, 0, 34, ORANGE);
		DrawText(TextFormat("%4f ms", dt), 0, 34, 34, BEIGE);
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}
	
	UnloadFont(font);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
