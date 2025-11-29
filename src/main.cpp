#include <Arduino.h>
#include <IRremote.hpp>
#include "Arduino_LED_Matrix.h"
#include "IRRemoteMap.h"   // you said you already use this mapping
#include "StepperController.h"
#include "RGBController.h"

// pins (keep your existing choices)
#define IR_PIN   2
#define R_PIN    6   // PWM
#define G_PIN    5   // PWM
#define B_PIN    3   // PWM

// stepper pins (ULN2003 IN1..IN4)
#define STP_IN1  8
#define STP_IN2  9
#define STP_IN3  10
#define STP_IN4  11

ArduinoLEDMatrix matrix;

// controllers
StepperController stepper(STP_IN1, STP_IN2, STP_IN3, STP_IN4);
RGBController rgb(R_PIN, G_PIN, B_PIN);

// steps per revolution: most modules: 4096 (half-step), but you can change if needed
const uint32_t STEPS_PER_REV = 4096;

void showTextOnMatrix(const String &text) {
  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  matrix.textScrollSpeed(50);
  matrix.textFont(Font_4x6);
  matrix.beginText(0, 1, 0xFFFFFFFF);
  matrix.print(text);
  matrix.endText(SCROLL_LEFT);
  matrix.endDraw();
}

void announce(const char *text) {
  Serial.println(text);
  showTextOnMatrix(String(text));
}

// map IR numeric buttons 1..6 to actions
void handleIRButton(IRButton btn) {
  switch(btn) {
    case IRButton::BTN_1: { // CCW slow
      rgb.setRed(); announce("CMD:1");
      stepper.rotate(StepperDir::CCW, STEPS_PER_REV/8, StepperSpeed::SLOW); // example: 1/8 revolution
      rgb.setGreen(); announce("DONE");
    } break;
    case IRButton::BTN_2: { // CCW normal
      rgb.setRed(); announce("CMD:2");
      stepper.rotate(StepperDir::CCW, STEPS_PER_REV/4, StepperSpeed::NORMAL);
      rgb.setGreen(); announce("DONE");
    } break;
    case IRButton::BTN_3: { // CCW fast
      rgb.setRed(); announce("CMD:3");
      stepper.rotate(StepperDir::CCW, STEPS_PER_REV/2, StepperSpeed::FAST);
      rgb.setGreen(); announce("DONE");
    } break;
    case IRButton::BTN_4: { // CW slow
      rgb.setRed(); announce("CMD:4");
      stepper.rotate(StepperDir::CW, STEPS_PER_REV/8, StepperSpeed::SLOW);
      rgb.setGreen(); announce("DONE");
    } break;
    case IRButton::BTN_5: { // CW normal
      rgb.setRed(); announce("CMD:5");
      stepper.rotate(StepperDir::CW, STEPS_PER_REV/4, StepperSpeed::NORMAL);
      rgb.setGreen(); announce("DONE");
    } break;
    case IRButton::BTN_6: { // CW fast
      rgb.setRed(); announce("CMD:6");
      stepper.rotate(StepperDir::CW, STEPS_PER_REV/2, StepperSpeed::FAST);
      rgb.setGreen(); announce("DONE");
    } break;
    default:
      // ignore others for now
      Serial.println("Ignored button");
      break;
  }
}

void setup() {
  Serial.begin(9600);
  delay(50);

  // begin matrix
  if (matrix.begin()) {
    Serial.println("Matrix init OK");
  } else {
    Serial.println("Matrix not present or init failed");
  }

  // begin controllers
  rgb.begin();
  rgb.setColor(255,0,0);
  rgb.setOn(true);       // red while not ready
  showTextOnMatrix("WAIT");

  stepper.begin();
  stepper.setStepsPerRevolution(STEPS_PER_REV); // configure

  // IR
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("IR Receiver ready.");

  // quick hardware test: small move to detect if everything is connected (mostly visual)
  Serial.println("Stepper test...");
  stepper.testMotor();
  delay(200);

  // if test succeeded (visual), set green & RDY
  rgb.setGreen();
  showTextOnMatrix("RDY");
}

void loop() {
  if (!IrReceiver.decode()) return;
  uint32_t raw = IrReceiver.decodedIRData.decodedRawData;
  IRButton btn = IRRemoteMap::getButton(raw);
  const char *name = IRRemoteMap::toString(btn);
  Serial.print("BTN: "); Serial.println(name);

  handleIRButton(btn);

  IrReceiver.resume();
  delay(120);
}
