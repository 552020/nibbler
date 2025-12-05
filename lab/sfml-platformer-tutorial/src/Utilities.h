#pragma once

#include <iostream>
#include <string>
#include <algorithm>

namespace Utils {
#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #include <Shlwapi.h>
    inline std::string GetWorkingDirectory() {
        HMODULE hModule = GetModuleHandle(nullptr);
        if (hModule) {
            char path[256];
            GetModuleFileName(hModule, path, sizeof(path));
            PathRemoveFileSpec(path);
            strcat_s(path, "\\");
            return std::string(path);
        }
        return "";
    }
#elif defined(__APPLE__) || defined(__linux__)
    #include <unistd.h>
    #include <limits.h>
    inline std::string GetWorkingDirectory() {
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != nullptr) {
            return std::string(cwd) + std::string("/");
        }
        return "";
    }
#else
    // Fallback for other platforms
    inline std::string GetWorkingDirectory() {
        return "./";
    }
#endif
}

