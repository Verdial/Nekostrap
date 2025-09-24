package com.nekostrap;

public class NekoStrap {
    static {
        System.loadLibrary("nekostrap");
    }

    public native void copySettings(String src, String dst);
}
