param (
    [string]$command
)

if ($command -eq "build") {
    # Run CMake to generate build files
    cmake -G "MinGW Makefiles" -B ./build
}
elseif ($command -eq "make") {
    # Run mingw32-make in the build directory
    mingw32-make --directory ./build
    if ($LASTEXITCODE -ne 0) {
        Write-Host "There were build errors..."
        Write-Host "Build exited with status code $LASTEXITCODE"
    }
}
elseif ($command -eq "run") {
    # Run the executable in the bin directory
    ./bin/main
}
elseif ($command -eq "clean") {
  Remove-Item -force -recurse ./build
  Remove-Item -force -recurse ./bin
} 
elseif ($command -eq "make-run") {
    mingw32-make --directory ./build

    if ($LASTEXITCODE -eq 0) {
        Write-Host "Build succeeded.."
        Write-Host "Running Build.."
        Write-Host "-----------------------------------------"
        Write-Host
        ./bin/main
    }
    else {
        Write-Host "Can't run build failed"
    }
} 
else {
    Write-Host "Invalid command. Use 'build', 'make', 'run', 'build-run' or 'clean'."
}
