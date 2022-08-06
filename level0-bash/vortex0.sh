#!/bin/bash

hexadd() {
    echo "obase=16;ibase=16;$1+$2" | bc
}

host=vortex.labs.overthewire.org
port=5842
exec 3<>/dev/tcp/$host/$port


sum=$((0))

for ((i=0;i<4;i++))
do
  recv=$(dd  bs=4 count=1 <&3 2> /dev/null)
  echo "received: $recv (size: ${#recv})"
  recv=`echo -ne $recv | xxd -u -p`
  echo "orig. endianness: $recv (size: ${#recv})"
  recv=`echo -ne $recv | ./endian.sh`
  sum=`hexadd $sum $recv`
  echo "sum $sum (size: ${#sum})"
  echo "endian changed: $recv (size: ${#recv})"
done
sum=`echo -ne $sum | tr [:upper:] [:lower:]| ./endian.sh`
echo " final sum: $sum (size: ${#sum})"
echo "now binpack sum again:"
sum=`echo -ne $sum | xxd -r -p`
echo "packed sum: $sum (size: ${#sum})"

echo -ne "$sum" >&3
RESPONSE=$(dd bs=100 count=1 <&3 2> /dev/null)
echo "RESPONSE: $RESPONSE"
