#pragma once
#include <Arduino.h>

enum class StepperSpeed { SLOW, NORMAL, FAST };
enum class StepperDir { CW, CCW };

class StepperController {
public:
  StepperController(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4);
  void begin();
  // do a small test motion, return true if loop executed (can't truly detect missing motor)
  void testMotor();
  // rotate for `steps` half-steps in the given direction at a given speed
  void rotate(StepperDir dir, uint32_t steps, StepperSpeed speed);
  // convenience: rotate approximately n revolutions (uses stepsPerRevolution)
  void rotateRevolutions(StepperDir dir, float revolutions, StepperSpeed speed);

  // configure resolution (defaults to 4096 half-steps per revolution)
  void setStepsPerRevolution(uint32_t sprev);

private:
  uint8_t pins[4];
  uint32_t stepsPerRevolution = 4096; // default half-step resolution for typical 28BYJ-48
  void stepOnce(uint8_t stepIndex);
  uint8_t seqIndex = 0;
};
