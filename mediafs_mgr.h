#ifndef MEDIAFS_MGR_H_
#define MEDIAFS_MGR_H_

int mfs_remote_available();
int mfs_path_is_remote(path);
int mfs_remote_getattr(path, stbuf);

#endif //MEDIAFS_MGR_H_
