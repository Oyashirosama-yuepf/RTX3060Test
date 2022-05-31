# Introduction

C version of holo projects for dragonglass.

# Build

## Legacy build

#set HOLO_ROOT environment(Optional)
export HOLO_ROOT=<holo_project install root directory>

mkdir <build-dir>
cd <build-dir>
cmake .. <holo_c source dir>
make -j <processor number>

#Test
make test

#Doc
make doc

#Install
make install

## Using holo builder
holo build holo_c

#Test
holo test holo_c

#Doc
holo build holo_c --build_args doc

# Documentation

Please see **Build** section about how to generate documentations.

Docs will be generated to <build-dir>/doc/holo_c/html or <install-dir>/share/doc/holo_c/html

