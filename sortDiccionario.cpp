#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <regex>

static void removeAccented( std::string & str ) {
    std::stringstream result;
    std::regex filter("(á)+");
    std::regex_replace(std::ostream_iterator<char>(result), str.begin(), str.end(), filter, "&a");
    str = result.str();

    std::stringstream result1;
    filter = std::regex("(é)+");
    std::regex_replace(std::ostream_iterator<char>(result1), str.begin(), str.end(), filter, "&e");
    str = result1.str();

    std::stringstream result2;
    filter = std::regex("(í)+");
    std::regex_replace(std::ostream_iterator<char>(result2), str.begin(), str.end(), filter, "&i");
    str = result2.str();

    std::stringstream result3;
    filter = std::regex("(ó)+");
    std::regex_replace(std::ostream_iterator<char>(result3), str.begin(), str.end(), filter, "&o");
    str = result3.str();

    std::stringstream result4;
    filter = std::regex("(ú)+");
    std::regex_replace(std::ostream_iterator<char>(result4), str.begin(), str.end(), filter, "&u");
    str = result4.str();

    std::stringstream result5;
    filter = std::regex("(Á)+");
    std::regex_replace(std::ostream_iterator<char>(result5), str.begin(), str.end(), filter, "&a");
    str = result5.str();

    std::stringstream result6;
    filter = std::regex("(É)+");
    std::regex_replace(std::ostream_iterator<char>(result6), str.begin(), str.end(), filter, "&e");
    str = result6.str();

    std::stringstream result7;
    filter = std::regex("(Í)+");
    std::regex_replace(std::ostream_iterator<char>(result7), str.begin(), str.end(), filter, "&i");
    str = result7.str();

    std::stringstream result8;
    filter = std::regex("(Ó)+");
    std::regex_replace(std::ostream_iterator<char>(result8), str.begin(), str.end(), filter, "&o");
    str = result8.str();

    std::stringstream result9;
    filter = std::regex("(Ú)+");
    std::regex_replace(std::ostream_iterator<char>(result9), str.begin(), str.end(), filter, "&u");
    str = result9.str();
}

int main() {
    std::ifstream ifs("diccionario.txt");

    std::vector<std::string> vec;

    std::string n, palabra, fre, norm;
    int i = 0;
    while (ifs >> n >> palabra >> fre >> norm) {
        // Transformar tildes a normales
        removeAccented(palabra);

        std::cout << palabra << std::endl;

        vec.push_back(palabra);
        std::cout << i << std::endl;
        i++;
    }

    std::sort(vec.begin(), vec.end());

    std::ofstream ofs("./sortDic.txt");

    std::ostream_iterator<std::string> output_iterator(ofs, "\n");
    std::copy(vec.begin(), vec.end(), output_iterator);
}