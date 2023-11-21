if [ -d "./build" ]; then
cd ./build
cmake --build .;
elif [ ! -d "./build" ]; then
mkdir build
cd ./build
cmake ..
cmake --build .
fi
