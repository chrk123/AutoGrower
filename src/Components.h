#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

enum class TurnDirection {
    Clockwise,
    Counterclockwise,
    None
};

class RotaryEncoder {
public:
    explicit RotaryEncoder(uint8_t clk, uint8_t dt) : m_CLK(clk), m_DT(dt), m_LastValueCLK(digitalRead(m_CLK)) {
        pinMode (m_CLK, INPUT);
        pinMode (m_DT, INPUT);

        digitalWrite(m_CLK, true);
        digitalWrite(m_DT, true);
    }

    TurnDirection GetDirection() {
        auto const current_value_CLK = digitalRead(m_CLK);
        auto const current_value_DT = digitalRead(m_DT);

        if (m_LastValueCLK == current_value_CLK)
            return TurnDirection::None;

        m_LastValueCLK = current_value_CLK;
        return current_value_DT != current_value_CLK ? TurnDirection::Clockwise : TurnDirection::Counterclockwise;
    }

private:
    uint8_t m_CLK;
    uint8_t m_DT;
    int m_LastValueCLK;
};

class Relay {
public:
    explicit Relay(uint8_t digital_out);

    void on() const;

    void off() const;

private:
    uint8_t m_Pin;
};

class TemperatureSensor {
public:
    explicit TemperatureSensor(uint8_t digital_in);

    float read();

private:
    OneWire m_Wire;
    DallasTemperature m_Sensors;
};

class MoistureSensor {
public:
    explicit MoistureSensor(uint8_t analog_in);

    float read() const;

private:
    uint8_t m_AnalogIn;
    int m_ReadingInAir{827};
    int m_ReadingInWater{423};
};

#endif