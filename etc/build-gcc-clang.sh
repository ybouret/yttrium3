#!/bin/sh
ninja -C build-clang rebuild_cache && ninja -C build-clang && \
ninja -C build-gcc   rebuild_cache && ninja -C build-gcc   && \
echo "-- Installing from clang" && \
(ninja -C build-clang install &> /dev/null)
