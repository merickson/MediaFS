#include <fuse.h>
#include "mediafs.h"

int main (int argc, char **argv) {
  return fuse_main(argc, argv, &mediafs_filesystem_operations, NULL);
}
