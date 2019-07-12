# GLib

GLib is a library that allows for the simple creation of binary modules for Garry's Mod. It automatically handles the stack for most cases, and provides an easy to use object oriented interface.

## Getting started
Due to a bug in the build system for Visual Studio 2019, this library should only be used with Visual Studio 2017 or older.

First, you will need to recursively clone the repository. This can be done in Visual Studio, or by entering the following into the command line:
```bash
git clone --recursive https://github.com/Techmo2/GLib.git
```
After cloning the repository, simply open the project file in Visual Studio and ensure the build mode is set to x86.

## Testing
In order to run the example plugin, ensure the build mode is set to **Release** and build the project. If this is not done, optimizations will be ignored, and the built in benchmark will be very slow. Copy ```gmsv_testing_win32.dll``` from the Release folder to the ```garrysmod/lua/bin``` folder in your server directory. If the bin directory does not exist, create it. Place ```test.lua``` into ```garrysmod/lua/autorun/server``` and start the server. You should see the function tests, and the built in benchmark.

## Known issues
The ```garrysmod_common``` repository this project uses for it's ```ILuaObject``` class seems to be out of date. The functions ```GetBool()``` ```GetDouble()		``` and ```GetVector()``` do not match the signatures in the Garry's Mod lua_shared binary, and will cause run-time errors if used. There are simple workarounds described in the example project file.