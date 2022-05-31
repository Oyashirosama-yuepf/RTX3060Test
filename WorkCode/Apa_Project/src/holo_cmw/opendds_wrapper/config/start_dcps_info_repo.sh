#!/bin/bash -e

export HOLO_ROOT=${PWD}
export LD_LIBRARY_PATH=${HOLO_ROOT}/lib:${HOLO_ROOT}/3rdparty/lib

if [ -f 3rdparty/bin/DCPSInfoRepo ]; then
    ./3rdparty/bin/DCPSInfoRepo -ORBListenEndPoints iiop://127.0.0.1:12345
fi
