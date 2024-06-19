#!/bin/bash

# Update package lists and install Python 3.10 and development headers
apt update
apt install -y python3.10 python3.10-dev

# Install Python pip
apt-get install -y python3-pip

# Install Python packages using pip
pip install six
pip install psutil

# Source the upmem_env.sh script (assuming it's in the current directory)
source upmem_env.sh

# Install pkg-config
apt install -y pkg-config

apt-get install -y libnuma1 libedit2 build-essential software-properties-common curl wget git libc6 libstdc++6 libgcc-9-dev libgomp1
