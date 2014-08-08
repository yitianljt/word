//
//  FileTool.h
//  CrazyWord
//
//  Created by jintao on 14-8-6.
//
//

#ifndef __CrazyWord__FileTool__
#define __CrazyWord__FileTool__

#include <iostream>
#include <fstream>
#include <vector>


namespace COMutils {
    // 当前工作目录
    std::string getCurrentWorkingDirectory();
    
    // 检查目录最后是否含"/"，没有则补上
    void checkPath(std::string &path);
    
    // 创建目录
    bool createDirectory(const char *path);
    
    // 删除空目录
    bool deleteDirectory(const char *path);
    
    // 递归删除目录
    int rmrf(const char *path);
    
    // 获取某个路径下的所有文件名，包括目录
    std::vector<std::string> getFilesAtPath(const char *path);
    
    // 获取文件大小
    long long getFileSize(const char *fileName);
    
    // 判断文件是否存在
    bool fileExistsAtPath(const char *path);
    
    // 移除文件
    bool renameFile(const char *oldName, const char *newName);
    
    // 重命名或移动文件
    bool removeFile(const char *path);
    
    // 从文件读取数据
    bool readFile(const char *filename, const char *mode, std::string& buffer);
    bool readFile(const char *filename, const char *mode, std::vector<char>& buffer);
    
    // 写数据到文件
    bool writeFile(const char *filename, const char *mode, const std::string& data);
    bool writeFile(const char *filename, const char *mode, const char *data, long size);
    
    // 读方式打开文件，返回输入流
    inline std::ifstream& openFile(std::ifstream &in,
                                   const std::string &filename,
                                   std::ifstream::openmode mode = std::ios_base::in)
    {
        in.close();
        in.clear();
        in.open(filename.c_str(), mode);
        return in;
    }
    
    // 写方式打开文件，返回输出流
    inline std::ofstream& openFile(std::ofstream &out,
                                   const std::string &filename,
                                   std::ofstream::openmode mode = std::ios_base::out)
    {
        out.close();
        out.clear();
        out.open(filename.c_str(), mode);
        return out;
    }
    
}
#endif /* defined(__CrazyWord__FileTool__) */
