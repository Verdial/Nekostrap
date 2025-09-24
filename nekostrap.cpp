#include <jni.h>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <android/log.h>

#define LOG_TAG "NekoStrap"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

static void copyFile(const char* src, const char* dst) {
    std::ifstream in(src, std::ios::binary);
    if (!in.is_open()) {
        LOGI("Source not found: %s", src);
        return;
    }

    // buat folder tujuan kalau belum ada
    std::string dstPath(dst);
    size_t pos = dstPath.find_last_of('/');
    if (pos != std::string::npos) {
        std::string folder = dstPath.substr(0, pos);
        mkdir(folder.c_str(), 0777);
    }

    std::ofstream out(dst, std::ios::binary);
    out << in.rdbuf();

    in.close();
    out.close();

    LOGI("Copied: %s -> %s", src, dst);
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGI("NekoStrap JNI_OnLoad triggered");

    const char* src = "/storage/emulated/0/Nekostrap/ClientAppSettings.json";
    const char* dst = "/data/data/com.roblox.client/files/exe/ClientSettings/ClientAppSettings.json";

    // buat folder Nekostrap di internal kalau belum ada
    mkdir("/storage/emulated/0/Nekostrap", 0777);

    copyFile(src, dst);

    return JNI_VERSION_1_6;
}
