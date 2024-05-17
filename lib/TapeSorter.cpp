//
// Created by Елизавета Кравченкова on 16.05.2024.
//

#include <sys/unistd.h>
#include <unistd.h>
#include "TapeSorter.h"




std::string CreatePath(uint32_t k){
    //char s[10];
    //sprintf(s, "%d", k);
    return "tmp/hook_"+ std::to_string(k);
}




int32_t* getListFromFile(const char* filename,uint32_t k){
    int32_t* mass=new int32_t [pow(2,k)];
    std::ifstream fin(filename);
    int32_t ch = 0;
    uint32_t pos=0;
    while (fin>>ch) {
        mass[pos]=ch;
        ++pos;
        if (pos==pow(2,k)){
            break;
        }
    }
    fin.close();
    return mass;
}

int32_t* getSortListFrom2SortedLists(int32_t* list1,int32_t* list2,uint32_t count){
    int32_t* mass=new int32_t [2*count];
    uint32_t idx1=0;
    uint32_t idx2=0;
    while (idx1<count && idx2 <  count){
        if (list1[idx1]<=list2[idx2]){
            mass[idx2+idx1]=list1[idx1];
            ++idx1;
        }
        else{
            mass[idx2+idx1]=list2[idx2];
            ++idx2;
        }
    }
    while (idx1< count){
        mass[idx2+idx1]=list1[idx1];
        ++idx1;
    }
    while (idx2 < count){
        mass[idx2+idx1]=list2[idx2];
        ++idx2;
    }
    delete [] list1;
    delete [] list2;
    return mass;
}


bool existKhook(uint32_t k){
    return (access(CreatePath(k).c_str(), F_OK ) != -1);
}

void hang(uint32_t k, int32_t* list){
    if (existKhook(k)){
        int32_t* other =  getListFromFile(CreatePath(k).c_str(),k);
        int32_t* sort=getSortListFrom2SortedLists(list,other,pow(2,k));
        hang(k+1, sort);
        remove(CreatePath(k).c_str());
        return;
    }
    std::ofstream fout;
    const char* name=CreatePath(k).c_str();
    fout.open(CreatePath(k), std::ios::out);
    if (!fout.is_open()) {
        std::cerr << " Файл для ленты не удалось создать ";
        return;
    }
    for (int i=0;i<pow(2,k);++i){
        fout<<list[i];
        if (i != (pow(2,k)-1)){
            fout<<'\n';
        }
    }
    delete [] list;
    fout.close();
}


void WriteSortListFrom2File(const char* file1,const char* file2,uint64_t count,const char* outfile){
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


void WriteSortListFromFile(const char* file1,const char* file2,const char* outfile){
    std::ifstream fin1(file1, std::ios::out);
    std::ifstream fin2(file2, std::ios::out);
    std::ofstream fout(outfile, std::ios::out);
    int32_t ch1;
    int32_t ch2;
    fin1>>ch1;
    fin2>>ch2;
    bool flag= false;

    while (!fin1.eof() && !fin2.eof()){
        flag=true;
        if (ch1<=ch2){
            fout<<ch1;
            fin1>>ch1;
            if (fin1.eof()){
                fout<<'\n'<<ch1;
                break;
            }
        }
        else{
            fout<<ch2;
            fin2>>ch2;
            if (fin2.eof()){
                fout<<'\n'<<ch2;
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
        if (!flag){
            if (ch2<=ch1){
                flag=true;
                fout<<ch2<<'\n';
            }
        }
        fout<<ch1;
        fin1>>ch1;
        if (fin1.eof()){
            fout<<'\n'<<ch1;
            break;
        }
        fout<<'\n';
    }
    while (!fin2.eof()){
        if (!flag){
            if (ch1<=ch2){
                flag=true;
                fout<<ch1<<'\n';
            }
        }
        fout<<ch2;
        fin2>>ch2;
        if (fin2.eof()){
            fout<<'\n'<<ch2;
            break;
        }
        fout<<'\n';
    }
    fin1.close();
    fin2.close();
    fout.close();
}


void hang2(uint32_t k, const char* filename){
    if (existKhook(k)){
        //int32_t* other =  getListFromFile(CreatePath(k).c_str(),k);
        //int32_t* sort=getSortListFrom2SortedLists(list,other,pow(2,k));
        WriteSortListFrom2File(filename,CreatePath(k).c_str(),pow(2,k),("tmp/sort"+ std::to_string(k)).c_str());
        hang2(k+1,( "tmp/sort"+ std::to_string(k)).c_str());
        remove(("tmp/sort"+ std::to_string(k)).c_str());
        remove(CreatePath(k).c_str());
        return;
    }
    std::filesystem::rename(filename,CreatePath(k));
    /*
    std::ofstream fout;
    const char* name=CreatePath(k).c_str();
    fout.open(CreatePath(k), std::ios::out);
    if (!fout.is_open()) {
        std::cerr << " Файл для ленты не удалось создать ";
        return;
    }
    for (int i=0;i<pow(2,k);++i){
        fout<<list[i];
        if (i != (pow(2,k)-1)){
            fout<<'\n';
        }
    }
    delete [] list;
    fout.close();
     */
}


uint32_t countFilesInDir(const char* name){
    uint32_t ans=0;
    for (auto const& dir_entry : std::filesystem::recursive_directory_iterator(name))
        ++ans;
    return ans;
}
void TapeSorter::Sort(Tape& tape) {

    std::filesystem::remove_all("tmp");
    std::filesystem::create_directories("tmp");
    std::ofstream fout("tmp/loop", std::ios::out);

    fout<<tape.Read();
    fout.close();
    hang2(0,"tmp/loop");

    while (tape.MoveLeft()){
        std::cout<<"\n read: "<<tape.Read();
        //list0=new int32_t [1]{tape.Read()};
        //hang(0,list0);
        fout.open("tmp/loop", std::ios::out);
        fout<<tape.Read();
        //int32_t* list0=new int32_t [1]{tape.Read()};
        fout.close();
        hang2(0,"tmp/loop");
    }
    remove("tmp/loop");

    uint64_t idx=0;
    while(countFilesInDir("tmp") > 1){
        std::filesystem::path first=begin(std::filesystem::recursive_directory_iterator("tmp"))->path();
        std::filesystem::path second=(++begin(std::filesystem::recursive_directory_iterator("tmp")))->path();
        std::cout<<first.c_str()<<" "<<second.c_str();
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
