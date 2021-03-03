#include "Timer.h"

static struct timer_entry timer_entries[MAX_TIMERS];
static void init()
{
  for (int i = 0; i < MAX_TIMERS; i++) {
    timer_entries[i].timer_type = empty_timer_type;
  }
}
static void tick()
{
  int i = 0;
  u32 ticks = HAL_GetTick();
  for (i = 0; i < MAX_TIMERS; i++) {
    struct timer_entry *curr_timer = &timer_entries[i];
    if (curr_timer->timer_type != empty_timer_type) {
      if (ticks > (curr_timer->start + curr_timer->duration)) {
        if (curr_timer->callback != NULL) {
          if (curr_timer->timer_type == in_timer_type) {
            curr_timer->timer_type = empty_timer_type;
          }
          curr_timer->callback();
        }
        if (curr_timer->timer_type == every_timer_type) {
          curr_timer->start = HAL_GetTick();
        }
      }
    }
  }
}
static int get_free_timer_idx()
{
  int i;
  for (i = 0; i < MAX_TIMERS; i++) {
    if (timer_entries[i].timer_type == empty_timer_type) {
      return i;
    }
  }
  return -1;
}
static int add_timer(struct timer_entry timer_entry)
{
  int timer_idx = get_free_timer_idx();
  if (timer_idx < 0) {
    return -1;
  }
  timer_entries[timer_idx] = timer_entry;
  return timer_idx;
}
static int in(u32 time, void(*callback))
{
  return add_timer((struct timer_entry){
    .callback = callback,
    .timer_type = in_timer_type,
    .duration = time,
    .start = HAL_GetTick() });
}

static int every(u32 time, void(*callback))
{
  return add_timer((struct timer_entry){
    .callback = callback,
    .timer_type = every_timer_type,
    .duration = time,
    .start = HAL_GetTick() });
}
static bool cancel(int timer)
{
  if (timer >= 0 && timer<MAX_TIMERS) {
    if (timer_entries[timer].timer_type != empty_timer_type) {
      timer_entries[timer].timer_type = empty_timer_type;
      return true;
    }
  }
  return false;
}
static bool reset(int timer)
{
  if (timer >= 0 && timer<MAX_TIMERS) {
    struct timer_entry *curr_timer = &timer_entries[timer];
    if (curr_timer->timer_type != empty_timer_type) {
      curr_timer->start = HAL_GetTick();
      return true;
    }
  }
  return false;
}
const struct timer Timer = { .init = init,
           .tick = tick,
           .in = in,
           .every = every,
           .cancel = cancel,
           .reset = reset };
