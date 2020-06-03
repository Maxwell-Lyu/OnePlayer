# What is this
This is a simple music player using Qt5, written for my course NJU AP 2020  
Intented to learn qt as a demo project  
Code: ~1000 lines of cpp  

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
cp ./taglib/libtag.a ../
```
# Build the project in QtCreator







# Other problems

1. under ubuntu 14.04: no decoder for audio/mpeg

   ```bash
   sudo apt-get install gstreamer0.10-fluendo-mp3 
   ```

   
