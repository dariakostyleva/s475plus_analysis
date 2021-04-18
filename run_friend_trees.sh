#!/bin/bash

# paths to files with FRS detectors data and with DSSD data
frs_file=/data.local2/s475plus_data/root/converted/s475plus_70Br_246-298_frs.root
ucesb_file=/data.local2/s475plus_data/root/converted/s475plus_70Br_246-298_ucesb.root
out_file=/data.local2/s475plus_data/root/converted/s475plus_70Br_246-298_out.root

# turn on correct root version
. /cvmfs/csee.gsi.de/go4/503-02/go4login

if [ -z ${ROOTSYS+x} ]; then
  echo "ROOTSYS is unset. Aborting.";
  exit;
else
  echo "ROOTSYS is set to '$ROOTSYS'";
fi

root -l -q 'friend_trees.C('\"$frs_file\"','\"$ucesb_file\"','\"$out_file\"')'
