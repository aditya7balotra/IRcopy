 # IRcopy: A Universal IR Remote Control Cloner

*IRcopy* is a simple yet powerful universal IR remote cloner built using the *Arduino framework* and developed with *PlatformIO*. It enables you to capture, store, and replay infrared (IR) signals from your existing remote controls using just an ESP32/ESP8266 board and a few electronic components.

Whether you're consolidating remotes or integrating IR control into your home automation system, IRcopy provides a flexible and easy-to-use solution.

---

## 🚀 Features

- *Capture:* Easily record IR signals from almost any remote control.
- *Store:* Save captured signals directly to device memory.
- *Replay:* Transmit saved IR signals to control TVs, ACs, stereos, etc.
- *Arduino + PlatformIO:* Built using Arduino codebase and structured with PlatformIO for seamless cross-platform development.
- *Configurable:* Signal count, timings, and behavior can be changed easily via the configuration file.

---

## 🧰 Hardware Requirements

To get started, you'll need:

- An *ESP32, **ESP8266, or other **Arduino-compatible* development board  
- An *IR receiver module* (e.g., VS1838B) for signal input  
- An *IR LED* and a *transistor* (e.g., 2N2222) for signal output  
- A *breadboard* and *jumper wires*

---

## 🖥️ Software Requirements

- *PlatformIO Core*  
  Install via the [PlatformIO IDE](https://platformio.org/install/ide?install=vscode) for VS Code or through the command line.

---

## 📦 Project Structure

```text
IRcopy/
├── include/        # Project-specific header files
├── lib/            # Custom or third-party libraries
├── src/            # Main Arduino source code (core logic)
├── platformio.ini  # PlatformIO project configuration
```

## ⚙️ Getting Started

1. Clone the Repository:
```bash
  git clone https://github.com/aditya7balotra/IRcopy.git
  cd IRcopy
```

2. Open in PlatformIO:

    - Open the project folder in VS Code with the PlatformIO extension installed.


3. Connect & Upload:

    - Connect your ESP32 or ESP8266 board via USB.
    - In PlatformIO, click the "Upload" button (right-arrow icon) to compile and flash the code to your board.



---

## 🎮 Usage

Once the code is uploaded and hardware is wired up, here's how the device behaves:

- The IR receiver continuously listens for incoming IR signals.
- A signal is only saved if the device has available storage space.  
  By default, it can store up to **2 signals** in memory.

  > 🛠️ You can increase this limit from the configuration file.

- The device uses a single physical button to handle all actions:
  - **Short press:** Sends the saved signals alternatively — switches between them on every press.
  - **Long press:** Deletes all stored signals. The onboard LED will turn on to confirm the deletion.

- IR signals are transmitted via an IR LED and transistor, allowing the device to control TVs, ACs, stereos, and other IR-based appliances.
- The behavior, signal count, and timings are fully configurable from the configuration files in `src/` or `include/`.

> ✅ This has been tested on Arduino(UNO R3) board using the PlatformIO framework.

---

## 🤝 Contributing

Contributions are welcome!  
If you have suggestions, improvements, bug fixes or hardware tweaks:

- 🐞 Open an Issue  
- 🚀 Submit a Pull Request  

Let’s build a better universal IR remote cloner together!

---

## 📝 License

This project is licensed under the MIT License.  
See the [LICENSE](LICENSE) file for full details.
