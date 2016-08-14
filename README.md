# LeTrebuchet
OpenGL Assignment in a course about computergraphics

## How to open the project

The project in this repo was compiled with at least VC++ version 120 (Visual Studio 2013) on a Windows 7 64bit platform.
The binaries for the .exe and libs are Win32.

So usually you can just go into bin/Debug/Win32 and hit the .exe file and it should start.

If its not starting, then you probably have a different base configuration. In this case you would need to
build the project itself via the solution. If the build fails because of linker-errors of a lib like freeglut or glew, 
you would need to download the correct binaries of these and update the Thirdparty/lib folder as well as adding the .dll of the
lib to the binary where the exe LeTreb is nested.
