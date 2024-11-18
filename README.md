# **Music Artist Management System**

## **Description**
This project implements a music and artist management system using AVL (self-balancing binary search trees). It supports operations to manage artists and their associated music tracks, including adding, deleting, searching, displaying, and saving/loading data to/from a JSON file.

---

## **Features**
### **Artist Management**
- Add a new artist with a unique ID and name.
- Delete an artist (and automatically remove all associated music tracks).
- Search for an artist by ID.
- Display all artists in the system.

### **Music Management**
- Add a new music track with a unique ID, title, duration, and an associated artist ID.
- Delete a music track.
- Search for a music track by ID.
- Display all music tracks in the system.

### **Data Persistence**
- Save artists and music tracks to a JSON file.
- Load artists and music tracks from a JSON file.

### **Tree Visualization**
- Display hierarchical views of both the artist and music AVL trees.

---

## **Project Structure**
The project is modular and organized into the following directories:

### **Source Files**
- **`src/`**: Contains the source code files.
  - `main.c`: Main entry point of the program with an interactive menu.
  - `artist.c`: Functions related to artist management.
  - `music.c`: Functions related to music management.
  - `tree.c`: Generic AVL tree implementation.

### **Header Files**
- **`include/`**: Contains header files.
  - `artist.h`: Declarations for artist-related functions and structures.
  - `music.h`: Declarations for music-related functions and structures.
  - `tree.h`: Generic AVL tree function declarations.

### **Data Files**
- **`data/`**: Contains saved JSON files.
  - `database.json`: Stores artists and music tracks in JSON format.

---

## **Requirements**
### **Compiler**
- GCC or any compatible C compiler.

### **Libraries**
- **json-c**: A JSON parsing and manipulation library for C.
  - Used to read and write JSON files.

#### **Installing `json-c` on Ubuntu**
```bash
sudo apt update
sudo apt install libjson-c-dev
```

## Installation

### Installing `json-c` on Other Systems

#### MacOS (using Homebrew)
```bash
brew install json-c
```

#### Windows (using MinGW)
* Download and build the library from the official GitHub repository.

## Compilation and Execution

### 1. Compilation
Use the provided `Makefile` to compile the project:
```bash
make
```

### 2. Running the Program
Run the compiled program:
```bash
./build/music_db
```

### 3. Cleaning the Build
To remove compiled files:
```bash
make clean
```

## Usage

When you start the program, the following interactive menu will be displayed:

```
----------------- Artist and Music Database Manager ----------------
1. Add Artist
2. Add Music
3. Display Artists
4. Display Musics
5. Search Artist by ID
6. Search Music by ID
7. Remove Artist
8. Remove Music
9. Display Trees (Hierarchical View)
10. Save to JSON
11. Load from JSON
12. Exit
----------------------------------------------------------------------
```

### Example Commands

#### Add an Artist
* Enter option `1` to add a new artist.
* Example:
```
Enter Artist ID: 1
Enter Artist Name: Eminem
```

#### Add a Music Track
* Enter option `2` to add a new music track.
* Example:
```
Enter Music ID: 101
Enter Music Title: LoseYourself
Enter Music Duration (in seconds): 300
Enter Artist ID: 1
```

#### Save Data to JSON
* Enter option `10`. The data will be saved in `data/database.json`.

#### Load Data from JSON
* Enter option `11`. Data will be loaded from the JSON file.

### JSON File Format

Artists and music tracks are saved in the following JSON structure:
```json
{
  "artists": [
    {
      "id": 1,
      "name": "Eminem",
      "left": null,
      "right": null
    }
  ],
  "musics": [
    {
      "id": 101,
      "title": "Lose Yourself",
      "duration": 300,
      "artist_id": 1,
      "left": null,
      "right": null
    }
  ]
}
```

## Technical Details

### Key Data Structures

#### Artist
* ID (integer)
* Name (string)

#### Music
* ID (integer)
* Title (string)
* Duration (unsigned integer)
* Artist ID (integer, foreign key referencing an artist)

### AVL Trees
* Both artists and music tracks are stored in AVL trees for efficient insertion, search, and deletion operations.

## Known Issues
* Invalid input may cause crashes if not handled carefully.
* JSON files must adhere strictly to the expected structure.

## Future Improvements
* Add unit tests for better reliability.
* Improve error handling for invalid inputs.
* Support for exporting and importing data in CSV or XML formats.

## Contributors
* **Author:** Donnesh YATHAVARASAN
* **Affiliation:** ESGI, 3rd Year, Cybersecurity specialization.
