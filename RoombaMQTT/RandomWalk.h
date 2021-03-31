#ifndef RANDOMWALK_H
#define RANDOMWALK_H

#include "LedMatrix.h"
#include "ParLoop.h"
#include "Pixel.h"

/// @todo Remove unused include files in the interface.
#include <algorithm>
#include <functional>
#include <mutex>
#include <random>

/// Active class, uses ParLoop class for executing the random walk of one pixel
/// on the SenseHAT device #leds_. The function #randomWalk is thread safe,
/// using a shared mutex object #mtx_.
class RandomWalk
{
public:
   RandomWalk(LedMatrix& leds, const Pixel& pixel, int walkStepSeconds);
   RandomWalk(const RandomWalk& other) = delete;
   RandomWalk& operator=(const RandomWalk& other) = delete;
   void randomWalk();

private:
   static std::mutex mtx_;

   std::random_device rdev_;
   std::default_random_engine reng_;
   std::uniform_int_distribution<int> uniformRandom_;
   LedMatrix leds_;
   int x_;
   int y_;
   Pixel pixel_;
   ParLoop pl_;
};

#endif
