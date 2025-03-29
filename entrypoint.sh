#!/bin/sh
case "$1" in
    sup2disk)
        shift
        exec /app/sup2disk "$@"
        ;;
    sup2srt)
        shift
        exec /app/sup2srt "$@"
        ;;
    *)
        exec /app/sup2srt "$@"
        ;;
esac