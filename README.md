# Arduino-Door-lock
Arduino-based password-protected door lock system using a 4x4 keypad and a servo motor. Demonstrates embedded security logic, input processing, and actuator control.

## 🔌 Circuit Diagram

A complete ASCII wiring diagram is included:

📁 `circuits/diagram.txt`

It shows:
- 4×4 keypad matrix pin connections  
- Servo motor wiring  
- Power and ground layout  

## 🛠 Hardware Used

| Component | Quantity | Purpose |
|-----------|----------|---------|
| Arduino Uno/Nano | 1 | Main controller |
| 4×4 Keypad | 1 | Password input |
| Servo motor (SG90/MG90S) | 1 | Lock actuator |
| Jumper wires | — | Wiring |
| Breadboard | 1 | Prototyping |
| Optional: External 5V supply | 1 | Recommended for stable servo power |

## 🔧 Pin Map

**Keypad Pins → Arduino:**
- Row1 → D9  
- Row2 → D8  
- Row3 → D7  
- Row4 → D6  
- Col1 → D5  
- Col2 → D4  
- Col3 → D3  
- Col4 → D2  

**Servo:**
- Signal → D10  
- +5V → 5V  
- GND → GND  

## ▶️ How to Use

1. Wire the keypad and servo as shown in `circuits/diagram.txt`.  
2. Open `src/door_lock.ino` in Arduino IDE.  
3. Select correct board & COM port.  
4. Upload the sketch.  
5. Open Serial Monitor at **9600 baud** to see input and status messages.  

### Default Password:


### Controls:
- Enter digits → they build up password  
- Press `*` → submit  
- Press `#` → clear input  
