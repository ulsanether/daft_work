로스 2 관련 정리 

젯슨나노 이
https://ahnbk.dev/?p=29

젯슨나노 20.04 이미지
https://qengineering.eu/install-ubuntu-20.04-on-jetson-nano.html

로봇 호스트에서 터미널 접속 
https://keep-steady.tistory.com/47?category=922869


조인트 스테이트 퍼블리셔 
sudo apt install ros-galactic-joint-state-publisher ros-galactic-joint-state-publisher-gui ros-galactic-robot-state-publisher

리노로봇 수동 설치 사이트 
https://github.com/linorobot/linorobot2/blob/galactic/ROBOT_INSTALLATION.md

작업 공간 만들기
https://docs.ros.org/en/galactic/Tutorials/Beginner-Client-Libraries/Creating-A-Workspace/Creating-A-Workspace.html


터틀붓 설치ㅣ
https://ubuntu.com/blog/simulate-the-turtlebot3


 빌드
colcon build --symlink-install

작업 공간 만들기 
source /opt/ros/galactic/setup.bash
mkdir -p ~/dev_ws/src
cd ~/dev_ws/src


리얼센스 파라매터
https://dev.intelrealsense.com/docs/ros-wrapper

dds 설치 사이트 
https://docs.ros.org/en/galactic/Installation/DDS-Implementations/Working-with-Eclipse-CycloneDDS.html


ws안에서 rosdep실행할때 스킵 키 실행할 것. 
rosdep update && rosdep install --from-path src --ignore-src -y --skip-keys microxrcedds_agent


 파일 다운
git clone https://github.com/ros/ros_tutorials.git -b galactic-devel
cd ..
rosdep install -i --from-path src --rosdistro galactic -y
colcon build


source /opt/ros/galactic/setup.bash
cd /tmp
wget https://raw.githubusercontent.com/linorobot/linorobot2/${ROS_DISTRO}/install_linorobot2.bash
bash install_linorobot2.bash mecanum ydlidar
source ~/.bashrc




작업 공간 만든후 오버레이(즐겨찾기) 소싱--
source /opt/ros/galactic/setup.bash
cd ~/dev_ws
sudo 
 apt-key list
로 현재 설치된 키를 확인 할 수 있다.


SMBJ5.0A 과전압 방지 회로 

ydllidar 드라이버 깔끔한 ㄳ 
git clone https://github.com/PinkWink/YDLidar-SDK.git
git clone https://github.com/PinkWink/ydlidar_ros2_driver.git

중국 사이트 yldirver
https://www.cxyzjd.com/article/weixin_46068920/109553262



가제보 에러없는 설치 
https://www.youtube.com/watch?v=8w3xhG1GPdo
참고
https://emanual.robotis.com/docs/en/platform/turtlebot3/quick-start/
패키지 삭제 
sudo apt remove ros-foxy-turtlebot3
찌꺼기 삭제
sudo apt-get autoremove


테네시 플랫폼 io
cd linorobot2_hardware/calibration
pio run --target upload -e teensy40

screen /dev/ttyACM0

cd linorobot2_hardware/firmware

//마이크로 에이전트 
ros2 run micro_ros_agent micro_ros_agent serial --dev /dev/ttyACM0


ros2 launch linorobot2_bringup bringup.launch.py

ws안에서 rosdep실행할때 스킵 키 실행할 것. 
rosdep update && rosdep install --from-path src --ignore-src -y --skip-keys microxrcedds_agent


스캔
ros2 topic echo /scan

ydlidar드라이버 실행
ros2 launch ydlidar_ros2_driver ydlidar_launch.py
ros2 launch ydlidar_ros2_driver ydlidar_launch_view.py


마이크로 로스  teensy 40 관련이슈
https://github.com/micro-ROS/micro_ros_arduino/issues/145

리얼센스 이슈 
https://github.com/IntelRealSense/realsense-ros/issues/1324

https://github.com/IntelRealSense/librealsense




dds 설치 사이트 
https://docs.ros.org/en/galactic/Installation/DDS-Implementations/Working-with-Eclipse-CycloneDDS.html


로케일 설정

sudo apt-get install locales
sudo locale-gen en_US.UTF-8
sudo echo "LANG=en_US.UTF-8" > /etc/default/locale 

or

sudo pip3 install --upgrade pip
 export LC_ALL=C
 pip install virtualenv

sudo apt install build-essential zlib1g-dev libncurses5-dev libgdbm-dev libnss3-dev libssl-dev libreadline-dev libffi-dev libsqlite3-dev wget libbz2-dev
pip install --upgrade pip==20.3
pip install --upgrade pip