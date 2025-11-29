# IRStepperMotorRGB
> This readme is AI Generated
**IRStepperMotorRGB** is an Arduino project designed for the **Arduino Uno R4 WiFi** that provides comprehensive control over a stepper motor using an IR remote. It features real-time visual feedback using both an RGB LED and the Uno R4's built-in LED Matrix.

## 🚀 Features

*   **IR Remote Control**: Intuitive control using a standard IR remote (mapped via `IRRemoteMap`).
*   **Stepper Motor Control**:
    *   **Continuous Mode**: Run the motor continuously in CW or CCW directions.
    *   **Precise Control**: Execute specific fractional revolutions (1/8, 1/4, 1/2) with varying speeds using numeric keys.
*   **Visual Feedback**:
    *   **RGB LED**: Indicates system state (Green = Ready, Red = Busy/Command, Blinking Red/Blue = Siren Mode/Continuous Run).
    *   **LED Matrix**: Displays text status (e.g., "RDY", "LEFT", "RIGHT", "POS") and real-time position tracking (Steps & Revolutions).
*   **Safety**: Auto-stop timeout (10 minutes) for continuous running modes to prevent overheating or unwanted operation.

## 🛠️ Hardware Requirements

*   **Arduino Uno R4 WiFi**
*   **Stepper Motor**: 28BYJ-48 (5V) with ULN2003 Driver Board (Code configured for 4096 steps/rev).
*   **IR Receiver Module**: Generic VS1838B or compatible.
*   **RGB LED**: Common Cathode/Anode LED.

## 🔌 Pin Configuration

The pin assignments are defined in `src/main.cpp`:

| Component | Pin | Note |
| :--- | :--- | :--- |
| **IR Receiver** | `2` | |
| **RGB LED (Red)** | `6` | PWM |
| **RGB LED (Green)** | `5` | PWM |
| **RGB LED (Blue)** | `3` | PWM |
| **Stepper IN1** | `8` | |
| **Stepper IN2** | `9` | |
| **Stepper IN3** | `10` | |
| **Stepper IN4** | `11` | |

## 🎮 Controls

The project uses `IRRemoteMap` to map IR signals. Standard directional and numeric keys are used:

| Button | Action | Description |
| :--- | :--- | :--- |
| **LEFT** | Continuous CCW | Starts rotating Counter-Clockwise. RGB blinks Red/Blue (Siren). |
| **RIGHT** | Continuous CW | Starts rotating Clockwise. RGB blinks Red/Blue (Siren). |
| **OK** | Stop | Stops any continuous rotation. RGB turns Green. |
| **1** | CCW 1/8 Rev | Rotate CCW 1/8th turn (Slow speed). |
| **2** | CCW 1/4 Rev | Rotate CCW 1/4th turn (Normal speed). |
| **3** | CCW 1/2 Rev | Rotate CCW 1/2 turn (Fast speed). |
| **4** | CW 1/8 Rev | Rotate CW 1/8th turn (Slow speed). |
| **5** | CW 1/4 Rev | Rotate CW 1/4th turn (Normal speed). |
| **6** | CW 1/2 Rev | Rotate CW 1/2 turn (Fast speed). |

## 💻 Installation & Build

This project is built using **PlatformIO**.

1.  **Clone the repository**:
    ```bash
    git clone https://github.com/pavitra14/IRStepperMotorRGB.git
    cd IRStepperMotorRGB
    ```

2.  **Open in VS Code**: Ensure you have the [PlatformIO IDE](https://platformio.org/platformio-ide) extension installed.

3.  **Install Dependencies**: PlatformIO will automatically install the required libraries defined in `platformio.ini`:
    *   `Arduino-IRremote`
    *   `ArduinoGraphics`
    *   `IRRemoteMap`

4.  **Upload**: Connect your Arduino Uno R4 WiFi and click the **Upload** button in the PlatformIO toolbar.

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
