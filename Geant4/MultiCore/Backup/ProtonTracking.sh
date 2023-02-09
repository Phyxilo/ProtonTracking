#!/bin/bash

#loopCnt=5
maxLT=8

#minSegPos=-10000
#maxSegPos=10000

loopCnt=1
minSegPos=-1000
maxSegPos=1000
interval=2000

plateDist=$((5885-175))
#slope=0.0887978
slope=0

transArea=$(echo "$slope*$plateDist" | bc)
transArea=${transArea%.*}

posDif=$(($maxSegPos-$minSegPos))

#interval=$(($posDif/$loopCnt))
totInt=$(($interval+$transArea))

cnt=0

start=$SECONDS

runRoot () {

    yMin=$(($midY-$interval/2-$transArea))
    yMax=$(($midY+$interval/2+$transArea))

    xMin=$(( $xMin+$interval*($j-1) ))
    xMax=$(( $xMax+$interval*($j-1) ))

    #echo "xMin: " $xMin ", xMax: " $xMax
    #echo "yMin: " $yMin ", yMax: " $yMax

    root -l -b -q 'ProtonTracking.C('$maxLT', '$xMin', '$xMax', '$yMin', '$yMax', '$cnt')'
}

midY=$(($minSegPos+$interval/2))

for i in $(seq $loopCnt);
do
    midX=$(($minSegPos+$interval/2))

    xMin=$(echo "$midX-$interval/2-$transArea" | bc)
    xMax=$(echo "$midX+$interval/2+$transArea" | bc)

    for j in $(seq $loopCnt); 
    do
        runRoot $j &
        cnt=$(($cnt+1))
    done

    midY=$(($midY+$interval))
    #echo "--------------------------"
    wait
done

wait
cd Output
mkdir Merged

for i in $(seq 0 $(($maxLT-1)) );
do
    cat connectedDS_0"$i"_Z* > connectedDS_0"$i".dat
    cat connectedUS_0"$i"_Z* > connectedUS_0"$i".dat

    mv connectedDS_0"$i".dat Merged/connectedDS_0"$i".dat
    mv connectedUS_0"$i".dat Merged/connectedUS_0"$i".dat
done

duration=$((SECONDS-start))

echo "Completed in $duration seconds"