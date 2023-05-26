# GBinder for Ashita v4

This plugin enables use of the Logitech G-Keys for Ashita v4.

# Runtime Requirements

In order to use this plugin, you need to have installed Logitech Gaming Software and running.
It typically installs a .dll to `C:\Program Files\Logitech Gaming Software\SDK\G-key\x86\LogitechGkey.dll` which is required for use.


# Build Requirements

In order to compile this project, you need the following:

  - `Microsoft Visual Studio 2022` - https://visualstudio.microsoft.com/vs/
  - `Logitech G-Key Macro SDK` - https://www.logitechg.com/en-us/innovation/developer-lab.html
  - The Ashita v4 SDK environment path setup. See `SDK Environment Variable Setup` at https://github.com/AshitaXI/ExamplePlugin/
  
The G-Key SDK must be installed to your project directory with the folder name GKeySDK such that the following paths are available relative to the solution file's directory:

* build-debug.bat
* build-release.bat
* GBinder.sln
* GKeySDK\Include\LogitechGkeyLib.h
* GKeySDK\Lib\x86\LogitechGkeyLib.lib
* LICENSE.md
* README.md

# In-Game Usage

When loaded, the plugin will send a command to Ashita with the name the macro set and key. For example, if you are in M1 and press G5, it will send `/m1g5`. You can `/alias m1g5 /say hello!` to say "hello!" in game area chat. The plugin receives callbacks and will trigger only on key down. Key up is not supported.

This plugin also will attempt to read mouse button callbacks, but **it does not appear to work** as of writing. The callback is never actually received upon pressing those buttons. The command it will run would be `/mouse_m1g3` if you pressed G3 on your mouse in macro set 1.

# About

This was created using the Ashita Plugin SDK: https://github.com/AshitaXI/ExamplePlugin/
