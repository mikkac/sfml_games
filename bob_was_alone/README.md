# Bob was alone- clone of popular game called 'Thomas was alone'
This game was made when I was learning basics of game development and SFML library with book '_Beginning C++ Game Programming_' by _John Horton_
![Play1](samples/bob_was_alone_start2.png?raw=true)

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
cp bob_was_alone ..
cd ..
./bob_was_alone
```
or simply run `make.sh`
```
./make.sh
```

To run clang-tidy
```
cd ./build
cmake ..
make bob_was_alone-tidy
```
To run clang-format
```
cd ./build
cmake ..
make bob_was_alone-format
```
To run game with valgrind check
```
./valgrind
```
### Samples
![Start](samples/bob_was_alone_start.png?raw=true)
![Start2](samples/bob_was_alone_start2.png?raw=true)
![Split](samples/bob_was_alone_split.png?raw=true)
![Level2](samples/bob_was_alone_level2.png?raw=true)

All of the used resources (graphics, fonts, sounds) were borrowd from official book repository.
