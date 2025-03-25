#include <NAU7802.h>

int32_t offSetValue = 0;

NAU7802::NAU7802() {}

/**
 * @brief Initializes the NAU7802 module.
 * 
 * This function initializes the NAU7802 module by beginning communication with Wire, setting the sample rate to 10SPS,
 * setting the gain to 128, setting the LDO voltage, configuring the ADC and power registers, and powering up the module.
 * 
 * @return True if the initialization is successful, otherwise false.
 */
bool NAU7802::begin() {

    Wire.begin();
    setSampleRate(RATE_10SPS);
    setGain(GAIN_128);
    setLdoVoltage(NAU7802_3v0);
    setBit(0x15, 4); //ADC register
    setBit(0x15, 5); //ADC register
    //setBit(0x1B, 6); //PGA register
    setBit(0x1C, 7); //PWR register

    powerUp();

    return true;
}

/**
 * @brief Checks if the NAU7802 module is available for communication.
 * 
 * This function checks if the NAU7802 module is available for communication by beginning a transmission with the default address
 * and checking if the end of the transmission is successful.
 * 
 * @return True if the module is available for communication, otherwise false.
 */
bool NAU7802::isAvailable() {
    Wire.beginTransmission(NAU7802_DEFAULT_ADDR);
    return Wire.endTransmission() == 0;
}

/**
 * @brief Resets the NAU7802 module.
 * 
 * This function resets the NAU7802 module by setting the reset bit in the power-up control register, delaying for 10 milliseconds,
 * and then clearing the reset bit.
 */
void NAU7802::reset() {
    setBit(NAU7802_PU_CTRL, PU_CTRL_RR);
    delay(10);
    return (clearBit(NAU7802_PU_CTRL, PU_CTRL_RR));
}

/**
 * @brief Powers up the NAU7802 module.
 * 
 * This function powers up the NAU7802 module by setting the power-up and power-up analog bits in the power-up control register,
 * waiting for the power-up ready bit to be set, setting the chip select bit, and returning true if the module is successfully powered up.
 * 
 * @return True if the module is successfully powered up, false if the operation times out.
 */
bool NAU7802::powerUp() {
    setBit(NAU7802_PU_CTRL, PU_CTRL_PUD);
    setBit(NAU7802_PU_CTRL, PU_CTRL_PUA);

    uint8_t counter = 0;
    while(1) {
        if(readBit(NAU7802_PU_CTRL, PU_CTRL_PUR)) {
        break;
        }
        delay(10);
        if(counter++ > 100) {
        return false;
        }
    }
    setBit(NAU7802_PU_CTRL, PU_CTRL_CS);

    return true;
}

/**
 * @brief Powers down the NAU7802 module.
 * 
 * This function powers down the NAU7802 module by clearing the power-up and power-up analog bits in the power-up control register.
 * 
 * @return True if the module is successfully powered down.
 */
bool NAU7802::powerDown() {
    clearBit(NAU7802_PU_CTRL, PU_CTRL_PUD);
    clearBit(NAU7802_PU_CTRL, PU_CTRL_PUA);
}

/**
 * @brief Performs calibration on the NAU7802 module.
 * 
 * This function initiates the calibration process by setting the calibration start bit in the control register,
 * waits for the calibration to finish, and checks for any calibration errors.
 * 
 * @return True if calibration is successful and there are no calibration errors, false otherwise.
 */
bool NAU7802::calibrate() {
    setBit(NAU7802_CTRL2, CTRL2_CALS); // Begin calibration
    readUntilFalse(NAU7802_CTRL2, CTRL2_CALS); // Wait for calibration to finish
    return !readBit(NAU7802_CTRL2, CTRL2_CAL_ERR); // Check for calibration error
}

/**
 * @brief Reads the ADC value from the NAU7802 module.
 * 
 * This function waits until the conversion is ready by checking the conversion ready bit in the power-up control register,
 * reads the ADC value from the specified register, and returns the ADC value as a signed 32-bit integer.
 * 
 * @return The ADC value read from the NAU7802 module as a signed 32-bit integer.
 */
int32_t NAU7802::readADCValue() {
    readUntilTrue(NAU7802_PU_CTRL, PU_CTRL_CR);
    uint32_t adcValue = read24(NAU7802_ADCO_B2);
    return (int32_t)adcValue;
}

/**
 * @brief Selects the channel on the NAU7802 module.
 * 
 * This function selects the specified channel on the NAU7802 module by setting or clearing the channel select bit in the control register.
 * It then performs calibration to ensure accurate readings for the selected channel.
 * 
 * @param channel The channel to be selected (CHANNEL1 or CHANNEL2).
 */
