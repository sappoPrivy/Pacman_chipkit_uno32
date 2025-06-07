# Pacman on Chipkit Uno32 Board
_IS1500 Computer Organization and Components, 9 credits at KTH Royal Institute of Technology_, Autumn 2023  
Republished code primarily developed by Tenzin Sangpo Choedon  
Skeleton code (gameplay.S, stubs.c, vectors.S) provided by Axel Isaksson and F Lundevall at KTH as clearly stated at the top of the specified files   

## 📄 Overview
This project implements pacman game logic on a uno32 chipkit board. 

## 🗂️ Table of Contents

- [Overview](#-overview)
- [Project Structure](#-project-structure)
- [Prerequisites](#-prerequisites)
- [Usage](#-usage)

## 🏗️ Project Structure

root/  
├── src/                     # C source codes  
├── pixil-images/            # Pixelated images and python script for generating bitmaps from these images  
├── pixil-files/             # Pixil files used in https://www.pixilart.com/draw#  
└── README.md  

## ✅ Prerequisites

**GCC**  
- Required GNU Compiler Collection:  
  ```bash
  sudo apt install gcc
  ```

  **Make**  
- Install curl using:  
  ```bash
  sudo apt install make
  ```

## 🚀 Usage

Run the scripts in this order:

1. **Generate pixmaps from images**  
   ```bash
   python3 genpix.py map.png 
   ```
2. **Set up environment and build project**  
   ```bash
   . /opt/mcb32tools/environment/  
    make
   ```
3. **Install compiled code to the uno32 board**  
   ```bash
   make install TTYDEV=/dev/ttyUSB0 
   ```
   
