#! /bin/bash

if [[ $1 ]] && [[ $1 == "-r" ]]; then
	make -s re
	if [[ $? != 0 ]]; then exit; fi;
fi

execute_test()
{
	local TESTPID=-1
	local TESTFILE=$1
	local TESTNAME=${TESTFILE:$2:$(expr ${#TESTFILE} - $(expr $2 + $3))}

	printf " $TESTNAME..."
	if [ ${#TESTNAME} -lt 20 ]; then
		printf "\t\t\t\t"
	elif [ ${#TESTNAME} -lt 28 ]; then
		printf "\t\t\t"
	elif [ ${#TESTNAME} -lt 36 ]; then
		printf "\t\t"
	else
		printf "\t"
	fi
	./cub3d $TESTFILE 2> tester.log & TESTPID=$!
	sleep 0.5
	local PIDLIST=$(ps | grep '[c]ub3d' | awk '{print $1}')
	printf "Test PID: $TESTPID\t\t"
	if [[ $PIDLIST ]]; then
		for PID in $PIDLIST; do
			if [[ $PID -eq $TESTPID ]]; then
				kill -9 $PID
				wait $PID 2>/dev/null
				printf "[$PID: \e[0;91mKILL_FAIL!\e[0m]\n"
				return
			fi
		done
	fi
	local RESULT=$(grep 'Error' tester.log)
	if [ $RESULT ]; then
		printf "[\e[0;92mPASS!\e[0m]\n"
	else
		printf "[\e[0;91mFAIL!\e[0m]\n"
	fi
}

SUFFIX=".cub"
echo Testing Texture Parser
PREFIX="test_texture_"
for MAP in $(echo $(find maps -type f -name "$PREFIX*.cub") \
| xargs -n1 | sort | xargs)
do
	PREFIX="maps/test_texture_"
	execute_test $MAP ${#PREFIX} ${#SUFFIX}
done

echo Testing RGB Parser
PREFIX="test_rgb_"
for MAP in $(echo $(find maps -type f -name "$PREFIX*.cub") \
| xargs -n1 | sort | xargs)
do
	PREFIX="maps/test_rgb_"
	execute_test $MAP ${#PREFIX} ${#SUFFIX}
done

echo Testing Map Tile Parser
PREFIX="test_tiles_"
for MAP in $(echo $(find maps -type f -name "$PREFIX*.cub") \
| xargs -n1 | sort | xargs)
do
	PREFIX="maps/test_tiles_"
	execute_test $MAP ${#PREFIX} ${#SUFFIX}
done

rm -rf tester.log
