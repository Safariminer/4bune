#!/bin/bash
rm -rf deps
mkdir -p deps/{buildenv,include}
cd deps/buildenv
git clone https://github.com/rxi/dyad
cd dyad
cp src/dyad* ../../include/
pwd
cd ../../../../