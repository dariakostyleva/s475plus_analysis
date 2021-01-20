#!/bin/bash

#INPUTFILENAME=/u/frsgast/s475plus/upexps/202003_s474s475p/rootfiles/s475plus_08_70Br_0804.root
#INPUTFILENAME=/u/frsgast/s475plus/upexps/202003_s474s475p/s475plus_08_70Br_0439.root
#INPUTFILENAME=/u/frsgast/s475plus/upexps/202003_s474s475p/s475plus_10_70Br_2132.root
INPUTFILENAME=/u/frsgast/s475plus/upexps/202003_s474s475p/s475plus_08_70Br_1009_ucesb.root
TREENAME=h101
NEVENTS=35098

OUTPUTFILENAME=$(basename "$INPUTFILENAME")
OUTPUTFILENAME="./result/"${OUTPUTFILENAME//".root"/}"_subtr.root"

if [ -z ${ROOTSYS+x} ]; then
  echo "ROOTSYS is unset. Aborting.";
  exit;
else
  echo "ROOTSYS is set to '$ROOTSYS'";
fi

BASEDIR="$PWD"

# Remove textual output if it already exists from previous analysis
if [ -d ${BASEDIR}/textoutput/ ]; then
  rm -fv ${BASEDIR}/textoutput/*
else
  mkdir ${BASEDIR}/textoutput
fi

# Remove the graph output if it already exists from previous analysis
if [ -d ${BASEDIR}/result/ ]; then
  rm -fv ${BASEDIR}/result/*
else
  mkdir ${BASEDIR}/result
fi

# Remove figures if it already exists from previous analysis
if [ -d ${BASEDIR}/figures/ ]; then
  rm -fv ${BASEDIR}/figures/*
else
  mkdir ${BASEDIR}/figures
fi


root -l -q -b 'pedAnalyse.C('\"$INPUTFILENAME\"','\"$OUTPUTFILENAME\"','\"$TREENAME\"','$NEVENTS')'

for number in 1 2 3
do

TEXTOUTFILE=${BASEDIR}/textoutput/out_${number}.txt
TEXTERRFILE=${BASEDIR}/textoutput/err_${number}.txt

#root -l -q -b 'sigma.C('\"$OUTPUTFILENAME\"','\"$TREENAME\"','$NEVENTS','$number')' & #>> TEXTOUTFILE 2> TEXTERRFILE & 
#root -l -q -b 'mean.C('\"$OUTPUTFILENAME\"','\"$TREENAME\"','$NEVENTS','$number')' & #>> TEXTOUTFILE 2> TEXTERRFILE & 
#root -l -q -b 'sigma.C('\"$INPUTFILENAME\"','\"$TREENAME\"','$NEVENTS','$number')' & #>> TEXTOUTFILE 2> TEXTERRFILE & 
#root -l -q -b 'mean.C('\"$INPUTFILENAME\"','\"$TREENAME\"','$NEVENTS','$number')' & #>> TEXTOUTFILE 2> TEXTERRFILE &

done

wait
#root -l 'drawResults.C('\"$OUTPUTFILENAME\"','\"$TREENAME\"','$NEVENTS')'
#root -l 'drawResults.C('\"$INPUTFILENAME\"','\"$TREENAME\"','$NEVENTS')'
