#!/bin/bash

# Request superuser if is not running script as superuser
if [[ "${EUID}" -ne 0 ]]; then
	echo "Not running script as root, escalating."
	exec sudo "$0" "$@"
	end
fi

# Clean up the testcase files and results files before testing
echo "Cleaning up the testcase files and results files before testing."
rm -rf ./testcases/*
rm -rf ./results/*

# List of all the services need to be disabled
services_name=("lightdm" "NetworkManager" "ModemManager" "packagekit" "polkit" "docker" "containerd" "mariadb" "systemd-oomd" "tailscaled" "waydroid-container" "teamviewerd" "php-fpm" "figma-agent" "fwupd" "firewalld")

# Switch off all of the unnecessary services for the benchmark

for service in "${services_name[@]}"; do
	echo "Killing ${service}."
	sudo systemctl stop "${service}"
done

systemctl --user stop pipewire pipewire-pulse

# Compile and start the benchmark
echo "Compiling the benchmark."
mkdir -p "./build"
if cmake --build ./build --target all -j 18 --config MinSizeRel -- ; then
	echo "Starting benchmark."
	./benchmark_sorting_algos
else
	echo "Compile error. Exiting script."
fi