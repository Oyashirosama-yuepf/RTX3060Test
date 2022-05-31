#!/bin/bash -e

if [ -d config ]; then
    cd config
    cp -fl opendds_config_repo.ini opendds_config.ini
    echo "OK."
fi

