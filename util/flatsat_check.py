# Author: Ned Flanders
# Arguments-drive_name: Flash drive name to print information from

import os
import sys
import struct

# if sys.argv[1] == 'slc':
#     drive = '/mnt/slc_drive/'
#     type = 'slc'
# elif sys.argv[1] == 'mlc1':
#     drive = '/mnt/mlc1_drive/'
#     type = 'mlc'
# elif sys.argv[1] == 'mlc2':
#     drive = '/mnt/mlc2_drive/'
#     type = 'mlc'

# DEBUG
drive = ''
type = 'slc'
offset = 8240

spectrum = []
with open(drive + 'datafile','rb') as f:
    f.seek(-offset,os.SEEK_END)
    timestamp = struct.unpack('I',f.read(4))
    for i in range(0,2048):
        spectrum.append(struct.unpack('f',f.read(4)))
    spec_temp = struct.unpack('f',f.read(4))
    rpi_temp = struct.unpack('f',f.read(4))
    hk_temp_bat1 = struct.unpack('f',f.read(4))
    hk_temp_bat2 = struct.unpack('f',f.read(4))
    hk_temp_slc = struct.unpack('f',f.read(4))
    env_temp = struct.unpack('f',f.read(4))
    env_hum = struct.unpack('f',f.read(4))
    ads1 = struct.unpack('f',f.read(4))
    ads2 = struct.unpack('f',f.read(4))
    ads3 = struct.unpack('f',f.read(4))
    ads4 = struct.unpack('f',f.read(4))

data_format = """Drive: {0}
Timestamp: {1}
ENV Hum: {2} %; ENV Temp: {3} C;
HK Temp SLC: {4} C;  HK Temp Bat1: {5} C;  HK Temp Bat2:{6} C
Spec Temp: {7} C; RPi Temp: {8} C; Spec: {9}
ADS1: {10} A; ADS2: {11} A; ADS3: {12} A; ADS4: {13} A; """

print(data_format.format(drive,
                         timestamp,
                         env_hum,
                         env_temp,
                         hk_temp_slc,
                         hk_temp_bat1,
                         hk_temp_bat2,
                         spec_temp,
                         rpi_temp,
                         spectrum[0],
                         ads1,
                         ads2,
                         ads3,
                         ads4))
                    
