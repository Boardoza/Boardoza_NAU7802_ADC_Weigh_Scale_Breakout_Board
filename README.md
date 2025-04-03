# Boardoza NAU7802 24-bit Dual-Channel ADC Breakout Board

The **Boardoza NAU7802** is a high-resolution, dual-channel **24-bit analog-to-digital converter breakout board** specifically designed for **weight, pressure, and load cell sensor applications**. It integrates the **NAU7802 ADC** from Nuvoton, known for its **low-noise performance**, **dual differential input channels**, and compact design.

This board is ideal for use in **digital scales**, **pressure transducers**, and any system where **precise analog signal acquisition** is essential. With **I²C communication**, it easily interfaces with microcontrollers and embedded systems, enabling flexible and fast integration.

## [Click here to purchase!](https://www.ozdisan.com/maker-and-iot-products/boardoza/boardoza-modules/BOARDOZA-NAU7802/1206517)

|Front Side|Back Side|
|:---:|:---:|
| ![NAU7802 Front](./assets/NAU7802%20Front.png)| ![NAU7802 Back](./assets/NAU7802%20Back.png)|

---

## Key Features

- **24-bit ADC Resolution:** Delivers high-accuracy digital conversion for precise sensor readings.
- **Dual Differential Inputs:** Supports two full differential sensor channels, ideal for load cells.
- **Integrated Low-Noise Amplifier:** Ensures signal integrity and stable readings in noisy environments.
- **Selectable Output Rates:** Allows trade-off between measurement speed and precision.
- **Simple I²C Interface:** Enables easy integration with a wide range of microcontrollers.

---

## Technical Specifications

**Model:** Nuvoton NAU7802  
**Input Voltage:** 2.7V – 5.5V  
**Supply Current:** 2mA  
**Functions:** 24-bit ADC for bridge sensor applications  
**ADC Resolution:** 24-bit  
**Channels:** 2 Differential Input Channels  
**Interface:** I²C  
**Operating Temperature:** -40°C ~ +85°C  
**Board Dimensions:** 20mm x 40mm  

---

## Board Pinout

### ( J1 ) Sensor Channel 1

| Pin Number | Pin Name | Description     |
|:----------:|----------|-----------------|
| 1          | WHT      | - Signal         |
| 2          | GRN      | + Signal         |
| 3          | BLK      | - Excitation     |
| 4          | RED      | + Excitation     |

### ( J2 ) Power & I²C Communication

| Pin Number | Pin Name | Description         |
|:----------:|----------|---------------------|
| 1          | GND      | Ground              |
| 2          | SDA      | I²C Serial Data     |
| 3          | SCL      | I²C Serial Clock    |
| 4          | 3.3V     | Positive Power Supply |

### ( J3 ) Advanced Functionality

| Pin Number | Pin Name | Description           |
|:----------:|----------|-----------------------|
| 1          | VDDA     | Analog Power Supply   |
| 2          | INT      | Interrupt Output Pin  |
| 3          | GND      | Ground                |

### ( J4 ) Sensor Channel 2

| Pin Number | Pin Name | Description     |
|:----------:|----------|-----------------|
| 1          | GRN      | + Signal         |
| 2          | WHT      | - Signal         |
| 3          | BLK      | - Excitation     |
| 4          | RED      | + Excitation     |

---

## Board Dimensions

<img src="./assets/NAU7802 Dimensions.png" alt="NAU7802 Dimension" width="450"/>

---

## Step Files

[Boardoza NAU7802.step](./assets/Boardoza%20NAU7802.step)

---

## Datasheet

[Boardoza NAU7802 Datasheet.pdf](./assets/NAU7802%20Data%20Sheet%20V1.7.pdf)

---

## Version History

- V1.0.0 - Initial Release

---

## Support

- If you have any questions or need support, please contact <support@boardoza.com>

---

## License

Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a [Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
