#ifndef NAU7802_h
#define NAU7802_h

#include <Arduino.h>
#include <Wire.h>

#define NAU7802_DEFAULT_ADDR 0x2A
#define NAU7802_PU_CTRL 0x00
#define NAU7802_CTRL1 0x01
#define NAU7802_CTRL2 0x02
#define NAU7802_ADCO_B2 0x12
#define NAU7802_ADC 0x15
#define NAU7802_PGA 0x1B
#define NAU7802_POWER 0x1C
#define NAU7802_REVISION_ID 0x1F

typedef enum {
    NAU7802_4v5 = 0b000,
    NAU7802_4v2 = 0b001,
    NAU7802_3v9 = 0b010,
    NAU7802_3v6 = 0b011,
    NAU7802_3v3 = 0b100,
    NAU7802_3v0 = 0b101,
    NAU7802_2v7 = 0b110,
    NAU7802_2v4 = 0b111,
} LdoVoltages;

typedef enum  {
    GAIN_1 = 0b000,
    GAIN_2 = 0b001,
    GAIN_4 = 0b010,
    GAIN_8 = 0b011,
    GAIN_16 = 0b100,
    GAIN_32 = 0b101,
    GAIN_64 = 0b110,
    GAIN_128 = 0b111,
} Gain;

typedef enum {
    RATE_10SPS = 0b000,
    RATE_20SPS = 0b001,
    RATE_40SPS = 0b010,
    RATE_80SPS = 0b011,
    RATE_320SPS = 0b111,
} SampleRate;

typedef enum {
    CHANNEL1 = 0,
    CHANNEL2 = 1,
} Channels;

// PU_CTRL register
typedef enum {
    PU_CTRL_RR = 0,
    PU_CTRL_PUD = 1,
    PU_CTRL_PUA = 2,
    PU_CTRL_PUR = 3,
    PU_CTRL_CS = 4,
    PU_CTRL_CR = 5,
    PU_CTRL_OSCS = 6,
    PU_CTRL_AVDDS = 7,
} PU_CTRL_Bits;

// CTRL1 registers
typedef enum {
    CTRL1_GAIN = 2,
    CTRL1_VLDO = 5,
    CTRL1_DRDY_SEL = 6,
    CTR1_CRP = 7,
} CTRL1_Bits;

// CTRL2 Registers
typedef enum {
    CTRL2_CALMOD = 0,
    CTRL2_CALS = 2,
    CTRL2_CAL_ERR = 3,
    CTRL2_CRS = 4,
    CTRL2_CHS = 7,
} CTRL2_Bits;

// PGA registers
typedef enum {
    PGA_CHP_DIS = 0,
    PGA_INV = 3,
    PGA_BYPASS_ENABLE = 4,
    PGA_OUT_BUF_EN = 5,
    PGA_LDO_MODE = 6,
    PGA_RD_OTP_SEL = 7,
} PGA_Bits;

// Calibration mode
typedef enum {
    CALMODE_INTERNAL = 0,
    CALMODE_OFFSET = 2,
    CALMODE_GAIN = 3,
} CalibrationMode;

class NAU7802 {
  public:
    NAU7802();
    bool begin();
    void reset();
    bool isAvailable();
    bool powerUp();
    bool powerDown();
    bool calibrate();
    int32_t readADCValue();
    void channelSelect(Channels channel);
    float readVoltage();
    float readWeight(float calibrationFactor);
    void setCalibration();
    void tare(byte times);
    int32_t setOffset(int32_t tempADCValue);
    void setGain(Gain gain);
    void setSampleRate(SampleRate rate);
    void setChannel(Channels channel);
    void setLdoVoltage(LdoVoltages voltage);
    void calibTest();
  private:
    uint8_t readRegister(uint8_t reg);
    void writeRegister(uint8_t reg, uint8_t value);
    uint32_t read24(uint8_t reg);
    void setBit(uint8_t reg, uint8_t bit);
    void clearBit(uint8_t reg, uint8_t bit);
    bool readBit(uint8_t reg, uint8_t bit);
    void readUntilTrue(uint8_t reg, uint8_t bit);
    void readUntilFalse(uint8_t reg, uint8_t bit);
    float _calibrationFactor;
    int32_t _offset;
};

#endif