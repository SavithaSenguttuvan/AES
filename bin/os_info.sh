#!/bin/bash

echo "OS type "
echo $'\t'
uname -s
echo $'\n'	
echo "Operating System Distribution "	
echo $'\t'	
lsb_release -i
echo $'\n'
echo "Kernel Version "	
echo $'\t'		
uname -r
echo $'\n'
echo "Information on the kernel build "
echo $'\t'			
cat /proc/version 
echo $'\n'
echo "Kernel gcc version build "
echo $'\t'			
cat /proc/version | cut -d'(' -f3
echo $'\n'
echo "Kernel build time "
echo $'\t'	
uname -v	
echo $'\n'
echo "System Architecture information "
echo $'\t'
uname -m		
echo $'\n'