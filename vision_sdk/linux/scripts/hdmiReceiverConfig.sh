#!/bin/sh

#ADV configuration taken from BSP,
# it enables hdmi receiver

function ADVConfig
{
    echo "The Vision App Board is with ADV7611,
    Configuring HDMI Receiver for ADV7611"

    echo "Configuration in progress ... "
    msleep 10; i2cset -f -y 1 0x4c 0x15 0xbe
    msleep 10; i2cset -f -y 1 0x4c 0x0b 0x44
    msleep 10; i2cset -f -y 1 0x4c 0x0c 0x42
    msleep 10; i2cset -f -y 1 0x4c 0xff 0x01
    msleep 10; i2cset -f -y 1 0x4c 0xf4 0x80
    msleep 10; i2cset -f -y 1 0x4c 0xf5 0x7c
    msleep 10; i2cset -f -y 1 0x4c 0xf8 0xaa
    msleep 10; i2cset -f -y 1 0x4c 0xf9 0xac
    msleep 10; i2cset -f -y 1 0x4c 0xfa 0xae
    msleep 10; i2cset -f -y 1 0x4c 0xfb 0x68
    msleep 10; i2cset -f -y 1 0x4c 0xfd 0x44
    msleep 10; i2cset -f -y 1 0x4c 0x1b 0x01
    msleep 10; i2cset -f -y 1 0x34 0x48 0x40
    msleep 10; i2cset -f -y 1 0x34 0x15 0xbe
    msleep 10; i2cset -f -y 1 0x34 0x83 0xff
    msleep 10; i2cset -f -y 1 0x22 0x6c 0x00
    msleep 10; i2cset -f -y 1 0x34 0x9b 0x03
    msleep 10; i2cset -f -y 1 0x34 0x6f 0x0c
    msleep 10; i2cset -f -y 1 0x34 0x87 0x70
    msleep 10; i2cset -f -y 1 0x34 0x03 0x98
    msleep 10; i2cset -f -y 1 0x34 0x4c 0x44
    msleep 10; i2cset -f -y 1 0x22 0x3e 0x00
    msleep 10; i2cset -f -y 1 0x22 0x40 0x80
    msleep 10; i2cset -f -y 1 0x34 0x83 0xfe
    msleep 10; i2cset -f -y 1 0x4c 0x01 0x06
    msleep 10; i2cset -f -y 1 0x4c 0x00 0x02
    msleep 10; i2cset -f -y 1 0x4c 0x0c 0x42
    msleep 10; i2cset -f -y 1 0x4c 0x14 0x7f
    msleep 10; i2cset -f -y 1 0x4c 0x19 0x83
    msleep 10; i2cset -f -y 1 0x4c 0x33 0x40
    msleep 10; i2cset -f -y 1 0x22 0x69 0x14
    msleep 10; i2cset -f -y 1 0x34 0x6c 0xa0
    msleep 10; i2cset -f -y 1 0x57 0x00 0x00
    msleep 10; i2cset -f -y 1 0x57 0x01 0xff
    msleep 10; i2cset -f -y 1 0x57 0x02 0xff
    msleep 10; i2cset -f -y 1 0x57 0x03 0xff
    msleep 10; i2cset -f -y 1 0x57 0x04 0xff
    msleep 10; i2cset -f -y 1 0x57 0x05 0xff
    msleep 10; i2cset -f -y 1 0x57 0x06 0xff
    msleep 10; i2cset -f -y 1 0x57 0x07 0x00
    msleep 10; i2cset -f -y 1 0x57 0x08 0x4d
    msleep 10; i2cset -f -y 1 0x57 0x09 0x29
    msleep 10; i2cset -f -y 1 0x57 0x0a 0x09
    msleep 10; i2cset -f -y 1 0x57 0x0b 0x05
    msleep 10; i2cset -f -y 1 0x57 0x0c 0x0a
    msleep 10; i2cset -f -y 1 0x57 0x0d 0x00
    msleep 10; i2cset -f -y 1 0x57 0x0e 0x00
    msleep 10; i2cset -f -y 1 0x57 0x0f 0x00
    msleep 10; i2cset -f -y 1 0x57 0x10 0x1a
    msleep 10; i2cset -f -y 1 0x57 0x11 0x14
    msleep 10; i2cset -f -y 1 0x57 0x12 0x01
    msleep 10; i2cset -f -y 1 0x57 0x13 0x03
    msleep 10; i2cset -f -y 1 0x57 0x14 0x80
    msleep 10; i2cset -f -y 1 0x57 0x15 0x52
    msleep 10; i2cset -f -y 1 0x57 0x16 0x2e
    msleep 10; i2cset -f -y 1 0x57 0x17 0x78
    msleep 10; i2cset -f -y 1 0x57 0x18 0x2a
    msleep 10; i2cset -f -y 1 0x57 0x19 0x1b
    msleep 10; i2cset -f -y 1 0x57 0x1a 0xbe
    msleep 10; i2cset -f -y 1 0x57 0x1b 0xa2
    msleep 10; i2cset -f -y 1 0x57 0x1c 0x55
    msleep 10; i2cset -f -y 1 0x57 0x1d 0x34
    msleep 10; i2cset -f -y 1 0x57 0x1e 0xb3
    msleep 10; i2cset -f -y 1 0x57 0x1f 0x26
    msleep 10; i2cset -f -y 1 0x57 0x20 0x14
    msleep 10; i2cset -f -y 1 0x57 0x21 0x4a
    msleep 10; i2cset -f -y 1 0x57 0x22 0x52
    msleep 10; i2cset -f -y 1 0x57 0x23 0xaf
    msleep 10; i2cset -f -y 1 0x57 0x24 0xce
    msleep 10; i2cset -f -y 1 0x57 0x25 0x00
    msleep 10; i2cset -f -y 1 0x57 0x26 0x81
    msleep 10; i2cset -f -y 1 0x57 0x27 0x80
    msleep 10; i2cset -f -y 1 0x57 0x28 0x90
    msleep 10; i2cset -f -y 1 0x57 0x29 0x40
    msleep 10; i2cset -f -y 1 0x57 0x2a 0x01
    msleep 10; i2cset -f -y 1 0x57 0x2b 0x01
    msleep 10; i2cset -f -y 1 0x57 0x2c 0x01
    msleep 10; i2cset -f -y 1 0x57 0x2d 0x01
    msleep 10; i2cset -f -y 1 0x57 0x2e 0x01
    msleep 10; i2cset -f -y 1 0x57 0x2f 0x01
    msleep 10; i2cset -f -y 1 0x57 0x30 0x01
    msleep 10; i2cset -f -y 1 0x57 0x31 0x01
    msleep 10; i2cset -f -y 1 0x57 0x32 0x01
    msleep 10; i2cset -f -y 1 0x57 0x33 0x01
    msleep 10; i2cset -f -y 1 0x57 0x34 0x01
    msleep 10; i2cset -f -y 1 0x57 0x35 0x01
    msleep 10; i2cset -f -y 1 0x57 0x36 0x02
    msleep 10; i2cset -f -y 1 0x57 0x37 0x3a
    msleep 10; i2cset -f -y 1 0x57 0x38 0x80
    msleep 10; i2cset -f -y 1 0x57 0x39 0x18
    msleep 10; i2cset -f -y 1 0x57 0x3a 0x71
    msleep 10; i2cset -f -y 1 0x57 0x3b 0x38
    msleep 10; i2cset -f -y 1 0x57 0x3c 0x2d
    msleep 10; i2cset -f -y 1 0x57 0x3d 0x40
    msleep 10; i2cset -f -y 1 0x57 0x3e 0x58
    msleep 10; i2cset -f -y 1 0x57 0x3f 0x2c
    msleep 10; i2cset -f -y 1 0x57 0x40 0x45
    msleep 10; i2cset -f -y 1 0x57 0x41 0x00
    msleep 10; i2cset -f -y 1 0x57 0x42 0x34
    msleep 10; i2cset -f -y 1 0x57 0x43 0xcd
    msleep 10; i2cset -f -y 1 0x57 0x44 0x31
    msleep 10; i2cset -f -y 1 0x57 0x45 0x00
    msleep 10; i2cset -f -y 1 0x57 0x46 0x00
    msleep 10; i2cset -f -y 1 0x57 0x47 0x1e
    msleep 10; i2cset -f -y 1 0x57 0x48 0x66
    msleep 10; i2cset -f -y 1 0x57 0x49 0x21
    msleep 10; i2cset -f -y 1 0x57 0x4a 0x50
    msleep 10; i2cset -f -y 1 0x57 0x4b 0xb0
    msleep 10; i2cset -f -y 1 0x57 0x4c 0x51
    msleep 10; i2cset -f -y 1 0x57 0x4d 0x00
    msleep 10; i2cset -f -y 1 0x57 0x4e 0x1b
    msleep 10; i2cset -f -y 1 0x57 0x4f 0x30
    msleep 10; i2cset -f -y 1 0x57 0x50 0x40
    msleep 10; i2cset -f -y 1 0x57 0x51 0x70
    msleep 10; i2cset -f -y 1 0x57 0x52 0x36
    msleep 10; i2cset -f -y 1 0x57 0x53 0x00
    msleep 10; i2cset -f -y 1 0x57 0x54 0x00
    msleep 10; i2cset -f -y 1 0x57 0x55 0x00
    msleep 10; i2cset -f -y 1 0x57 0x56 0x00
    msleep 10; i2cset -f -y 1 0x57 0x57 0x00
    msleep 10; i2cset -f -y 1 0x57 0x58 0x00
    msleep 10; i2cset -f -y 1 0x57 0x59 0x1e
    msleep 10; i2cset -f -y 1 0x57 0x5a 0x00
    msleep 10; i2cset -f -y 1 0x57 0x5b 0x00
    msleep 10; i2cset -f -y 1 0x57 0x5c 0x00
    msleep 10; i2cset -f -y 1 0x57 0x5d 0xfc
    msleep 10; i2cset -f -y 1 0x57 0x5e 0x00
    msleep 10; i2cset -f -y 1 0x57 0x5f 0x48
    msleep 10; i2cset -f -y 1 0x57 0x60 0x44
    msleep 10; i2cset -f -y 1 0x57 0x61 0x4d
    msleep 10; i2cset -f -y 1 0x57 0x62 0x49
    msleep 10; i2cset -f -y 1 0x57 0x63 0x0a
    msleep 10; i2cset -f -y 1 0x57 0x64 0x0a
    msleep 10; i2cset -f -y 1 0x57 0x65 0x0a
    msleep 10; i2cset -f -y 1 0x57 0x66 0x0a
    msleep 10; i2cset -f -y 1 0x57 0x67 0x0a
    msleep 10; i2cset -f -y 1 0x57 0x68 0x0a
    msleep 10; i2cset -f -y 1 0x57 0x69 0x0a
    msleep 10; i2cset -f -y 1 0x57 0x6a 0x0a
    msleep 10; i2cset -f -y 1 0x57 0x6b 0x0a
    msleep 10; i2cset -f -y 1 0x57 0x6c 0x00
    msleep 10; i2cset -f -y 1 0x57 0x6d 0x00
    msleep 10; i2cset -f -y 1 0x57 0x6e 0x00
    msleep 10; i2cset -f -y 1 0x57 0x6f 0xfd
    msleep 10; i2cset -f -y 1 0x57 0x70 0x00
    msleep 10; i2cset -f -y 1 0x57 0x71 0x37
    msleep 10; i2cset -f -y 1 0x57 0x72 0x4c
    msleep 10; i2cset -f -y 1 0x57 0x73 0x0f
    msleep 10; i2cset -f -y 1 0x57 0x74 0x44
    msleep 10; i2cset -f -y 1 0x57 0x75 0x0a
    msleep 10; i2cset -f -y 1 0x57 0x76 0x0f
    msleep 10; i2cset -f -y 1 0x57 0x77 0x00
    msleep 10; i2cset -f -y 1 0x57 0x78 0x20
    msleep 10; i2cset -f -y 1 0x57 0x79 0x20
    msleep 10; i2cset -f -y 1 0x57 0x7a 0x20
    msleep 10; i2cset -f -y 1 0x57 0x7b 0x20
    msleep 10; i2cset -f -y 1 0x57 0x7c 0x20
    msleep 10; i2cset -f -y 1 0x57 0x7d 0x20
    msleep 10; i2cset -f -y 1 0x57 0x7e 0x01
    msleep 10; i2cset -f -y 1 0x57 0x7f 0x6e
    msleep 10; i2cset -f -y 1 0x57 0x80 0xff
    msleep 10; i2cset -f -y 1 0x57 0x81 0xff
    msleep 10; i2cset -f -y 1 0x57 0x82 0xff
    msleep 10; i2cset -f -y 1 0x57 0x83 0xff
    msleep 10; i2cset -f -y 1 0x57 0x84 0xff
    msleep 10; i2cset -f -y 1 0x57 0x85 0xff
    msleep 10; i2cset -f -y 1 0x57 0x86 0xff
    msleep 10; i2cset -f -y 1 0x57 0x87 0xff
    msleep 10; i2cset -f -y 1 0x57 0x88 0xff
    msleep 10; i2cset -f -y 1 0x57 0x89 0xff
    msleep 10; i2cset -f -y 1 0x57 0x8a 0xff
    msleep 10; i2cset -f -y 1 0x57 0x8b 0xff
    msleep 10; i2cset -f -y 1 0x57 0x8c 0xff
    msleep 10; i2cset -f -y 1 0x57 0x8d 0xff
    msleep 10; i2cset -f -y 1 0x57 0x8e 0xff
    msleep 10; i2cset -f -y 1 0x57 0x8f 0xff
    msleep 10; i2cset -f -y 1 0x57 0x90 0xff
    msleep 10; i2cset -f -y 1 0x57 0x91 0xff
    msleep 10; i2cset -f -y 1 0x57 0x92 0xff
    msleep 10; i2cset -f -y 1 0x57 0x93 0xff
    msleep 10; i2cset -f -y 1 0x57 0x94 0xff
    msleep 10; i2cset -f -y 1 0x57 0x95 0xff
    msleep 10; i2cset -f -y 1 0x57 0x96 0xff
    msleep 10; i2cset -f -y 1 0x57 0x97 0xff
    msleep 10; i2cset -f -y 1 0x57 0x98 0xff
    msleep 10; i2cset -f -y 1 0x57 0x99 0xff
    msleep 10; i2cset -f -y 1 0x57 0x9a 0xff
    msleep 10; i2cset -f -y 1 0x57 0x9b 0xff
    msleep 10; i2cset -f -y 1 0x57 0x9c 0xff
    msleep 10; i2cset -f -y 1 0x57 0x9d 0xff
    msleep 10; i2cset -f -y 1 0x57 0x9e 0xff
    msleep 10; i2cset -f -y 1 0x57 0x9f 0xff
    msleep 10; i2cset -f -y 1 0x57 0xa0 0xff
    msleep 10; i2cset -f -y 1 0x57 0xa1 0xff
    msleep 10; i2cset -f -y 1 0x57 0xa2 0xff
    msleep 10; i2cset -f -y 1 0x57 0xa3 0xff
    msleep 10; i2cset -f -y 1 0x57 0xa4 0xff
    msleep 10; i2cset -f -y 1 0x57 0xa5 0xff
    msleep 10; i2cset -f -y 1 0x57 0xa6 0xff
    msleep 10; i2cset -f -y 1 0x57 0xa7 0xff
    msleep 10; i2cset -f -y 1 0x57 0xa8 0xff
    msleep 10; i2cset -f -y 1 0x57 0xa9 0xff
    msleep 10; i2cset -f -y 1 0x57 0xaa 0xff
    msleep 10; i2cset -f -y 1 0x57 0xab 0xff
    msleep 10; i2cset -f -y 1 0x57 0xac 0xff
    msleep 10; i2cset -f -y 1 0x57 0xad 0xff
    msleep 10; i2cset -f -y 1 0x57 0xae 0xff
    msleep 10; i2cset -f -y 1 0x57 0xaf 0xff
    msleep 10; i2cset -f -y 1 0x57 0xb0 0xff
    msleep 10; i2cset -f -y 1 0x57 0xb1 0xff
    msleep 10; i2cset -f -y 1 0x57 0xb2 0xff
    msleep 10; i2cset -f -y 1 0x57 0xb3 0xff
    msleep 10; i2cset -f -y 1 0x57 0xb4 0xff
    msleep 10; i2cset -f -y 1 0x57 0xb5 0xff
    msleep 10; i2cset -f -y 1 0x57 0xb6 0xff
    msleep 10; i2cset -f -y 1 0x57 0xb7 0xff
    msleep 10; i2cset -f -y 1 0x57 0xb8 0xff
    msleep 10; i2cset -f -y 1 0x57 0xb9 0xff
    msleep 10; i2cset -f -y 1 0x57 0xba 0xff
    msleep 10; i2cset -f -y 1 0x57 0xbb 0xff
    msleep 10; i2cset -f -y 1 0x57 0xbc 0xff
    msleep 10; i2cset -f -y 1 0x57 0xbd 0xff
    msleep 10; i2cset -f -y 1 0x57 0xbe 0xff
    msleep 10; i2cset -f -y 1 0x57 0xbf 0xff
    msleep 10; i2cset -f -y 1 0x57 0xc0 0xff
    msleep 10; i2cset -f -y 1 0x57 0xc1 0xff
    msleep 10; i2cset -f -y 1 0x57 0xc2 0xff
    msleep 10; i2cset -f -y 1 0x57 0xc3 0xff
    msleep 10; i2cset -f -y 1 0x57 0xc4 0xff
    msleep 10; i2cset -f -y 1 0x57 0xc5 0xff
    msleep 10; i2cset -f -y 1 0x57 0xc6 0xff
    msleep 10; i2cset -f -y 1 0x57 0xc7 0xff
    msleep 10; i2cset -f -y 1 0x57 0xc8 0xff
    msleep 10; i2cset -f -y 1 0x57 0xc9 0xff
    msleep 10; i2cset -f -y 1 0x57 0xca 0xff
    msleep 10; i2cset -f -y 1 0x57 0xcb 0xff
    msleep 10; i2cset -f -y 1 0x57 0xcc 0xff
    msleep 10; i2cset -f -y 1 0x57 0xcd 0xff
    msleep 10; i2cset -f -y 1 0x57 0xce 0xff
    msleep 10; i2cset -f -y 1 0x57 0xcf 0xff
    msleep 10; i2cset -f -y 1 0x57 0xd0 0xff
    msleep 10; i2cset -f -y 1 0x57 0xd1 0xff
    msleep 10; i2cset -f -y 1 0x57 0xd2 0xff
    msleep 10; i2cset -f -y 1 0x57 0xd3 0xff
    msleep 10; i2cset -f -y 1 0x57 0xd4 0xff
    msleep 10; i2cset -f -y 1 0x57 0xd5 0xff
    msleep 10; i2cset -f -y 1 0x57 0xd6 0xff
    msleep 10; i2cset -f -y 1 0x57 0xd7 0xff
    msleep 10; i2cset -f -y 1 0x57 0xd8 0xff
    msleep 10; i2cset -f -y 1 0x57 0xd9 0xff
    msleep 10; i2cset -f -y 1 0x57 0xda 0xff
    msleep 10; i2cset -f -y 1 0x57 0xdb 0xff
    msleep 10; i2cset -f -y 1 0x57 0xdc 0xff
    msleep 10; i2cset -f -y 1 0x57 0xdd 0xff
    msleep 10; i2cset -f -y 1 0x57 0xde 0xff
    msleep 10; i2cset -f -y 1 0x57 0xdf 0xff
    msleep 10; i2cset -f -y 1 0x57 0xe0 0xff
    msleep 10; i2cset -f -y 1 0x57 0xe1 0xff
    msleep 10; i2cset -f -y 1 0x57 0xe2 0xff
    msleep 10; i2cset -f -y 1 0x57 0xe3 0xff
    msleep 10; i2cset -f -y 1 0x57 0xe4 0xff
    msleep 10; i2cset -f -y 1 0x57 0xe5 0xff
    msleep 10; i2cset -f -y 1 0x57 0xe6 0xff
    msleep 10; i2cset -f -y 1 0x57 0xe7 0xff
    msleep 10; i2cset -f -y 1 0x57 0xe8 0xff
    msleep 10; i2cset -f -y 1 0x57 0xe9 0xff
    msleep 10; i2cset -f -y 1 0x57 0xea 0xff
    msleep 10; i2cset -f -y 1 0x57 0xeb 0xff
    msleep 10; i2cset -f -y 1 0x57 0xec 0xff
    msleep 10; i2cset -f -y 1 0x57 0xed 0xff
    msleep 10; i2cset -f -y 1 0x57 0xee 0xff
    msleep 10; i2cset -f -y 1 0x57 0xef 0xff
    msleep 10; i2cset -f -y 1 0x57 0xf0 0xff
    msleep 10; i2cset -f -y 1 0x57 0xf1 0xff
    msleep 10; i2cset -f -y 1 0x57 0xf2 0xff
    msleep 10; i2cset -f -y 1 0x57 0xf3 0xff
    msleep 10; i2cset -f -y 1 0x57 0xf4 0xff
    msleep 10; i2cset -f -y 1 0x57 0xf5 0xff
    msleep 10; i2cset -f -y 1 0x57 0xf6 0xff
    msleep 10; i2cset -f -y 1 0x57 0xf7 0xff
    msleep 10; i2cset -f -y 1 0x57 0xf8 0xff
    msleep 10; i2cset -f -y 1 0x57 0xf9 0xff
    msleep 10; i2cset -f -y 1 0x57 0xfa 0xff
    msleep 10; i2cset -f -y 1 0x57 0xfb 0xff
    msleep 10; i2cset -f -y 1 0x57 0xfc 0xff
    msleep 10; i2cset -f -y 1 0x57 0xfd 0xff
    msleep 10; i2cset -f -y 1 0x57 0xfe 0xff
    msleep 10; i2cset -f -y 1 0x57 0xff 0xff
    msleep 10; i2cset -f -y 1 0x56 0x74 0x01
    msleep 10; i2cset -f -y 1 0x4c 0x03 0x80
    msleep 10; i2cset -f -y 1 0x4c 0x04 0x62
    msleep 10; i2cset -f -y 1 0x4c 0x06 0xa1
    msleep 10; i2cset -f -y 1 0x40 0x00 0x00
    msleep 10; i2cset -f -y 1 0x40 0x0c 0x00
    msleep 10; i2cset -f -y 1 0x40 0x0d 0x11
    msleep 10; i2cset -f -y 1 0x40 0x0c 0x00
    msleep 10; i2cset -f -y 1 0x40 0x0d 0x11
    msleep 10; i2cset -f -y 1 0x40 0x0c 0x01
    msleep 10; i2cset -f -y 1 0x40 0x0d 0x11
    msleep 10; i2cset -f -y 1 0x40 0x0c 0x01
    msleep 10; i2cset -f -y 1 0x40 0x0d 0x11
    msleep 10; i2cset -f -y 1 0x40 0x0c 0x21
    msleep 10; i2cset -f -y 1 0x40 0x0d 0x11
    msleep 10; i2cset -f -y 1 0x4c 0x15 0x00
    echo "Configuration done"
}

