#include <Arduino.h>

//Button Pins 
const int left = 12;
const int up = 11;
const int right = 10;
const int down = 9;

//Buzzer Pin
const int buzzer = 8;

//Buttton Delay
unsigned long bounceDelay = 300;
unsigned long prevTime = 0;

//Simon Says Patterns
int simonSays[10]; 

//Led Colors
enum Colors {
    YELLOW = 5,
    GREEN = 4,
    RED = 3,
    BLUE = 2
};
Colors allColors[4] = {YELLOW, GREEN, RED, BLUE};

//Random Color Choice
int simonChoice = random(0,4);


//Led Hold Time
unsigned long prevLedTime = 0;
const unsigned long universalLedTime = 300;



class Led {
    private:
    int state;
    Colors color;
    unsigned long ledPrevTime;

    public:
    Led(Colors color) {
        state = LOW;
        this->color = color;
        ledPrevTime = 0;
    }
    void turnOn() {
        state = HIGH;
        digitalWrite(this->color, state);
    }
    void turnOff() {
        state = LOW;
        digitalWrite(this->color, state);
    }
    int ledState() {
        return state;
    }
    unsigned long lastTime() {
        return ledPrevTime;
    }
    void updateLastTime() {
        ledPrevTime = millis();
    }
};


//Led Objects
Led Yellow(YELLOW);
Led Red(RED);
Led Blue(BLUE);
Led Green(GREEN);





    void normalFeedback(int buttonState, Led& led) {
        if (buttonState == LOW && millis() - led.lastTime() >= bounceDelay) {
            Serial.println("left button pressed");
            led.turnOn();
            led.updateLastTime();
            tone(buzzer, 262, 100);
            prevTime = millis();
        }

        if (led.ledState() == HIGH && millis() - led.lastTime() >= universalLedTime) {
            led.turnOff();
        }    
    };




void setup() {
    Serial.begin(9600);

    pinMode(buzzer, OUTPUT);

    pinMode(YELLOW, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(RED, OUTPUT);
    pinMode(BLUE, OUTPUT);

    pinMode(left, INPUT_PULLUP);
    pinMode(up, INPUT_PULLUP);
    pinMode(right, INPUT_PULLUP);
    pinMode(down, INPUT_PULLUP);
}

void loop() {
    int YellowState = digitalRead(YELLOW);
    int GreenState = digitalRead(GREEN);
    int RedState = digitalRead(RED);
    int BlueState = digitalRead(BLUE);

    int leftState = digitalRead(left);
    int upState = digitalRead(up);
    int rightState = digitalRead(right);
    int downState = digitalRead(down);


    normalFeedback(leftState, Yellow);
    normalFeedback(upState, Red);
    normalFeedback(rightState, Blue);
    normalFeedback(downState, Green);


    }