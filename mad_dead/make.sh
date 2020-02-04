mkdir ./build
cd ./build
cmake ..
make -j4
mv mad_dead ..
cd ..
./mad_dead

