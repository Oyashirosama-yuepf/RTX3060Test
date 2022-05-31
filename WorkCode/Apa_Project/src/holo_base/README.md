## Introduction

This `holo_base` library provides common functionality to be sharde across 
multiple projects.

## Details

## Build Instruction

### Legacy build

#set HOLO_ROOT environment(Optional)
export HOLO_ROOT=<holo_project install root directory>

mkdir <build-dir>
cd <build-dir>
cmake <holo_base-source-dir>
make -j <processor number>

#Test
make test

#Doc
make doc

#Install
make install

### Using holo_builder

holo build holo_base

#Test
holo test holo_base

#Doc
holo build holo_base --build_args doc
