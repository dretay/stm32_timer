#include "../src/Timer.h"
#include "gpio.h"
#include "unity.h"
#include <stdbool.h>
#include <string.h>

//test helper fns
extern u32 HAL_TICK;
int TIMER_CALLBACK_COUNT;
void TEST_Advance_Systick(u32 loop_ms)
{
    for (int i = 0; i < loop_ms; i++) {
        HAL_TICK++;
        Timer.tick();
    }
}
void timer_callback_fn(void)
{

    TIMER_CALLBACK_COUNT++;
}

void setUp(void)
{
  Timer.init();
  TIMER_CALLBACK_COUNT = 0;
}

void tearDown(void)
{
}

void test_timer_instantiate_every(void)
{
  int test_interval = 50;
  int result = Timer.every(test_interval,timer_callback_fn);
  TEST_ASSERT_GREATER_THAN(-1,result);
  TEST_Advance_Systick(test_interval + 1);
  TEST_ASSERT_EQUAL_INT(1,TIMER_CALLBACK_COUNT);
}
void test_timer_instantiate_in(void)
{
  int test_interval = 50;
  int result = Timer.in(test_interval,timer_callback_fn);
  TEST_ASSERT_GREATER_THAN(-1,result);
  TEST_Advance_Systick(test_interval + 1);
  TEST_ASSERT_EQUAL_INT(1,TIMER_CALLBACK_COUNT);
  TEST_Advance_Systick(test_interval + 1);
  TEST_ASSERT_EQUAL_INT(1,TIMER_CALLBACK_COUNT);
}
void test_cant_instantiate_in(void)
{
  int test_interval = 50;
  for(int i=0;i<MAX_TIMERS;i++){
    int result = Timer.in(test_interval,timer_callback_fn);
    TEST_ASSERT_GREATER_THAN(-1,result);
  }
  int result = Timer.in(test_interval,timer_callback_fn);
  TEST_ASSERT_EQUAL_INT(-1,result);
}
void test_cant_instantiate_every(void)
{
  int test_interval = 50;
  for(int i=0;i<MAX_TIMERS;i++){
    int result = Timer.every(test_interval,timer_callback_fn);
    TEST_ASSERT_GREATER_THAN(-1,result);
  }
  int result = Timer.every(test_interval,timer_callback_fn);
  TEST_ASSERT_EQUAL_INT(-1,result);
}
void test_timer_in_reset_invalid(void)
{
  int test_interval = 50;
  int result = Timer.in(test_interval,timer_callback_fn);
  TEST_ASSERT_GREATER_THAN(-1,result);
  TEST_Advance_Systick(test_interval -1);
  bool reset_result = Timer.reset(result+1);
  TEST_ASSERT_FALSE(reset_result);
}
void test_timer_in_cancel_invalid(void)
{
  int test_interval = 50;
  int result = Timer.in(test_interval,timer_callback_fn);
  TEST_ASSERT_GREATER_THAN(-1,result);
  TEST_Advance_Systick(test_interval -1);
  bool cancel_result = Timer.cancel(result+1);
  TEST_ASSERT_FALSE(cancel_result);
}
void test_timer_in_reset(void)
{
  int test_interval = 50;
  int result = Timer.in(test_interval,timer_callback_fn);
  TEST_ASSERT_GREATER_THAN(-1,result);
  TEST_Advance_Systick(test_interval -1);
  bool reset_result =Timer.reset(result);
  TEST_ASSERT_TRUE(reset_result);
  TEST_Advance_Systick(2);
  TEST_ASSERT_EQUAL_INT(0,TIMER_CALLBACK_COUNT);
  TEST_Advance_Systick(test_interval + 1);
  TEST_ASSERT_EQUAL_INT(1,TIMER_CALLBACK_COUNT);
}
void test_timer_in_cancel(void)
{
  int test_interval = 50;
  int result = Timer.in(test_interval,timer_callback_fn);
  TEST_ASSERT_GREATER_THAN(-1,result);
  TEST_Advance_Systick(test_interval -1);
  bool cancel_result =Timer.cancel(result);
  TEST_ASSERT_TRUE(cancel_result);
  TEST_Advance_Systick(2);
  TEST_ASSERT_EQUAL_INT(0,TIMER_CALLBACK_COUNT);
  TEST_Advance_Systick(test_interval + 1);
  TEST_ASSERT_EQUAL_INT(0,TIMER_CALLBACK_COUNT);
}