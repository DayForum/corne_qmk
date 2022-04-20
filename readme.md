# QMK
## My own QMK fork that targeting Corne keyboard

## How to compile 
using PowerShell
##### Preparation step: Getting and configuring the MingW64
```sh
(New-Object System.Net.WebClient).DownloadFile( 'https://github.com/msys2/msys2-installer/releases/download/2022-03-19/msys2-x86_64-20220319.exe', 'msys2.exe' )
./msys2.exe
```
##### When the installation is complete you must update packages via Pacman

```sh
pacman -Syu --noconfirm 
### After successful command execution you will be prompted to restart MinGW ###
### execute next command in next 'MSYS2 MSYS' session ###
pacman -Su --noconfirm
```

##### Configuring QMK and QMK packages
Configuring QMK packages
```sh
### Start exactly "MSYS2 MiniGW x64" this is important
pacman --needed --noconfirm --disable-download-timeout -S git mingw-w64-x86_64-toolchain mingw-w64-x86_64-python3-pip
python3 -m pip install qmk==0.0.37
qmk setup -H "C:/$HOMEPATH/keyboards/corne_qmk" DayForum/corne_qmk
```

##### If you are getting an errors with path's simply ignore it and answer "Y"
`ERROR Can't find arm-none-eabi-gcc in your path.`

`ERROR Can't find avr-gcc in your path.`

`ERROR Can't find avrdude in your path.`

`ERROR Can't find dfu-programmer in your path.`

`ERROR Can't find dfu-util in your path.`

##### Configuring QMK
```sh
qmk setup -H "C:/$HOMEPATH/keyboards/corne_qmk" DayForum/corne_qmk
qmk config user.qmk_home="C:/$HOMEPATH/keyboards/corne_qmk"
```
##### Compiling firmware
```sh
qmk compile -kb crkbd -km rcw_left
qmk compile -kb crkbd -km rcw_right
```
###### If compilation was ended successfully you will find ready to flash files in 
`С:\$HOMEPATH\keyboards\corne_qmk\.build`

### Customizing keymap
##### By default keymap is located at:
`С:\$HOMEPATH\keyboards\corne_qmk\keyboards\rcw_left\keymap.c` - Left hand layout
`С:\$HOMEPATH\keyboards\corne_qmk\keyboards\rcw_right\keymap.c` - Right hand layout
