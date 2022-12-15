#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Encoder.h>

#include "StateContext.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
Encoder encoder{2, 3};
StateContext context{lcd, 25, 0.5};

volatile bool clicked = false;
ISR (PCINT2_vect) {
    clicked = digitalRead(7);
}

long last_value = -999;
enum class RotationDirection {
    None,
    Clockwise,
    Counterclockwise
};

RotationDirection GetRotation() {
    auto const current_reading = encoder.read();
    if (current_reading == last_value)
        return RotationDirection::None;

    auto ret = current_reading > last_value ? RotationDirection::Clockwise : RotationDirection::Counterclockwise;
    last_value = current_reading;
    delay(10);
    return ret;
}

void setup() {
    pinMode(0, INPUT_PULLUP);
    pinMode(1, INPUT_PULLUP);
    pinMode(5, INPUT_PULLUP);
    pinMode(6, INPUT_PULLUP);
    pinMode(8, INPUT_PULLUP);
    pinMode(9, INPUT_PULLUP);
    pinMode(10, INPUT_PULLUP);
    pinMode(13, INPUT_PULLUP);

    lcd.init();
    lcd.backlight();
    Serial.begin(9600);

    pinMode(7, INPUT);
    *digitalPinToPCMSK(7) |= bit (digitalPinToPCMSKbit(7));  // enable pin
    PCIFR |= bit (digitalPinToPCICRbit(7)); // clear any outstanding interrupt
    PCICR |= bit (digitalPinToPCICRbit(7)); // enable interrupt for the group

    delay(1000);
}

void loop() {
    auto const rot = GetRotation();

    if (clicked) {
        noInterrupts();
        context.handleClick();
        clicked = false;
        interrupts();
    } else if (rot == RotationDirection::Counterclockwise) {
        context.handleLeft();
    } else if (rot == RotationDirection::Clockwise) {
        context.handleRight();
    } else {
        context.run();
    }
    delay(200);
}
