#!/bin/bash -e

if [ -d config ]; then
    cd config
    cp -fl opendds_config_rtps.ini opendds_config.ini
    echo "OK."
fi

