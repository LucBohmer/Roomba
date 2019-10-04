#include "InterfaceConfig.h"

// Command data
std::vector<uint8_t> startSafe()
{
   return {START, MODE_SAFE};
}

/// Velocities in mm/sec
std::vector<uint8_t> driveDirect(int16_t rightVelocity, int16_t leftVelocity)
{
   return {DRIVE_DIRECT_4,
           static_cast<uint8_t>(rightVelocity >> 8),
           static_cast<uint8_t>(rightVelocity & 0x00ff),
           static_cast<uint8_t>(leftVelocity >> 8),
           static_cast<uint8_t>(leftVelocity & 0x00ff)
   };
}