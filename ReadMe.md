<picture>
    <source media="(prefers-color-scheme: dark)" srcset="/.github/assets/dark_theme_banner.png">
    <source media="(prefers-color-scheme: light)" srcset="/.github/assets/light_theme_banner.png">
    <img
        alt="A pixel art of a Dophin with text: Flipper Zero Official Repo"
        src="/.github/assets/light_theme_banner.png">
</picture>

# Flipper Zero Bluetoorh Keyboard FIirmware

Flipper as keyboard with autoconnection (almost) and predefined text to send. Use only for education purposes.

[Origin firmeware repo](https://github.com/flipperdevices/flipperzero-firmware)

## General logic

* Program staring
* Flipper sending to PC or Mac around signal that new BlueTooth keybord (or mouse) ready to connect
* PC or Mac should show the popup notification about keyboard (or mouse)
* After connection, by pressing one button on flipper it send the predefined button combination and text to connected laptop

## Main problems

* A lot of laptops have different BT devices notification algorithm, so it's better to use logitech advertising signal as the most popular
* It's better to send signal as keyboard, rather than mouse, as most OS do not accepts keyboard buttons signals from mouse (but not always)
* Sometimes it prompts you to enter a PIN, but this does not affect the connection

## Advertising signal

The biggest problem is to find working advertising signal to call popup on laptop. You can use Bluetooth LE Explorer to catch the signals from devises and then emulate it from flipper.

## Changed files

* [lib/ble_profile/extra_profiles/hid_profile.c](lib/ble_profile/extra_profiles/hid_profile.c) - minor changes for name in bluetooth config
* [targets/f7/ble_glue/gap.c‎](targets/f7/ble_glue/gap.c‎) - here you should define advertising packege in bytes, which you can listen from Bluetooth LE Explorer. Also in this file you can setup the package order sending to bluetooth broadcast which is important for creation connection popup.
