#!/bin/bash

#runNumber='12545 12556 12558 12560 12601 12638 12598 12514 12518 12521 12600 12636 12539 12628 12512 12526 12567 12633 12591 12612 12530 12528 12569 12639 12610 12609 12607 12604 12602'
runNumber='12567 12633 12591 12612 12530 12528 12569 12639 12610 12609 12607 12604 12602'

for i in $runNumber
  do
    echo ""
    echo "Processing Run ${i}..."

    #echo "dqm4hep-start-module -f /lustre/scratch/epp/ilc/tc297/DQM4HEP/forks/dqm4hep-dream/equalisation/steering-${i}.xml"
    dqm4hep-start-module -f /lustre/scratch/epp/ilc/tc297/DQM4HEP/forks/dqm4hep-dream/equalisation/steering-${i}.xml

    echo "---   ---   ---   ---   ---   ---"

done