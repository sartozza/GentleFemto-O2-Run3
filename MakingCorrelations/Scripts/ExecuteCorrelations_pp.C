#include "GetCorrelations_pp.C"

int main(int argc, char* argv[]) {
  const char* filename1 = argv[1];
  const char *filename2 = argv[2];
  //prefix: should be the same for both files
  const char* prefix = argv[3];
  const char* addon = (argv[4]) ? argv[3] : "";
  GetCorrelations_pp(filename1, filename2, prefix, addon, 0.24, 0.34);
  return 1;
}
