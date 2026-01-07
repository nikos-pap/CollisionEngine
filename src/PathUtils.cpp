#include "PathUtils.h"
#include <vector>
#include <system_error>

#if defined(_WIN32)
#include <windows.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#elif defined(__linux__)
#include <unistd.h>
#include <limits.h>
#endif

std::filesystem::path QueryExecutablePath() {
#if defined(_WIN32)
    std::vector<wchar_t> buf(32768);
    DWORD n = GetModuleFileNameW(nullptr, buf.data(), (DWORD)buf.size());
    if (n == 0) throw std::system_error((int)GetLastError(), std::system_category(), "GetModuleFileNameW failed");
    return std::filesystem::path(std::wstring(buf.data(), n));
#elif defined(__APPLE__)
    uint32_t size = 0;
    _NSGetExecutablePath(nullptr, &size);
    std::vector<char> buf(size + 1);
    if (_NSGetExecutablePath(buf.data(), &size) != 0) throw std::runtime_error("_NSGetExecutablePath failed");
    buf[size] = '\0';
    return std::filesystem::weakly_canonical(std::filesystem::path(buf.data()));
#elif defined(__linux__)
    std::vector<char> buf(PATH_MAX + 1);
    ssize_t n = readlink("/proc/self/exe", buf.data(), PATH_MAX);
    if (n < 0) throw std::system_error(errno, std::system_category(), "readlink(/proc/self/exe) failed");
    buf[(size_t)n] = '\0';
    return std::filesystem::path(buf.data());
#else
    return std::filesystem::current_path();
#endif
}
