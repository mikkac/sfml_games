Install important libraries
```
sudo apt install build-essential libudev-dev libopenal-dev libvorbis-dev libflac-dev libsfml-dev
```
Clone and build SFML
```
git clone https://github.com/SFML/SFML ~/SFML
cd ~/SFML
mkdir ./build
cd ./build
cmake ..
make
sudo make install
```
