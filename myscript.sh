#!/bin/bash
while true; do
    INFO=$(/usr/bin/ryzenadj -i)
    SKIN_TEMP=$(echo "$INFO" | grep "STT VALUE APU" | cut -d '|' -f3 | tr -d ' ')
    THM_CORE=$(echo "$INFO" | grep "THM VALUE CORE" | cut -d '|' -f3 | tr -d ' ')
    echo "$SKIN_TEMP" > /tmp/custom_sensor_1.txt
    echo "$THM_CORE" > /tmp/custom_sensor_2.txt
    sleep 2
done
