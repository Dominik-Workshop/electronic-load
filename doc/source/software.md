## Microcontroller Firmware

The firmware is written for the ATmega328P. It handles:

- Reading analog values (voltage, current, temperature)
- Controlling DAC for setting current levels
- User interaction through encoder, keypad, and LCD
- Switching between multiple operation modes
- Communication with PC via USB-UART (CH340)

## Operating Modes

1. **Constant Current** – Maintains fixed current regardless of input voltage.
2. **Constant Power** – Adjusts current dynamically to maintain fixed power.
3. **Constant Resistance** – Simulates a fixed resistance load.
4. **Step Response** – Alternates between two current values to test power supply response.
5. **Battery Test** – Discharges a battery until a cutoff voltage and calculates capacity.

## PC Application

![PC app](img/desktop-app-battery-discharge.png)

Written in C++ with Qt, the application allows:

- Starting/stopping the load
- Setting current and cutoff voltage
- Monitoring voltage, current, and battery capacity
- Saving graphs as JPG or CSV
- Multi-language UI: English, Polish, German

Communication with the load is via USB using a serial port.
