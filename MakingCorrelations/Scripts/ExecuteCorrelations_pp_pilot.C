#include "GetCorrelations_pp.C"

int main(int argc, char* argv[]) {
  const char* filename = argv[1];
  //prefix: should be the same for both files
  const char* prefix = argv[2];
  const char *subwag = (argv[3]) ? argv[3] : "";

  GetCorrelations_pp(filename, prefix,subwag, 0.6, 1.);
  return 1;
}
