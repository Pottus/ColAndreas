GPP=g++
GCC=gcc
OUTFILE="base.so"

COMPILE_FLAGS=-I /usr/local/include/bullet -c -m32 -O3 -w -DLINUX -I../src/SDK/amx/

all:
	$(GPP) $(COMPILE_FLAGS) ../src/SDK/*.cpp
	$(GPP) $(COMPILE_FLAGS) ../src/*.cpp
	$(GPP) -L ../bullet/src -lBulletDynamics -lBulletCollision -lLinearMath -m32 -O2 -fshort-wchar -shared -o $(OUTFILE) *.o
