#!/bin/bash

# What BulletPhysics version are we using?
if [ -z "$BULLETPHYSICS_VERSION" ]; then
	BULLETPHYSICS_VERSION=2.83.5
fi

# Life helpers
COLOR_MAGENTA=`tput setaf 6`
COLOR_RESET=`tput sgr0`

yell() { echo "${COLOR_MAGENTA}$0: $*${COLOR_RESET}" >&2; }
die() { yell "$*"; exit 111; }
try() { "$@" || die "Error: Cannot \"$*\""; }

# Taking care of dependencies
echo "${COLOR_MAGENTA}Checking if BulletPhysics libraries are already built...${COLOR_RESET}"
if [ ! -d bullet3-${BULLETPHYSICS_VERSION}/output_static ] || [ ! -d bullet3-${BULLETPHYSICS_VERSION}/output_shared ]; then
	echo "${COLOR_MAGENTA}BulletPhysics libraries not found!${COLOR_RESET}"

	# Delete any remainings from old BulletPhysics builds
	rm -rf bullet3-${BULLETPHYSICS_VERSION}
	rm -f ${BULLETPHYSICS_VERSION}.tar.gz

	# Download BulletPhysics
	echo "${COLOR_MAGENTA}Downloading BulletPhysics...${COLOR_RESET}"
	try wget https://github.com/bulletphysics/bullet3/archive/${BULLETPHYSICS_VERSION}.tar.gz
	try tar -xzvf ${BULLETPHYSICS_VERSION}.tar.gz
	rm -f ${BULLETPHYSICS_VERSION}.tar.gz
	cd bullet3-${BULLETPHYSICS_VERSION}	

	# Make sure we build BulletPhysics for x86 architecture
	export CFLAGS="-m32"
	export CXXFLAGS="-m32"
 
	# Create directories for CMake
	mkdir build_static
	mkdir build_shared

	# Build static libraries
	echo "${COLOR_MAGENTA}Building static libraries...${COLOR_RESET}"
	cd build_static
	try cmake -DBUILD_EXTRAS=OFF -DBUILD_BULLET3=OFF -DBUILD_UNIT_TESTS=OFF -DBUILD_BULLET2_DEMOS=OFF -DBUILD_CPU_DEMOS=OFF -DCMAKE_INSTALL_PREFIX=../output_static  ..
	try make -j4
	try make install
	cd ..

	# Build shared libraries
	echo "${COLOR_MAGENTA}Building shared libraries...${COLOR_RESET}"
	cd build_shared
	try cmake -DINSTALL_LIBS=ON -DBUILD_SHARED_LIBS=ON -DBUILD_EXTRAS=OFF -DBUILD_BULLET3=OFF -DBUILD_UNIT_TESTS=OFF -DBUILD_BULLET2_DEMOS=OFF -DBUILD_CPU_DEMOS=OFF -DCMAKE_INSTALL_PREFIX=../output_shared  ..
	try make -j4
	try make install
	cd ..

	cd ..
	echo "${COLOR_MAGENTA}BulletPhysics libraries successfully built!${COLOR_RESET}"
else
	echo "${COLOR_MAGENTA}BulletPhysics libraries found!${COLOR_RESET}"
fi

# Back to ColAndreas
echo "${COLOR_MAGENTA}Building ColAndreas...${COLOR_RESET}"

# Delete any remainings from old ColAndreas builds
rm -rf build_static
rm -rf build_shared
rm -rf build

# Create directories for CMake and binaries
mkdir build_static
mkdir build_shared
mkdir build

# Build ColAndreas
cd build_static
try cmake -DCMAKE_BUILD_TYPE=Release -DBULLET_ROOT=$(pwd)/../bullet3-${BULLETPHYSICS_VERSION}/output_static .. 
try make -j4
mv ColAndreas_static.so ../build/.
cd ..

cd build_shared
try cmake -DCMAKE_BUILD_TYPE=Release -DBULLET_ROOT=$(pwd)/../bullet3-${BULLETPHYSICS_VERSION}/output_shared ..
try make -j4
mv ColAndreas.so ../build/.
cd ..

# Clean up
rm -rf build_static
rm -rf build_shared

echo "${COLOR_MAGENTA}ColAndreas successfully built!${COLOR_RESET}"
exit 0

