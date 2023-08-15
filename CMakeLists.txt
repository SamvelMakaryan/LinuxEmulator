cmake_minimum_required(VERSION 3.0)
project(Emuliator)

set(SOURCES 
    src/Component.cpp
    src/FileSystemComponent.cpp
    src/Directory.cpp
    src/File.cpp
    src/TxtFile.cpp
    src/Group.cpp
    src/User.cpp
    src/System.cpp
   	src/Emulator.cpp
    Commands/mkdir.cpp
    Commands/ls.cpp
    Commands/cd.cpp
    Commands/touch.cpp
    Commands/pwd.cpp
    Commands/rmdir.cpp
    Commands/rm.cpp
    Commands/date.cpp
	Commands/cal.cpp
	Commands/chmod.cpp
	Commands/history.cpp
	Commands/cat.cpp
    Commands/useradd.cpp
    Commands/userdel.cpp
    Commands/su.cpp
    Commands/whoami.cpp
)

add_executable(Emulator ${SOURCES})