#SIL configuration taken from BSP,
# it enables hdmi receiver
function SILConfig()
{

    echo "The Vision App Board is with SIL ,
    Configuring HDMI Receiver for SIL"

    echo "Configuration in progress ... "
    msleep 10; i2cset -f -y 1 0x35 0x3e 0x43
    msleep 10; i2cset -f -y 1 0x35 0x3f 0xad
    msleep 10; i2cset -f -y 1 0x31 0x08 0x05
    msleep 500; i2cset -f -y 1 0x31 0x05 0x2f
    msleep 10; i2cset -f -y 1 0x31 0x05 0x10
    msleep 10; i2cset -f -y 1 0x31 0x09 0x20
    msleep 10; i2cset -f -y 1 0x31 0x0a 0x09
    msleep 10; i2cset -f -y 1 0x32 0x87 0x03
    msleep 10; i2cset -f -y 1 0x32 0x81 0x10
    msleep 10; i2cset -f -y 1 0x32 0x88 0x40
    msleep 10; i2cset -f -y 1 0x31 0x4a 0xba
    msleep 10; i2cset -f -y 1 0x31 0x49 0x0b
    msleep 10; i2cset -f -y 1 0x31 0x48 0x05
    msleep 10; i2cset -f -y 1 0x31 0x08 0x05
    msleep 10; i2cset -f -y 1 0x31 0x56 0x05
    msleep 10; i2cset -f -y 1 0x35 0x3e 0x47
    msleep 10; i2cset -f -y 1 0x35 0x3f 0xed
    echo "Configuration done"
}

if [ $(i2cget -f -y 1 0x31 0xea) ];
then
SILConfig
exit
fi

if [ $(i2cget -f -y 1 0x4c 0xea) ];
then
ADVConfig
exit
fi