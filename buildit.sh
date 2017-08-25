mkdir build
cd build/
g++ -c ../src/*.cpp -I../src/ -std=c++11 -Wall
cd ../
g++ -o gert-ctml -std=c++11 -Wall build/*.o
