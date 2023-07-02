# Linux Emulator

The Linux Emulator is a project that simulates a Linux environment(filesystem, commands, ...) without using native Linux commands.

## Features

- **Linux Environment**: The emulator creates a virtual Linux environment that replicates the behavior and functionality of a real Linux system.
- **Application Compatibility**: Users can run a command-line tools within the emulator.
- **Command Execution**: The emulator allows users to execute Linux commands directly from the terminal, providing a familiar command-line interface.
- **File System**: The project provides a simulated file system that mimics the file structure and organization of a Linux distribution.

##Commands
This program supports following commands with appropriate options.

- Commands  | options

- mkdir     | [-p, -v, -m, --verbose, --parents, --version]
- rmdir		  | [-p, -v, --parents, --verbose, --help, --version]
- touch 	  | [--help, --version]
- rm 		    | [-r, -R, -v, -d, --verbose, --dir, --help, --version]
- cd		    | [--help]
- cal		    | no options 
- cat		    | [-n, -b, --number, --number-nonblank, --help, --version]
- chmod		  | [-v, -c, -R, --verbose, --changes, --recursive, --help, --version]
- date		  | no options
- history	  | [-c, --help]
- ls		    | [-l, -a, -la, -A, --all, --almost-all, --help, --version]
- pwd		    | [--help]
- su		    | [--help, --version]
- useradd	  | [-m, --create-home, --help]
- userdel	  | [--help]
- whoami	  | [--help, --version]
- exit		  | no options 

## Usage

1. Clone this repository.
2. Move to LinuxEmulator directory.
3. Create build directory.
4. Run "cmake .." .
5. Run "make".
6. Use executable Emulator.

### Example

![Screenshot from 2023-07-02 14-23-55](https://github.com/SamvelMakaryan/LinuxEmulator/assets/123547362/02fdad50-9d3a-4858-ad6b-f6ccacfbb920)

