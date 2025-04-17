### Flashing board

Keep latest platformio

Open PlatformIO CLI and run:
```bash
pio pkg update
```

Keep latest PlatformIO Core:
```bash
pio upgrade
```

Build project using GUI or with cli
```bash
pio run -e blackpill_f411ce
```

Ensure that `dfu-util` is installed

If MCU dfu is protected first you have to force unprotect DFU mode
```bash
dfu-util -a 0 -D <path_to_build/firmware.bin> -s :unprotect:force
```

Since now you can normaly flash the board.

Firstly reset the board.

Now put board in DFU mode: press BOOT0 button and keep holding it, press NRST button once, release BOOT0. Board should be flashable now.

Now you can flash the board using PlatformIO GUI or manually using `dfu-util` in CLI.

When using PlatformIO GUI you should see similar output:

```bash
Downloading element to address = 0x08000000, size = 11792

Erase           [                         ]   0%            0 bytes
Erase           [====                     ]  17%         2048 bytes
Erase           [========                 ]  34%         4096 bytes
Erase           [=============            ]  52%         6144 bytes
Erase           [=================        ]  69%         8192 bytes
Erase           [=====================    ]  86%        10240 bytes
Erase           [=========================] 100%        11792 bytes
Erase    done.

Download        [                         ]   0%            0 bytes
Download        [====                     ]  17%         2048 bytes
Download        [========                 ]  34%         4096 bytes
Download        [=============            ]  52%         6144 bytes
Download        [=================        ]  69%         8192 bytes
Download        [=====================    ]  86%        10240 bytes
Download        [=========================] 100%        11792 bytes
Download done.
File downloaded successfully
```