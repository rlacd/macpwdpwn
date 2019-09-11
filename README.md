# mpwdpwn

Copyright (C) mr_chainman (techspider) 2019.

macOS Account Unlocking Tool for Mojave and up.

## Important Notice

Please note that this tool may only be used for personal use; it is 100% illegal to unlock accounts on machines that you do not own (this includes college owned laptops).

The author of this software is not responsible from any damage caused from this tool, proceed at your own risk!

The tool is currently in beta stage and is unfinished. Once again, proceed at your own risk.

## What is it?

mpwdpwn is a command line tool which will allow you to unlock password protected accounts on your local Mac machine (even T2 secured Macs). This is very useful if you have forgotten the password to your own user account.

Please note that this tool will not attempt to extract/crack user passwords.

## How do I use it?

To use the tool, download the latest binary release (from the Releases tab) or compile from source (requires XCode command line tools). Once finished, copy the binary file to a USB flash drive.

Once the binary has been copied, reboot your mac into recovery mode by pressing `COMMAND+R` on startup. Once booted, open Terminal and run the program from the flash drive. If the program does not run, use chmod to fix permissions or copy it to a temporary folder on your hard disk.

From there, follow the instructions displayed by the tool.

## Tested Macs

* MacBook Pro (13-inch, 2017, 2 TB3 ports) with Mojave 10.14.1

## Known Issues

* On Macs with T2 and startup security, if an administrator password is modified, it will not change the startup password (your old password will still be required).

## Reporting Bugs

Simply open an issue on GitHub.

## Planned Features

* Option to reverse unlock from backup.
* General code fixes

## License

Licensed under GNU GPLv3.