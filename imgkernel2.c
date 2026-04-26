#include <stdio.h>
#include <raylib.h>
#include <math.h>

# define WIDTH 1800
# define HEIGHT 1000



static void normalizekernel(float *kernel, int size)
{
	float sum = 0;
	for (int i = 0; i < size; i++) sum += kernel[i];

	if (sum != 0){
		for(int i = 0; i < size; i++) kernel[i] = kernel[i]/sum;
	}
}



int main(void)
{	
	// Getting Started
	InitWindow(WIDTH, HEIGHT, "I WuW Raylib");
	Image image = LoadImage("haha.jpg");

	if (image.data == NULL) {
    		TraceLog(LOG_ERROR, "Failed to load image!");
    		CloseWindow();
    		return 1;
	}

	

	// For Edge Detection
	float Edgedetection[] = {
		0.0f, -1.0f, 0.0f,
		-1.0f, 4.0f, -1.0f,
		0.0f, -1.0f, 0.0f
	};

	float Sharpenkernel[] = {
		0.0f, -1.0f, 0.0f,
		-1.0f, 5.0f, -1.0f,
		0.0f, -1.0f, 0.0f
	};

	float Sobelkernel[] = {
		-1.0f, 0.0f, 1.0f,
		-2.0f, 0.0f, 2.0f,
		-1.0f, 0.0f, 1.0f
	};
	
	float Embross[] = {
   		-2.0f, -1.0f, 0.0f,
    		-1.0f, 1.0f, 1.0f,
    		 0.0f, 1.0f, 2.0f
		};






	// Normalize Kernel to avoid Britness
	normalizekernel(Edgedetection, 9);
	normalizekernel(Sharpenkernel, 9);
	normalizekernel(Sobelkernel, 9);
	normalizekernel(Embross, 9);


	Image new_image_edge = ImageCopy(image);
	ImageKernelConvolution(&new_image_edge, Edgedetection, 9);

	Image new_image_sharpen = ImageCopy(image);
	ImageKernelConvolution(&new_image_sharpen, Sharpenkernel, 9);

	Image new_image_sobel = ImageCopy(image);
	ImageKernelConvolution(&new_image_sobel, Sobelkernel, 9);

	Image new_image_embross = ImageCopy(image);
	ImageKernelConvolution(&new_image_embross, Embross, 9);



	Texture2D old_one = LoadTextureFromImage(image);
	Texture2D edge_one = LoadTextureFromImage(new_image_edge);
	Texture2D sharpen_one = LoadTextureFromImage(new_image_sharpen);
	Texture2D sobel_one = LoadTextureFromImage(new_image_sobel);
	Texture2D embross_one = LoadTextureFromImage(new_image_embross);
	


	SetTargetFPS(60);


	float splitX = WIDTH/ 2.0f;
	bool dragging = false;
	int count = 0;


	while (!WindowShouldClose())
	{

		Vector2 mouse_pos = GetMousePosition();

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			if (fabsf(mouse_pos.x - splitX) < 10.0f) dragging = true;

		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) dragging = false;

		if (dragging) splitX = mouse_pos.x;


		// Clamping
		if (splitX < 10) splitX = 10;
		if (splitX > WIDTH - 10) splitX = WIDTH - 10;


		if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) count++;

		Texture2D filters[] = {old_one, edge_one, sharpen_one, sobel_one, embross_one};
		const char *filter_names[] = {"Normal", "Edge", "Sharpen", "Sobel", "Embross"};
		Texture2D Rtex = filters[count % 5];


		BeginDrawing();
		ClearBackground(RAYWHITE);

		float splitRatio = splitX / (float)WIDTH;


		// LEFT SIDE
		Rectangle srcLeft = {
			0, 0, 
			old_one.width * splitRatio,
			old_one.height,
		};
		Rectangle dstLeft = {
			0, 0,
			splitX,
			HEIGHT,
			
		};
		DrawTexturePro(old_one, srcLeft, dstLeft, (Vector2){0, 0}, 0.0f, WHITE);

		

		// RIGHT SIDE
		Rectangle srcRight = {
			0,
			0,  WIDTH - splitX,
			//WIDTH - (1.0f - splitX),
			HEIGHT
		};
		Rectangle dstRight = {
			splitX,
			0,
			WIDTH - splitX,
			HEIGHT,
		};
		

		DrawTexturePro(Rtex, srcRight, dstRight, (Vector2){0, 0}, 0.0f, WHITE);

		// Middle seperation line
		DrawLineEx((Vector2){splitX, 0}, (Vector2){splitX, HEIGHT}, 2.0f, RED);


		// Labels
		int Llabel_width, Rlabel_width; 
		

		if (splitX >= 130) Llabel_width = 120;
		else Llabel_width = splitX - 10;
		



		DrawRectangle(10, 10, Llabel_width, 40, (Color){0,0,0,150} );
		DrawText( "Original", 15, 15, 30, WHITE);


		DrawRectangle(splitX + 10, 10, 140, 40, (Color){0,0,0,150} );
		DrawText(filter_names[count % 5], splitX + 15, 15, 30, YELLOW);

		DrawText("Right-click to change filter", 10, HEIGHT - 30, 25, GRAY);
	

		EndDrawing();
	}

	UnloadImage(image);
	UnloadImage(new_image_edge);
	UnloadImage(new_image_sharpen);
	UnloadImage(new_image_sobel);
	UnloadImage(new_image_embross);

	
	UnloadTexture(embross_one);
	UnloadTexture(old_one);	
	UnloadTexture(edge_one);
	UnloadTexture(sharpen_one);
	UnloadTexture(sobel_one);



	CloseWindow();
	return 0;
}
