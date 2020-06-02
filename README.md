# Mandelbrot_Capstone

This is a Capstone Project completed for the Udacity C++ Course.

After spending time learning C++, I was assigned a Capstone Project where I was to demonstrate whay I have learned. Through this projcet, I have implemented my knowledge of, Classes, functions I/O from files, Memory Management, and Concurrency. 
For my Capstone I decided to creat a Mandelbrot Fractal Image Generator. The program creates a 1200,1200 sized image and calculates the escape time per pixel. To calculate escape time, you mus recusively calculate an equation for a set number of iterations which I have set to 1000. To calculate the escape time for each pixel, one by one, would take an extremely large amount of time but, with concurrency the image generation time is significantly reduce.

## To run Locally
I used Visual Studio 2019 to create and build this program.

You can download Visual Studio at the link below.
https://visualstudio.microsoft.com/

## Files and Classes

-Tutorial.cpp
  This file was from a tutorial which I used as my foundation for my program. Link to the tutorial below.
  https://medium.com/farouk-ounanes-home-on-the-internet/mandelbrot-set-in-c-from-scratch-c7ad6a1bf2d9
  This file contains an easy to understand Mandlebrot Image Generator. Should this file be ran, it will save a ppm image in the source file of fractal image with Red out lines around it. However, this code is all commented out so only code I have written is compiled. 
  
-Image.cpp
  This file contains the Main(). Here, the image size is set, a new image is created, tasks are created for calculating the escape time of each pixel over an entire row. Then finally the information is written to the image, pixel by pixel.
    
-Pixel.h
  This file contains the Class Pixel. This class hold all the information of a pixel such as its coordinate and RGB. This class also contains functions used to calculate the Escape Time of the Pixel. Some of the equations found here were created by Paul Silisteanu. He also created a tutorial for Mandelbrot Generators, link below.
  https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11/
  
- Window.h
  This file contains the Template Class Window. This class was created by  This class is used to determine the size of the image for example. The Class contains related variables such as dimensions such as width and  height. This class was created by Paul Silisteanu. However, I did make some changes such as having the width calculated in the constructor, to make working with it a bit easier.
  
- PixelQueue.h
  This file is a customized "message queue". This file contains the class PixelQueue which is used to facilitate the movement of information from task back to main. Here, the color of each pixel within the rows are calculated, put into rows which are associated with their row number. Then the row is put into a Map container. When a row is needed, a row number is used to call the associated row.
  
## Project Points

- The project demonstrates an understanding of C++ functions and control structures:
  The project includes many examples of loops such as the nested loop in Image.cpp Line 56.
  Also includes many Functions such as iterations, Line 43 of Pixel.h
  
- The project reads data from a file and process the data, or the program writes data to a file:
  The project uses ofstream to create a ppm image in Line 29 of Image.cpp.
  Also the program writes to each pixel in the created image in Line 66 of Image.cpp.
  
- The project uses Object Oriented Programming techniques:
  The project creates class Pixel in Pixel.h where a many private attributes are created (Lines 101 - 109 of Pixel.h).
  Many methods are used in calculation or simply to retrieve information such as getRed (Line 25 of Pixel.h)
  
- Classes use appropriate access specifiers for class members:
  Public methods are declared starting at Line 12 of Pixel.h.
  Private methods and atributes are declared starting Line 59 of Pixel.h.
  
- Class constructors utilize member initialization lists:
  Constuctor used to intialize attributes of Pixel starting line 14 of Pixel.h.
  
- Classes abstract implementation details from their interfaces:
  All functions are documented via comments such as Line 75 of Pixel.h which explains the "escape()" function.
  
- Templates generalize functions in the project:
  The template class Window<T> uses many template functions.
  The template is declared in Line 10 of Window.h.
  
  - The project uses multithreading:
    The program is given the ability to use multiple threads in Line 42 of Image.cpp
    
  - A mutex or lock is used in the project:
    In PixelQueue.h, Line 42, a lock is used to prevent other threads from accessing the _pixelQueue while it is in use.
