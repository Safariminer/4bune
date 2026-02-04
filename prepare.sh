#!/bin/bash
rm -rf deps
mkdir -p deps/{buildenv,include}
cd deps/buildenv

# downloading dyad
git clone https://github.com/rxi/dyad
cd dyad
cp src/dyad* ../../include/

# downloading pugixml
cd ..
git clone https://github.com/zeux/pugixml
cd pugixml
cp src/pugi* ../../include/


cd ../../../../