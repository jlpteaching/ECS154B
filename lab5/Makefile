
all: mm2 mm4 mm8 mm16 mm32 mm64 nbmm

mm2: mm.cpp
	g++ mm.cpp -o mm2 -DBLOCK_SIZE=2 -O3 -std=c++11

mm4: mm.cpp
	g++ mm.cpp -o mm4 -DBLOCK_SIZE=4 -O3 -std=c++11

mm8: mm.cpp
	g++ mm.cpp -o mm8 -DBLOCK_SIZE=8 -O3 -std=c++11

mm16: mm.cpp
	g++ mm.cpp -o mm16 -DBLOCK_SIZE=16 -O3 -std=c++11

mm32: mm.cpp
	g++ mm.cpp -o mm32 -DBLOCK_SIZE=32 -O3 -std=c++11

mm64: mm.cpp
	g++ mm.cpp -o mm64 -DBLOCK_SIZE=64 -O3 -std=c++11

nbmm: mm.cpp
	g++ mm.cpp -o nbmm -O3 -std=c++11

clean:
	rm -f mm2 mm4 mm8 mm16 mm32 mm64 nbmm
