#include <fstream>

#include <iostream>

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const* argv[])
{
    std::ifstream in("board_2015_12_07.txt", std::ios::in);

    int count = 0;
        char sink[3] = {""};
        int size = 3;
        char delim = '|';
        while (in.good()){
        if (0 != in.getline(sink, size, delim)) {

            std::cout << "sink: " << atoi(sink) << std::endl;
            count = count + 1;
            bzero(sink, 0);
        }

    }

    std::cout << count << std::endl;
    in.close();
    return 0;
}
