## Introduction

The `holo_cmw` library provides functions for applications to create ros/dds endpoints.

## Details

## Supported Platforms

System: Ubuntu 16.04

Compiler: gcc-5.4

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

- ROS

- RTI Connect DDS [Optional]

## Build Instruction

1. Install prerequisite software 

2. Create a workspace to clone the holo_cmw project.

        mkdir $YOUR_WORK_DIR
        cd  $YOUR_WORK_DIR
        git clone $HOLO_3D_REPO_PATH

3. Build `holo_cmw` 3rdparty libraries
        
        Follow 3rdparty support section

4. Build 'holo_cmw' library

- Build for x86 host

        cd $YOUR_WORK_DIR/holo_cmw
        mkdir build_x86 && cd build_x86
        cmake ..
        make -j`nproc`

- Build for arm host

        source crossenv.sh
        cd $YOUR_WORK_DIR/holo_cmw
        mkdir build_arm && cd build_arm
        cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain/armv7a_toolchain.cmake
        make -j`nproc`

5. Run all tests

        make test

6. Installation

        sudo -E PYTHONPATH=$PYTHONPATH make install

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

## Changelog

2017/11/09    initialization.
