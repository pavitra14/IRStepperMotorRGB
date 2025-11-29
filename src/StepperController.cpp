#include "StepperController.h"

// Half-step sequence (8-step): IN1,IN2,IN3,IN4 pattern
static const uint8_t HALFSTEP_SEQ[8][4] = {
  {1,0,0,0},
  {1,1,0,0},
  {0,1,0,0},
  {0,1,1,0},
  {0,0,1,0},
  {0,0,1,1},
  {0,0,0,1},
  {1,0,0,1}
};

StepperController::StepperController(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4) {
  pins[0] = in1; pins[1] = in2; pins[2] = in3; pins[3] = in4;
}

void StepperController::begin() {
  for (int i=0;i<4;i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
  }
  seqIndex = 0;
}

void StepperController::setStepsPerRevolution(uint32_t sprev){
  stepsPerRevolution = sprev;
}

void StepperController::stepOnce(uint8_t stepIndex){
  for (int i=0;i<4;i++) {
    digitalWrite(pins[i], HALFSTEP_SEQ[stepIndex & 0x07][i] ? HIGH : LOW);
  }
}

void StepperController::rotate(StepperDir dir, uint32_t steps, StepperSpeed speed){
  // map speeds to delay per half-step (ms)
  uint16_t delayMs;
  switch (speed) {
    case StepperSpeed::SLOW:   delayMs = 8;  break;
    case StepperSpeed::NORMAL: delayMs = 4;  break;
    case StepperSpeed::FAST:   delayMs = 2;  break;
    default: delayMs = 4;
  }

  for (uint32_t s=0; s<steps; ++s){
    if (dir == StepperDir::CW) {
      seqIndex = (seqIndex + 1) & 0x07;
    } else {
      seqIndex = (seqIndex + 7) & 0x07; // -1 mod 8
    }
    stepOnce(seqIndex);
    delay(delayMs);
  }
  // after move, turn coils off to reduce heat (optional)
  for (int i=0;i<4;i++) digitalWrite(pins[i], LOW);
}

void StepperController::rotateRevolutions(StepperDir dir, float revolutions, StepperSpeed speed){
  uint32_t steps = (uint32_t)(revolutions * (float)stepsPerRevolution);
  rotate(dir, steps, speed);
}

void StepperController::testMotor(){
  // small forward/backward sweep to validate wiring
  rotate(StepperDir::CW, 50, StepperSpeed::NORMAL);
  delay(80);
  rotate(StepperDir::CCW, 50, StepperSpeed::NORMAL);
}
