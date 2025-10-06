#include <iostream>
#include <string>
#include <fstream>
#include <json.hpp>

int main()
{
    std::string file1 = "./my_data.json";
    std::string file2 = "./my_data.txt";
    std::string text = "{name : John Doe , age : 30}\r\nWe are storing a json object in text file";
    nlohmann::json dataJson; 
    dataJson["name"] = "John Doe";
    dataJson["age"] = 30;
    std::ofstream write_to_file;
    write_to_file.open(file1);
    if(!write_to_file)
    {
        std::cerr << "Error opening " << file1 << " while attempting to write data into it " << std::endl;
        return 1;
    } 

    write_to_file << dataJson << std::endl;
    write_to_file.close();

    write_to_file.open(file2);
    if(!write_to_file)
    {
        std::cerr << "Error opening " << file2 << " while attempting to write data into it " << std::endl;
        return 1;
    } 

    write_to_file << text << std::endl;
    write_to_file.close();

    std::ifstream read_from_file(file1);
    if(!read_from_file)
    {
        std::cerr << "Error opening " << file1 << " while attempting to read data from it " << std::endl;
        return 1;
    } 

    nlohmann::json readJson;
    read_from_file >> readJson;

    std::cout << "READ JSON IS " << readJson.dump(2) << "\n";
    
    read_from_file.close();

    read_from_file.open(file2);
    if(!read_from_file)
    {
        std::cerr << "Error opening " << file2 << " while attempting to read data from it " << std::endl;
        return 1;
    } 

    std::string line;
    int i = 1;
    while(std::getline(read_from_file, line))
    {
        std::cout << "LINE NUMBER " << i << ": " << line << std::endl;
        i++;
    }
    read_from_file.close();

    return 0;
}