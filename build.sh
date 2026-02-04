#!/bin/bash
g++ -o 4bune-bouchot -I deps/include -I src src/*.cpp deps/include/dyad.c deps/include/pugixml.cpp -fpermissive