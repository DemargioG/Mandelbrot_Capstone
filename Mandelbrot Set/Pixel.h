#ifndef PIXEL_H
#define PIXEL_H

#include <iostream>
#include <complex>
#include <math.h>

#include "Window.h"

class Pixel
{
public:
	// Initalize Pixels with Cartesaian Coordinates.
	Pixel(int &xCoord, int &yCoord) : _xCoord(xCoord), _yCoord(yCoord) 
	{
		_blue = 0;
		_green = 0;
		_red = 0;

		_escapeIter = 1000; //_maxIter
		_scaledEscapeInter = 1.0;
	}

	//Getters
	int getRed()
	{
		return _red;
	}

	int getBlue()
	{
		return _blue;
	}

	int getGreen()
	{
		return _green;
	}


	// Completes the Pixel object using its Coordinate to determine is Escape Time
	// and then assgining its Color.
	void iterations(Window<int> &screen, Window<double> &frac)
	{
		std::complex<double>coords((double)_yCoord, (double)_xCoord);

		coords = coordinateConversion(screen, frac, coords);

		_escapeIter = escape(coords, 1000);//_maxIter

		_scaledEscapeInter = (double)_escapeIter / 1000.0;//_maxIter

		color();

	}



private:

	// Background Equations

	//Mandelbrot equation z = z^2 + c 
	std::complex<double> mandelBrot(std::complex<double>& z, std::complex<double>& c)
	{
		return (z * z) + c;
	}

	//Converts a pixel from carteasian to complex coordiantes (Equation created by Paul Silisteanu)
	std::complex<double> coordinateConversion(Window<int>& screen, Window<double>& frac, std::complex<double> coords)
	{
		return std::complex<double>((coords.real() / screen.getWidth() * frac.getWidth()) + frac.getMinX(), (coords.imag() / screen.getHeight() * frac.getHeight()) + frac.getMinY());
	}

	// The "escape time" algorithm. This essentially checks if the coordinate is part of the Mandlebrot set. If the function fails to yeild a Z value
	//  2 or greater before reaching the max number of iterations, then it is part of the set. 
	int escape(std::complex<double> coords, int maxIter)
	{
		std::complex<double> z(0,0);
		int iter = 0;

		while (abs(z) < 2.0 && iter < maxIter)
		{
			z = mandelBrot(z, coords);

			iter++;
		}

		return iter;
	}

	// Set Colors using bernstein polynomials. (Equations created by Paul Silisteanu)
	void color()
	{
		_red = 9 * (1.0 - _scaledEscapeInter) * std::pow(_scaledEscapeInter, 3.0) * 255;
		_blue = 8.5 * std::pow((1.0 - _scaledEscapeInter), 3.0) * _scaledEscapeInter * 255;
		_green = 15 * std::pow((1.0 - _scaledEscapeInter), 2.0) * std::pow(_scaledEscapeInter, 2.0) * 255;
	}


	int _xCoord;
	int _yCoord;
	int _escapeIter;
	double _scaledEscapeInter;


	int _red;
	int _blue;
	int _green;


};



#endif
