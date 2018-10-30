Install important libraries
```
sudo apt install build-essential libudev-dev libopenal-dev libvorbis-dev libflac-dev
```
Clone and build SFML
```
git clone https://github.com/SFML/SFML ~
cd ~/SFML
cmake ..
make
sudo make install
```
