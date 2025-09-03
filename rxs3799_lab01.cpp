//Name: Riyan Shrestha
//ID: 1002223799
//Language Version: C++ (GCC 13.3.0)
//OS: Ubuntu 24.04 (Omega server)

#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

uintmax_t calculate_size(const fs::path& path) {
    uintmax_t total = 0;
    error_code ec;  // Used to handle errors without exceptions

    // Iterate through all entries in the current directory
    for (const auto& entry : fs::directory_iterator(path, ec)) {
        if (ec) {
            continue; // Skip entries thta cannot be read
        }

        // Check if the current entry is a directory
        if (entry.is_directory(ec)) {
            // Recurse into the subdirectory
            total += calculate_size(entry.path());
        } else if (entry.is_regular_file(ec)) {
            // Add size of a normal file
            auto sz = entry.file_size(ec);
            if (!ec) {
                total += sz;
            }
        }
    }

    return total;
}

int main(int argc, char* argv[]) {
    try {
        fs::path start_dir = (argc > 1) ? fs::path(argv[1]) : fs::path(".");
        // Use command line argument for the starting directory or use the current directory if not provided 
        uintmax_t bytes = calculate_size(start_dir);
        cout << bytes << endl;
    } catch (const fs::filesystem_error& ex) {
        cerr << "Filesystem error: " << ex.what() << endl;
        return 1;
    }
    return 0;
}
