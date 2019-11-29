#ifndef LEDMATRIX_H
#define LEDMATRIX_H

#include <cstdint>

class Pixel;

class LedMatrix
{
public:
   static const int MAX_X;
   static const int MAX_Y;
   static const int MIN_X;
   static const int MIN_Y;

   LedMatrix();
   ~LedMatrix();
   void clear();
   void clear(const Pixel& pixel);
   void invert();
   int setPixel(uint8_t x, uint8_t y, const Pixel& pixel);
   Pixel getPixel(uint8_t x, uint8_t y) const;
private:

};

#endif
