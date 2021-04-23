#!/bin/bash

PORT=$2

if [ -z "$2" ]
then
    PORT=8082
fi

SCENE=$1
if [ -z "$1" ]
then
    SCENE=scenes/robot.json
fi

ROOTDIR=`git rev-parse --show-toplevel`

gdb --args ${ROOTDIR}-build/bin/web-app $PORT web $SCENE
