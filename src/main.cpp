#include "adpcm.h"
#include <cstdint>
#include <iostream>
#include <string.h>
using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 3) {
    cout << "Should be of the format \"./build/main (--e|--d) "
            "--if=<input_file> --of=<output_file>\"\n";
  }

  for (int i = 0; i < argc; i++) {
    void (*function)(short *, char *, int);
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
      int8_t *data_buffer[BUFFER_SIZE]; // Buffering because big files rip
      int total_size{0};
      while ((bytes_read =
                 fread(data_buffer, sizeof(int8_t), BUFFER_SIZE/sizeof(int8_t), input_data)) > 0) {
        total_size+=bytes_read;
      }
    }
  }
}
