# ESP32 Basic Series - Small Mimic Panel Node

This **ESP32 node** is part of the Basic Series and is designed for small mimic panels in model railway layouts. It offers intuitive route control via buttons or network events, drives up to 8 turnouts with staggered timing, and provides 16 LED outputs for clear panel indications.

---

## Features

- **5 Route Selection Inputs** – Can be triggered by momentary push buttons or consumed events from another node
- **8 Turnout Outputs** – Supports staggered delays between events for realistic operation
- **16 LED Output Channels** – Perfect for mimic panel indicators (route status, turnout position, track occupancy, etc.)
- **CAN Bus Communication** – Uses the standard **SN65HVD230** transceiver module (fully compatible with other Basic Series nodes)

---

## Pin Configuration

| Function              | ESP32 GPIO Pins                          | Notes |
|-----------------------|------------------------------------------|-------|
| **Route Inputs**      | `4`, `16`, `17`, `5`, `18`              | Momentary push buttons or consumed events |
| **Outputs**           | `19, 21, 22, 23, 13, 12, 14, 27, 26, 25, 33, 32` | Turnouts + LED indicators |
| **CAN RX**            | `15`                                     | SN65HVD230 |
| **CAN TX**            | `2`                                      | SN65HVD230 |

> **Total Outputs:** 12 GPIO pins supporting 8 turnout controls + 16 LED channels (via firmware logic).

---

## Hardware

- **Microcontroller:** ESP32 Devkit 1 30 pin
- **CAN Transceiver:** SN65HVD230 (standard across Basic Series)
- **Input Type:** Momentary push buttons (active low recommended)
- **Output Type:** Suitable for LEDs

---

**This node is ideal for small mimic panels** where space is limited but reliable route control and clear visual feedback are essential.

<img width="900" height="400" alt="Timeline 1_00_00_10_05" src="https://github.com/user-attachments/assets/0fafe5b9-bcdd-449e-8213-5ffa69af6f23" />


---

