#include "Components.h"

#include <Arduino.h>

int clamp(int val, int min, int max) {
    return val < min ? min
                     : val > max ? max : val;
}

float normalize(int val, int min, int max) {
    val = clamp(val, min, max);
    return (val - min) / static_cast<float>(max - min);
}

Relay::Relay(uint8_t digital_out) : m_Pin{digital_out} {
    pinMode(m_Pin, OUTPUT);
    digitalWrite(m_Pin, LOW);
}

void Relay::on() const {
    digitalWrite(m_Pin, HIGH);
}

void Relay::off() const {
    digitalWrite(m_Pin, LOW);
}

TemperatureSensor::TemperatureSensor(uint8_t digital_in) : m_Wire{digital_in}, m_Sensors{&m_Wire} {
m_Sensors.begin();
}

float TemperatureSensor::read() {
    m_Sensors.requestTemperatures();
    return m_Sensors.getTempCByIndex(0);
}

MoistureSensor::MoistureSensor(uint8_t analog_in) : m_AnalogIn(analog_in) {
}

float MoistureSensor::read() const {
    Serial.println(analogRead(m_AnalogIn));
    return 1 - normalize(analogRead(m_AnalogIn), m_ReadingInWater, m_ReadingInAir);
}