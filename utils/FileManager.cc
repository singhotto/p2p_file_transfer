#include "FileManager.hh"

const std::string FileManager::FILE_PATH = "./manager/files";
const std::string FileManager::FILE_RECEIVED_PATH = "./manager/received";

std::vector<std::string> FileManager::getFileList() const {
    std::vector<std::string> fileNames;

    try {
        // Check if the directory exists
        if (!fs::exists(FILE_PATH)) {
            std::cerr << "Directory does not exist: " << FILE_PATH << '\n';
            return fileNames;
        }
        
        if (!fs::is_directory(FILE_PATH)) {
            std::cerr << "Path is not a directory: " << FILE_PATH << '\n';
            return fileNames;
        }

        // Iterate through the directory
        for (const auto& entry : fs::directory_iterator(FILE_PATH)) {
            if (entry.is_regular_file()) {
                fileNames.push_back(entry.path().filename().string());
            }
        }

        // Sort the file names in ascending order
        std::sort(fileNames.begin(), fileNames.end());
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << '\n';
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }

    return fileNames;
}

std::vector<char> FileManager::getFile(const std::string& fileName) const {
    std::string fullPath = FILE_PATH + "/"+fileName;
    std::ifstream file(fullPath, std::ios::binary | std::ios::ate);
    
    if (!file) {
        std::cerr << "Error opening file: " << fullPath << '\n';
        return {}; // Return an empty vector if file can't be opened
    }

    // Get the size of the file
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Resize the buffer to the size of the file
    std::vector<char> buffer(fileSize);

    // Read the file into the buffer
    if (!file.read(buffer.data(), fileSize)) {
        std::cerr << "Error reading file: " << fullPath << '\n';
        return {}; // Return an empty vector in case of read error
    }

    return buffer;
}

void FileManager::writeFile(const std::string &fileName, const std::string &data)
{
    std::string fullPath = FILE_RECEIVED_PATH + "/"+fileName;
    std::ofstream file(fullPath);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << fileName << '\n';
        return;
    }
    
    file << data;
}

std::string FileManager::convertBinaryToASCII(const std::vector<char>& data) {
    std::string asciiData;
    for (char c : data) {
        if (std::isprint(static_cast<unsigned char>(c))) {
            asciiData += c;
        } else {
            asciiData += '\n';
        }
    }
    return asciiData;
}
