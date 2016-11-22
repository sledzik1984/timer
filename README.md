On clean, freshly installed Raspbian:

apt-get install qt5-qmake qt5-default libqt5svg5-dev 

git clone https://github.com/dimitry-ishenko-casparcg/oscpack.git
cd oscpack
make 
make install


git clone https://github.com/dimitry-ishenko-casparcg/timer.git
qmake
make
