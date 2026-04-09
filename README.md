<div align="center">
  <h1>🚀 Smart Tracker (DATN NAS)</h1>
  <p><strong>v1.0 Board Firmware based on STM32 & FreeRTOS</strong></p>
</div>

---

## 📌 Overview
This repository contains the firmware for a modular Smart Tracker system designed as a graduation project (Đồ án Tốt nghiệp). The core architecture is built around the **STM32** microcontroller and leverages **FreeRTOS** for robust real-time multitasking, utilizing a clean separation between Hardware Drivers and Application Services.

## ⚙️ Current Progress & Key Features

### 🧭 1. IMU Sensor Engine (ICM-42605)
A high-performance SPI driver explicitly tailored for low-latency sensor data acquisition.
* **Hardware-to-RTOS Bridging**: Utilizes hardware interrupts (EXTI) efficiently routed to the service layer via lightweight *FreeRTOS Task Notifications*.
* **Feature Highlights**:
  * Real-time 6-axis telemetry (Accelerometer + Gyroscope).
  * **Crash Detection Algorithm**: Specialized sensor fusion algorithm to accurately monitor and catch sudden impacts/accidents.

### 💾 2. Persistent Flash Storage (W25Q32JV SPI Flash)
A fault-tolerant, DMA-ready Flash driver thoroughly decoupled from the SPI bus to support asynchronous operations without blocking the CPU.
* **Reliable Storage Manager**: Structured data-logging validated by specific *Magic Words* to completely avoid reading corrupt records.
* **Periodic Telemetry logger**: Dedicated background task tracking system telemetry every 5 seconds.
* **Wear & Boot Optimization**:
  * Utilizes an isolated **Tracking Sector** that strictly respects page boundaries to minimize flash wear.
  * **Binary Search Recovery**: Rapidly locates the latest append index on boot without the need to sequentially scan the entire storage matrix, ensuring instant system startups.

---

## 🛠️ Technology Stack
* **Core**: STM32 Microcontroller 
* **OS**: FreeRTOS
* **Sensors & Peripherals**: ICM-42605 (IMU), W25Q32JV (Flash Memory)

<br>

> *This README will be continuously updated as new modules are developed and integrated into the board.*
