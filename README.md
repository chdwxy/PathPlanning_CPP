# PathPlanning_CPP
The C++ code implementation of the common algorithm for autonomous driving planning and control.

# Running ENV
This project runs on Ubuntu ststem, both 18.04 and 22.04 can run normally. 
``` bash
- python3
- matplotlib
- camke
- Eigen
- OSQP
- osqp-eigen
- imagemagick
- SFML
- CppAD
- Ipopt
- OpenCV
```

- eigen & osqp
``` bash
sudo apt install build-essential cmake git libeigen3-dev
git clone --recursive -b release-0.6.3 https://github.com/oxfordcontrol/osqp.git
cd osqp
mkdir build  
cd build
cmake .. 
make
sudo make install
source ~./bashrc
```

- osqp-eigen
``` bash
git clone https://github.com/robotology/osqp-eigen.git
cd osqp-eigen
mkdir build 
cd build
cmake .. 
make
sudo make install
```

- imagemagick
``` bash
git clone https://github.com/ImageMagick/ImageMagick.git ImageMagick-7.1.1
sudo apt-get remove imagemagick
cd ImageMagick-7.1.1
./configure --with-magick-plus-plus
make
sudo make install
sudo ldconfig /usr/local/lib
```

- SFML
``` bash 
sudo apt-get update
sudo apt-get install cmake libflac-dev libogg-dev libvorbis-dev libopenal-dev libjpeg-dev libfreetype6-dev libx11-dev libxrandr-dev libudev-dev libgl1-mesa-dev
wget https://www.sfml-dev.org/files/SFML-2.5.1-sources.zip
unzip SFML-2.5.1-sources.zip
mkdir SFML-build
cd SFML-build
cmake ../SFML-2.5.1
make
sudo make install
```

- CppAD & Ipopt  
The reference link is : https://blog.csdn.net/BigDavid123/article/details/136289314

- OpenCV  
The reference link is : https://blog.csdn.net/ljn1046016768/article/details/131485934?ops_request_misc=&request_id=&biz_id=102&utm_term=ubuntu%E4%B8%8A%E4%BD%BF%E7%94%A8opencv&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-3-131485934.142^v100^control&spm=1018.2226.3001.4187

# Compile
``` bash
cd Project
mkdir build
cd build
camke ..
make
```

# Result
``` bash
Planning -> Project/build/bin_planning;  
Tracking -> Project/build/bin_tracking; 
```