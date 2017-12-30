# SSH Alias begin
function SSH-FWQ{ bash -c 'ssh root@copie.cn'}
Set-Alias fwq SSH-FWQ
# SSH Alias end
# RUN C/C++ or Python file Alias begin
Set-Alias yx C:\Users\copie\Documents\dayworkspace\script\yx\yx.ps1
# RUN C/C++ or Python file Alias end
# copy file to clip Alias begin
function Copy-File-To-Clip ($file) {
        if ([String]::IsNullOrEmpty($file)){
            Write-Output "the file is miss"
            return $null
        }
        if(Test-Path $file){
            Get-Content $file | clip
            return $null            
        }
        Write-Output "the file is miss"
}
Set-Alias cv Copy-File-To-Clip
# copy file to clip Alias begin

# windows path to Linux path begin
function To-Linux-Path($file){
    $file = Get-ChildItem $file
    $file = $file.FullName
    $paths = $file.split("\")
    $file_path = '/mnt/'
    $pan = $paths[0].ToLower()[0]
    $file_path += $pan
    for ($i = 1; $i -lt $paths.Count; $i++) {
       $file_path += '/'
       $file_path += $paths[$i]
    }
    return $file_path
}
# windows path to Linux path end

# linux gcc Alias begin
function Linux-Gcc ($file) {
    $file = To-Linux-Path($file)
    $file = "gcc  " + $file
    bash -c $file
}
Set-Alias gcc Linux-Gcc
# linux gcc Alias end
# linux g++ Alias begin
function Linux-GPP ($file) {
    $file = To-Linux-Path($file)
    $file = "g++  " + $file
    bash -c $file
}
Set-Alias g++ Linux-GPP
# linux g++ Alias end
# Run Linux app begin
function Run-Linux-APP {
    $file = ""
    foreach ($i in $args) {
        if(Test-Path $i){
            $file += To-Linux-Path($i)
            $file += " "
        }else {
            $file += $i
            $file += " "
        }
        
    }
    bash -c $file
}
Set-Alias run Run-Linux-APP
# Run Linux app end