#include <iostream>
#include <string>
#include <windows.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
using namespace std;
string customer,command,addr1;
void moveFile(){
    fstream file;
    file.open("list.txt");
    string file_name;
    while(getline(file,file_name)){
        cout<<file_name<<endl;/*print all file*/
        command="move .\\" + file_name +" .\\"+customer;
        system(command.c_str());
    }
}
void moveFolder(){
    fstream file;
    file.open("Folder.txt");
    string folder_name,subfile;
    string command;
    while(getline(file,folder_name)){
        if(folder_name!=customer){ /*customer Folder是要移動的目的，過濾掉*/
            cout<<"folder: "+folder_name<<endl;/*print all file*/
            string subfile=addr1+folder_name;
            cout<<"now path="+subfile;
            if(_chdir(subfile.c_str())==0){
                cout<<"successfully enter"+folder_name<<endl;
            }else{
                cout<<"error"<<endl;
            }
            /*system( ("cd "+folder_name).c_str() );  */          /*enter folder ex:2017*/
            system(("dir *"+customer+"* /a /B /od >list.txt").c_str());   /*make a list.txt of file_name contains customer_name*/
            fstream file2;
            file2.open("list.txt");
            while(getline(file2,subfile)){

                system( ("md ..\\"+customer+"\\"+folder_name).c_str() );/*在廠商名稱資料夾下建立新的資料夾檔名為目前資料夾的檔名*/

                system( ("move "+subfile+" ..\\"+customer+"\\"+folder_name).c_str() );
            }
            chdir(addr1.c_str());
        }
    }
}
void rename(){
    string customer_folder;
    customer_folder+=customer;
    chdir(customer_folder.c_str());
    command="cmd /e:on /v:on /c \"for %f in (\".\\*"+customer+"*.*\") do (set \"n=%~nxf\" & set \"n=!n:"+customer+"-""=!\" & ren \"%~ff\" \"!n!\" )\"";
    system(command.c_str());
}
int main()
{   char moduleFileName[MAX_PATH];
    GetModuleFileNameA(0, moduleFileName, MAX_PATH);
    string addr(moduleFileName);
    size_t pos = addr.find_last_of("\\");
    addr = addr.substr(0, pos+1);
    addr1=addr;
    cout<<"請輸入廠商名稱:";
    cin>>customer;                         /* /A? */
    system( ("dir *"+customer+"*  /B /on >list.txt").c_str() );
    system( ("md "+customer).c_str() );/*make a new file "customer" under this file*/
    moveFile();
    command="dir /ad/b>Folder.txt";
    system( command.c_str() );/*save all directories name to Folder.txt*/
    /*according to Folder.txt move all *customer_name* Files under Folder to customer_name Folder*/
    moveFolder();
    rename();
    system("PAUSE");
    return 0;
}

