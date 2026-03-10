# ATSAMD21-Light-Activated-GPIO-System
This project demonstrates the use of Direct Register Manipulation to interface an ATSAMD21E18A  with an analog sensor circuit. By utilizing a voltage divider and internal pull-up resistors, the system creates a digital light-level threshold to control an LED.
### Technical Features
- **Direct GPIO Register Control:** Manually configured `DIRSET` (Direct Set), `DIRCLR` (Direct Clear), `OUTSET` (Output Set), and `OUTCLR` (Output Clear) registers to manage I/O directions and logic states.
- **Hardware Threshold Detection:** Used a Photoresistor (LDR) in a voltage-divider configuration to create a high/low digital signal at the input pin based on light levels.
- **Internal Pull-up Configuration:** Programmed the `PINCFG` (Pin Configuration) register to enable internal pull-up resistors and input buffers (`INEN`), ensuring stable readings and preventing signal "floating".
- **Polling Loop Implementation:** Implemented a continuous monitoring loop in `main.c` that reads the `IN` (Input Data) register and provides real-time LED response to light level changes.
### Hardware
- **Microcontroller:** ATSAMD21E18A
- **Programmer:** MPLAB Snap In-Circuit Programmer/Debugger
- **Signal Conditioning:** 10kΩ Resistor (Voltage Divider)
- **Sensor:** Photoresistor (LDR)
- **Output:** LED with a 220Ω current-limiting resistor
## Software
- **IDE:** MPLAB X IDE
- **Compiler:** XC32 Compiler
## Challenge & Solution
A major issue that I ran into is dealing with "floating" signals, where the pin can't decide if a signal is a definitive High or Low due to the noise. To resolve this problem, I implemented two layers of stability. First, a hardware 10kΩ pull-down resistor was used in the voltage divider. Second, I configured the ATSAMD21's internal Pull-Up Resistor via the `PINCFG` and `OUTSET` registers. By taking this approach, I ensured the input pin `PA05` provides a clean, bounce-free transition between light and dark states.
## Project Structure
- `main.c`: The source application code that includes the peripheral clock enabling and the polling logic.

