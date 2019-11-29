#ifndef PIXEL_H
#define PIXEL_H

#include <cstdint>

class Pixel
{
   friend bool operator==(const Pixel& lhs, const Pixel& rhs);
   friend bool operator!=(const Pixel& lhs, const Pixel& rhs);
   
public:
   enum class RGB {R, G, B};

   static const Pixel RED;
   static const Pixel GREEN;
   static const Pixel BLUE;
   static const Pixel WHITE;
   static const Pixel GREY;
   static const Pixel BLANK;

   Pixel();
   Pixel(uint8_t r, uint8_t g, uint8_t b);
   Pixel(const Pixel& other) = default;
   Pixel& operator=(const Pixel& other) = default;
   ~Pixel() = default;

   uint8_t operator[](const RGB& c) const;
   uint8_t& operator[](const RGB& c);
   uint16_t packed() const;
   void invert();

private:
   uint8_t r_;
   uint8_t g_;
   uint8_t b_;
};

#endif
