#!/bin/bash

set -bm

startjob(){
root -l run_ZInvEstFromW.C
}
# {
#  if [ $count -lt $total_jobs ]; then
#    ./countandcombine.py $count $x1 $x2 > ".out_$count" &
#   count=$(($count+1))
#  fi
#}


#######
START=$(date +%s.%N)

max_parallel=70
#total_jobs=900

#x1=150
#x2=800

#./countandcombine.py $x1 0

trap 'startjob' SIGCHLD

#count=1
started=0
while [ $started -lt $max_parallel ]; do
  startjob
  started=$(($started+1))
done

wait


#######
END=$(date +%s.%N)
DIFF=$(echo "$END - $START" | bc)
echo ""
