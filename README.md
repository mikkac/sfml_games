# Mad Dead- clone of popular game called 'Over 9000 Zombies'
This game was made when I was learning basics of game development and SFML library with book '_Beginning C++ Game Programming_' by _John Horton_

## How to run the game
### Prepare environment
Install important libraries
```
sudo apt install build-essential libudev-dev libopenal-dev libvorbis-dev libflac-dev libsfml-dev xorg-dev
```
If there still will be some cmake errors, then make sure that all of standard libraries are installed on you ubuntu:
```
sudo apt-get install ubuntu-desktop ubuntu-standard ubuntu-minimal
```
Clone and build SFML
```
git clone https://github.com/SFML/SFML ~/SFML
cd ~/SFML
cmake .
make
sudo make install
```
### Build project
```
mkdir build
cd ./build
cmake ..
make -j8
cp mad_dead ..
cd ..
./mad_dead
```
or simply run `make.sh`
```
./make.sh
```

To run clang-tidy
```
cd ./build
cmake ..
make mad_dead-tidy
```
To run clang-format
```
cd ./build
cmake ..
make mad_dead-format
```
Unfortunately header files are not handled by clang format- I use plugin in Visual Studio Code to format the code.
