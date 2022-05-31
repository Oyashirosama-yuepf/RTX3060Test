#!/bin/bash -e

if [ "${BASH_SOURCE}" = "" -o "${BASH_SOURCE}" = "$0" ]; then
    echo "This script can only be source from bash!"
    return
fi

export HOLO_ROOT=$(cd `dirname ${BASH_SOURCE}`; pwd)
export LD_LIBRARY_PATH=${HOLO_ROOT}/lib:${HOLO_ROOT}/3rdparty/lib:${LD_LIBRARY_PATH}
