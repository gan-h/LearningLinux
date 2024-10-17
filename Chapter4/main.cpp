#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <memory>
using namespace std;

class File
{
    string filename;
    int fd;

public:
    File(string filename) : filename(filename)
    {
        fd = open(filename.c_str(), O_RDWR | O_APPEND);
        if (fd < 0)
        {
            throw "bruh it didn't work";
        }
    }

    void printFile()
    {
        std::unique_ptr<char[]> array = make_unique<char[]>(1000);
        int bytes_read = read(fd, array.get(), 999);
        array[-1 + bytes_read + 1] = '\0';
        cout << array.get();
    }

    void makeFileHole()
    {
        lseek(fd, 100000, SEEK_CUR); 
        write(fd, "hey this is a file hole!\n", 25);
    }

    ~File()
    {
        close(fd);
    }
};

int main()
{
    // Table 4-1: Standard File Descriptors:
    // 0 - standard input
    // 1 - standard output
    // 2 - standard error
    // Also known as stdin, stdout, stderr, POSIX names defined in <unistd.h>
    File f = File("./test.txt");
    f.printFile();
    f.makeFileHole();
}