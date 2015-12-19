# PINTADO
A colorful drawing application for the UPLB ICS-OS.

# DESCRIPTION
	Draw simple objects such as points and lines using key events.

# INSTALLATION
	To install Pintado in [ICS-OS] (https://github.com/srg-ics-uplb/ics-os):
		Extracting and placement of source code.
			1. Extract files from pintado.zip.
			2. Copy pintado folder to ics-os/contrib.

		Building the program
			3. Open a terminal.
			4. Go to the directory of pintado inside the ICS-OS.
				cd ics-os/contrib/pintado
			5. Install the program using the following commands:
				make
				make install
		Re-building ICS-OS
			6. Since a new application was installed, ICS-OS must
			be rebuilt using the following commands:
			(NOTE: Go back to the root directory of ics-os [cd ../..])
				make clean
				make
				sudo make install
		Running the pintado.
			7. Boot the ics-os using a floppy disc or an emulator.
			8. Go to /apps.
				cd apps
			9. Run pintado.
				pintado.exe

# CONTROLS
	Here are the different key events recognized by Pintado:
	
	Change the color of the pen:
		1 - Black
		2 - Blue
		3 - Green
		4 - Red
		5 - Brown 
		6 - Yellow
		7 - White
	
	Move the pen:
		q - Upper left
		w - Upward
		e - Upper right
		a - Left
		d - Right
		z - Lower left
		s - Downward
		c - Lower Right
	NOTE: This also colors the path with the current pen color.
		Default color is black.
		Default position of the pen is at the center.
	
	Other keys:
		0 				- Clears the canvas and moves the pen to the center.
		f<color_key>	- Fill the current pixel, including all adjacent ones 
						with same color as the current pixel, with the color 
						specified.
		p 				- Exit.
		
# MANUAL
	Objects can be drawn by using the controls described aboved. All you need 
	to do is to guide the pen using the movement keys and change its color 
	using the color keys.

	Here are some guides for you to start drawing:

	A. Drawing a straight line.
		By pressing a movement key multiple times, you can form a line.
		Examples: 
			Pressing the following keys will create a horizontal line:
				dddddddddddddddd
			Pressing the following keys will create a vertical line:
				wwwwwwwwwwwwwwww
		Drawing and combining lines can create more complex objects.

	B. Drawing a polygon.
		Lines must be strategically created to form a closed figure.
		Example:
			Pressing the following keys will create a small rectangle:
				wwwwwwdddddddddddsssssaaaaaaaaaaa

	C. Filling a figure.
		You can fill an area with the same color using the 'f' key followed by
		a color key. 
		Example:
			First, create polygon or any closed figure. Afterwards, move the 
			pen inside that polygon.
			(NOTE: You will notice that going inside your polygon will also
			make a line of path. To avoid this, right after you enter the
			polygon, change the pen's color to the color of the background.)
			Press 'f' then a color key. This will make every pixel inside the
			polygon colored same with the color specified.

	D. Clearing the canvas.
		Pressing '0' will reset your canvas. It also sets back the pen's color
		and position to the default one.

	E. Other Tips and Tricks
		To change the background color of your canvas, before drawing anything
		else, set the color of your pen to the current backgrounnd color, then
		use fill to update the background color.

		You can erase objects using a WHITE-colored PEN.

		There is no undo; take care.

# AUTHORS
	Written by 
		Clinton E. Poserio (ceposerio@up.edu.ph) and 
		Kenneth B. Kim (kbkim@up.edu.ph).
	
# REPORTING BUGS
	Report Pintado bugs to our emails.
	
# COPYRIGHT
	This is a free software: you are free to change and redistribute it.
	There is NO WARRANTY, to the extent permitted by law.

----------------------------------------------------------------------------	
Comments and suggestions for development are very welcome!