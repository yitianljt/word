//
//  FileTool.cpp
//  CrazyWord
//
//  Created by jintao on 14-8-6.
//
//

#include "FileTool.h"
#include <cassert>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>


/******* android-8下没有<ftw.h>，使用<fts.h>来实现 ****/

#include <fts.h>

#define	FTW_F		0	/* File.  */
#define	FTW_D		1	/* Directory.  */
#define	FTW_DNR		2	/* Directory without read permission.  */
#define	FTW_DP		3	/* Directory with subdirectories visited.  */
#define	FTW_NS		4	/* Unknown type; stat() failed.  */
#define	FTW_SL		5	/* Symbolic link.  */
#define	FTW_SLN		6	/* Sym link that names a nonexistent file.  */

#define	FTW_PHYS	0x01	/* Physical walk, don't follow sym links.  */
#define	FTW_MOUNT	0x02	/* The walk does not cross a mount point.  */
#define	FTW_DEPTH	0x04	/* Subdirs visited before the dir itself. */
#define	FTW_CHDIR	0x08	/* Change to a directory before reading it. */

/****************************/

using namespace std;
namespace COMutils {
    
struct FTW {
    int base;
    int level;
};
    
std::string getCurrentWorkingDirectory()
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        //fprintf(stdout, "Current working dir: %s\n", cwd);
        return cwd;
    }
    else
    {
        perror("getcwd() error");
        return "";
    }
}
    
    
// 检查目录
void checkPath(string &path)
{
    if (path.size() > 0 && path[path.size() - 1] != '/')
    {
        path.append("/");
    }
}
    
// 创建目录
bool createDirectory(const char *path)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    BOOL ret = CreateDirectoryA(path, NULL);
    if (!ret && ERROR_ALREADY_EXISTS != GetLastError())
    {
        return false;
    }
    return true;
#else
    mode_t processMask = umask(0);
    int ret = mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO);
    umask(processMask);
    if (ret != 0 && (errno != EEXIST))
    {
        return false;
    }
    
    return true;
#endif
}
    
bool deleteDirectory(const char *path)
{
    if (rmdir(path) == 0)
    {
        return true;
    }
    else
    {
        fprintf(stderr, "rmdir(%s) failed.\n", path);
        return false;
    }
}
    
// 检查文件是否存在
bool fileExistsAtPath(const char *path)
{
    if( access(path, F_OK ) != -1 )
    {
        return true;
    }
    else
    {
        fprintf(stderr, "access file(%s) failed.\n", path);
        return false;
    }
}

    
    
// 目录遍历
int nftw(const char *path, int (*fn)(const char *, const struct stat *, int,
                                     struct FTW *), int nfds, int ftwflags)
{
    /* LINTED */
    char * const paths[2] = { (char *)path, NULL };
    struct FTW f;
    FTSENT *cur;
    FTS *ftsp;
    int ftsflags, fnflag, error, postorder, sverrno;
    
    /* XXX - nfds is currently unused */
    if (nfds < 1 || nfds > OPEN_MAX) {
        errno = EINVAL;
        return (-1);
    }
    
    ftsflags = FTS_COMFOLLOW;
    if (!(ftwflags & FTW_CHDIR))
        ftsflags |= FTS_NOCHDIR;
    if (ftwflags & FTW_MOUNT)
        ftsflags |= FTS_XDEV;
    if (ftwflags & FTW_PHYS)
        ftsflags |= FTS_PHYSICAL;
    postorder = (ftwflags & FTW_DEPTH) != 0;
    ftsp = fts_open(paths, ftsflags, NULL);
    if (ftsp == NULL)
        return (-1);
    error = 0;
    while ((cur = fts_read(ftsp)) != NULL) {
        switch (cur->fts_info) {
            case FTS_D:
                if (postorder)
                    continue;
                fnflag = FTW_D;
                break;
            case FTS_DNR:
                fnflag = FTW_DNR;
                break;
            case FTS_DP:
                if (!postorder)
                    continue;
                fnflag = FTW_DP;
                break;
            case FTS_F:
            case FTS_DEFAULT:
                fnflag = FTW_F;
                break;
            case FTS_NS:
            case FTS_NSOK:
                fnflag = FTW_NS;
                break;
            case FTS_SL:
                fnflag = FTW_SL;
                break;
            case FTS_SLNONE:
                fnflag = FTW_SLN;
                break;
            case FTS_DC:
                errno = ELOOP;
                /* FALLTHROUGH */
            default:
                error = -1;
                goto done;
        }
        f.base = cur->fts_pathlen - cur->fts_namelen;
        f.level = cur->fts_level;
        error = fn(cur->fts_path, cur->fts_statp, fnflag, &f);
        if (error != 0)
            break;
    }
done:
    sverrno = errno;
    (void) fts_close(ftsp);
    errno = sverrno;
    return (error);
}
    
    
// 解除文件链接
int unlink_cb(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    int rv = remove(fpath);
    
    if (rv)
        perror(fpath);
    
    return rv;
}
    
