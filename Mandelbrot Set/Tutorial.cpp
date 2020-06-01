// I used this code as a starting point and reference for my code.
// It is from a Tutorial created by Farouk Ounane.
// the tutorial can be found at https://medium.com/farouk-ounanes-home-on-the-internet/mandelbrot-set-in-c-from-scratch-c7ad6a1bf2d9
// I did not create any of the code below.

// (I've commented out the code so my own code would properly compile in VS) 


/*
#include <iostream>
#include <fstream>
#include <complex>

float width = 600;
float height = 600;

int value(int x, int y)
{
	std::complex<float> point((float)x / width - 1.5, (float)y / height - 0.5);

	std::complex<float> z(0, 0);

	unsigned int nb_inter = 0;

	while (abs(z) < 2 && nb_inter <= 34) 
	{
		z = z * z + point;

		nb_inter++;
	}

	if (nb_inter < 34) 
	{
		return (255*nb_inter)/33;
	}
	else
	{
		return 0;
	}
}


int main()
{
	std::ofstream my_Image("mandelbrot.ppm");
	if (my_Image.is_open()) 
	{
		my_Image << "P3\n" << width << " " << height << " 255\n";

		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				int val = value(i, j);
				my_Image << val << ' ' << 0 << ' ' << 0 << std::endl;
			}
		}

		my_Image.close();

	}
	else 
	{
		std::cout << "Failed to open file." << std::endl;
	}


	return 0;

}

*/
