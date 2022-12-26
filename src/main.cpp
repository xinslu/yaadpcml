#include "adpcm.h"
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string.h>
using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 3) {
    cout << "Should be of the format \"./build/main (--e|--d) "
            "--if=<input_file> --of=<output_file>\"\n";
  }

  for (int i = 0; i < argc; i++) {
    void (*function)(int8_t *, int8_t *, int);
    int8_t *output_buffer;
    if (strcmp(argv[i], "--e") == 0) {
      function = encode;
    }
    if (strcmp(argv[i], "--d") == 0) {
      function = decode;
    }

    if (strncmp(argv[i], "--if", 4) == 0) {
      char *input_file = argv[i] + 5;
      FILE *input_data = std::fopen(input_file, "r");
      if (input_data == nullptr) {
        fprintf(stderr, "Unable to open wave file: %s\n", input_file);
        return 1;
      }
      wav_header header;
      size_t bytes_read = fread(&header, 1, sizeof(wav_header), input_data);
      cout << "File Header Read " << bytes_read << " bytes." << endl;
      if (bytes_read == 0) {
        fprintf(stderr, "Unable to read wave file: %s\n", input_file);
        return 1;
      }
      if (!(memcmp(header.RIFF, "RIFF", 4) == 0 &&
            memcmp(header.WAVE, "WAVE", 4) == 0 &&
            memcmp(header.fmt, "fmt", 3) == 0 &&
            memcmp(header.Subchunk2ID, "data", 4) == 0)) {
        fprintf(stderr, "Incorrect Header for the File: %s\n", input_file);
        return 1;
      }
      static const uint16_t BUFFER_SIZE = 8192;
      int8_t data_buffer[BUFFER_SIZE]; // Buffering because big files rip
      int total_size{0};
      if (function == nullptr) {
        fprintf(stderr, "You Must Specify the operation before the file name");
        return 1;
      }
      while ((bytes_read = fread(data_buffer, sizeof(int8_t),
                                 BUFFER_SIZE / sizeof(int8_t), input_data)) >
             0) {
        output_buffer = (int8_t *)malloc(bytes_read);
        function(data_buffer, output_buffer, bytes_read);
        total_size += bytes_read;
      }
    }
    if (strncmp(argv[i], "--of", 4) == 0) {
      char *output_file = argv[i] + 5;
      FILE *output_data = std::fopen(output_file, "w");
      if (output_data == nullptr) {
        fprintf(stderr, "Unable to open wave file to write: %s\n", output_file);
        return 1;
      }
    }
  }
}
