#include "fastBPE.hpp"
#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace fastBPE;

void printUsage() {
  cerr
      << "usage: fastbpe <command> <args>\n\n"
      << "The commands supported by fastBPE are:\n\n"
      << "getvocab input1 [input2]                  extract the vocabulary from one "
         "or two text files\n"
      << "learnbpe nCodes input1 [input2]           learn BPE codes from one or two "
         "text files\n"
      << "applybpe output input codes rate [vocab]  apply BPE codes to a text file\n"
      << "applybpe_stream codes rate [vocab]        apply BPE codes to stdin and output to stdout\n"
      << endl;
}


int main(int argc, char **argv) {
  if (argc < 2) {
    printUsage();
    exit(EXIT_FAILURE);
  }

  /* initialize random seed: */
  srand(time(NULL));

  string command = argv[1];
  if (command == "getvocab") {
    assert(argc == 3 || argc == 4);
    getvocab(argv[2], argc == 4 ? argv[3] : "");
  } else if (command == "learnbpe") {
    assert(argc == 4 || argc == 5);
    learnbpe(stoi(argv[2]), argv[3], argc == 5 ? argv[4] : "");
  } else if (command == "applybpe") {
    assert(argc == 6 || argc == 7);
    applybpe(argv[2], argv[3], argv[4], argc == 7 ? argv[6] : "", argv[5]);
  } else if (command == "applybpe_stream") {
    assert(argc == 4 || argc == 5);
    applybpe_stream(argv[2], argc == 5 ? argv[4] : "", argv[3]);
  } else {
    printUsage();
    exit(EXIT_FAILURE);
  }
  return 0;
}
