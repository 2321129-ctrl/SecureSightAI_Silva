# SecureSight AI: An Agentic AI-Driven Distance-Based Threat Detection and Alarm Monitoring System

**SILVA, GWEN M.**  
**CPE 3B**  

* **SecureSight AI** is an intelligent, hardware-integrated security monitoring system that bridges physical sensors with Local Large Language Models (LLMs) via LM Studio. Instead of relying on static, hardcoded threshold rules, this project utilizes a local AI Agent to reason through physical distance tracking and context to classify proximity threat levels. The system provides immediate updates on an I2C LCD screen while outputting dynamic multi-stage physical responses using color-coded LEDs and an audio buzzer to prevent unauthorized intrusions.

---

## Key Features

* **Smart Proximity Tracking:** Using an Ultrasonic Sensor.
* **AI-Driven Threat Classification:** Leverages a local LLM (via the LM Studio API) to intelligently assess whether an object's proximity constitutes a `SAFE`, `WARNING`, or `ALERT` status.
* **Precision Distance Tracking:** Employs an ultrasonic sensor for real-time physical distance tracking. Continuously tracks physical distance updates dynamically, feeding real-time positional data directly to the local AI agent.
* **Visual Alerts:** Outputs dynamic physical responses based on the proximity status.
  * **Green LED:** Safe state (No immediate threat).
  * **Blue LED:** Warning state (Object approaching/Caution).
  * **Red LED + Piezo Buzzer:** Active Alert state (Critical proximity breach).
* **Live Status Display:** Outputs live distance data and real-time AI status assessments directly onto a 16×2 I2C LCD Screen for localized monitoring.

---

## Project Hardware Components

To build the physical deployment loop, the following hardware components are required:

* **Arduino Microcontroller:** Primary hardware processing unit.
* **HC-SR04 Ultrasonic Sensor:** Handles real-time distance tracking data collection.
* **SG90 Servo Motor:** Acts as an automatic physical lock or gate. It stays open (0°) when the system is `SAFE`, moves to a cautionary position when a `WARNING` is active, and immediately swings closed (90° or 180°) to block access whenever an `ALERT` is triggered.
* **16×2 I2C LCD Display:** Local text status output for immediate user visibility.
* **3x LEDs:** Color-coded status indicators (Green, Blue, Red).
* **3x Resistors (220Ω):** Current-limiting protection to prevent LED burnout.
* **Piezo Buzzer:** Frequency-driven acoustic indicator for active alarm states.
* **Breadboard & Jumper Wires:** Used for clean structural prototyping and component connections.

---

## Software Setup 

### Integrated Development Environments (IDEs)

* **Arduino IDE:** Used for writing, compiling, and flashing the low-level C++ firmware directly onto the microcontroller. 
* **VS Code (Visual Studio Code):** Used as the primary environment for managing the Python-based AI agent script, running the serial communication bridge, and handling project configuration files.

### Microcontroller Libraries
The following libraries must be installed within the Arduino IDE environment:
* `Wire.h` (Built-in library utilized for core I2C communications)
* `LiquidCrystal_I2C.h` (Handles text formatting and writing data to the 16x2 LCD screen over the I2C bus)
* `Servo.h` (Built-in library utilized for controlling the position of the SG90 Servo Motor)

### Python Packages
The communication bridge requires Python 3.x. Install the necessary ecosystem dependencies using pip:

```bash
pip install openai pyserial requests

```

---

## Local LLM Configuration (LM Studio)

* **Hosting Platform:** **LM Studio** acts as the local inference engine, spinning up an offline, OpenAI-compatible HTTP server hosted locally at `http://127.0.0.1:1234`.
* **Target Model:** `qwen/qwen3-1.7b` — A highly optimized, lightweight 1.7-billion parameter language model. It is perfect for local edge computing because it runs fluidly on standard consumer hardware while strictly adhering to structured system prompt instructions.

```

```
