#!/bin/bash

runNumber='12659 12664 12677 12672 12671 12670 12669 12667'

for i in $runNumber
  do
    echo ""
    echo "Processing Run ${i}..."

    #echo "dqm4hep-start-module -f /lustre/scratch/epp/ilc/tc297/DQM4HEP/forks/dqm4hep-dream/equalisation/steering-${i}.xml"
    dqm4hep-start-module -f /lustre/scratch/epp/ilc/tc297/DQM4HEP/forks/dqm4hep-dream/equalisation/steering-${i}.xml

    echo "---   ---   ---   ---   ---   ---"

done