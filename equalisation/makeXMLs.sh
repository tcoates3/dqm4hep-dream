#!/bin/bash

#runNumber=12070
runNumber='12545 12556 12558 12560 12601 12638 12598 12514 12518 12521 12600 12636 12539 12628 12512 12526 12567 12633 12591 12612 12530 12528 12569 12639 12610 12609 12607 12604 12602 12659 12664 12677 12672 12671 12670 12669 12667'


for i in $runNumber
  do
    sed "s!datafile_ntup_runXXXXX.root!datafile_ntup_run${i}.root!" /lustre/scratch/epp/ilc/tc297/DQM4HEP/forks/dqm4hep-dream/equalisation/eq_template.xml | tee /lustre/scratch/epp/ilc/tc297/DQM4HEP/forks/dqm4hep-dream/equalisation/steering-temp.xml
    sed "s!archive-XXXXX.root!archive-${i}.root!" /lustre/scratch/epp/ilc/tc297/DQM4HEP/forks/dqm4hep-dream/equalisation/steering-temp.xml | tee /lustre/scratch/epp/ilc/tc297/DQM4HEP/forks/dqm4hep-dream/equalisation/steering-${i}.xml
done