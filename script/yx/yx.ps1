function Run_file ($file) {
   $extension =  $file.Extension
   # 或取文件的扩展名
   if ($extension -eq '.py') {
       # Python 文件
       Write-Output $file.FullName
       python $file
   }
   if ($extension -eq '.ps1') {
       # Power Shell 文件
       Write-Output "this is a power shell file"
   }
   if ($extension -eq '.cpp' -or $extension -eq ".c"){
       # C/C++ 文件
        Write-Output "this is a C/C++ file"
        run g++ -g -static $file
        if($LASTEXITCODE -eq 0){
            run .\a.out
            Remove-Item a.out
        }else {
            Write-Output "filed"
        }

   }
}

if ($args.Count -eq 0) {
    # 如果不给要在终端运行的简单文件
    # 这里就要选择最后保存的文件 
    $files = Get-ChildItem | Sort-Object -Property LastWriteTime -Descending
    # 或取当前文件夹里面所有的文件并把文件按照最后保存的放在最前面
    # $myfile = $files[0]
    foreach ($i in $files) {
        if(".c .cpp .py .ps1"| Select-String $i.Extension){
            $myfile = $i
            break
        }
    }
    # 拿出最后保存的文件
    Run_file($myfile)
} else {
    Write-Output "You specified the file you want to run as you wish"
    foreach ($file in $args) {
    # 迭代出所有的输入参数
        $file  = Get-ChildItem $file
        # 将输入的文件名转换成文件对象
        Write-Output $file.FullName
        Run_file($file)
    }
}