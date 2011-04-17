#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#include <fuse.h>

#include "mediafs.h"
#include "mediafs_mgr.h"

static int mediafs_getattr(const char *path, struct stat *stbuf) {
    memset(stbuf, 0, sizeof(struct stat));

    if (strcmp(path, "/") == 0) { // FS root
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 3;
    } else if (!mfs_remote_available() && 
               mfs_file_is_remote(path)) { /* File is remote, and the remote FS is
                                         unavailable. */
        mfs_remote_getattr(path, stbuf);
    } else {
        return stat(path, stbuf);
    }

    return 0;
}

static int mediafs_open(const char *path, struct fuse_file_info *fi) {
    if (!mfs_remote_available() &&
        mfs_file_is_remote(path)) { /* If the remote is available,
                                       return that we can't access the
                                       file. */
        return -EACCES;
    }
#ifdef MEDIAFS_RO
    else if ((fi->flags & O_ACCMODE) != O_RDONLY) { // Only allow RO access.
        return -EACCES;
    }
#endif //MEDIAFS_RO

    return 0;
}

static int mediafs_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                           off_t offset, struct fuse_file_info *fi) {
    return 0;
}
