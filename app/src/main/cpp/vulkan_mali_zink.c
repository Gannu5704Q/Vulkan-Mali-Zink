#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <jni.h>
#include <elf.h>
#include <android/log.h>

#define LOG_TAG "VulkanMaliZink"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

int is_x86_64_binary(const char* lib_path) {
    FILE *fp = fopen(lib_path, "rb");
    if (!fp) return 0;
    Elf64_Ehdr header;
    fread(&header, 1, sizeof(header), fp);
    fclose(fp);
    return (memcmp(header.e_ident, ELFMAG, SELFMAG) == 0 && header.e_machine == EM_X86_64);
}

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGI("Vulkan Mali Zink Plugin Booting...");

    setenv("MESA_GL_VERSION_OVERRIDE", "4.6FC", 1);
    setenv("MESA_GLSL_VERSION_OVERRIDE", "460", 1);

    setenv("MESA_EXTENSION_OVERRIDE", 
           "+GL_ARB_compute_shader "
           "+GL_ARB_buffer_storage "
           "+GL_ARB_direct_state_access "
           "+GL_ARB_multi_draw_indirect "
           "+GL_ARB_shader_image_load_store", 1);

    setenv("ZINK_DESCRIPTORS", "cached", 1);
    setenv("ZINK_DEBUG", "compact", 1);
    setenv("MESA_VK_WSI_PRESENT_MODE", "mailbox", 1);

    setenv("BOX64_DYNAREC", "1", 1);
    setenv("BOX64_DYNAREC_STRONGMEM", "1", 1);

    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL
Java_com_vulkan_mali_zink_NativeHook_loadModLibrary(JNIEnv *env, jclass clazz, jstring path) {
    const char *lib_path = (*env)->GetStringUTFChars(env, path, NULL);

    if (is_x86_64_binary(lib_path)) {
        LOGI("x86_64 Mod -> Hooking Box64...");
        void* (*box64_dlopen)(const char*, int) = (void*(*)(const char*, int))dlsym(RTLD_DEFAULT, "box64_dlopen");
        if (box64_dlopen) {
            box64_dlopen(lib_path, RTLD_GLOBAL);
        }
    } else {
        LOGI("ARM64/Java Mod -> Native Execution!");
        dlopen(lib_path, RTLD_GLOBAL);
    }

    (*env)->ReleaseStringUTFChars(env, path, lib_path);
}
