# Dependency for building this project
``` bash
sudo apt install build-essential cmake qt5-default qtcreator qtmultimedia5-dev libqt5multimedia5-plugins
```
# Install taglib headers for build 
``` bash
# under "OnePlayer" directory
cd ./lib/taglib-1.11.1
cmake -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_BUILD_TYPE=Release .
make
sudo make install
```
# Build the project in QtCreator