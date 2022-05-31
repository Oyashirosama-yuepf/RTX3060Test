#!/usr/bin/env bash

SOURCE=${BASH_SOURCE[0]}
while [ -h "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  SCRIPTPATH=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )
  SOURCE=$(readlink "$SOURCE")
  [[ $SOURCE != /* ]] && SOURCE=$SCRIPTPATH/$SOURCE # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
SCRIPTPATH=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )

if [ -f $SCRIPTPATH/setup.sh ]; then
    source $SCRIPTPATH/setup.sh
fi

export HOLO_ROOT=$SCRIPTPATH
export LD_LIBRARY_PATH=$SCRIPTPATH/lib:$SCRIPTPATH/3rdparty/lib:$LD_LIBRARY_PATH
export PYTHONUSERBASE=$HOLO_ROOT
