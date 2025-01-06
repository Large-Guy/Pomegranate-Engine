#!/usr/bin/env bash

cd "./external"

echo "Installing LuaJIT..."

# Check if the directory exists
if [ ! -d "./LuaJIT" ]; then
    git clone https://github.com/LuaJIT/LuaJIT.git
fi

cd "./LuaJIT"

# Grab the mac os version
make MACOSX_DEPLOYMENT_TARGET=$(sw_vers -productVersion)