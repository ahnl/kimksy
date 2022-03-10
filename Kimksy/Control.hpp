#pragma once

#include "Servo.h"
#include "Config.hpp"

namespace Control {
    namespace Servos {
        Servo servoA;
        Servo servoB;

        void attach() {
            servoA.attach(SERVO_A_PIN);
            servoB.attach(SERVO_B_PIN);

            servoA.writeMicroseconds(SERVO_A_STOP);
            servoB.writeMicroseconds(SERVO_B_STOP);
        }
        void start(bool reverse = false) {
            if (reverse) {
                servoB.write(0);
                servoA.write(3000);
            } else {
                servoA.write(0);
                servoB.write(3000);
            }
        }
        void stop() {
            servoA.write(SERVO_A_STOP);
            servoB.write(SERVO_B_STOP);
        }
    }  

    enum ShredderState {
        STANDBY, SHREDDING, HALTING
    };
    ShredderState state = STANDBY;

    long startTime; 
    long beepTime;

    void setState(ShredderState newState) {
        startTime = millis();
        state = newState;
    }
    void shred() {
        Servos::start();  
        setState(SHREDDING);
    }
    void reverse() {
        Servos::start(true);  
        setState(SHREDDING);
    }
    void halt() {
        Servos::stop();
        setState(HALTING);
        tone(BUZZER_PIN, 500, HALT_TIME);
    } 
    void loop() {
        // Timers and sounds
        if (state == SHREDDING) {
            if (millis() - startTime > SHRED_TIME) {
                Servos::stop();
                setState(STANDBY);
            }
            if (millis() - beepTime > BEEP_INTERVAL) {
                beepTime = millis();
                tone(BUZZER_PIN, 500, BEEP_INTERVAL / 2);
            }
        } else if (state == HALTING) {
            if (millis() - startTime > HALT_TIME) {
                setState(STANDBY);
            }
        }
    }
    void init() {
        Servos::attach();
        pinMode(BUZZER_PIN, OUTPUT);
    }
}