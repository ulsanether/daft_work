우분투 1차 정리 

cmake 3.15.2 설치 참조 
$ wget https://cmake.org/files/v3.15/cmake-3.15.2.tar.gz
$ tar xvfz cmake-3.15.2.tar.gz
$ cd cmake-3.15.2
$ ./bootstrap
$ make
$ make install
$ cmake --version


GDAL 설치 참조
gdal설치는 아래를 사용 
sudo apt install gdal-bin

https://mothergeo-py.readthedocs.io/en/latest/development/how-to/gdal-ubuntu-pkg.html
안되면 아래 리포지토리 추가 할것 
sudo add-apt-repository ppa:ubuntugis/ubuntugis-unstable
sudo apt install gdal-bin python-gdal python3-gdal


GTEST 적용 참고
참고한 사이트
https://tech.sangron.com/archives/453

sudo apt-get install libgtest-dev
(이후 시스템에는 소스코드만 설치 됨으로 사용자가 컴파일 하여 lib 폴더로 옮겨야 한다.)
sudo apt-get install cmake # install cmake
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make

# copy or symlink libgtest.a and libgtest_main.a to your /usr/lib folder
sudo cp *.a /usr/lib

gtest에러시 참고 
https://stackoverflow.com/questions/24295876/cmake-cannot-find-googletest-required-library-in-ubuntu



젯슨나노 wifi 접속 에러시 참고
 pciacm 지원 off 
참고 사이트
https://forums.developer.nvidia.com/t/disable-aspm-via-kernel-command-line/214498/2
부팅시 인텔 WIFI모듈 접속에 문제가 생겼을 경우 꺼줘야 한다. 


UDEV관련 사항시
근본적으로 idVendor과 idProduct등등의 이름 까지 같을 경우는 해결이 안되었다. 
https://ds5qdr-dv.tistory.com/127
https://ahnbk.com/?p=1702


우분투 패키지 관리 명령어 참고  
https://wnw1005.tistory.com/363


openni2  18이후 버전에 설치 되는것 
https://github.com/mikeh9/OpenNI2-TX1


다운 캐시 락 걸렸을때
sudo rm /var/lib/apt/lists/lock 
sudo rm /var/cache/apt/archives/lock
sudo rm /var/lib/dpkg/lock*
sudo dpkg --configure -a
sudo apt update



설치된 패키지 확인 방법

$ dpkg --get-selections
설치된 패키지의 설치경로 확인방법
$ dpkg -L 패키지 이름
설치된 패키지의 버전 확인방법
$ dpkg -l 패키지이름
dpkg -l libcgal-dev


포트 확인 
ls -al /dev/serial/by-id
ls -l /dev/ttyS* /dev/ttyUSB* /dev/ttyTHS*
ls -ltrh /dev/video* 

udevadm info -a /dev/ttyUSB0 | grep '{serial}'
udevadm info /dev/ttyUSB1 

udevadm monitor --udev --subsystem-match=usb --property


cmake 쓰는 법  
https://gist.github.com/luncliff/6e2d4eb7ca29a0afd5b592f72b80cb5c

파이썬 라이브러리 cmake 빌드 
https://stackoverflow.com/questions/55439016/how-to-fix-importerror-no-module-named-tensorflow-when-embedding-python-in


파이선 cmake
https://stackoverflow.com/questions/72159216/embed-python-in-c-using-cmake



파이썬 c++ 설명 잘된것 
https://kukuta.tistory.com/83?category=984648

파이썬 플라스크 
https://github.com/smoqadam/PyFladesk