void NAU7802::channelSelect(Channels channel) {
    if(channel == CHANNEL1) {
        clearBit(NAU7802_CTRL2, 7); // Channel 1 selected
    }else if(channel == CHANNEL2) {
        setBit(NAU7802_CTRL2, 7); // Channel 2 selected
    }
    calibrate();
}

/**
 * @brief Reads the voltage value from the NAU7802 module.
 * 
 * This function reads the raw ADC value from the module, and then calculates and returns the voltage value represented by the ADC reading.
 * The reference voltage, gain setting, and full scale range of the ADC are used in the calculation.
 * 
 * @return The voltage value read from the NAU7802 module in float format.
 */
float NAU7802::readVoltage() {
    // Read the raw ADC value
    int32_t rawADCValue = readADCValue();

    // The reference voltage used for the NAU7802
    float referenceVoltage = 3.3;

    // The gain setting used for the NAU7802
    float gain = 128.0;

    // The full scale range of the ADC
    int32_t fullScaleRange = 8388608; // 2^23

    // Calculate the voltage
    float voltage = (rawADCValue * referenceVoltage) / (gain * fullScaleRange);
    
    return voltage;
}

/**
 * @brief Sets the calibration mode for the NAU7802 module.
 * 
 * This function sets the calibration start bit, calibration mode bit, and additional calibration mode bit in the control register
 * to enable calibration mode for the NAU7802 module.
 */
void NAU7802::setCalibration() {
    setBit(NAU7802_CTRL2, CTRL2_CALS);
    setBit(NAU7802_CTRL2, CTRL2_CALMOD);
    setBit(NAU7802_CTRL2, CTRL2_CALMOD + 1);
}

/**
 * @brief Performs tare operation on the NAU7802 module.
 * 
 * This function reads the ADC value multiple times with a delay interval, calculates the average, and sets the offset value
 * to compensate for any drift or initial measurement bias. The calculated offset value is stored in the 'offSetValue' variable.
 * 
 * @param times The number of times to read ADC value for tare calculation.
 */
void NAU7802::tare(byte times) {
    long sum = 0;

    for(byte i = 0; i < times; ++i) {
        sum += readADCValue();
        delay(100);
    }
    offSetValue = (sum / times);
    Serial.print(offSetValue);
        Serial.print("  ");
    Serial.print(sum);
        Serial.println("  ");
}

/**
 * @brief Sets the offset value for calibration in the NAU7802 module.
 * 
 * This function takes a temporary ADC value as input, prints the temporary ADC value and the current offset value to Serial,
 * and calculates the corrected ADC value by subtracting the offset value. The calculated corrected value is returned.
 * 
 * @param tempADCValue The temporary ADC value to be used for offset correction.
 * @return The corrected ADC value after applying the offset correction.
 */
int32_t NAU7802::setOffset(int32_t tempADCValue) {
    Serial.print(tempADCValue);
    Serial.print("  "); 
    Serial.print(offSetValue);
    Serial.print("  ");
    return (tempADCValue - offSetValue);
}

/**
 * @brief Sets the gain value for the NAU7802 sensor.
 * 
 * This function sets the gain value for the NAU7802 sensor to the specified value.
 * 
 * @param gain The gain value to be set for the sensor (enum type).
 */
void NAU7802::setGain(Gain gain) {
    uint8_t value = readRegister(NAU7802_CTRL1);
    value &= 0b11111000; // Clear gain bits
    value |= gain; // Set new gain bits
    writeRegister(NAU7802_CTRL1, value);
}

/**
 * @brief Sets the sample rate for the NAU7802 sensor.
 * 
 * This function sets the sample rate for the NAU7802 sensor to the specified value.
 * 
 * @param rate The sample rate value to be set for the sensor (enum type).
 */
void NAU7802::setSampleRate(SampleRate rate) {
    uint8_t value = readRegister(NAU7802_CTRL2);
    value &= 0b10001111; // Clear sample rate bits
    value |= rate << 4; // Set new sample rate bits
    writeRegister(NAU7802_CTRL2, value);
}

/**
 * @brief Sets the LDO voltage for the NAU7802 sensor.
 * 
 * This function sets the LDO voltage for the NAU7802 sensor to the specified value.
 * 
 * @param voltage The LDO voltage value to be set for the sensor (enum type).
 */
void NAU7802::setLdoVoltage(LdoVoltages voltage) {
    uint8_t ldoValue = voltage;

    uint8_t value = readRegister(NAU7802_CTRL1);
    value &= 0b11000111; // Clear LDO bits
    value |= ldoValue << 3; // Mask in new LDO bits
    writeRegister(NAU7802_CTRL1, value);

    setBit(NAU7802_PU_CTRL, PU_CTRL_AVDDS);
}

