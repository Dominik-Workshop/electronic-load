# DC Electronic Load

## 🎥 Introduction

Watch a full project overview on [YouTube](https://youtu.be/NScaRQj53l0).

This open-source programmable **DC electronic load** is designed to test power supplies, batteries, and other DC sources. It simulates a variety of load conditions to evaluate performance and reliability.

The design was inspired by several community projects, especially [Scullcom’s Electronic DC Load](https://www.youtube.com/watch?v=9fsf1CgnTRk).

## ⚙️ Key Features

- Supports up to **50 V** and **8 A** input
- Power dissipation: **200 W** continuous / **300 W** peak
- **Five operating modes**: constant current, power, resistance, step load, battery test
- **Remote voltage sensing**
- **User-friendly interface**: rotary encoder + numeric keypad
- **PC application** for real-time monitoring, control, and data logging
- **Fully open-source**: hardware, firmware, and software

## 🛠️ Tools Used

<table style="width: 100%; border-collapse: collapse;">
  <thead>
    <tr style="border-bottom: 2px solid #ccc;">
      <th style="text-align: left; padding: 8px;">Tool</th>
      <th style="text-align: left; padding: 8px;">Usage</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="padding: 8px;"><strong>Autodesk Eagle</strong></td>
      <td style="padding: 8px;">Schematic and PCB design</td>
    </tr>
    <tr>
      <td style="padding: 8px;"><strong>Fusion 360</strong></td>
      <td style="padding: 8px;">3D modeling for the enclosure and front panel</td>
    </tr>
    <tr>
      <td style="padding: 8px;"><strong>PlatformIO + VS Code</strong></td>
      <td style="padding: 8px;">Firmware development and microcontroller programming</td>
    </tr>
    <tr>
      <td style="padding: 8px;"><strong>Qt (C++ with Qt)</strong></td>
      <td style="padding: 8px;">Desktop application for monitoring and control</td>
    </tr>
  </tbody>
</table>