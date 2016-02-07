#!/usr/bin/python

try:
    from subprocess import call
except ImportError, e:
    print("sys module not found! Please make sure you have Python 2.7" +
          " installed correctly.")
    exit(2)

try:
    from sys import platform as _platform
except ImportError, e:
    print("sys module not found! Please make sure you have Python 2.7" +
          " installed correctly.")
    exit(2)

if _platform == "linux" or _platform == "linux2":
    call("make -f \"Linux.mk\" install", shell=True)
elif _platform == "darwin":
    call("make -f \"OSX.mk\" install", shell=True)
elif _platform == "win32":
    print("Windows not supported!")
