NKRO_ENABLE = yes           # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
RGBLIGHT_ENABLE = yes       # Enable WS2812 RGB underlight. 
LTO_ENABLE = yes            # This enables Link Time Optimization.This can save a good chunk of space
BACKLIGHT_ENABLE = yes      # Enable keyboard backlight functionality (not support on corne) 
TAP_DANCE_ENABLE = yes

OLED_DRIVER_ENABLE = no     # OLED driver support (see SRC)
WPM_ENABLE = no             # WPM support counter enable (see SRC)
VIA_ENABLE = no             # VIA support enable
RGB_MATRIX_ENABLE = no      # RGB Matrix support
# RGB_MATRIX_DRIVER = WS2812  # RGB Matrix driver
UNICODE_ENABLE = no         # Unicode
EXTRAKEY_ENABLE = no        # Audio control and System control(+450)
SPACE_CADET_ENABLE = no     # Get some firmware space back
STENO_ENABLE = no           # Additional protocols for Stenography(+1700), requires VIRTSER
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no        # Mouse keys(+4700)
CONSOLE_ENABLE = no         # Console for debug(+400)
COMMAND_ENABLE = no         # Commands for debug and configuration
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID 
SWAP_HANDS_ENABLE = no      # Enable one-hand typing
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# BOOTLOADER = qmk-dfu


# matrix rows 3
# matrix cols 10






# SRC += ./lib/rgb_state_reader.c \
         ./keymaps/rcw_right/wpm.c \
         ./keymaps/rcw_right/oled_right.c # \ РАЗКОМЕНТИТЬ ЕСЛИ ЮЗАЕТСЯ!!!!!!!!!!!!!!!!!
#        ./lib/layer_state_reader.c \
         ./lib/logo_reader.c \
         ./lib/keylogger.c \