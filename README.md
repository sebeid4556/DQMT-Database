# DQMT-Database
This application is a database for monster in DQMT (Dragon Quest Monsters Terry's Wonderland 3D)
Select the monster from the left to see their stats in the main window.
![Alt text](screenshot/small.png)

# Technical
IMPORTANT: To use this software, you must first have a copy of the game. This is because the database is constructed using the raw ROM files of the game. If you have a dumped copy of the game, running the program for the first time will construct the database.

The database is stored in a custom binary format that follows the data structure used by the program.

In the database are 4 sub-databases:
- Monsters (data/monsters.bin)
- Traits (data/traits.bin)
- Moves (data/moves.bin)
- Skills (data/skills.bin)

# Building
Setting up environment:
- Create folder named sdl2 in root directory (if using a different location, edit CMakeLists.txt accordingly).
- Download SDL2 to sdl2. Add C:/sdl2/bin to PATH environment variable.
- Download SDL2_image & SDL2_ttf. Copy header files to C:/sdl2/incldue. Do the same for binaries into C:/sdl2/bin and C:sdl2/lib.

Building:
Run the following batch scripts:
```
configure
build
```
Run by simply:
```
run
```
# All Screenshots
![Alt text](screenshot/small.png)
![Alt text](screenshot/mega.png)
![Alt text](screenshot/giga.png)