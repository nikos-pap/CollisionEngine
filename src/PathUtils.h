#pragma once
#include <filesystem>
#include <string_view>

std::filesystem::path QueryExecutablePath();

inline const std::filesystem::path& GetExecutablePath() { 
	static const std::filesystem::path p = QueryExecutablePath();
	return p;
}
inline const std::filesystem::path& GetExecutableDir() { 
	static const std::filesystem::path d = GetExecutablePath().parent_path();
	return d;
}
inline const std::filesystem::path& GetShaderRoot() {
	static const std::filesystem::path s = GetExecutableDir() / "shaders";
	return s;
}

inline std::filesystem::path ResolveFromExeDir(std::filesystem::path path) {

	if (path.is_absolute()) {
		return path;
	}

	return GetExecutableDir() / path;
}
