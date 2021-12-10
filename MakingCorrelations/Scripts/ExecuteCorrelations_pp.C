#include "GetCorrelations_pp.C"

int main(int argc, char* argv[]) {
  const char* filename = argv[1];
  const char* prefix = argv[2];
  const char* addon = (argv[3]) ? argv[3] : "";
  GetCorrelations_pp(filename, prefix, addon, 0.24, 0.34);
  return 1;
}
