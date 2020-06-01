#include <iostream>
#include <fstream>
#include <complex>
#include <vector>
#include <future>
#include <mutex>
#include <thread>
#include <chrono>
#include <deque>


#include "Window.h"
#include "PixelQueue.h"
#include "Pixel.h"


int main()
{
	// Initiates the container for the futures (fut) and the Map for the rows of Pixels (list).
	std::vector<std::future<void>> fut;
	std::shared_ptr<PixelQueue> list(new PixelQueue);

	//Windows for the image, "Screen", and the subsections for evaluation, "Frac"
	Window<int> screen(0, 1200, 0, 1200);
	Window<double> frac (-2.2, 1.2, -1.7, 1.7);


	// Creates and opens the image.
	std::ofstream my_Image("mandelbrot.ppm");
	if (my_Image.is_open())
	{
		// Sizes the image based on the Window 'screen" and then, fills it with red.
		my_Image << "P3\n" << screen.getWidth() << " " << screen.getHeight() << " 255\n";

		//Iterates the height of the image file creating a thread for each row.
		// In each row, each pixel color will be calculated based on its escape time.
		for (int i = 0; i < screen.getWidth(); i++)
		{

			std::deque<Pixel> p;

			fut.emplace_back(std::async(&PixelQueue::send, list, std::move(p), std::ref(screen), std::ref(frac),i));

			std::this_thread::sleep_for(std::chrono::milliseconds(1)); //reduce cpu usage

		}

		// Waits for all threads to finish.
		std::for_each(fut.begin(), fut.end(), [](std::future<void>& ftr)
		{
			ftr.wait();
		});

		// Retrieves the designated row, then iterates over each pixel writing the new color
		// to the image.
		for (int m = 0; m < screen.getWidth(); m++)
		{

			std::deque<Pixel> row = list->receive(m);

			for (int n = 0; n < screen.getHeight(); n++)
			{
				Pixel pixel = std::move(row.back());
				row.pop_back();

				my_Image << pixel.getRed() << ' ' << pixel.getGreen() << ' ' << pixel.getBlue() << std::endl;

				std::this_thread::sleep_for(std::chrono::milliseconds(1)); //reduce cpu usage
			}

		}
		// Saves and closes the image file. 
		my_Image.close();

	}
	// If the file was unable to be created.
	else
	{
		std::cout << "Failed to open file." << std::endl;
	}


	return 0;
}