g++ -std=c++11 -framework ApplicationServices -O3 tools.cpp base.cpp display.cpp plan.cpp solver.cpp x.cpp
./a.out < in
rm ./a.out
