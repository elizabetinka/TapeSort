//
// Created by Елизавета Кравченкова on 16.05.2024.
//

#include <sys/unistd.h>
#include <unistd.h>
#include "TapeSorter.h"

std::string TapeSorter::CreatePath(uint32_t k){
    return "tmp/hook_"+ std::to_string(k);
}

bool TapeSorter::existKhook(uint32_t k){
    return (access(CreatePath(k).c_str(), F_OK ) != -1);
}

void TapeSorter::WriteSortListFromFile(const char* file1,const char* file2,const char* outfile){
    std::ifstream fin1(file1, std::ios::out);
    std::ifstream fin2(file2, std::ios::out);
    std::ofstream fout(outfile, std::ios::out);
    if (!fin1.is_open()){
        throw std::runtime_error("can't open file");
    }
    if (!fin2.is_open()){
        throw std::runtime_error("can't open file");
    }
    if (!fout.is_open()){
        throw std::runtime_error("can't open file");
    }
    int32_t ch1;
    int32_t ch2;
    fin1>>ch1;
    fin2>>ch2;
    bool flag= false;
    bool miss= false;

    while (!fin1.eof() && !fin2.eof()){
        flag=true;
        if (ch1<=ch2){
            fout<<ch1;
            fin1>>ch1;
            if (fin1.eof()){
                //fout<<'\n'<<ch1;
                miss=true;
                break;
            }
        }
        else{
            fout<<ch2;
            fin2>>ch2;
            if (fin2.eof()){
                miss=true;
                break;
            }
        }
        if (!fin1.eof() && !fin2.eof()){
            fout<<'\n';
        }
    }
    if (flag && (!fin1.eof() || !fin2.eof())){
        fout<<'\n';
    }

    while (!fin1.eof()){
        if ( miss){
            if (ch2<=ch1){
                miss=false;
                fout<<ch2<<'\n';
            }
        }
        fout<<ch1;
        fin1>>ch1;
        if (fin1.eof()){
            if ( miss){
                if (ch2<=ch1){
                    miss=false;
                    fout<<ch2<<'\n';
                }
            }
            fout<<'\n'<<ch1;
            if (miss){
                fout<<'\n'<<ch2;
            }
            break;
        }
        fout<<'\n';
    }
    while (!fin2.eof()){
        if (miss){
            if (ch1<=ch2){
                miss=false;
                fout<<ch1<<'\n';
            }
        }
        fout<<ch2;
        fin2>>ch2;
        if (fin2.eof()){
            if (miss){
                if (ch1<=ch2){
                    miss=false;
                    fout<<ch1<<'\n';
                }
            }
            fout<<'\n'<<ch2;
            if (miss){
                fout<<'\n'<<ch1;
            }
            break;
        }
        fout<<'\n';
    }
    if (!flag){
        if (ch1<=ch2){
            fout<<ch1<<'\n'<<ch2;
        }
        else{
            fout<<ch2<<'\n'<<ch1;
        }

    }

    fin1.close();
    fin2.close();
    fout.close();
}


void TapeSorter::hang(uint32_t k, const char* filename){
    if (existKhook(k)){
        //WriteSortListFrom2File(filename,CreatePath(k).c_str(),pow(2,k),("tmp/sort"+ std::to_string(k)).c_str());
        WriteSortListFromFile(filename,CreatePath(k).c_str(),("tmp/sort"+ std::to_string(k)).c_str());
        hang(k+1,( "tmp/sort"+ std::to_string(k)).c_str());
        remove(("tmp/sort"+ std::to_string(k)).c_str());
        remove(CreatePath(k).c_str());
        return;
    }
    std::filesystem::rename(filename,CreatePath(k));
}


uint32_t TapeSorter::countFilesInDir(const char* name){
    uint32_t ans=0;
    for (auto const& dir_entry : std::filesystem::recursive_directory_iterator(name))
        ++ans;
    return ans;
}

void TapeSorter::Sort(ITape& tape) {
    std::filesystem::remove_all("tmp");
    std::filesystem::create_directories("tmp");
    std::ofstream fout("tmp/loop", std::ios::out);
    if (!fout.is_open()){
        throw std::runtime_error("can't open file");
    }
    fout<<tape.Read();
    fout.close();
    hang(0,"tmp/loop");

    while (tape.MoveLeft()){
        fout.open("tmp/loop", std::ios::out);
        if (!fout.is_open()){
            throw std::runtime_error("can't open file");
        }
        fout<<tape.Read();
        fout.close();
        hang(0,"tmp/loop");
    }
    remove("tmp/loop");

    uint64_t idx=0;
    while(countFilesInDir("tmp") > 1){
        std::filesystem::path first=begin(std::filesystem::recursive_directory_iterator("tmp"))->path();
        std::filesystem::path second=(++begin(std::filesystem::recursive_directory_iterator("tmp")))->path();
        WriteSortListFromFile(first.c_str(),second.c_str(),("tmp/rec"+std::to_string(idx)).c_str());
        ++idx;
        std::filesystem::remove(first.c_str());
        std::filesystem::remove(second.c_str());
    }
    for (std::filesystem::path  dir_entry : std::filesystem::directory_iterator("tmp")){
        tape.ChangeData(dir_entry.c_str());
        return;
    }

}


void TapeSorter::WriteSortListFrom2File(const char* file1,const char* file2,uint64_t count,const char* outfile){
    std::ifstream fin1(file1, std::ios::out);
    std::ifstream fin2(file2, std::ios::out);
    std::ofstream fout(outfile, std::ios::out);
    int32_t ch1;
    int32_t ch2;
    fin1>>ch1;
    fin2>>ch2;
    uint64_t idx1=0;
    uint64_t idx2=0;
    while (idx1<count && idx2 <  count){
        if (ch1<=ch2){
            fout<<ch1;
            ++idx1;
            if (idx1<(count)){
                fin1>>ch1;
            }
        }
        else{
            fout<<ch2;
            ++idx2;
            if (idx2<(count)){
                fin2>>ch2;
            }
        }
        if ((idx1+idx2)!=(2*count)){
            fout<<'\n';
        }
    }

    while (idx1< count){
        fout<<ch1;
        ++idx1;
        if (idx1<(count)){
            fin1>>ch1;
        }
        if ((idx1+idx2)!=(2*count)){
            fout<<'\n';
        }
    }
    while (idx2 < count){
        fout<<ch2;
        ++idx2;
        if (idx2<(count)){
            fin2>>ch2;
        }
        if ((idx1+idx2)!=(2*count)){
            fout<<'\n';
        }
    }
    fin1.close();
    fin2.close();
    fout.close();
}
