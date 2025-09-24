#include <jni.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

// JNI method: copy file from src -> dst
JNIEXPORT void JNICALL
Java_com_nekostrap_NekoStrap_copySettings(JNIEnv *env, jobject thiz,
                                          jstring jsrc, jstring jdst) {
    const char *src = (*env)->GetStringUTFChars(env, jsrc, 0);
    const char *dst = (*env)->GetStringUTFChars(env, jdst, 0);

    int inFd = open(src, O_RDONLY);
    if (inFd < 0) {
        // create empty file if not exist
        int fd = open(src, O_CREAT | O_WRONLY, 0644);
        if (fd >= 0) close(fd);
        inFd = open(src, O_RDONLY);
    }

    int outFd = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (inFd >= 0 && outFd >= 0) {
        char buf[4096];
        ssize_t size;
        while ((size = read(inFd, buf, sizeof(buf))) > 0) {
            write(outFd, buf, size);
        }
    }

    if (inFd >= 0) close(inFd);
    if (outFd >= 0) close(outFd);

    (*env)->ReleaseStringUTFChars(env, jsrc, src);
    (*env)->ReleaseStringUTFChars(env, jdst, dst);
}
