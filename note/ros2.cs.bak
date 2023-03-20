로스 1 관련 정리 

아두이노로 접속 코드 
rosrun rosserial_python serial_node.py _port:=/dev/ttyUSB0 _baud:=57600

rostopic pub /moveServo std_msgs/UInt16 2 --once


자동 잔디 깍기 
https://github.com/llDev-Rootll/Autonomous_Lawn_Mower

http://classic.gazebosim.org/tutorials?tut=install_from_source&cat=install

gazebo 관련 에러 해결 할 것
수동 클린 설치 방법
http://classic.gazebosim.org/tutorials?tut=install_from_source&cat=install


초기화 종속성 
rosdep install -r --ignore-src -y --from-paths .
https://github.com/Fields2Cover/Fields2Cover


ppr_cpr 관련 링크 
https://groups.google.com/g/linorobot/c/lVNqFQKIROw/m/7-nNIDFoAAAJ

roscd linorobot/teensy/firmware
platformio run --target upload -e teensy41


 IntelliThings iAHRS (RB-SDA-v1)

    <!-- IMU Relay and Filter     <include file="$(find iahrs_driver)/launch/iahrs_driver.launch" />
 -->

sudo chmod 666 /dev/linobase

현재 연마로봇 관련

rosrun map_server map_saver -f ~map2


imu 전원 단자 헐겁거나 인식 약함 
rosa한쪽만 전원 연결시 동작 명령이 바로 작동되는데 반해 
두 바퀴 모두 전원 연결시 밀림. 5v출력과 24v출력 보강해 볼것. 

런처 파라미터 설명
https://enssionaut.com/board_robotics/974

키보드 노드 설명
https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=rbdud96&logNo=






221448718336

펌웨어 빌드 관련 게시글 
https://groups.google.com/g/linorobot/search?q=firmware

roslaunch linorobot bringup.launch
roslaunch linorobot mininal.launch
roslaunch linorobot slam.launch
roslaunch linorobot navigate.launch
rosrun teleop_twist_keyboard teleop_twist_keyboard.py



sudo cp 58-lino.rules /etc/udev/rules.d/58-lino.rules
sudo service udev reload
sudo service udev restart
ls /dev/linobase
ls /dev/linolidar
이미지 해상도와 크기는 
로봇 슬램상에서 설정되어 있다. 

roscd lino_visualize/rviz
rviz -d slam.rviz

로스 버전과 패치 관련 정보   
printenv | grep ROS

//설 끝나고 확인 할것 
https://github.com/h-brenne/ROS-UV-Cleaning-Robot/tree/master/src


커버리지 경로 관련 깃 
https://github.com/topics/coverage-path-planning


알리아스 설정 외우기
alias eb='nano ~/.bashrc'
alias sb='source ~/.bashrc'
alias cw='cd ~/catkin_ws'
alias cs='cd ~/catkin_ws/src'
alias cm='cd ~/catkin_ws && catkin_make'


아수스 딥 센서 참고 할 것. 
https://www.youtube.com/watch?v=IIlvF9c8Wzw&list=PLRG6WP3c31_VIFtFAxSke2NG_DumVZPgw&index=8
//https://cafe.naver.com/openrt/6070


맵서버 저장과 변경에 관련된 파일 
https://automaticaddison.com/how-to-create-a-map-for-ros-from-a-floor-plan-or-blueprint/


 image 점유 격자 지도의 이미지 경로 ex) test.png
 resolution 해상도 공식 : 미터 / 픽셀
 origin MAP 원점 좌표(위치) 2D 포즈 (x, y, yaw)
 occupied_thresh 임계 값보다 큰 점유를 가진 픽셀은 점유 상태로 확인
 free_thresh 점유값이 임계 값보다 작은 픽셀은 비어있는 상태로 확인
 negate white / black free / occupied semantics가 반전되어야하는지 여부

teensy lc 변경 관련
https://groups.google.com/g/linorobot/c/7RBAsB8i2VU/m/ebIR-42cDAAJ


