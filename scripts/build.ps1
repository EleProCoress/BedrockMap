$build_dir = "./build"
if (Test-Path $build_dir) {
    Remove-Item $build_dir -Recurse -Force
}
New-Item -Path "." -Name $build_dir -ItemType Directory 
# 编译
cmake -G "MinGW Makefiles" -B  $build_dir .
cmake --build $build_dir --config Debug -j 18 -- 