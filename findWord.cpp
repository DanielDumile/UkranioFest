#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sys/time.h>
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


int main(int argc, char **argv) {
    std::ifstream ifs("sortDic.txt");

    std::vector<std::string> vec;
    std::string palabra;

    while (ifs >> palabra) {
        vec.push_back(palabra);
    }

    ifs.close();

    timeval actual{}, final{};

    ifs.open("./textos_pruebas/Dostoievski, Fiódor (1880). Los hermanos Karamazov [14926].txt");

    while (ifs >> palabra) {
        // filtrar puntuacines y numeros
        const std::regex filter("([^A-zÁÉÍÓÚáéíóú])+");

        std::stringstream result;
        std::regex_replace(std::ostream_iterator<char>(result), palabra.begin(), palabra.end(), filter, "");

        palabra = result.str();

        // Transformar tildes a normales
        removeAccented(palabra);

        // tranforma a minusculas
        std::transform(palabra.begin(), palabra.end(), palabra.begin(),
                       [](unsigned char c) { return std::tolower(c); });


        std::cout << palabra << std::endl;


        // bucas palabra
        /*if (palabra.length()) {
            gettimeofday(&actual, nullptr);

            bool found = std::binary_search(vec.begin(), vec.end(), palabra);

            gettimeofday(&final, nullptr);

            final.tv_sec -= actual.tv_sec;
            final.tv_usec -= actual.tv_usec;

            std::cout << palabra << " found: " << found << ", " << final.tv_sec << "s " << final.tv_usec << "us"
                      << std::endl;
        }*/


    }

}