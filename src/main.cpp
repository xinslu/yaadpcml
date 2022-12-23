#include <cstdio>
#include <iostream>
#include <string.h>
#include "adpcm.h"
using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cout << "Should be of the format \"./build/main (--e|--d) --if=<input_file> --of=<output_file>\"\n";
    }

    for (int i = 0; i < argc; i++) {
        void (*function)(short *,char *, int);
        if (strcmp(argv[i], "--e") == 0) {
            function = encode;
        }
        if (strcmp(argv[i], "--d") == 0) {
            function = decode;
        }
        
        if (strncmp(argv[i],"--if", 4) == 0) {
            string input_file(argv[i]+5);
            cout << input_file;
        }
    }  
}
