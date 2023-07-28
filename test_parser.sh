#! /bin/bash

if [[ $1 ]] && [[ $1 == "-r" ]]; then
	make -s re
	if [[ $? != 0 ]]; then exit; fi;
fi

execute_test()
{
	local TESTPID=-1
	local TESTFILE=$1
	local TESTNAME=${TESTFILE:10:$(expr ${#TESTFILE} - 14)}

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

echo Testing Texture Parser
for MAP in $(echo $(find maps -type f -name 'test_invalid_texture*.cub') \
| xargs -n1 | sort | xargs)
do
	execute_test $MAP
done

echo Testing RGB Parser
for MAP in $(echo $(find maps -type f -name 'test_invalid_rgb*.cub') \
| xargs -n1 | sort | xargs)
do
	execute_test $MAP
done

echo Testing Map Tile Parser
for MAP in $(echo $(find maps -type f -name 'test_invalid_tiles*.cub') \
| xargs -n1 | sort | xargs)
do
	execute_test $MAP
done

rm -rf tester.log