https://www.youtube.com/watch?v=iGdQHi_wL1Y&list=PLRG6WP3c31_VIFtFAxSke2NG_DumVZPgw&index=7
부터 유투브 볼것 


이타인 클럽
https://opentutorials.org/course/2845/16605

ros 멜로딕 설치
https://www.notion.so/2-ROS-22dcd11590bf432085273ce91e96ef9c
sudo apt-get install ros-melodic-<package name>

젯슨나노 opencv 연결 에러 
https://omorobot.gitbook.io/manual/product/omo-r1mini/ros/ros1-melodic/yolo1/yolo-error

청소 로봇 알고리즘
https://medium.com/cse-468-568-robotic-algorithms/robot-vacuum-cleaner-part-3-3-2bc317cf17db

ㅁ
패키지(hello_ros) 처음 만들기 
cd ~/catkin_ws/src
catkin create pkg hello_ros --catkin-deps roscpp rospy
source ~/catkin_ws/devel/setup.bash

플랫폼 io 관련 오류
pip uninstall platformio
sudo add-apt-repository ppa:deadsnakes/ppa
sudo apt-get update
sudo apt-get install python3.6
curl https://bootstrap.pypa.io/get-pip.py | sudo python3.6
pip3.6 install platformio

커버리지 맵
https://opentutorials.org/course/2845/16664


ROS 셀 명령어

누락된 종속성 채크
rosdep update
rosdep check --from-paths . --ignore-src --rosdistro melodic
누락된 종속성 자동 설치 
rosdep install --from-paths . --ignore-src --rosdistro melodic -y

– roscd: 지정한 ros 패키지 디렉터리로 이동
– rosls: ros 패키지 파일 목록 확인
– rosed: ros 패키지 파일 편집
– roscp: ros 패키지 파일 복사
– rospd: ros 디렉터리 인덱스에 디렉터리 추가
– rosd: ros 디렉터리 인덱스 확인

ROS 실행 명령어

– roscore: master (ROS name service) + rosout (stdout/stderr) + parameter server (파라미터 관리)
– rosrun: 패키지 노드 실행
– roslaunch: 패키지 노드를 여러 개 실행
– rosclean: ros 로그 파일을 검사하거나 삭제

ROS 정보 명령어

– rostopic: 토픽 정보 확인
– rosservice: 서비스 정보 확인
– rosnode: 노드 정보 확인
– rosparam: 파라미터 정보 확인, 수정
– rosbag: 메세지 기록, 재생
– rosmsg: 메세지 정보 확인
– rossrv: 서비스 정보 확인
– rosversion: 패키지 및 배포 릴리스 정보 확인
– roswtf: ros 시스템 검사

ROS catkin 명령어

– catkin_create_pkg: catkin 빌드 시스템으로 패키지 자동 생성
– ROS: catkin 빌드 시스템으로 빌드
– catkin_eclipse: 생성한 패키지를 eclipse에서 사용할 수 있도록 변경
– catkin_prepare_release: changelog 정리 및 버전 태깅
– catkin_init_workspace: catkin 빌드 시스템의 작업 폴더 초기화
– catkin_find: 검색

ROS package 명령어

– rospack: 패키지와 관련된 정보 보기
– rosinstall: 추가 패키지 설치
– rosdep: 해당 패키지의 의존성 파일 설치
– roslocate: 패키지 정보 관련 명령어
– roscreate-pkg: 패키지 자동 생성 (구 빌드 시스템에서 사용)
– rosmake: 패키지 빌드 (구 빌드 시스템에서 사용)

강좌
https://www.notion.so/byeongkyu/ROS-73000a9914684ac89ed8a835c6963b5e

https://kasimov.korea.ac.kr/dokuwiki/doku.php/activity/public/2021/ros/6




퍼블리셔 서브스크라이버 클래스 한 노드에 작성 
https://m.blog.naver.com/nswve/222089931436

