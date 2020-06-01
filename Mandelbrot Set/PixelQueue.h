#ifndef PIXELQUEUE_H
#define PIXELQUEUE_H

#include <iostream>
#include <complex>
#include <queue>
#include <mutex>
#include <thread> 
#include <chrono>
#include <map>


#include "Pixel.h"
#include "Window.h"

class PixelQueue
{
public:

	// Retrieves the Row from the Map (_pixelQueue) given the row number.
	std::deque<Pixel> receive(int x)
	{
		std::unique_lock<std::mutex> ulck(_mutex);
		_con.wait(ulck, [this] {return !_pixelQueue.empty();});

		std::deque<Pixel> pix = std::move(_pixelQueue[x]);
		_pixelQueue.erase(x);

		return pix;
	}

	void send(std::deque<Pixel>&& queue, Window<int> screen, Window<double> frac, int iter)
	{
		// Iterates over eatch pixel in a row, solving for is RGB then pushing into the row (queue).
		for (int j = 0; j < screen.getHeight(); j++)
		{
			Pixel pix(iter, j);

			pix.iterations(screen, frac);

			queue.emplace_back(std::move(pix));

			std::this_thread::sleep_for(std::chrono::milliseconds(1)); //reduce cpu usage
		}
		
		// Initate the lock to safely write to the Map.
		std::lock_guard<std::mutex> ulck(_mutex);

		_pixelQueue[iter] = std::move(queue);
		_con.notify_one();
	}


private:
	
	std::map<int,std::deque<Pixel>> _pixelQueue; // Using a Map to contain each row and its row number.
	std::condition_variable _con;
	std::mutex _mutex;
};


#endif