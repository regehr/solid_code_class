#include <cstdio>
#include <cstring>
#include <cassert>

int main(int argc, char* argv[]) {
  FILE* out = fopen("increasing.bin", "w");
  assert(out != NULL);

  char bytes[256];
  for (int i = 0; i < 256; i++) {
    memset(bytes, i, i);
    // Irresponsible, but this is one-time code that generates test files, it's fine
    int res = fwrite(bytes, sizeof(char), i, out);
    assert(res == i);
  }

  int res = fclose(out);
  assert(res == 0);

  return 0;
}
