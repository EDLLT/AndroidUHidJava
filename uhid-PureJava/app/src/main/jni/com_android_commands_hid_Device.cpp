#include <jni.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <linux/uinput.h>
#include <cerrno>
#include <fcntl.h>
#include <poll.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <termios.h>
#include <unistd.h>
#include <linux/uhid.h>
#include <linux/input.h>
#include <jni.h>
#include <android/log.h>
#include <vector>

// Couldn't figure out how to convert from jbyteArray to unsigned char as it kept on not working
static unsigned char description[] = {
        0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
        0x09, 0x06,        // Usage (Keyboard)
        0xA1, 0x01,        // Collection (Application)
        0x05, 0x07,        //   Usage Page (Kbrd/Keypad)
        0x19, 0xE0,        //   Usage Minimum (0xE0)
        0x29, 0xE7,        //   Usage Maximum (0xE7)
        0x15, 0x00,        //   Logical Minimum (0)
        0x25, 0x01,        //   Logical Maximum (1)
        0x75, 0x01,        //   Report Size (1)
        0x95, 0x08,        //   Report Count (8)
        0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0x95, 0x01,        //   Report Count (1)
        0x75, 0x08,        //   Report Size (8)
        0x81, 0x03,        //   Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0x95, 0x05,        //   Report Count (5)
        0x75, 0x01,        //   Report Size (1)
        0x05, 0x08,        //   Usage Page (LEDs)
        0x19, 0x01,        //   Usage Minimum (Num Lock)
        0x29, 0x05,        //   Usage Maximum (Kana)
        0x91, 0x02,        //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0x95, 0x01,        //   Report Count (1)
        0x75, 0x03,        //   Report Size (3)
        0x91, 0x03,        //   Output (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0x95, 0x06,        //   Report Count (6)
        0x75, 0x08,        //   Report Size (8)
        0x15, 0x00,        //   Logical Minimum (0)
        0x25, 0x65,        //   Logical Maximum (101)
        0x05, 0x07,        //   Usage Page (Kbrd/Keypad)
        0x19, 0x00,        //   Usage Minimum (0x00)
        0x29, 0x65,        //   Usage Maximum (0x65)
        0x81, 0x00,        //   Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0xC0,              // End Collection

};


// Function to convert jbyteArray to std::vector<uint8_t>
std::vector<uint8_t> convertJByteArrayToVector(JNIEnv* env, jbyteArray byteArray) {
    std::vector<uint8_t> result;

    // Check if the input array is valid
    if (byteArray == nullptr) {
        return result; // Return empty vector if input is null
    }

    // Get the length of the byte array
    jsize length = env->GetArrayLength(byteArray);

    // Obtain a pointer to the elements of the byte array
    jbyte* elements = env->GetByteArrayElements(byteArray, nullptr);

    // Copy the elements of the byte array into the result vector
    for (jsize i = 0; i < length; i++) {
        result.push_back(static_cast<uint8_t>(elements[i]));
    }

    // Release the array elements
    env->ReleaseByteArrayElements(byteArray, elements, JNI_ABORT);

    return result;
}




static int uhid_fd;
static struct uhid_event uhidEventXY;


