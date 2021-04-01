#include "RandomWalk.h"
#define UNUSED(x) (void)(x)

std::mutex RandomWalk::mtx_;

RandomWalk::RandomWalk(LedMatrix& leds,
                       const Pixel& pixel,
                       int walkStepSeconds):

   rdev_{},
   reng_{rdev_()},
   uniformRandom_{-1, 1},
   leds_{},
   x_{4},
   y_{4},
   pixel_{pixel},
   pl_{std::bind(&RandomWalk::randomWalk, this), walkStepSeconds}
{
   UNUSED(leds);
}

void RandomWalk::randomWalk()
{
   int xPrevious_ = x_;
   int yPrevious_ = y_;

   std::lock_guard<std::mutex> lgLeds(mtx_);
   do
   {
      x_ = std::min(std::max(LedMatrix::MIN_X, x_ + uniformRandom_(reng_)),
                    LedMatrix::MAX_X);
      y_ = std::min(std::max(LedMatrix::MIN_Y, y_ + uniformRandom_(reng_)),
                    LedMatrix::MAX_Y);
   } while (leds_.getPixel(x_, y_) != Pixel::BLANK);

   leds_.setPixel(xPrevious_, yPrevious_, Pixel::BLANK);
   leds_.setPixel(x_, y_, pixel_);
}
