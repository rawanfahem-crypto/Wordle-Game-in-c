#  Wordle Game in C

A console-based version of the famous **Wordle** game, written in **C Language**.

##  Features
* **Dynamic Feedback:** Tells you if letters are in the correct spot (Green), wrong spot (Yellow), or not in the word (Grey).
* **Time Tracking:** Uses pointers to track and store how long you take for each guess.
* **File Handling:** Reads the secret word list from an external `words.txt` file.
* **Memory Management:** Demonstrates the use of dynamic memory allocation (`malloc` and `free`).

## How to Run
1. Make sure you have a C compiler (like GCC) installed.
2. Ensure `words.txt` is in the same folder as the code.
3. Compile the code: `gcc main.c -o wordle`
4. Run the program: `./wordle`

##  Concepts Used
* Arrays & Strings
* Pointers & Memory Allocation
* File I/O
* Time Library (`time.h`)
