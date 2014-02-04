#include <algorithm>
#include <vector>
#include <cstdio>
#include <cassert>

int main(int argc, char* argv[]) {
  char bytes[256];
  for (int i = 0; i < 256; i++)
    bytes[i] = i;
  std::random_shuffle(bytes, bytes+256);

  FILE* out = fopen("1each.bin", "w");
  assert(out != NULL);

  // Ain't nobody got time for write errors
  int res = fwrite(bytes, sizeof(char), 256, out);
  assert(res == 256);
  res = fclose(out);
  assert(res == 0);

  return 0;
}
