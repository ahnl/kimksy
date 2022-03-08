#include <Servo.h>


class Servos {
    private:
        int aPin;
        int bPin;
        Servo servoA;
        Servo servoB;
    public:
        Servos(int a, int b) {
            aPin = a;
            bPin = b;

            servoA.attach(aPin);
            servoB.attach(bPin);

            servoA.writeMicroseconds(SERVO_A_STOP);
            servoB.writeMicroseconds(SERVO_B_STOP);
        }

};
