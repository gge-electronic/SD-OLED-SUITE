
<img width="640" height="394" alt="Handbuch SD Oled Suite_html_462d3f" src="https://github.com/user-attachments/assets/1c5f4133-326e-4443-870b-6451d51c6fa6" />
# SD-OLED-SUITE
A high-performance graphic asset pipeline and runtime library for LGT8F328/Arduino / AVR microcontrollers.

# SD OLED Suite v1.00

🚀 **A High-Performance Asset Pipeline & Runtime for Monochrome MCU Graphics**

The **SD OLED Suite** is a complete, custom toolchain designed to create, manage, and stream rich graphical content on microcontrollers (like the LGT8F328 / AVR) at blazing fast speeds of **up to 50 FPS**—all within a budget of around €10. 

By offloading heavy graphical assets entirely to an SD card, this suite solves the chronic flash memory limitations of smaller microcontrollers.

---

## ⚡ The Core Innovation: SD RAW Format

Unlike standard graphics libraries that rely on heavy FAT/FAT32 file systems, this suite utilizes a custom **SD RAW Format**. 
* **Zero Filesystem Overhead:** Data is read directly via the SD card controller into an optimized 512-byte buffer.
* **Maximum Throughput:** Stream screens, fonts, and animations at hardware-limited speeds.
* *Note: SD cards flashed in RAW format will appear as "unformatted" to Windows PCs. This is normal and required for maximum performance!*

---

## 🛠️ Features & Toolchain Components

1. **Screen Editor (Desktop Tool):** Design complete display contents matching your OLED's pixel resolution.
2. **Word & Tile Creation:** Create sub-elements (64x8 pixels) and tiles (8x8 pixels) that the MCU can rotate dynamically.
3. **Custom Font Generator:** Design your own typography—fully customized, no standard font limitations.
4. **Animation Engine:** Generate fluid transitions (e.g., Slide Left, Center Wipe) with configurable frame counts (up to 32 frames recommended).
5. **Asset Pipeline:** Automatically bundles your `.sed` editor projects into a single `.img` container file.
6. **Built-in Flasher:** Flash your LGT8F328 directly from the desktop application.

---

## 🚀 Getting Started

### 1. Prerequisites & Installation
* Download and run the installer.
* **Important:** Always launch the desktop suite with **Administrator Rights** (`Run as Administrator`), otherwise the tool will not have permission to write the RAW Asset Pipeline directly to the SD card.
* Accept the installer prompt to extract the **Demo Project**. It includes pre-configured folders for standard OLED resolutions.

### 2. File Extensions Quick Reference
* `.sed` — Internal editor project files (Editable)
* `.8x8` / `.8w8` / `.8f8` — Formatted asset outputs (Non-editable compiled files)

### 3. Flashing the SD Card
1. Load your `.sed` files into the editor and click **Export Screenlist**.
2. Verify all 3 `.sed` and 3 `.8xx` files are present in the Project Manager.
3. Click **Make IMG File** and save your asset image (e.g., `SC-2.img`).
4. Insert an SD card (32GB or smaller recommended for safety) into your card reader.
5. Click **WRITE IMG**, select your drive, and hit **Write**. 

---

## 📺 Video Demo
See the suite and the 50 FPS rendering engine in action on YouTube:  
▶️ **[Watch the SD OLED Demo on YouTube]((https://www.youtube.com/watch?v=Hi7pBKslpc8))**

---

## 📝 Author's Note
*This toolchain represents 7 months of dedicated free-time development. Version 1.00 is now officially in feature freeze to ensure stability. Enjoy building fluid embedded UIs!*

