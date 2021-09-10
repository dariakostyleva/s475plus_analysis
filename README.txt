Steps to analyse data from EXPERT experiment in March 2020

1. Decide which .lmd files come together, i.e. create .lml
2. FRS part: convert files using go4
3. DSSD part: convert files using ucesb
4. (Optional, can be performed later) Subtract pedestals from DSSD files
5. Friend two .root files (FRS data and DSSD data) with bash script with sh run_friend_trees.sh 
6. Start analyzing 

In more detail:
1. See table with files in list_of_files.ods

2. FRS data should be converted with the correct root and go4 versions, namely
/cvmfs/csee.gsi.de/go4/600-00/bin/go4
/cvmfs/csee.gsi.de/root/618-04/bin/root
. /cvmfs/csee.gsi.de/go4/600-00/go4login
Code is from /u/profi/NewGo4_2020/s474_s475
I use copy locally at /u/dkostyl/experiment_march_2020/s475plus_analysis !check setup file!
To unpack several files:
go4analysis -lib libGo4UserAnalysis.so -file /data.local2/s475plus_data/lmd/s475plus_70Br_246-298.lml -disable-asf -step Analysis -enable-store -store /data.local2/s475plus_data/root/converted/s475plus_70Br_246-298_frs.root

3. ucesb requires correct file sidped_daq.txt for unpacking (correct means the one used while compressing the data). This file sidped_daq.txt is the same as sidped.txt, which is saved in ./sid_files_daq/ along with others used for compressing during experiment. ucesb should be compiled with the correct version of sidped_daq.txt file!!! The latter is done at dkostyl user in 
~/LOS_synch/upexps/202003_s474s475p/
Version of root needed is invoked by r3broot alias.
To unpack several files:
./202003_s474s475p \
$(cat /data.local2/s475plus_data/lmd/s475plus_70Br_246-298.lml) \
--ntuple=RAW,/data.local2/s475plus_data/root/converted/s475plus_70Br_246-298_ucesb.root

4. Subtraction of pedestals in done using macros from ./scripts_subtr_pedest 

5. Specify the names of two converted files in run_friend_trees.sh file, run it. The actual macro for analysis is friend_trees.C , it is self-explaining

Note: pedestal files are unpacked with ~/experiment_march_2020/go4_siderem_frs code with root6 and go4 5 