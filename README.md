# Smoke detector

Simple smoke detector that will beep in a pattern until a button is pressed (which will snooze it for 5 minutes) or timeout occurs.

The main usage idea is to detect cigarette smoke and alert the user to close the window manually when it happens.

It uses `Arduino Uno R3` as the logic board.

# Circuit

Electronics schematic can be viewed using `Autodesk Eagle` (open the `schematic.sch` file).

The rendered png file is available as `schematic.png` and visible below.

MQ2 smoke/gas detector with digital output adaptation is used as a sensor.
![Schematic](schematic.png?raw=true "Schematic")

# Logic

```mermaid
flowchart TD
    A[Start] --> B{Is smoke detected?}
    B -->|Yes| C[Buzz + blink]
    B -->|No| B
    C --> D{Was button pressed?}
    D -->|Yes| E[Quiet down]
    D -->|No| F[Have 5 seconds passed since detection?]
    F -->|Yes| E
    F -->|No| C
    E --> G[Sleep 5 minutes]
    G --> B
```

# Building

It uses the Arduino flavoured C++ under the hood and needs [arduino-cli](https://github.com/arduino/arduino-cli) to work.

Rust caused problems during compilation and I don't have time to fix these :/

Run `make` to build and `make install` to flash the binary to a device.
This requires the Arduino to be present as `/dev/ttyACM0`

# End notes

This project makes use of:

- [Adafruit-Eagle-Library](https://github.com/adafruit/Adafruit-Eagle-Library) for Arduino Uno R3
- [Eagle-Libraries](https://github.com/chiengineer/Eagle-Libraries) project for the buzzer schematic
- [Eagle-Libraries](https://github.com/chiengineer/Eagle-Libraries) project for the tactile switch schematic
