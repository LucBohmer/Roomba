#include "LedMatrix.h"
#include "Pixel.h"

#include "LedMatrixDevice.h"

const int LedMatrix::MAX_X{7};
const int LedMatrix::MAX_Y{7};
const int LedMatrix::MIN_X{0};
const int LedMatrix::MIN_Y{0};

LedMatrix::LedMatrix()
{
   ::init_fb();
}

LedMatrix::~LedMatrix()
{
   ::blank();
}

void LedMatrix::clear()
{
   ::blank();
}

void LedMatrix::clear(const Pixel& pixel)
{
   ::clear(pixel[Pixel::RGB::R], pixel[Pixel::RGB::G], pixel[Pixel::RGB::B]);
}

void LedMatrix::invert()
{
   ::invert();
}

int LedMatrix::setPixel(uint8_t x, uint8_t y, const Pixel& pixel)
{
   return set_pixel(x, y,
      pixel[Pixel::RGB::R],
      pixel[Pixel::RGB::G],
      pixel[Pixel::RGB::B]);
}

Pixel LedMatrix::getPixel(uint8_t x, uint8_t y) const
{
   uint8_t r;
   uint8_t g;
   uint8_t b;
   get_pixel(x, y, &r, &g, &b);

   return Pixel{r, g, b};
}