/**
 * @brief Sets the channel for the NAU7802 sensor.
 * 
 * This function sets the channel for the NAU7802 sensor to the specified value.
 * 
 * @param channel The channel to be set for the sensor (enum type).
 */
void NAU7802::setChannel(Channels channel) {
    channelSelect(channel);
}

/**
 * @brief Reads a register value from the NAU7802 sensor.
 * 
 * This function reads the value of a specific register from the NAU7802 sensor.
 * 
 * @param reg The register address to read from.
 * @return The value read from the specified register.
 */
uint8_t NAU7802::readRegister(uint8_t reg) {
    Wire.beginTransmission(NAU7802_DEFAULT_ADDR);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(NAU7802_DEFAULT_ADDR, (uint8_t)1);
    return Wire.read();
}

/**
 * @brief Writes a value to a register in the NAU7802 sensor.
 * 
 * This function writes a value to a specific register in the NAU7802 sensor.
 * 
 * @param reg The register address to write to.
 * @param value The value to write to the register.
 */
void NAU7802::writeRegister(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(NAU7802_DEFAULT_ADDR);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

/**
 * @brief Reads a 24-bit value from the NAU7802 sensor.
 * 
 * This function reads a 24-bit value from the specified register address in the NAU7802 sensor.
 * 
 * @param reg The register address to read the 24-bit value from.
 * @return The 24-bit value read from the specified register address.
 */
uint32_t NAU7802::read24(uint8_t reg) {
    uint32_t value;
    Wire.beginTransmission(NAU7802_DEFAULT_ADDR);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom(NAU7802_DEFAULT_ADDR, (uint8_t)3);
    value = Wire.read(); // receive [16:23] byte
    value <<= 8;
    value |= Wire.read(); // receive [8:15] byte
    value <<= 8;
    value |= Wire.read(); // receive [0:7] byte
    if (value & 0x800000) {
    value |= 0xFF000000;
    }
    return value;
}

/**
 * @brief Sets a specific bit in a register of the NAU7802 sensor.
 * 
 * This function sets a specific bit in a register of the NAU7802 sensor.
 * 
 * @param reg The register address where the bit will be set.
 * @param bit The bit position to set (0-7).
 */
void NAU7802::setBit(uint8_t reg, uint8_t bit) {
    uint8_t value = readRegister(reg);
    value |= (0x01 << bit);
    writeRegister(reg, value);
}

/**
 * @brief Clears a specific bit in a register of the NAU7802 sensor.
 * 
 * This function clears a specific bit in a register of the NAU7802 sensor.
 * 
 * @param reg The register address where the bit will be cleared.
 * @param bit The bit position to clear (0-7).
 */
void NAU7802::clearBit(uint8_t reg, uint8_t bit) {
    uint8_t value = readRegister(reg);
    value &= ~(0x01 << bit);
    writeRegister(reg, value);
}

/**
 * @brief Reads the value of a specific bit in a register of the NAU7802 sensor.
 * 
 * This function reads the value of a specific bit in a register of the NAU7802 sensor.
 * 
 * @param reg The register address where the bit will be read.
 * @param bit The bit position to read (0-7).
 * @return True if the bit is set, false if the bit is clear.
 */
bool NAU7802::readBit(uint8_t reg, uint8_t bit) {
    uint8_t value = readRegister(reg);
    return (value & (1 << bit)) != 0;
}

/**
 * @brief Reads the register until a specific bit is set to true.
 * 
 * This function continuously reads the specified register until the specified bit is set to true.
 * 
 * @param reg The register address to read from.
 * @param bit The bit position to check (0-7).
 */
void NAU7802::readUntilTrue(uint8_t reg, uint8_t bit) {
    uint8_t bitmask = 1 << bit;
    bool readUntil = false;
    while (!readUntil) {
        int value = readRegister(NAU7802_PU_CTRL);
        
        if (readRegister(reg) & bitmask) {
            readUntil = true;
        }
    }
}

/**
 * @brief Reads the register until a specific bit is set to false.
 * 
 * This function continuously reads the specified register until the specified bit is set to false.
 * 
 * @param reg The register address to read from.
 * @param bit The bit position to check (0-7).
 */
void NAU7802::readUntilFalse(uint8_t reg, uint8_t bit) {
    uint8_t bitmask = 1 << bit;
    bool readUntil = false;
    while (!readUntil) {
        if (!(readRegister(reg) & bitmask)) {
            readUntil = true;
        }
    }
}

void NAU7802::calibTest() {
    setSampleRate(RATE_10SPS);
    setGain(GAIN_128);
    setLdoVoltage(NAU7802_3v0);
    setBit(0x15, 4); //ADC register
    setBit(0x15, 5); //ADC register
    //setBit(0x1B, 6); //PGA register
    setBit(0x1C, 7); //PWR register

    powerUp();
}