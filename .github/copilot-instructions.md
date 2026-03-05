# Copilot Instructions

## Project Overview

Spy Bot is an Arduino-based surveillance robot that hosts an embedded HTTP web server for real-time motor control and IP camera viewing from any browser on the local network. The Arduino Ethernet Shield serves an HTML control panel with directional buttons that drive four GPIO-connected motor outputs, while an embedded iframe streams live MJPEG video from a networked IP camera with pan/tilt CGI control.

> **Status: Discontinued** — This project was archived in September 2018 and is preserved as a historical reference. No new features or bug fixes are planned.

## Repository Structure

```
spy-bot/
├── main.ino              # Arduino sketch: Ethernet server setup, HTTP request parsing,
│                         #   GPIO motor control, and inline HTML page generation
├── files/
│   ├── index.html        # Standalone HTML control panel prototype (SecurityBot v1.0)
│   │                     #   with camera pan/tilt and robot movement controls
│   ├── testehtml.html    # Test page for hold-to-click button behavior
│   └── hold.js           # JavaScript library implementing long-press detection
│                         #   with configurable delay (300ms) and event prevention
├── README.md             # Project documentation
├── CONTRIBUTING.md       # Historical build information and discontinued status notice
└── LICENSE               # Project license
```

## Technology Stack

| Component | Technology |
|-----------|------------|
| Language | Arduino C++ (`.ino` sketch) |
| Platform | Arduino (ATmega-based) with Ethernet Shield (W5100, SPI) |
| Networking | HTTP/1.1 web server on port 80 with static IP |
| Motor driver | H-bridge (L298N or similar) via 4 digital GPIO pins (4, 5, 6, 7) |
| Camera | IP camera with CGI control interface and MJPEG streaming |
| Client interface | Inline HTML/CSS/JavaScript generated and served by the Arduino |

**Arduino Libraries:**
- `<SPI.h>` — Serial Peripheral Interface (required by Ethernet Shield)
- `<Ethernet.h>` — Arduino Ethernet library (W5100 driver)

## Architecture

### Network Architecture

```
[Browser] --HTTP--> [Arduino @ 192.168.1.101:80] --GPIO--> [H-Bridge] --> [DC Motors]
                                |
                                +--iframe/CGI--> [IP Camera @ 192.168.1.200:81] --> [MJPEG Stream]
```

### HTTP Request Parsing

The Arduino reads incoming requests character by character, buffering from the `G` character (start of `GET`). Every 10 characters it checks the buffer for query parameter patterns (`?go=E/D/F/T/O`) and activates the corresponding motor pins. This avoids heap allocation on the constrained microcontroller.

### Motor Control (Differential Drive)

Two DC motors are controlled through four digital pins using an H-bridge:

| Command | Query param | Pins HIGH |
|---------|-------------|-----------|
| Forward | `?go=F` | 7, 5 |
| Backward | `?go=T` | 4, 6 |
| Left | `?go=E` | 7, 4 |
| Right | `?go=D` | 6, 5 |
| Off | `?go=O` | none (all LOW) |

### Camera Pan/Tilt Control

Pan/tilt commands are sent directly from the browser to the IP camera via CGI links (`decoder_control.cgi`) targeting a hidden `null` iframe, so the main page does not reload.

## Build and Deployment

There is no automated build system, CI/CD pipeline, or test suite — this is an embedded firmware project.

### Hardware Requirements

- Arduino board (Uno, Mega, or compatible)
- Arduino Ethernet Shield (W5100-based)
- H-bridge motor driver (L298N or similar)
- Two DC motors with appropriate power supply
- IP camera with CGI control support (optional, for video stream)

### Software Setup

1. Install the [Arduino IDE](https://www.arduino.cc/en/software)
2. Open `main.ino` in the Arduino IDE
3. Update the static IP address (`192.168.1.101`) to match your network
4. Update the camera IP address (`192.168.1.200`) to match your camera
5. Update the MAC address (`0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED`) if needed to avoid conflicts
6. Upload the sketch to the Arduino board via USB
7. Open a browser and navigate to `http://<arduino-ip>`

## Coding Conventions

- **Arduino paradigm** — `setup()` runs once on power-on; `loop()` runs continuously
- **GPIO pin references** — direct integer literals (4, 5, 6, 7) for motor control pins
- **Variable naming** — camelCase with descriptive names (`currentLineIsBlank`, `left`, `right`, `front`, `back`)
- **Network configuration** — hardcoded MAC address and static IP (no DHCP)
- **HTML generation** — string-based via `client.println()` to minimize heap use on constrained hardware
- **JavaScript** — inline event handlers (`onmousedown`, `ontouchstart`) mixed into HTML output; no external dependencies
- **Memory efficiency** — avoid `String` concatenation in hot paths; prefer character-level parsing

## Common Tasks

### Change the Arduino's IP Address

Edit line 12 of `main.ino`:
```cpp
IPAddress ip(192, 168, 1, 101); // change to desired address
```

### Change the Camera IP Address

Search `main.ino` for `192.168.1.200` and replace with your camera's IP.

### Add a New Motor Direction

1. Define a new query parameter value in the HTTP parsing block (around line 57)
2. Add the corresponding `digitalWrite` calls in the motor control block (around line 67)

### Modify the Hold-to-Click Delay

Edit the delay value in `files/hold.js` (default: 300 ms).
