#include <iostream>
#include <sstream>
#include <string>

void demonstrate_string_streams()
{
    std::cout << "--- 1. Parsing Data using istringstream ---\n";
    std::string input_data = "Name: Akash Score: 95.5";
    std::istringstream iss(input_data); 

    std::string name_label, student_name, score_label;
    double student_score;

    iss >> name_label >> student_name;
    iss >> score_label >> student_score;

    std::cout << "Name label is " << name_label << std::endl;
    std::cout << "Parsed Name is " << student_name << std::endl;
    std::cout << "Score Label is " << score_label << std::endl;
    std::cout << "Parsed Score is " << student_score << std::endl;

    std::ostringstream oss;
    oss << "Student: " << student_name << 
    ", successfully finished the test and earned a score of " << student_score << " points" << std::endl;

    std::string final_formatted_string = oss.str();

    std::cout << "Final formatted string using ostringstream is " << final_formatted_string << std::endl;
}

void demonstrate_single_string_stream()
{
    std::cout << "--- 2. Parsing Data using stringstream ---\n";
    std::string input_data = "Name: Bharath Score: 85.6";

    std::stringstream sss(input_data);

    std::string name_label, student_name, score_label;
    double student_score;

    sss >> name_label >> student_name;
    sss >> score_label >> student_score;

    std::cout << "Name label is " << name_label << std::endl;
    std::cout << "Parsed Name is " << student_name << std::endl;
    std::cout << "Score Label is " << score_label << std::endl;
    std::cout << "Parsed Score is " << student_score << std::endl;

    sss.str(""); //Clear contents of stringstream
    sss.clear(); //Clear EOF flag in stringstream

    sss << "Student: " << student_name 
    << ", successfully finished the test and earned a score of " << student_score << " points. " << std::endl;

    std::string final_formatted_string = sss.str();

    std::cout << "Final formatted string using stringstream is " << final_formatted_string << std::endl;
}

void safe_type_conversion(const std::string& string_val)
{
    std::stringstream integer_conversion_ss(string_val);
    
    long long int integer_val = 0;

    integer_conversion_ss >> integer_val;

    // Check 1: Did the extraction succeed?
    // Check 2: Is the stream now at the End-of-File (EOF)? 
    // If it's at EOF, the *entire* string was converted.
    if(integer_conversion_ss.fail() || !integer_conversion_ss.eof())
    {
        std::cout << "Input '" << string_val << "' -> FAILED (Contains non-numeric data or wasn't fully read).\n";
    }
    else
    {
        std::cout << "Input '" << string_val << "' -> SUCCESS! Integer value: " << integer_val << "\n";
    }
}

int main()
{
    demonstrate_string_streams();
    demonstrate_single_string_stream();
    std::cout << "\n--- 3. Type Conversion Example ---" << std::endl;
    safe_type_conversion("1234");
    safe_type_conversion("1234a");
    safe_type_conversion("abc");
    safe_type_conversion("9000000000");
    return 0;
}