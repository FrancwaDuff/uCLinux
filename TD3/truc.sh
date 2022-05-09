#! /bin/sh

stty 115200 cs8 raw -echo -echoe -echonl -echok -echoprt -echoctl -parenb < /dev/ttyUSB0
