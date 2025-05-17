#!/usr/bin/env bash

if [ -z "$EMSDK" ]; then
	echo "Please install and activate Emscripten first"
	echo "See https://emscripten.org/docs/getting_started/downloads.html"
	exit 1
fi

make \
	CXX=em++ \
	CXXFLAGS='-Os' \
	LDFLAGS='-L./lib-wasm -sUSE_GLFW=3 -sASYNCIFY -sTOTAL_STACK=64MB -sINITIAL_MEMORY=500MB -sASSERTIONS --shell-file shell.html --preload-file assets' \
	BIN='$(BINDIR)/condot.html' \
