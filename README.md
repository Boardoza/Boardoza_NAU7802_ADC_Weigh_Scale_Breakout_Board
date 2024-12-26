# Boardoza NAU7802 24-bit ADC Breakout Board
The NAU7802 24-bit Dual-Channel ADC Breakout Board is designed for high-precision weight and pressure measurements. At its core is the NAU7802, a highly integrated analog-to-digital converter with an onboard low-noise amplifier, making it perfect for load cell applications. The board supports I2C communication and provides two differential input channels, enabling precise data acquisition in projects requiring accurate sensor readings, such as digital scales and pressure monitoring systems.

### [Click here to purchase!](https://www.ozdisan.com/maker-and-iot-products/boardoza/boardoza-modules/BOARDOZA-NAU7802/1206517)


|Front Side|Back Side|
|:---:|:---:|
| ![NAU7802 Front](./assets/NAU7802%20Front.png)| ![NAU7802 Back](./assets/NAU7802%20Back.png)|

---
## Key Features
- 24-bit ADC resolution for high-precision measurements.
- Dual differential input channels for flexible sensor integration.
- Low noise performance for stable and reliable readings.
- Selectable data output rates for high-speed or high-accuracy operation.
- Simple I<sup>2</sup>C interface for easy connection with MCUs.
---

## Technical Specifications
**Input Voltage:**	2.7V or 5.5V

**Supply Current** 2mA

**Functions:**	24-Bit Dual-Channel ADC For Bridge Sensors

**ADC Resolution:** 24-bit  

**Interface:** I<sup>2</sup>C

**Channel** 2 Input Channel

**Operating Temperature:**	-40°C ~ +85°C

**Board Dimensions:**	20mm x 40mm

---

## Board Pinout

| J1 Pin Number | Pin Name | Description |
| :---: | --- | --- |
| 1 | WHT | - Signal |
| 2 | GRN | + Signal |
| 3 | BLK | - Excitation |
| 4 | RED | + Excitation |

| J2 Pin Number | Pin Name | Description |
| :---: | --- | --- |
| 1 | GND | Negative Power Supply |
| 2 | SDA | I2C Serial Data |
| 3 | SCL | I2C Serial Clock Input |
| 4 | 3.3V | Positive Power Supply |

| J3 Pin Number | Pin Name | Description |
| :---: | --- | --- |
| 1 | VDDA | Analog Power Supply |
| 2 | INT | Interrupt Pin |
| 3 | GND | Negative Power Supply

| J4 Pin Number | Pin Name | Description |
| :---: | --- | --- |
| 1 | GRN | + Signal |
| 2 | WHT | - Signal |
| 3 | BLK | - Excitation |
| 4 | RED | + Excitation |

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
- If you have any questions or need support, please contact support@boardoza.com

---
## License

Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a [Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
