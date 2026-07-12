# Interrupt-Driven Automatic Visitor Counting System

An embedded system that automatically counts the number of people entering and exiting a room using a pair of IR sensors, hardware interrupts, and a microcontroller. The system is "interrupt-driven," meaning the microcontroller stays idle and only reacts when a sensor detects a visitor — instead of continuously polling the sensors — making it faster to respond and more power-efficient.



## Features

- Real-time visitor counting using interrupt service routines (ISRs)
- Bidirectional detection (distinguishes entry vs. exit using two IR sensors)
- Live count displayed on an LCD (e.g. 16x2)
- Low power consumption — MCU stays in idle/sleep state until a sensor triggers an interrupt
- Optional automatic light/relay control based on occupancy (ON when count > 0, OFF when room is empty)

## How It Works

1. Two IR transmitter-receiver pairs are placed a short distance apart at the entrance/exit.
2. When a visitor breaks the IR beam, the receiver's output triggers a hardware interrupt on the microcontroller.
3. The order in which the two sensors are triggered determines direction:
   - Sensor 1 → Sensor 2 triggered in sequence = **entry** (count incremented)
   - Sensor 2 → Sensor 1 triggered in sequence = **exit** (count decremented)
4. The ISR updates a global counter variable and returns control to the main program.
5. The current count is displayed on the LCD in real time.

## Hardware Requirements

| Component | Notes |
|---|---|
| Microcontroller | *(e.g. Arduino Uno / 8051 — update to match your board)* |
| IR Sensor Modules x2 | Transmitter + receiver pair, placed at entry/exit |
| 16x2 LCD Display | Displays live visitor count |
| Relay Module (optional) | For automatic light control |
| Resistors, jumper wires, breadboard/PCB | Supporting components |
| Power Supply | 5V regulated supply |

## Pin Configuration

*(Update this table with your actual wiring)*

| MCU Pin | Connected To |
|---|---|
| INT0 | IR Sensor 1 output |
| INT1 | IR Sensor 2 output |
| Digital Pins | LCD (RS, EN, D4–D7) |
| Digital Pin | Relay IN (optional) |

## Software / Requirements

- *(e.g. Arduino IDE 1.8+ or Keil uVision for 8051)*
- Required libraries: *(e.g. `LiquidCrystal.h`)*

## Getting Started

```bash
git clone https://github.com/venkatesanappu1986-byte/Interrupt-Driven-Automatic-Visitor-Counting-System.git
cd Interrupt-Driven-Automatic-Visitor-Counting-System
```

1. Open the source file in your IDE (Arduino IDE / Keil / etc.)
2. Connect the hardware as per the pin configuration above
3. Compile and upload/flash the code to your microcontroller
4. Power on the circuit — the LCD should initialize and show a count of 0
5. Walk through the sensor pair to test entry/exit counting

## Applications

- Seminar halls, conference rooms, classrooms
- Shopping malls, temples, offices
- Occupancy-based automatic lighting control
- Crowd/capacity monitoring for restricted-capacity venues

## Future Improvements

- IoT connectivity for remote/cloud monitoring
- Data logging with timestamps
- Buzzer/alert when capacity limit is exceeded

## License

*(Add your license here, e.g. MIT)*

## Author

*(Your name / GitHub handle)*
