#!/bin/bash

dependencies=(
  build-essential
  libarmadillo-dev
  libboost-python-dev
  libflann-dev
  python-numpy)

function package_exists() {
  dpkg -l $1 > /dev/null 2>&1
  INSTALLED=$?
  if [ $INSTALLED == '0' ]; then
      return 0 #echo "installed"
  else
      return 1 # not installed
  fi
}

for i in ${dependencies[@]}
do
    if ! package_exists $i; then
       echo -e "$i    \e[31mmissing\033[0m"
       apt-get install $i
    else
       echo -e "$i    \e[32mfound\033[0m"
    fi
 done
