## Introduction

This `holo_localization_vision` library provides common functionality to be shared across 
multiple projects.

## Details

## Supported Platforms

System: Ubuntu 14.04/Ubuntu 16.04/Ubuntu 18.04

Compiler: gcc-4.9/gcc-5.4

## Setup cross compile environment for ARMv7-a[Optional]

1. Install cross compile toolchain

        sudo apt-get install g++-arm-linux-gnueabihf gfortran-arm-linux-gnueabihf

2. Setup target file system

    option1: Download preconfigured ubuntu root file system from holo ftp server

        login ftp.holomatic.ai and download haoyu/ubuntu-base-16.04-core-armhf-2018-6-12.tar.gz
        extract the file to /opt/ubuntu-base-16.04-core-armhf

    option2: Download unconfigure ubuntu root file system from official website.

        Please see "https://wiki.holomatic.cn/pages/viewpage.action?pageId=16486491" for details.

## 3rdparty support

### Pangolin support

Pangolin is a library to for visualization with OpenGL. To make it simple to use,
there is a submodule in `holo_localization_vision/3rdparty` to link to our own repo
that includes all of its dependency.

- Build for x86 host

        cd $YOUR_WORK_DIR/holo_localization_vision/3rdparty
        mkdir build_x86 && cd build_x86
        cmake ..
        make -j`nproc`

- Build for arm target

        cd $YOUR_WORK_DIR/holo_localization_vision/3rdparty
        mkdir build_arm && cd build_arm
        cmake .. -DCMAKE_TOOLCHAIN_FILE=../../cmake/toolchain/armv7a_toolchain.cmake
        make -j`nproc`

## Build Dependencies

- holo_base, holo_3d, holo_localization_base

## Build Instruction

1. Install prerequisite software

        sudo apt-get install libgflags-dev libboost-all-dev libgoogle-perftools-dev libglew-dev

2. Create a workspace to clone the holo_localization_vision project.

        mkdir $YOUR_WORK_DIR
        cd  $YOUR_WORK_DIR
        git clone $HOLO_LOCALIZATION_VISION_REPO_PATH

3. Follow the instruction in "3rdparty support" section.

4. Build `holo_localization_vision`

- Build for x86 host

        cd $YOUR_WORK_DIR/holo_localization_vision
        mkdir build_x86
        cd build_x86
        cmake ../
        make -j`nproc`

- Build for arm host

        cd $YOUR_WORK_DIR/holo_localization_vision
        mkdir build_arm
        cd build_arm
        cmake ../ -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain/armv7a_toolchain.cmake
        make -j`nproc`

5. Run all tests

        make test

6. Install localization libraries

        sudo make install

## How to enfore the astyle format?

1. Install astyle
        sudo apt-get install astyle

2. Install `format_holo_code.sh` (Optional)

        cd $YOUR_WORK_DIR/holo_base/script
        sudo chmod +x format_holo_code.sh
        sudo mv format_holo_code.sh /usr/local/bin

3. Run this shell

        format_holo_code.sh $THE_DIR_NEED_FORMATED
        
If path is a directory, will format all .h .hpp .c .cpp files in that directory.

If path is a file, will format the file.

If path is not specified, will format all .h .hpp .c .cpp files in current 
directory.

## Troubleshooting

1. Compilation error on virtual machine.
   Please try increasing the number of memory and CPU cores allocated to your VM
 settings.

2. Compilation error due to gcc version:
   This is because the gcc installed in the development system is outdated and 
thus build process is blocked by cmake enforcement
   Try the following command to update gcc to 4.9 version:

        cd $YOUR_WORK_DIR/holo_base/script
        ./upgrade_gcc

## Changelog

Example:
2017/08/11    some modification.