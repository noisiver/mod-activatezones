#!/usr/bin/env bash
MOD_ACTIVATEZONES_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )/" && pwd )"

source $MOD_ACTIVATEZONES_ROOT"/conf/conf.sh.dist"

if [ -f $MOD_ACTIVATEZONES_ROOT"/conf/conf.sh" ]; then
    source $MOD_ACTIVATEZONES_ROOT"/conf/conf.sh"
fi
