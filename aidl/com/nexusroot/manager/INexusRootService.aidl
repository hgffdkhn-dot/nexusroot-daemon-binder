package com.nexusroot.manager;

import com.nexusroot.manager.WhitelistItem;
import com.nexusroot.manager.INexusRootCallback;

interface INexusRootService {
    String getSuVersion();
    String getSuPath();
    boolean isDaemonAlive();

    List<WhitelistItem> getWhitelist();
    void addToWhitelist(in WhitelistItem item);
    void removeFromWhitelist(int uid);

    boolean requestAuth(int pid, int uid, in String[] capabilities);

    void registerCallback(INexusRootCallback callback);
    void unregisterCallback();
}
