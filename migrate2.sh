#!/usr/bin/env bash

NAME="guest17-debian"
DEST_URI="qemu+ssh://aru2/system"

while true
do

	usage="$(awk '{u=$2+$4; t=$2+$4+$5; if (NR==1){u1=u; t1=t;} else print ($2+$4-u1) * 100 / (t-t1) ""; }' <(grep 'cpu ' /proc/stat) <(sleep 1;grep 'cpu ' /proc/stat))"

	if (( $(echo "$usage > 90" | bc -l) ))
	then
		./virt-migration "$NAME" "$DEST_URI"
		break
	fi

	echo "No migration yet"

done