extern "C"
JNIEXPORT jlong JNICALL
Java_com_android_commands_hid_Device_nativeOpenDevice(JNIEnv* env,
                                                      jclass /* clazz */,
                                                      jstring name,
                                                      jint id,
                                                      jint vid,
                                                      jint pid,
                                                      jint bus,
                                                      jbyteArray rawDescriptor,
                                                      jobject callback) {

//    static jlong openDevice(JNIEnv* env, jclass /* clazz */, jstring name, jint id, jint vid,
//                            jint pid, jint bus, jbyteArray rawDescriptor, jobject callback) {
//
//
//        std::vector<uint8_t> desc = getData(env, rawDescriptor);
//
//        std::unique_ptr<uhid::DeviceCallback> cb(new uhid::DeviceCallback(env, callback));
//
//        std::unique_ptr<uhid::Device> d =
//                uhid::Device::open(id, reinterpret_cast<const char*>(name), vid, pid, bus, desc,
//                                   std::move(cb));
//        return reinterpret_cast<jlong>(d.release());
//    }


    //    //pressed ? (uhidEventXY.u.input.data[1] |= 1 << 6) : (uhidEventXY.u.input.data[1] &= ~(1 << 6));
    //    uhidEventXY.u.input.data[0] = 0x00;
    //    uhidEventXY.u.input.data[1] = 0x00;
    //    uhidEventXY.u.input.data[2] = pressed ? 0x1D : 0x00;
    //    uhidEventXY.u.input.data[3] = 0x00;
    //    uhidEventXY.u.input.data[4] = 0x00;
    //    uhidEventXY.u.input.data[5] = 0x00;
    //    uhidEventXY.u.input.data[6] = 0x00;
    //    uhidEventXY.u.input.data[7] = 0x00;
    //    write(uhid_fd, &uhidEventXY, sizeof(uhidEventXY));

    // Pass a pointer to the underlying data of the vector
    // Assuming you have a function that expects a pointer to uint8_t
//    uint8_t* description = convertedData.data();

    if ((uhid_fd = open("/dev/uhid", O_RDWR | O_NDELAY)) < 0) {
        __android_log_print(ANDROID_LOG_WARN, "MyTag", "FAILED TO OPEN UHID!!!!");
        return 0;//error process.
    }
    struct uhid_event ev;
    memset(&ev, 0, sizeof(uhid_event));
    ev.type = UHID_CREATE;
    strcpy((char *) ev.u.create.name, "uHidKeyboard");
    ev.u.create.rd_data = description;
    ev.u.create.rd_size = sizeof(description);
    ev.u.create.bus = bus;
    ev.u.create.vendor = vid;
    ev.u.create.product = pid;
    ev.u.create.version = 0x1;
    ev.u.create.country = 0;
    if (write(uhid_fd, &ev, sizeof(ev)) != sizeof(uhid_event)) {
        __android_log_print(ANDROID_LOG_WARN, "MyTag", "sizeof(ev)) != sizeof(uhid_event) !!!!!");
        return 0;
    }

    memset(&uhidEventXY, 0, sizeof(uhid_event));
    uhidEventXY.type = UHID_INPUT;
    uhidEventXY.u.input.size = 8;
    uhidEventXY.u.input.data[0] = 0x00;

    return 1;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_android_commands_hid_Device_nativeSendReport(JNIEnv *env,
                                                  jclass clazz,
                                                  jlong ptr,
                                                  jbyteArray rawReport) {

//    void Device::sendReport(const std::vector<uint8_t>& report) const {
//        if (report.size() > UHID_DATA_MAX) {
//            ALOGE("Received invalid report of size %zu, skipping", report.size());
//            return;
//        }
//
//        struct uhid_event ev = {};
//        ev.type = UHID_INPUT2;
//        ev.u.input2.size = report.size();
//        memcpy(&ev.u.input2.data, report.data(), report.size() * sizeof(ev.u.input2.data[0]));
//        writeEvent(mFd, ev, "UHID_INPUT2");
//    }

    std::vector<uint8_t> report = convertJByteArrayToVector(env, rawReport);

//    if (report.size() > UHID_DATA_MAX) {
//        ALOGE("Received invalid report of size %zu, skipping", report.size());
//        return;
//    }

    struct uhid_event ev = {};
    ev.type = UHID_INPUT;
    ev.u.input.size = report.size();
    memcpy(&ev.u.input.data, report.data(), report.size() * sizeof(ev.u.input.data[0]));
    write(uhid_fd, &ev, sizeof(ev));


//    __android_log_print(ANDROID_LOG_WARN, "MyTag", "HELLO WORLD THIS IS FROM JNI, WE R GONNA TRY RUNNING Z");
}

extern "C"
JNIEXPORT void JNICALL
Java_com_android_commands_hid_Device_nativeCloseDevice(JNIEnv *env,
                                                      jclass clazz,
                                                      jlong ptr) {

    struct uhid_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.type = UHID_DESTROY;
    write(uhid_fd, &ev, sizeof(ev));// > 0;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_android_commands_hid_Device_nativeSendGetFeatureReportReply(JNIEnv* env,
                                                                     jclass /* clazz */,
                                                                     jlong ptr,
                                                                     jint id,
                                                                     jbyteArray rawReport) {

    //static void sendGetFeatureReportReply(JNIEnv* env, jclass /* clazz */, jlong ptr, jint id,
    //        jbyteArray rawReport) {
    //uhid::Device* d = reinterpret_cast<uhid::Device*>(ptr);
    //if (d) {
    //std::vector<uint8_t> report = getData(env, rawReport);
    //d->sendGetFeatureReportReply(id, report);
    //} else {
    //ALOGE("Could not send get feature report reply, Device* is null!");
    //}
    //}


    std::vector<uint8_t> report = convertJByteArrayToVector(env, rawReport);

    struct uhid_event ev = {};
    ev.type = UHID_GET_REPORT_REPLY;
    ev.u.get_report_reply.id = id;
    ev.u.get_report_reply.err = report.size() == 0 ? EIO : 0;
    ev.u.get_report_reply.size = report.size();
    memcpy(&ev.u.get_report_reply.data, report.data(),
           report.size() * sizeof(ev.u.get_report_reply.data[0]));
    write(uhid_fd, &ev, sizeof(ev));// > 0;
}