// 递归删除目录
int rmrf(const char *path)
{
    return nftw(path, unlink_cb, 64, FTW_DEPTH | FTW_PHYS);
}
    
// 获取某个路径下的所有文件名，包括目录
std::vector<std::string> getFilesAtPath(const char *path)
{
    vector<string> files;
    
    // 获得文件列表
    struct dirent *ent;
    DIR *dir = opendir(path);
    if (dir != NULL)
    {
        while ((ent = readdir (dir)) != NULL)
        {
            //fprintf (stdout, "%s\n", ent->d_name);
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0 )
            {
                continue;
            }
            
            files.push_back(ent->d_name);
        }
        closedir (dir);
    }
    else
    {
        // 打开目录失败
        fprintf(stderr, "opendir(%s) failed.\n", path);
    }
    
    return files;
}

    
// 文件大小
long long getFileSize(const char *fileName)
{
    struct stat fileStat;
    if (stat(fileName, &fileStat) == -1)
    {
        return -1;
    }
    return (long long)fileStat.st_size;
}

    
// 移除文件
bool removeFile(const char *path)
{
    if (remove(path) != 0)
    {
        fprintf(stderr, "can not remove file %s.\n", path);
        return false;
    }
    
    return true;
}
    
// 重命名或移动文件
bool renameFile(const char *oldName, const char *newName)
{
    if (rename(oldName, newName) != 0)
    {
        fprintf(stderr, "can not rename file %s.\n", oldName);
        return false;
    }
    
    return true;
}

bool readFile(const char *filename, const char *mode, std::string& buffer)
{
    assert(filename != NULL && mode != NULL && "Invalid parameters.");
    
    long size = 0;
    
    // 打开文件
    FILE *fp = fopen(filename, mode);
    if (!fp)
    {
        fprintf(stderr, "Get data from file(%s) failed!\n", filename);
        return false;
    }
    
    // 获取文件大小
    fseek(fp,0,SEEK_END);
    size = ftell(fp);
    fseek(fp,0,SEEK_SET);
    
    // 读取文件, 这里用了取地址操作，只有容器是连续存放的才可以
    buffer.resize(size);
    size = fread(&buffer[0], sizeof(char), size, fp);
    
    // 关闭文件
    fclose(fp);
    
    return true;
}
    
bool readFile(const char *filename, const char *mode, std::vector<char>& buffer)
{
    assert(filename != NULL && mode != NULL && "Invalid parameters.");
    
    long size = 0;
    
    // 打开文件
    FILE *fp = fopen(filename, mode);
    if (!fp)
    {
        fprintf(stderr, "Get data from file(%s) failed!\n", filename);
        return false;
    }
    
    // 获取文件大小
    fseek(fp,0,SEEK_END);
    size = ftell(fp);
    fseek(fp,0,SEEK_SET);
    
    // 读取文件, 这里用了取地址操作，只有容器是连续存放的才可以
    buffer.resize(size);
    size = fread(&buffer[0], sizeof(char), size, fp);
    
    // 关闭文件
    fclose(fp);
    
    return true;
}

// 写数据到文件
bool writeFile(const char *filename, const char *mode, const std::string& data)
{
    return writeFile(filename, mode, data.data(), data.size());
}

bool writeFile(const char *filename, const char *mode, const char *data, long size)
{
    assert(filename != NULL && mode != NULL && data != NULL && size >= 0 && "Invalid parameters.");
    
    // 打开文件
    FILE *fp = fopen(filename, mode);
    if (!fp)
    {
        fprintf(stderr, "Write data to file(%s) failed!\n", filename);
        return false;
    }
    
    // 写入文件
    fwrite(data, sizeof(char), size, fp);
    
    // 关闭文件
    fclose(fp);
    
    return true;
}
    
}