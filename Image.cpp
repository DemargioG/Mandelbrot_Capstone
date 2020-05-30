#include <iostream>
#include <fstream>
#include <complex>
#include <vector>
#include <future>
#include <mutex>
#include <thread>
#include <chrono>

#include "Window.h"
#include "Pixel.h"

void lineCompletion(int line, Window<int> screen, Window<double> frac, std::ofstream& image)
{


	for (int j = 0; j < screen.getHeight(); j++)
	{
		Pixel p(line, j);

		p.iterations(screen, frac);

		image << p.getRed() << ' ' << p.getGreen() << ' ' << p.getBlue() << std::endl;


		std::this_thread::sleep_for(std::chrono::milliseconds(1)); // reduce cpu usage?
	}
}

int main()
{
	std::shared_ptr<std::vector<std::thread>> multiThread;
	std::vector<std::future<void>> fut;
	

	//Windows for the image, "Screen", and the subsections for evaluation, "Frac"
	Window<int> screen(0, 600, 0, 600);
	Window<double> frac (-2.2, 1.2, -1.7, 1.7);


	std::ofstream my_Image("mandelbrot.ppm");
	if (my_Image.is_open())
	{
		my_Image << "P3\n" << screen.getWidth() << " " << screen.getHeight() << " 255\n";

		//Iterate through the image filling in each pixel with the saved color.
		for (int i = 0; i < screen.getWidth(); i++)
		{
			std::cout << "Starting up thread " << i << std::endl;
			multiThread->emplace_back(std::thread(lineCompletion, &i, &screen, &frac, std::ref(my_Image)));

			std::this_thread::sleep_for(std::chrono::milliseconds(1)); // reduce cpu usage?
		}

		std::for_each(multiThread->begin(), multiThread->end(), [](std::thread& thread)
		{
			thread.join();
		});

		my_Image.close();

	}
	else
	{
		std::cout << "Failed to open file." << std::endl;
	}


	return 0;
}