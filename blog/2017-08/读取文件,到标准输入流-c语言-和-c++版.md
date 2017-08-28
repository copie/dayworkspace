#  读取文件，到标准输入流（c语言 和 c++版）

## c语言版

    #include<stdio.h>  
    #include<string.h>  
    
    int main()  
    {  
        freopen("E:/in.txt", "r", stdin); //文件输入到标准输入流   
        
        int temp;  
        for(int i = 0; i < 8; i++)  
        {  
            scanf("%d", &temp);  
            printf("%d ",temp);   
        }   
        
        fclose(stdin);  
        
        printf("\n");  
        return 0;  
    }

## C++版

    #include<iostream>  
    using namespace std;  
    #include<fstream>  
    
    int main()  
    {  
        ifstream cin("E:/in.txt"); //初始化一个输入流类(输入流是文件in.txt)   
        
        int temp;  
        for(int i = 0; i < 8; i++)  
        {  
            cin >> temp;  
            cout << temp << " ";  
        }  
        cout << endl;  
        
        cin.close();  
        
        return 0;  
    }  

* 创建一个输入流， 与文件关联