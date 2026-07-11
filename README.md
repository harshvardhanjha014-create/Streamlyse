# 🎬 Watch History Analyzer (C)

> **A lightweight command-line analytics engine built in C for processing streaming platform watch-history datasets.**

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Platform](https://img.shields.io/badge/Platform-macOS%20|%20Linux%20|%20Windows-success)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Status](https://img.shields.io/badge/Status-Active-brightgreen)

---

## 📖 About

**Watch History Analyzer** is a terminal-based analytics application written entirely in **C**.

It reads user watch-history records from a text database and generates useful platform insights through an interactive command-line interface.

The project was built to practice core systems programming concepts while solving a realistic data-processing problem using only the C Standard Library.

---

## ✨ Features

- 📂 Read persistent watch-history records
- 👥 Display complete user database
- 📊 Generate platform-wide statistics
- 🏆 Identify the highest watch-time user
- 🔍 Search for any show across the dataset
- 📈 Calculate average watch hours for individual shows
- ⚡ Automatically adapts to datasets of varying sizes
- 🧩 Modular and easy-to-read codebase

---

## 📁 Dataset Format

Each record consists of four fields:

- Username
- Show Name
- Genre
- Seconds Watched

Example structure:

```
Username
Show Name
Genre
Seconds Watched
```

The application dynamically scans every record without relying on hardcoded dataset sizes.

---

## 📊 Analytics

Current capabilities include:

- Total users recorded
- Total watch hours on the platform
- Average watch hours per user
- Highest watch duration
- Ascending watch-time listing
- Global show search
- Number of viewers for a show
- Average watch duration for a searched show

---

## 🛠 Tech Stack

| Component | Technology |
|-----------|------------|
| Language | C |
| Compiler | GCC / Clang |
| Storage | Plain Text Database |
| Platform | Windows • macOS • Linux |

---

## 📂 Project Structure

```
Watch-History-Analyzer/
│
├── analyser_tool.c
├── userdatav1.2.txt
├── LICENSE
└── README.md
```

---

## 🎯 Concepts Demonstrated

- Structures
- Functions
- Arrays
- Variable Length Arrays (VLAs)
- File Handling
- Sequential File Processing
- Bubble Sort
- Searching Algorithms
- String Manipulation
- Modular Programming
- Command-Line Application Development

---

## Roadmap

Planned enhancements include:

- User search by username
- Genre-wise analytics
- Top watched shows ranking
- CSV dataset support
- Improved input validation
  ---

## 💡 Design Philosophy

The project intentionally avoids external libraries and databases.

Every statistic is computed directly from raw data using standard C, making the implementation lightweight, portable, and educational.

---

## 📜 License

This project is licensed under the **MIT License**.

You are free to use, modify, distribute, and build upon this project, provided the original license is included with any substantial portions of the software.

See the **LICENSE** file for complete details.

---

## 👨‍💻 Author

**Harshvardhan Jha**

Built with C as part of a hands-on journey into systems programming, file processing, and real-world software development.

---

### ⭐ If you enjoyed this project, consider giving it a star.

It helps support future C projects and encourages continued open-source development.
