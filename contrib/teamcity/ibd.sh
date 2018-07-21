#!/bin/bash

set -euo pipefail

###
# Initial Block Download script.
# 
# Runs a lyokocoind process until initial block download is complete.
# Forwards the exit code from lyokocoind onward.
#

MYPID=$$

# Setup
mkdir -p ibd
touch ibd/debug.log
chmod +x lyokocoind

cleanup() {
    echo "Terminating (pid: ${1})"
    pkill -P ${MYPID} tail || true
}

# Launch lyokocoind
./lyokocoind -datadir=ibd -disablewallet &
lyokocoin_pid=$!

trap "cleanup ${lyokocoin_pid}" EXIT

# Wait for IBD to finish and kill the daemon
( 
    set +o pipefail
    tail -f ibd/debug.log | grep -m 1 'progress=1.000000'
    echo "Initial block download complete, killing lyokocoin daemon."
    kill ${lyokocoin_pid}
) &

# Show some progress 
tail -f ibd/debug.log | grep 'UpdateTip' | awk 'NR % 10000 == 0' &

# Wait for lyokocoind to exit
wait ${lyokocoin_pid}
exit $?
