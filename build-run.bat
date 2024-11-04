@echo off
cls

setlocal
set PATH=..\..\compiler\MinGW32\bin
set PATH=%PATH%;..\..\compiler\make\bin

make build-run