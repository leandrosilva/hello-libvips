/**
 * https://github.com/libvips/libvips/tree/master/cplusplus
 *
 * g++ -g -Wall example.cc `pkg-config vips-cpp --cflags --libs`
 */

#include <string>
#include <iostream>
#include <sstream>

#include <vips/vips8>

using namespace vips;

void print_usage()
{
    std::cout << "Usage:\n  hello-libvips [from file] [to file]" << std::endl;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "ERROR: Missing arguments!" << std::endl;
        print_usage();
        exit(666);
    }

    if (VIPS_INIT(argv[0]))
        vips_error_exit(NULL);

    char* from_file_path = argv[1];
    std::string to_file_path(argv[2]);
    std::string to_file_ext = to_file_path.substr(to_file_path.find_last_of("."), to_file_path.length() - to_file_path.find_last_of("."));
    
    // load an image from a file
    VImage im = VImage::new_from_file(from_file_path, VImage::option()->set("access", "sequential"));
    std::cout << "Loaded " << im.width() << " x " << im.height() << " pixel image from " << from_file_path << std::endl;

    // write to a formatted memory buffer
    size_t size;
    void *buf;
    im.write_to_buffer(to_file_ext.c_str(), &buf, &size);
    std::cout << "Written to memory " << buf << " in png format, " << size << " bytes" << std::endl;

    // load from the formatted memory area
    im = VImage::new_from_buffer(buf, size, "");
    std::cout << "Loaded from memory now, " << im.width() << " x " << im.height() << " pixel image" << std::endl;

    // write back to a file
    im.write_to_file(to_file_path.c_str());
    std::cout << "Written back to " << to_file_path << std::endl;

    return (0);
}