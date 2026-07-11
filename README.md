# ⌚ Surfcitytime

A lightweight, pixel-perfect digital watchface for Pebble/Rebble smartwatches. Designed with a retro pixelated aesthetic, this watchface is engineered from the ground up for absolute minimalism, high readability, and extreme battery efficiency.

## 🚀 The Core Philosophy: "Less is More"
Many modern watchfaces drain wearable batteries by constantly redrawing complex graphics. This project focuses on high-contrast pixel aesthetics paired with an ultra-efficient rendering pipeline—keeping the CPU completely asleep between minute updates, except for a lightweight second-interval blink.

## 🛠️ Technical Highlights & Optimization
As a self-taught developer, I built this project to dive deep into embedded software constraints and resource management.

* **Ultra-Low Power Consumption:** Optimized the event loop to ensure screen redraws only happen when absolutely necessary.
* **Blinking Colon Timing:** Implemented an efficient background timer toggle for the blinking `:` separator that consumes negligible CPU cycles.
* **Pixel-Perfect Scaling:** Hand-aligned pixel fonts and UI elements to native screen resolutions to prevent anti-aliasing artifacts and maintain crisp rendering.
* **Zero Bloat:** Stripped out unnecessary background processes to keep the compiled binary footprint as small as possible.

## 🧰 Tech Stack
* **Language:** C
* **Platform:** Pebble SDK / Rebble OS
* **Architecture:** Event-driven UI updates

## 🧠 What I Learned Building This
* **Handling Embedded Loops:** Learned how to work within the constraints of low-memory microcontrollers where every byte and CPU tick counts.
* **State Management:** Figured out how to handle simple state toggles (like the visible/invisible colon state) cleanly without memory leaks.
* **Resource Optimization:** Gained hands-on experience loading and rendering custom pixel font assets efficiently.

## 💻 How to Build & Run
To run this project locally using the Pebble/Rebble SDK:

1. Clone the repository:
   ```bash
   git clone [https://github.com/Airdroidz/Surfcitytime.git](https://github.com/Airdroidz/Surfcitytime.git)
   
