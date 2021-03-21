/*!
 * @file
 * @brief
 */

#ifndef SystemTick_hpp
#define SystemTick_hpp

#include "tiny/ITimeSource.h"

extern "C" {
#include "system_tick.h"
}

class SystemTick : public tiny::ITimeSource {
 public:
  SystemTick()
    : time_source(system_tick_init())
  {
  }

 public:
  auto virtual ticks() -> TickCount
  {
    return tiny_time_source_ticks(time_source);
  }

 private:
  i_tiny_time_source_t* time_source;
};

#endif
