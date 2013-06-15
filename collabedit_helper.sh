#!/bin/bash
# by Robert Oliveira

BASEDIR=$(dirname $0)
SUFIX=".py"
CODE=${BASEDIR}/code${SUFIX}
INPUT=${BASEDIR}/input.txt
OUTPUT=${BASEDIR}/output.txt
TEMP=/tmp/$$

URL=$1
if [ -z "$URL" ]; then 
	cat <<EOF
Usage: $(basename $0) <collabedit download link>
EOF
    exit 1
fi

touch "$CODE"
touch "$INPUT"

trap "rm -rf $TEMP"  SIGKILL SIGTERM

get_sufix() {
	if (! grep -q -E '^\s*def\s+\w+\(\s*(\S+\s*,?\s*)*\s*\)\s*:' "$TEMP" && 
	    ! grep -q -E '^\s*class\s+\w+\(\s*(\S+\s*,?\s*)*\s*\)\s*:' "$TEMP" ) ||
	   grep -q -E '^#include' "$TEMP" ||
	   grep -q -E '^int\s*main\s*\(' "$TEMP" 
    then 
		echo ".cpp"
	else
		echo ".py"
	fi
}
    

while : ; do 
	curl -s "$URL" >$TEMP &
    curl_pid=$!
	sleep 2; kill $curl_pid &>/dev/null &
	wait
	SUFIX=$(get_sufix)
	CODE=${BASEDIR}/code${SUFIX}
	if ! diff "$TEMP" "$CODE" &>/dev/null; then
		mv "$TEMP" "$CODE"
		echo -e "\n\n*** CHANGED: $CODE\n"

		case $SUFIX in
   			".py")
				pylint "$CODE" | tee >"$CODE.check"
				if python "$CODE" < "$INPUT" | tee > "$OUTPUT"; then
					head -n 30 "$OUTPUT"
				fi
				;;
			".cpp")
				cppcheck "$CODE" | tee "$CODE.check"
				if g++ -o code -Wall "$CODE" | tee "$CODE.log"; then
					if ./$(basename "$CODE" "$SUFIX") < "$INPUT" | tee > "$OUTPUT"; then
						head -n 30 "$OUTPUT"
					fi
				fi
				;;
		esac
	fi
	sleep 2
done
