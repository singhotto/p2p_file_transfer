#ifndef FILE_MANAGER_GUARD
#define FILE_MANAGER_GUARD

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

class FileManager {
private:
    static const std::string FILE_PATH;
    static const std::string FILE_RECEIVED_PATH;
public:
    std::vector<std::string> getFileList() const;
    std::vector<char> getFile(const std::string& fileName) const;
    void writeFile(const std::string& fileName, const std::string& data);

    std::string convertBinaryToASCII(const std::vector<char>& data);
};

#endif // FILE_MANAGER_GUARD
