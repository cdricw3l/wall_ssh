#!/usr/bin/bash

#uname -a for getting all information about architecture

ARCH=$(uname -a | cut -d " " -f1,2,3,4,5,7,8,11,12,15)

#lscpu for getting cpu informations
PCPU=$(lscpu | grep Socket | wc -l)


VCPU=$(cat /proc/cpuinfo | grep processor | wc -l)

#free for memory ram data
RAM_TOTAL=$(free -m |  awk 'NR == 2 {print $2}')
RAM_USED=$(free -m |  awk 'NR == 2 {print $3}')
RAM_RATIO=$(($RAM_USED * 100))
TOTAL_RATIO=$(($RAM_RATIO /  $RAM_TOTAL))


#df for available storage
DF_USED=$(df -BM  | awk ' NR > 1 {sum  += $3} END {print sum}')
DF_TOTAL=$(df -h --total | awk 'END {print $2}' | tr -d "G")
DF_RATIO=$(df -h --total | awk 'END {print $5}')


LAST_BOOT=$(who -b | awk '{print $3" "$4}')

if [ $(lsblk | grep lvm | wc -l) -gt 0 ]; then
	LVM=yes
else
	LVM=no
fi

TCP=$(lsof |  grep ESTABLISHED | wc -l)
USER_LOG=$(who | cut -d ' ' -f1  | uniq | wc -l) 
IP=$(ip addr show enp0s3  |  grep -w inet | awk ' {print $2}' | cut -d '/' -f 1) 
MAC=$(ip addr show enp0s3  |  grep ether | awk ' {print $2}') 
SUDO=$(cat /var/log/sudo/sudo.log | grep COMMAND |  wc -l)

CPU_USE=$(mpstat | awk 'NR==4 {sum += $4; sum += $5;sum += $6; sum += $7; sum += $9; sum += $9; sum += $10; sum += $11; sum += $12} END {print sum}')

echo "#Architecture: "$ARCH
echo "#Physical CPU: "$PCPU
echo "#vCPU: $VCPU"
echo "#Memory Usage: " $RAM_USED'/'$RAM_TOTAL'MB('$TOTAL_RATIO'%)'
echo "#Disk Usage: "$DF_USED'/'$DF_TOTAL'Gi ('$DF_RATIO')'
echo "#CPU load: $CPU_USE%"
echo "#Last boot: $LAST_BOOT"
echo "#LVM use:$LVM"
echo "#TCP Connections: $TCP"
echo "#User log: $USER_LOG"
echo "#Network: IP $IP $MAC"  
echo "#Sudo : $SUDO"



