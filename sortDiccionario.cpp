#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

int main() {
    std::ifstream ifs("diccionario.txt");

    std::vector<std::string> vec;

    std::string n, palabra, fre, norm;
    int i = 0;
    while (ifs >> n >> palabra >> fre >> norm) {
        vec.push_back(palabra);
        std::cout << i << std::endl;
        i++;
    }

    std::sort(vec.begin(), vec.end());

    std::ofstream ofs("./sortDic.txt");

    std::ostream_iterator<std::string> output_iterator(ofs, "\n");
    std::copy(vec.begin(), vec.end(), output_iterator);
}