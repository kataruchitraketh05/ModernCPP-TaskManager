#include <iostream>
#include <string>
#include <fstream>

struct Point 
{
    int x;
    int y;
};

void run_binary_io_setup()
{
    std::fstream file("points.bin", std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
    if(!file)
    {
        std::cerr << "Error opening points.bin\n";
        return;
    }

    Point p1 = {10, 20};
    Point p2 = {30, 40};
    Point p3 = {50, 60};

    auto pointSize = sizeof(Point);
    /*
    reinerpret_cast - Treat this memory address as a sequence of raw, unformatted bytes
    This is the most dangerous and powerful cast in C++. It simply takes the memory address 
    of one type (e.g., your Point struct) and forces the compiler to treat it as the memory 
    address of a completely different type (e.g., a char*).const char* / char*: In C++, streams 
    deal with data byte-by-byte. A pointer to a single byte of data is traditionally represented 
    by a pointer to a character (char*), as char is guaranteed to be one byte wide.
    */
    file.write(reinterpret_cast<const char*>(&p1), pointSize);
    file.write(reinterpret_cast<const char*>(&p2), pointSize);
    file.write(reinterpret_cast<const char*>(&p3), pointSize);

    std::cout << "Successfully wrote 3 Points in binary mode.\n";

    //Read data from the file
    Point bin_file_read;

    file.seekg(pointSize, std::ios::beg);// std::ios::beg means start counting from the beginning of the file
    file.read(reinterpret_cast<char*>(&bin_file_read), pointSize);

    if(file.gcount() == pointSize)
    {
        std::cout << "File read of Point P2 successful \n";
        std::cout << "  X: " << bin_file_read.x << ", Y: " << bin_file_read.y << std::endl;
    } 
    else 
    {
        std::cerr << "Error reading data or EOF reached.\n";
    }
    file.close();
}

int main()
{
    run_binary_io_setup();
    return 0;
}