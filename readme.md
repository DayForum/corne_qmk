# Change your path in 4, 6 and 7 steps!



## 1. Download
```
https://www.msys2.org/
```

## 2. First run after install
```
pacman -Syu
```

## 3. Second run 'MSYS2 MSYS'
```
pacman -Su
```

## 4. Third run 'MSYS2 MiniGW x64'
```
pacman --needed --noconfirm --disable-download-timeout -S git mingw-w64-x86_64-toolchain mingw-w64-x86_64-python3-pip
python3 -m pip install qmk==0.0.37
qmk setup -H "C:\Users\Day\keyboards\corne_qmk" DayForum/corne_qmk
```

just double press: Y

## 5. You will get an error
`ERROR Can't find arm-none-eabi-gcc in your path.`
`ERROR Can't find avr-gcc in your path.`
`ERROR Can't find avrdude in your path.`
`ERROR Can't find dfu-programmer in your path.`
`ERROR Can't find dfu-util in your path.`

just triple press: Y

## 6. Pre-last step
```
qmk setup -H "C:\Users\Day\keyboards\corne_qmk" DayForum/corne_qmk
```
You will get an - `QMK is ready to go` - it false info

## 7. And last step
```
qmk config user.qmk_home="C:\Users\Day\keyboards\corne_qmk"
```

## 8. Compile firmware
```
qmk compile -kb crkbd -km rcw_left
qmk compile -kb crkbd -km rcw_right
```

## 9. Default folder
```
C:\Users\Day\keyboards\corne_qmk\.build
```

## 10. Default path keymap.c file for edit
```
C:\Users\Day\keyboards\corne_qmk\keyboards\crkbd\keymaps\rcw_left\keymap.c
C:\Users\Day\keyboards\corne_qmk\keyboards\crkbd\keymaps\rcw_right\keymap.c
```
