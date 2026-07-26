package com.nexusroot.manager;

interface INexusRootCallback {
    void onLogEntry(int type, String tag, String message);
}