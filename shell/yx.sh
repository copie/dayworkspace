#!/bin/bash
if [ $# != 0 ] && [ -e $1 ] && [ -s $1 ] && [ -f $1 ]
then
    myfile=$1
    if [ "${myfile##*.}" == "cpp" ] || [ "${myfile##*.}" == "c" ] || [ "${myfile##*.}" == "cc" ]
    then
        # 编译C++
        
        g++ -g -std=gnu++14 -static $1
        if [ $? -eq 0 ]
        then
            trap "rm -f ./a.out; exit" 1 2 3 8 9 14 15
            ./a.out
            rm ./a.out
            exit
        fi
    fi
    
    if [ "${myfile##*.}" == "py" ]
    then
        # 运行python3
        python3 $* 
        exit
    fi
    echo "输入正确的文件"
fi
if [ $# -eq 0 ]
then
    myfile=`ls -lt | head -n 2 | awk '{print $9}'`
    if [ "${myfile##*.}" == "cpp" ] || [ "${myfile##*.}" == "c" ] || [ "${myfile##*.}" == "cc" ]
    then
        # 编译C++
        echo $myfile
        g++ -g -std=gnu++14 -static $myfile
        if [ $? -eq 0 ]
        then
            trap "rm -f ./a.out; exit" 1 2 3 8 9 14 15
            ./a.out
            rm ./a.out
            exit
        fi
    fi
    
    if [ "${myfile##*.}" == "py" ]
    then
        # 运行python3
        echo $myfile
        python3 $myfile 
        exit
    fi
    echo "没有匹配到文件"
fi