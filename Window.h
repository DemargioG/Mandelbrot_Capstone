#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <fstream>
#include <complex>



template <class T>
class Window
{
public:
	// Initalize Window with dimensions. Then derives other necessary variables.
	Window(T minX, T maxX, T minY, T maxY) : _minX(minX), _maxX(maxX), _minY(minY), _maxY(maxY) 
	{
		_width = maxX - minX;
		_height = maxY - minY;
	}

	// Getters
	T getMaxX()
	{
		return _maxX;
	}
	T getMinX()
	{
		return _minX;
	}
	T getMaxY()
	{
		return _maxY;
	}
	T getMinY()
	{
		return _minY;
	}

	T getWidth()
	{
		return _width;
	}
	T getHeight()
	{
		return _height;
	}

private:
	// Window dimensions

	T _minX;
	T _maxX;
	T _minY;
	T _maxY;

	T _width;
	T _height;
};



#endif