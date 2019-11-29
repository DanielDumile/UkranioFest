#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sys/time.h>

int main(int argc, char **argv) {
    std::ifstream ifs("sortDic.txt");

    std::vector<std::string> vec;
    std::string palabra;

    while (ifs >> palabra) {
        vec.push_back(palabra);
    }

    timeval actual{}, final{};
    std::string p;

    while (true) {
        std::cin >> p;

        gettimeofday(&actual, nullptr);

        bool found = std::binary_search(vec.begin(), vec.end(), p);

        gettimeofday(&final, nullptr);

        final.tv_sec -= actual.tv_sec;
        final.tv_usec -= actual.tv_usec;

        std::cout << "found: " << found << ", " << final.tv_sec << "s " << final.tv_usec << "us" << std::endl;

    }

}