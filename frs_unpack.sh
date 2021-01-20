#!/bin/sh

go4analysis -lib libGo4UserAnalysis.so -file $1 -disable-asf -step Sort -store sort_$2.root -enable-store -step Calibr -store calib_$2.root -enable-store -step Analysis -enable-store -store ana_$2.root
