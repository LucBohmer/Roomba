#include "Pixel.h"
#include "LedMatrixDevice.h"

bool operator==(const Pixel& lhs, const Pixel& rhs)
{
   return (lhs.r_ == rhs.r_) and (lhs.g_ == rhs.g_) and (lhs.b_ == rhs.b_); 
}

bool operator!=(const Pixel& lhs, const Pixel& rhs)
{
   return not (lhs == rhs);
}

const Pixel Pixel::RED{255, 0, 0};
const Pixel Pixel::GREEN{0, 255, 0};
const Pixel Pixel::BLUE{0, 0, 255};
const Pixel Pixel::WHITE{255, 255, 255};
const Pixel Pixel::GREY{128, 128, 128};
const Pixel Pixel::BLANK{0, 0, 0};

Pixel::Pixel():
   Pixel(0, 0, 0)
{}

Pixel::Pixel(uint8_t r, uint8_t g, uint8_t b):
   r_{r},
   g_{g},
   b_{b}
{}

uint8_t Pixel::operator[](const RGB& c) const
{
   switch (c) {
      case RGB::R:
         return r_;
      case RGB::G:
         return g_;
   }
   return b_;
}

uint8_t& Pixel::operator[](const RGB& c)
{
   switch (c) {
      case RGB::R:
         return r_;
      case RGB::G:
         return g_;
   }
   return b_;
}

uint16_t Pixel::packed() const
{
   uint16_t r16 = (r_ >> 3) & 0x1F;
	uint16_t g16 = (g_ >> 2) & 0x3F;
	uint16_t b16 = (b_ >> 3) & 0x1F;
	return (r16 << 11) + (g16 << 5) + b16;
}

void Pixel::invert()
{
   r_ = ~r_;
   g_ = ~g_;
   b_ = ~b_;
}
