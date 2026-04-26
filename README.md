# Image Filter Viewer
Built with C + raylib, Drag the splut to compare filters side by side

## Filters 
<prev>

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


</prev>

## Controls
- Drag middle line - compare original vs filter
- Rigth click - cycle through filters

## Build
<prev>
  gcc main.c -lraylib -lm -o viewer
</prev>
