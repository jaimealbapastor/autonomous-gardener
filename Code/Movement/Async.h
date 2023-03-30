#ifndef ASYNC_H
#define ASYNC_H

#include <stdint.h>
#include <Arduino.h>

class Task
{
public:
  uint32_t interval;
  uint32_t last_chrono;
  uint32_t function;

  bool can_be_destroyed;
  Task *next;

  Task(uint8_t id, unsigned int last_chrono);
  ~Task();
};

class Async
{
private:
  static Task *first_task;
  static uint8_t last_id;

public:
  static void check();
  static void add();
  static void end();
};

#endif