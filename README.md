# Plastic Object Identifier for Conveyor Belt Sorting 🚀

## 🏭 Project Overview
This project is developed for **Kursi**, a plastic recycling company. It classifies plastic objects into three categories — **Black**, **Transparent**, and **Colorful** — and sends them to the correct conveyor belt using a rule-based detection system.

### 🔄 Conveyor Belts:
- **Conveyor A** → Black objects
- **Conveyor B** → Transparent objects
- **Conveyor C** → Colorful objects

---

## 📁 Dataset
The dataset consists of student-captured images organized in three folders:
```
dataset/
│
├── black/ # 10 black plastic images
├── transparent/ # 10 transparent plastic images
└── colorful/ # 10 colorful plastic images
```

---

## ⚙️ How It Works

1. Load image using OpenCV.
2. Analyze:
   - **Brightness** (average pixel intensity)
   - **Colorfulness** (color variation)
3. Based on rules:
   - If brightness > 60 and colorfulness < 30 → Conveyor B
   - If colorfulness ≥ 30 → Conveyor C
   - Else → Conveyor A

---

## 🛠️ How to Run

### ✅ Prerequisites:
- C++ compiler
- OpenCV installed
- VS Code / MSYS2 terminal or other C++ setup

### 🧪 Compile:
```bash
g++ main.cpp -o object_identifier `pkg-config --cflags --libs opencv4`
```
### Run:
```
./object_identifier.exe
