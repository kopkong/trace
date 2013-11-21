#!/bin/bash

sshpass -p "nvidia" scp build/apitrace root@10.19.226.114:/root
sshpass -p "nvidia" scp build/eglretrace root@10.19.226.114:/root
