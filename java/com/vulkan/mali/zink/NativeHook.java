package com.vulkan.mali.zink;

public class NativeHook {
    static {
        System.loadLibrary("vulkan_mali_zink");
    }
    public static native void loadModLibrary(String path);
}
