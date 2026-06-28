# Password Manager Core Utilities

## Overview
This repository contains a collection of C utilities that simulate the core functionalities of a modern Password Manager. Inspired by cybersecurity best practices (such as the NSA guidelines on password security and the dangers of password reuse), this project implements secure password generation, data encryption, and automated form-filling mechanisms.

The project demonstrates proficiency in low-level programming concepts, including **strict dynamic memory management**, **bitwise operations**, **string manipulation**, and the use of **arrays of function pointers**.

---

## Recomandation

I do recommend to go through the test/problem*/in files to see how the inputs should look, especially for the autofill program.

## Core Modules

### 1. Vigenère Encryption Engine (`vigenere.c`)
A custom implementation of the Vigenère cipher designed to safely encrypt sensitive text.
* **Extended Alphabet:** Unlike the classic 26-letter cipher, this implementation uses a 52-character circular alphabet (`a-z` followed by `A-Z`).
* **Dynamic Key Extension:** Automatically repeats the encryption key to match the length of the plaintext.
* **Input Validation:** Ensures both the key and the plaintext consist strictly of valid alphabetical characters before processing.

### 2. AutoFill Processor (`autofill.c`)
Simulates the autofill feature of a password manager by dynamically replacing predefined placeholders in a text with sensitive user data.
* **Dynamic Memory Allocation:** Strictly allocates memory for the dictionary of key-value pairs (`struct pair`) and the final formatted text, ensuring zero memory waste.
* **Exact Boundary Matching:** Identifies keys within the text only when they appear as whole words (delimited by spaces or punctuation), avoiding accidental partial replacements.

### 3. Secure Password Generator (`encryption.c`)
Generates highly secure, unpredictable passwords based on a random seed and a specified length, using characters from the printable ASCII range `[32, 125]`. 
The module applies a randomized layer of encoding to each character using an **array of function pointers**, selecting one of the following transformations:
* **Frequency Encoding:** Concatenates the character with its occurrence count up to that point.
* **Bitwise Transformation:** Applies complex bit-level operations (toggling the 3rd and 6th bits, counting active bits, applying logical `OR` masks, and unsetting the LSB) to generate a completely new character.
* **Case Shifting:** Converts lowercase letters to uppercase while leaving symbols and numbers intact.

---

## Technical Highlights
* **Language:** C
* **Memory Management:** Zero memory leaks. All dynamic structures are meticulously freed. Validated using `Valgrind`.
* **Advanced C Concepts:** Utilizes arrays of function pointers for randomized algorithmic execution and bitwise operators for cryptographic character manipulation.
* **Coding Standards:** Highly modular code, strictly avoiding global variables, with functions limited to specific, single responsibilities.

---

## Compilation and Usage

The project requires the GCC compiler. You can compile each module separately as they are designed as standalone utilities.

### Compiling
```bash
gcc -Wall -g vigenere.c -o vigenere
gcc -Wall -g autofill.c -o autofill
gcc -Wall -g encryption.c -o encryption
```

## Running the Utilities

You can provide input manually via standard input (stdin).

## Memory Checks

You can also run this valgrind script to verify if there are any memory leaks.
(Change <program> with the name of one of the executables you want to  test)

```bash
valgrind --tool=memcheck --leak-check=full ./ <program>
```



