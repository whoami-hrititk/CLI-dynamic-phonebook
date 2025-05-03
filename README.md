# CLI Dynamic Phonebook 📱

A simple and dynamic phonebook application built using **C++** and **ncurses**, running in the Linux terminal.

This project allows you to create, search, and view contacts using a clean, interactive menu interface.

---

## ✨ Features

- 📇 Create new contacts with name and phone number  
- 🔍 Search contacts by name  
- 🎨 Colorful and keyboard-navigated menu using `ncurses`  
- ⌨️ Works fully in the command-line interface  

---

## 🛠️ Requirements

- Linux system (Debian or similar)
- C Compiler (e.g. `gcc`)
- `ncurses` library

To install `ncurses` if it's not already:

```bash
sudo apt install libncurses5-dev libncursesw5-dev
```
 How to Run

    Clone this repo:
```bash
git clone https://github.com/whoami-hritik/CLI-dynamic-phonebook.git
cd CLI-dynamic-phonebook
```
    Compile the code:
```bash
g++ phonebook.cpp -lncurses -o phonebook
```
    Run the program:
```bash
./phonebook
```
## 🎮 Controls

Use Arrow Keys to navigate the menu

Press Enter to select an option

Press ESC to go back or exit

## 📂 Project Structure

phonebook.cpp - Main source code with all features

README.md - Project documentation

## 💡 Future Improvements

Edit and remove contact options

Save contacts to a file

Load contacts on startup

## 🧑‍💻 Author

Made by whoami-hritik

