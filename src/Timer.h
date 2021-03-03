#pragma once
#include "stdbool.h"
#include "types_shortcuts.h"
#include <string.h>

#ifdef TEST
#include <stdio.h>

#include "gpio.h"
#include "hal.h"
#else
#include "UartLogger.h"
#include "stm32f1xx_hal.h"
#endif

#define MAX_TIMERS 10
enum timer_types {
  empty_timer_type,
  in_timer_type, // in X units of time
  every_timer_type, // every X units of time
};
struct timer_entry {
  enum timer_types timer_type;
  void (*callback)(void);
  u32 duration;
  u32 start;
};
struct timer {
  void (*init)(void);
  void (*tick)(void);
  int (*in)(u32 time, void(*callback));
  int (*every)(u32 time, void(*callback));
  bool (*cancel)(int timer);
  bool (*reset)(int timer);
};

extern const struct timer Timer;