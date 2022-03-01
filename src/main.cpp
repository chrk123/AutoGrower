#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

int clamp(int val, int min, int max) {
    return val < min ? min
                     : val > max ? max : val;
}

float normalize(int val, int min, int max) {
    val = clamp(val, min, max);
    return (val - min) / static_cast<float>(max - min);
}

class Relay {
public:
    explicit Relay(uint8_t digital_out) : m_Pin{digital_out} {
        pinMode(m_Pin, OUTPUT);
    }

    void on() const {
        digitalWrite(m_Pin, HIGH);
    }

    void off() const {
        digitalWrite(m_Pin, LOW);
    }

private:
    uint8_t m_Pin;
};

class TemperatureSensor {
public:
    explicit TemperatureSensor(uint8_t digital_in) : m_Wire{digital_in}, m_Sensors{&m_Wire} {
        m_Sensors.begin();
    }

    float read() {
        m_Sensors.requestTemperatures();
        return m_Sensors.getTempCByIndex(0);
    }

private:
    OneWire m_Wire;
    DallasTemperature m_Sensors;
};

class MoistureSensor {
public:
    explicit MoistureSensor(uint8_t analog_in) : m_AnalogIn(analog_in) {

    }

    float read() const {
        return 1 - normalize(analogRead(m_AnalogIn), m_ReadingInWater, m_ReadingInAir);
    }

private:
    uint8_t m_AnalogIn;
    int m_ReadingInAir{827};
    int m_ReadingInWater{423};
};

LiquidCrystal_I2C lcd(0x27, 16, 2);

MoistureSensor moistureSensor{0};
TemperatureSensor tempSensor{4};

Relay pump{13};
Relay heat{12};

void setup() {
    lcd.init();
    lcd.backlight();
    Serial.begin(9600);
}

void loop() {
    lcd.clear();

    auto const temperature = tempSensor.read();
    lcd.setCursor(0, 0);
    lcd.print("temp: ");
    lcd.print(temperature);
    lcd.print(static_cast<char>(223));
    lcd.print("C");


    auto const moisture = moistureSensor.read();
    lcd.setCursor(0, 1);
    lcd.print("moisture: ");
    lcd.print(moisture * 100);
    lcd.print("%");

    if (temperature < 25) {
        heat.on();
    } else {
        heat.off();
    }

    if (moisture < 0.25) {
        pump.on();
    } else {
        pump.off();
    }

    delay(2000);
}
