# AndroidUHidPureJava
��Javaʵ�ֵ�uhidģ��HID�豸��

# How it works
��׿6.0.1��ϵͳ������hidcommand_jni�⡣��������Ⲣʹ�ÿ��е�JNI�������ɡ�����ע�⣬������е�JNI�����Ľ��ղ����ڰ�׿8.1.0֮���б仯��������Ŀ�е�Java�����Ӧ�ڰ�׿8.1.0���JNI��������ˣ�����Ŀ�����ڰ�׿8.1.0������ʹ�á���������ڰ�׿6.0.1�Ͱ�׿8.0.0֮��ʹ��hidcommand_jni�⣬�밴AOSP�е� http://www.aospxref.com/android-6.0.1_r9/xref/frameworks/base/cmds/hid/src/com/android/commands/hid/Device.java �޸ı���Ŀ�е�JNI�����Ľ��ղ�����

# How to build this project and how to use
ʹ��Android Studio�������Ŀ������õ�һ��apk�ļ�����ѹapk�ļ��е�classes.dex�����������Android�豸�е�����λ�ã�����/sdcard/classes.dex�����ʹ�������������д�dex�ļ���

export CLASSPATH=/sdcard/classes.dex;app_process / com.android.commands.hid.Hid
