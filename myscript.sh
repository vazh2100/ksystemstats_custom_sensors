#!/bin/bash
while true; do
    /usr/bin/ryzenadj -i | awk -F'|' '
    NR == 7  && /STAPM LIMIT/     { print $3+0 > "/tmp/STAPM_LIMIT"; next }
    NR == 8  && /STAPM VALUE/     { print $3+0 > "/tmp/STAMP_VALUE"; next }
    NR == 9  && /PPT LIMIT FAST/  { print $3+0 > "/tmp/FAST_LIMIT";  next }
    NR == 10 && /PPT VALUE FAST/  { print $3+0 > "/tmp/FAST_VALUE";  next }
    NR == 11 && /PPT LIMIT SLOW/  { print $3+0 > "/tmp/SLOW_LIMIT";  next }
    NR == 12 && /PPT VALUE SLOW/  { print $3+0 > "/tmp/SLOW_VALUE";  next }
    NR == 26 && /THM VALUE CORE/  { print $3+0 > "/tmp/CPU_THM";     next }
    NR == 28 && /STT VALUE APU/   { print $3+0 > "/tmp/CPU_SKIN";    next }
    '
    sleep 5
done
