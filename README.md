# Rtype

![example workflow](https://github.com/EpitechPromo2024/B-CPP-501-RUN-5-1-rtype-julien.pause/actions/workflows/build.yml/badge.svg)
![example workflow](https://github.com/EpitechPromo2024/B-CPP-501-RUN-5-1-rtype-julien.pause/actions/workflows/tests.yml/badge.svg)

## Compiling
### Setup Conan
- (linux) sudo pip3 install conan
- (windows) Installer le logiciel Conan sur le site officiel https://conan.io/downloads.html
- conan profile new --detect default
- (linux only) conan profile update settings.compiler.libcxx=libstdc++11 default
- conan config set general.revisions_enabled=1
- conan remote add -i 0 conancenter https://center.conan.io
- conan remote add bincrafters https://bincrafters.jfrog.io/artifactory/api/conan/public-conan

### Linux (WSL2 too)

- mkdir build
- cd build
- conan install ..
- cmake .. -G "Unix Makefiles"
- cmake --build .
- ./bin/rtype_client

### Windows

- mkdir build && cd build
- conan install ..
- cmake .. -G "Visual Studio 16"
- cmake --build .
- .\bin\rtype_client.exe
