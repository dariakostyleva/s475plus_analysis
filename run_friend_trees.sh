#!/bin/bash

# paths to files with FRS detectors data and with DSSD data
frs_file=/data.local2/s475plus_data/root/converted/s475plus_05_70Br_0299_frs.root
ucesb_file=/data.local2/s475plus_data/root/converted/s475plus_05_70Br_0299_ucesb.root
out_file=/data.local2/s475plus_data/root/converted/s475plus_05_70Br_0299_out.root

# turn on correct root version
. /cvmfs/csee.gsi.de/go4/503-02/go4login

if [ -z ${ROOTSYS+x} ]; then
  echo "ROOTSYS is unset. Aborting.";
  exit;
else
  echo "ROOTSYS is set to '$ROOTSYS'";
fi

root -l -q 'friend_trees.C('\"$frs_file\"','\"$ucesb_file\"','\"$out_file\"')'

echo "Shall I also analyse? (y/n)" 
read answer
if [ "$answer" = "y" ]; then
  echo "Analysis is being done";
  root -l 'analyze_friend_trees.C('\"$out_file\"')'
else 
  echo "No analysis, I am free!";
fi