#ifndef RANDOMWALK_H
#define RANDOMWALK_H

#include "LedMatrix.h"
#include "ParLoop.h"
#include "Pixel.h"

#include <algorithm>
#include <functional>
#include <random>

class RandomWalk
{
public:
   RandomWalk(LedMatrix& leds):
      rdev_{},
      reng_{rdev_()},
      uniformRandom_{-1, 1},
      leds_{},
      x_{1},
      y_{2},
      xPrevious_{1},
      yPrevious_{2},
      pixelPrevious_{leds_.getPixel(x_, y_)},
      pl_{std::bind(&RandomWalk::randomWalk, this), 1}
   {}
   void randomWalk()
   {
      leds_.setPixel(xPrevious_, yPrevious_, pixelPrevious_);
      x_ = std::min(std::max(LedMatrix::MIN_X, x_ + uniformRandom_(reng_)),
                    LedMatrix::MAX_X);
      y_ = std::min(std::max(LedMatrix::MIN_Y, y_ + uniformRandom_(reng_)),
                    LedMatrix::MAX_Y);
      pixelPrevious_ = leds_.getPixel(x_, y_);
      xPrevious_ = x_;
      yPrevious_ = y_;
      leds_.setPixel(x_, y_, Pixel(30, 190, 100));
   }
private:
   std::random_device rdev_;
   std::default_random_engine reng_;
   std::uniform_int_distribution<int> uniformRandom_;
   LedMatrix leds_;
   int x_;
   int y_;
   int xPrevious_;
   int yPrevious_;
   Pixel pixelPrevious_;
   ParLoop pl_;
};

#endif
