#pragma once

#include "Servo.h"
#include "Config.hpp"

namespace Servos {
    Servo servoA;
    Servo servoB;

    void attach() {
        servoA.attach(SERVO_A_PIN);
        servoB.attach(SERVO_B_PIN);

        servoA.writeMicroseconds(SERVO_A_STOP);
        servoB.writeMicroseconds(SERVO_B_STOP);
    }
    void start() {
        servoA.write(0);
        servoB.write(3000);
    }
    void stop() {
        servoA.write(SERVO_A_STOP);
        servoB.write(SERVO_B_STOP);
    }
};
