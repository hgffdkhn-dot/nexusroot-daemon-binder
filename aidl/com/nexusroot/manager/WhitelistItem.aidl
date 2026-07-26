package com.nexusroot.manager;

// 必须带上字段，成为结构化 Parcelable
parcelable WhitelistItem {
    int uid;
    String packageName;
    boolean allowed;
}
