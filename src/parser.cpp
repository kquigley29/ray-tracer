#include "raytracer/parser.h"
#include <fstream>


std::string get_option_name(const std::string& option)
{
    std::string::size_type pos = option.find('=');
    return option.substr(0, pos);
}


std::string get_option_value(const std::string& option)
{
    std::string::size_type pos = option.find('=');
    return option.substr(pos + 1, option.size() - 1);
}


double get_option_value_double(const std::string& option)
{
    std::string value_str = get_option_value(option);
    return std::stod(value_str);
}


Eigen::Vector3d get_option_value_vector(const std::string& option)
{
    std::string value_str = get_option_value(option);
    std::vector<double> points(3);
    unsigned int start = value_str.find('(') + 1;
    unsigned int end = value_str.find(')') - 1;

    std::string vector_str = value_str.substr(start, end);

    std::stringstream ss(vector_str);
    std::string token;
    char delimiter = ',';
    int i = 0;

    while (std::getline(ss, token, delimiter))
    {
        points[i] = std::stod(token);
        i++;
    }
    return {points[0], points[1], points[2]};
}


std::array<double, 2> get_option_value_resolution(const std::string& option)
{
    std::string value_str = get_option_value(option);
    unsigned int x = value_str.find('x');
    double width = std::stod(value_str.substr(0, x));
    double height = std::stod(value_str.substr(x + 1));
    return {width, height};
}


std::vector<std::vector<std::string>> read_cfg(char* filename)
{
    std::ifstream file(filename);
    std::string line;
    int line_number = 0;

    std::vector<std::string> part;
    std::vector<std::vector<std::string>> parts;

    while (std::getline(file, line))
    {
        line_number++;
        line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

        switch (line[0])
        {
            case '[':
                if (part.empty())
                {
                part.push_back(line);
                }
                else
                {
                    parts.push_back(part);
                    part = std::vector<std::string>();
                    part.push_back(line);
                }
                break;

            case '\0':
            case '#':
            case ';':
                break;

            case '-':
                part.push_back(line.substr(1));
                break;

            default:
                printf("[cfg error] Failed to parse line %d.\n\n", line_number);
        }
    }
    parts.push_back(part);
    return parts;
}
