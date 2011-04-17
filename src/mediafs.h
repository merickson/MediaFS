#ifndef MEDIAFS_H_
#define MEDIAFS_H_

#define _FILE_OFFSET_BITS 64
#define FUSE_USE_VERSION 26

#include <fuse.h>

static int mediafs_getattr(const char *path, struct stat *stbuf);
static int mediafs_open(const char *path, struct fuse_file_info *fi);
static int mediafs_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                         off_t offset, struct fuse_file_info *fi);
static int mediafs_read(const char *path, char *buf, size_t size, off_t offset,
                        struct fuse_file_info *fi);

static struct fuse_operations mediafs_filesystem_operations = {
  .getattr = mediafs_getattr,
  .open    = mediafs_open,
  .read    = mediafs_read,
  .readdir = mediafs_readdir,
};

#endif //MEDIAFS_H_
