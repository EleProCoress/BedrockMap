$build_dir = "./build"
if (!(Test-Path $build_dir)) {
    New-Item -Path "." -Name $build_dir -ItemType Directory 
}
# 编译
cmake -G "MinGW Makefiles" -B  $build_dir .
cmake --build $build_dir --config Debug -j 18 -- 