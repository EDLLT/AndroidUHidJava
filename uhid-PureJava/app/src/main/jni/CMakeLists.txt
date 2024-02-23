# Sets the minimum CMake version required for this project.
cmake_minimum_required(VERSION 3.22.1)

# Declares the project name.
project("custom_hidcommand_jni")


# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
add_library(
        custom_hidcommand_jni
        SHARED
        com_android_commands_hid_Device.cpp)

# Specifies shared libraries to link with the target library.


target_link_libraries(${PROJECT_NAME}
        android
        log
        )

# Sets compilation flags for the shared library module.
#target_compile_options(${PROJECT_NAME} PRIVATE
#        -Wall
#        -Wextra
#        -Werror
#        )