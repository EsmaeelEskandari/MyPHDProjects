#! /bin/csh

#svn co -N svn+ssh://svn.cern.ch/reps/tdr2 myDir
#cd myDir
#svn update utils
#svn update -N notes
#svn update notes/AN-13-357
eval `../../tdr runtime -csh`
#cd notes/AN-13-357/trunk
tdr --verbose --style=an b AN-13-357

#svn add NewFileNames
#svn commit -m "commit message"





 
