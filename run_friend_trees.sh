#!/bin/bash

# paths to files with FRS detectors data and with DSSD data
frs_file=/data.local2/s475plus_data/root/converted/s475plus_05_70Br_0246.root
ucesb_file=/data.local2/s475plus_data/root/converted/s475plus_05_70Br_0246_ucesb_my.root

# turn on correct root version
. /cvmfs/csee.gsi.de/go4/503-02/go4login

if [ -z ${ROOTSYS+x} ]; then
  echo "ROOTSYS is unset. Aborting.";
  exit;
else
  echo "ROOTSYS is set to '$ROOTSYS'";
fi

root -l 'friend_trees.C('\"$frs_file\"','\"$ucesb_file\"')'
