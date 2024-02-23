# AndroidUHidPureJava

An HID device simulation implemented purely in Java! 

# How it works

Starting from Android 6.0.1, the "hidcommand_jni" library is built into the system. We can load this library and use the JNI functions provided in it.
This is only if our application has the same package name and class as it was originally intended to be used.

So for the sake of integrating it into my application, I tried to recreate the JNI to bypass it
Thanks mostly to this project I managed to do it although with a minor issue
https://github.com/WuDi-ZhanShen/Android-Gyroscope-MC

I wasn't able to figure out how to convert a jbyteArray to an unsigned char which is used for descriptors which left me to have to manually hardcode the description in the native code

# How to build this project and how to use

By compiling this project with Android Studio, you will get an apk file. Unzip the classes.dex file from the apk and place it anywhere on your Android device. In our case, we'll place it in /data/local/tmp. Then do the same thing for libcustom_hidcommand_jni.so located inside the libs directory(Make sure to pick out the one which correponds to your device's architecture) and place it in the same path.

Then, use the following command to run the dex file:

adb shell CLASSPATH="/data/local/tmp/classes.dex" app_process -Djava.library.path=/data/local/tmp / com.android.commands.hid.Hid

Adb or Root permission is required.
