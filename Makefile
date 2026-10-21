CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

cpu: CPU_driver.cpp CPU.cpp Core.cpp CPU.h Core.h
	$(CXX) $(CXXFLAGS) CPU_driver.cpp CPU.cpp Core.cpp -o cpu

test: cpu
	./cpu < test.txt

clean:
	rm -f cpu

.PHONY: test clean
