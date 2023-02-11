# -*-coding:utf-8 -*-
import sys
import threading

from PyQt5 import uic
from PyQt5.QtCore import *
from PyQt5.QtTest import QTest
from PyQt5.QtWidgets import *

from phue import Bridge

# import api1
import firebase_admin
from firebase_admin import credentials
from firebase_admin import db

# 파이어베이스 인증과  초기화
cred = credentials.Certificate("path/rpi-arduino-bc957-firebase-adminsdk-bm0cc-f3aa6b7ea2.json")
firebase_admin.initialize_app(cred, {'databaseURL': 'https://rpi-arduino-bc957.firebaseio.com/'})

##################필립스 휴#######https://mitny.github.io/articles/2018-11/PhilipsHue-control


b = Bridge(ip="http://hangmini.iptime.org:80")  # 접속 에러시 코드 대쳐 할것

b.get_api()

b.create_group('ether', [1, 2, 3, 4, 5, 6, 7, 8])
b.get_group()
lights = b.lights
b.connect()

form_class = uic.loadUiType("gui.ui")[0]  # ui파일을 불러 온다.

# 필립스 휴, 비밀 번호는 대문자 C로 시작한다.

psy_room1 = []
light_room1 = []
Fan_123_room1 = []
Fan_1_room2 = []
Fan_2_room2 = []
Fan_1_room3 = []
gate1_room3 = []
gate2_room3 = []
gate3_room3 = []
gate4_room3 = []
gate5_room3 = []
gate6_room3 = []
gate7_room3 = []
gate8_room3 = []


class switch_class:
    def __init__(self, room_no):
        self.room_no = room_no

    def switch_set(self, board_no, module_no, state):
        # 참조 주소
        room1 = db.reference(self.room_no)
        # 자식 주소
        board1 = room1.child(board_no)
        # 버튼 누를때 들어가는 값. 옮겨야 함.
        var1 = board1.update({module_no: state})
        var1 = room1.child(board_no).child(module_no).get()


###########################################################
######################  MAIN  #############################
###########################################################

class MyWindow(QMainWindow, form_class):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.setWindowFlag(Qt.FramelessWindowHint)  # 타이틀 바 지우기

        ######### 로그인 ##########

        self.pushButton_login.clicked.connect(self.login_pw)

        ############1번 방###########

        self.pushButton_room1_fan123_on.clicked.connect(self.fan_on_1)
        self.pushButton_room1_fan123_off.clicked.connect(self.fan_off_1)
        self.pushButton_room1_fan123_auto.clicked.connect(self.fan_auto_1)

        self.pushButton_room1_psyche_on.clicked.connect(self.psyche_on)
        self.pushButton_room1_psyche_off.clicked.connect(self.psyche_off)
        self.pushButton_room1_light_on.clicked.connect(self.light_on_1)
        self.pushButton_room1_light_off.clicked.connect(self.light_off_1)

        #############HUE#####################
        self.horizontalScrollBar_light_num.valueChanged.connect(self.hum_num(self.horizontalScrollBar_light_num.value))
        self.pushButton_room1_hue_on.clicked.connect(self.hue_on('on'))
        self.pushButton_room1_hue_off.clicked.connect(self.hue_off('off'))

        self.horizontalSlider.valueChanged.connect(self.fan3_val(self.horizontalSlider.value))

        #############2번방#############
        self.pushButton_room2_fan1_off.clicked.connect(self.fan_off_2)
        self.pushButton_room2_fan1_on.clicked.connect(self.fan_on_2)
        self.pushButton_room2_fan1_auto.clicked.connect(self.fan_auto_2)

        self.pushButton_room2_fan1_off_4.clicked.connect(self.fan_off_2_b)
        self.pushButton_room2_fan1_on_4.clicked.connect(self.fan_on_2_b)
        self.pushButton_room2_fan1_auto_4.clicked.connect(self.fan_auto_2_b)

        ###########3번방##################

        self.radioButton.clicked.connect(self.radfunc)
        self.radioButton_2.clicked.connect(self.radfunc)
        self.radioButton_3.clicked.connect(self.radfunc)
        self.radioButton_4.clicked.connect(self.radfunc)
        self.radioButton_5.clicked.connect(self.radfunc)

        self.pushButton_room3_gate1_on.clicked.connect(self.gate1_on_3)
        self.pushButton_room3_gate2_on.clicked.connect(self.gate2_on_3)
        self.pushButton_room3_gate3_on.clicked.connect(self.gate3_on_3)
        self.pushButton_room3_gate4_on.clicked.connect(self.gate4_on_3)

        self.pushButton_room3_gate1_off.clicked.connect(self.gate1_off_3)
        self.pushButton_room3_gate2_off.clicked.connect(self.gate2_off_3)
        self.pushButton_room3_gate3_off.clicked.connect(self.gate3_off_3)
        self.pushButton_room3_gate4_off.clicked.connect(self.gate4_off_3)

        self.pushButton_room3_gate5_on.clicked.connect(self.gate5_on_3)
        self.pushButton_room3_gate6_on.clicked.connect(self.gate6_on_3)
        self.pushButton_room3_gate7_on.clicked.connect(self.gate7_on_3)
        self.pushButton_room3_gate8_on.clicked.connect(self.gate8_on_3)

        self.pushButton_room3_gate5_off.clicked.connect(self.gate5_off_3)
        self.pushButton_room3_gate6_off.clicked.connect(self.gate6_off_3)
        self.pushButton_room3_gate7_off.clicked.connect(self.gate7_off_3)
        self.pushButton_room3_gate8_off.clicked.connect(self.gate8_off_3)

        ##cnc  연결 라즈베이에서 된다면.

        self.cnc_webview.load(QUrl("https://google.com"))
        ##스레드

        t1 = threading.Thread(target=self.pm25)  # API
        t1.daemon = True
        t1.start()

        t2 = threading.Thread(target=self.firebase_data)  # API
        t2.daemon = True
        t2.start()

    def login_pw(self):
        self.pw = self.lineEdit_pw.text()
        if self.pw == "hangmini":
            {
                self.frame_36.close()
            }
        else:
            self.lineEdit_pw.setText("다시 입력하세요")

    ####1번방##########
    # def hue_connect(self):

    def hue_on(state):
        # lights[hue 전구 인덱스].on/off = True/False
        if state == 'on':
            for i in range(0, len(lights)):
                lights[i].on = True
                # lights[hue 전구 인덱스].brightness = 0~254 숫자가 커질 수록 밝아진다
                lights[i].brightness = 254
        elif state == 'off':
            for i in range(0, len(lights)):
                lights[i].on = False

    def hum_num(self, hue_light_num):
        self.label_light_num.setText(str(hue_light_num))
        for i in range(0, len(lights)):
            lights[i].brightness = hue_light_num

        # lights[hue 전구 인덱스].xy = [0~1,0~1]

        for i in range(0, len(lights)):
            if i == 0:
                lights[i].xy = [0.1, 0.1]
            elif i == 1:
                lights[i].xy = [0.5, 1]
            elif i == 2:
                lights[i].xy = [0.7, 0.3]

    def fan3_val(self):
        global Fan_1_room3
        fan3 = switch_class("Room_3")  # 룸 넘버
        if self.radioButton.isChecked():
            self.lcdNumber_room3_Fan_1.setText("OFF")
            fan3.switch_set("board_2", "Fan_01", "FA00", Fan_1_room3)  # 보드 넘버, 모듈 넘버, 스테이트
        elif self.radioButton_2.isChecked():
            self.lcdNumber_room3_Fan_1.setText("80")
            fan3.switch_set("board_2", "Fan_01", "FA80", Fan_1_room3)  # 보드 넘버, 모듈 넘버, 스테이트
        elif self.radioButton_3.isChecked():
            self.lcdNumber_room3_Fan_1.setText("60")
            fan3.switch_set("board_2", "Fan_01", "FA60", Fan_1_room3)  # 보드 넘버, 모듈 넘버, 스테이트
        elif self.radioButton_4.isChecked():
            self.lcdNumber_room3_Fan_1.setText("40")
            fan3.switch_set("board_2", "Fan_01", "F40", Fan_1_room3)  # 보드 넘버, 모듈 넘버, 스테이트
        elif self.radioButton_5.isChecked():
            self.lcdNumber_room3_Fan_1.setText("100")
            fan3.switch_set("board_2", "Fan_01", "FA100", Fan_1_room3)  # 보드 넘버, 모듈 넘버, 스테이트

    def psyche_on(self):
        global psy_room1
        psy = switch_class("Room_1")  # 룸 넘버
        psy.switch_set("board_1", "psychic", "SA01", psy_room1)  # 보드 넘버, 모듈 넘버, 스테이트
        self.lcdNumber_room1_psyche.setText('ON')

    def psyche_off(self):
        global psy_room1
        psy = switch_class("Room_1")  # 룸 넘버
        psy.switch_set("board_1", "psychic", "SA00", psy_room1)  # 보드 넘버, 모듈 넘버, 스테이트
        self.lcdNumber_room1_psyche.setText('OFF')

    def light_on_1(self):
        global light_room1
        lig = switch_class("Room_1")  # 룸 넘버
        lig.switch_set("board_1", "light", "LI01", light_room1)  # 보드 넘버, 모듈 넘버, 스테이트
        self.lcdNumber_room1_light.setText('ON')

    def light_off_1(self):
        global light_room1
        lig = switch_class("Room_1")  # 룸 넘버
        lig.switch_set("board_1", "light", "LI00", light_room1)  # 보드 넘버, 모듈 넘버, 스테이트
        self.lcdNumber_room1_light.setText('OFF')

    def fan_off_1(self):
        global Fan_123_room1
        fan_1 = switch_class("Room_1")  # 룸 넘버
        fan_1.switch_set("board_1", "Fan_123", "FA00", Fan_123_room1)  # 보드 넘버, 모듈 넘버, 스테이트
        self.lcdNumber_room1_Fan_123.setText('OFF')

    def fan_on_1(self):
        global Fan_123_room1
        fan_1 = switch_class("Room_1")  # 룸 넘버
        fan_1.switch_set("board_1", "Fan_123", "FA01", Fan_123_room1)  # 보드 넘버, 모듈 넘버, 스테이트
        self.lcdNumber_room1_Fan_123.setText('ON')

    def fan_auto_1(self):
        global Fan_123_room1
        fan_1 = switch_class("Room_1")  # 룸 넘버
        fan_1.switch_set("board_1", "Fan_123", "FA02", Fan_123_room1)  # 보드 넘버, 모듈 넘버, 스테이트
        self.lcdNumber_room1_Fan_123.setText('AUTO')

    ##2번방

    def fan_off_2(self):
        global Fan_1_room2
        fan_2 = switch_class("Room_2")  # 룸 넘버
        fan_2.switch_set("board_1", "Fan_1", "FA00", Fan_1_room2)  # 보드 넘버, 모듈 넘버, 스테이트
        self.lcdNumber_room2_Fan_1.setText('OFF')

    def fan_on_2(self):
        global Fan_1_room2
        fan_2 = switch_class("Room_2")  # 룸 넘버
        fan_2.switch_set("board_1", "Fan_1", "FA01", Fan_1_room2)  # 보드 넘버, 모듈 넘버, 스테이트
        self.lcdNumber_room2_Fan_1.setText('ON')

    def fan_auto_2(self):
        global Fan_1_room2
        fan_2 = switch_class("Room_2")  # 룸 넘버
        fan_2.switch_set("board_1", "Fan_2", "FA02", Fan_1_room2)  # 보드 넘버, 모듈 넘버, 스테이트
        self.lcdNumber_room2_Fan_1.setText('AUTO')

    def fan_off_2_b(self):
        global Fan_2_room2
        fan_2 = switch_class("Room_2")  # 룸 넘버
        fan_2.switch_set("board_1", "Fan_2", "FA00", Fan_2_room2)  # 보드 넘버, 모듈 넘버, 스테이트
        self.lcdNumber_room2_Fan_4.setText('OFF')

    def fan_on_2_b(self):
        global Fan_2_room2
        fan_2 = switch_class("Room_2")  # 룸 넘버
        fan_2.switch_set("board_1", "Fan_2", "FA01", Fan_2_room2)  # 보드 넘버, 모듈 넘버, 스테이트
        self.lcdNumber_room2_Fan_4.setText('ON')

    def fan_auto_2_b(self):
        global Fan_2_room2
        fan_2 = switch_class("Room_2")  # 룸 넘버
        fan_2.switch_set("board_1", "Fan_1", "FA02", Fan_2_room2)  # 보드 넘버, 모듈 넘버, 스테이트
        self.lcdNumber_room2_Fan_4.setText('AUTO')

    ################3번방#############################

    def fan_on_3(self):  # 슬라이더 아직 수정 안함
        global Fan_1_room3
        fan_3 = switch_class("Room_3")  # 룸 넘버
        fan_3.switch_set("board_2", "Fan_1", "FA00", Fan_1_room3)  # 보드 넘버, 모듈 넘버, 스테이트
        self.lcdNumber_room3_Fan_1.setText()

    def gate1_on_3(self):
        global gate1_room3
        gate1 = switch_class("Room_3")  # 룸 넘버
        gate1.switch_set("board_1", "gate_1", "GA01", gate1_room3)  # 보드 넘버, 모듈 넘버, 스테이트
        self.lcdNumber_room3_gate1.setText('ON')

    def gate1_off_3(self):
        global gate1_room3
        gate1 = switch_class("Room_3")  # 룸 넘버
        gate1.switch_set("board_1", "gate_1", "GA00", gate1_room3)  # 보드 넘버, 모듈 넘버, 스테이트
        self.lcdNumber_room3_gate1.setText('OFF')

    def gate2_on_3(self):
        global gate2_room3
        gate2 = switch_class("Room_3")  # 룸 넘버
        gate2.switch_set("board_1", "gate_2", "GA11", gate2_room3)  # 보드 넘버, 모듈 넘버, 스테이트
        self.lcdNumber_room3_gate2.setText('ON')

    def gate2_off_3(self):
        global gate2_room3
        gate2 = switch_class("Room_3")  # 룸 넘버
        gate2.switch_set("board_1", "gate_2", "GA10", gate2_room3)  # 보드 넘버, 모듈 넘버, 스테이트
        self.lcdNumber_room3_gate2.setText('OFF')

    def gate3_on_3(self):
        global gate3_room3
        gate3 = switch_class("Room_3")  # 룸 넘버
        gate3.switch_set("board_1", "gate_3", "GA21", gate3_room3)  # 보드 넘버, 모듈 넘버, 스테이트
        self.lcdNumber_room3_gate3.setText('ON')

    def gate3_off_3(self):
        global gate3_room3
        gate3 = switch_class("Room_3")  # 룸 넘버
        gate3.switch_set("board_1", "gate_3", "GA20", gate3_room3)  # 보드 넘버, 모듈 넘버, 스테이트
        self.lcdNumber_room3_gate3.setText('OFF')

    def gate4_on_3(self):
        global gate4_room3
        gate4 = switch_class("Room_3")  # 룸 넘버
        gate4.switch_set("board_1", "gate_4", "GA31", gate4_room3)  # 보드 넘버, 모듈 넘버, 스테이트
        self.lcdNumber_room3_gate4.setText('ON')

    def gate4_off_3(self):
        global gate4_room3
        gate4 = switch_class("Room_3")  # 룸 넘버
        gate4.switch_set("board_1", "gate_4", "GA30", gate4_room3)  # 보드 넘버, 모듈 넘버, 스테이트
        self.lcdNumber_room3_gate4.setText('OFF')

    def gate5_on_3(self):
        global gate5_room3
        gate4 = switch_class("Room_3")  # 룸 넘버
        gate4.switch_set("board_1", "gate_5", "GA41", gate5_room3)  # 보드 넘버, 모듈 넘버, 스테이트
        self.lcdNumber_room3_gate5.setText('ON')

    def gate5_off_3(self):
        global gate5_room3
        gate4 = switch_class("Room_3")  # 룸 넘버
        gate4.switch_set("board_1", "gate_5", "GA50", gate5_room3)  # 보드 넘버, 모듈 넘버, 스테이트
        self.lcdNumber_room3_gate5.setText('OFF')

    def gate6_on_3(self):
        global gate6_room3
        gate4 = switch_class("Room_3")  # 룸 넘버
        gate4.switch_set("board_1", "gate_5", "GA41", gate6_room3)  # 보드 넘버, 모듈 넘버, 스테이트
        self.lcdNumber_room3_gate6.setText('ON')

    def gate6_off_3(self):
        global gate6_room3
        gate4 = switch_class("Room_3")  # 룸 넘버
        gate4.switch_set("board_1", "gate_5", "GA50", gate6_room3)  # 보드 넘버, 모듈 넘버, 스테이트
        self.lcdNumber_room3_gate6.setText('OFF')

    def gate7_on_3(self):
        global gate7_room3
        gate4 = switch_class("Room_3")  # 룸 넘버
        gate4.switch_set("board_1", "gate_5", "GA41", gate7_room3)  # 보드 넘버, 모듈 넘버, 스테이트
        self.lcdNumber_room3_gate7.setText('ON')

    def gate7_off_3(self):
        global gate7_room3
        gate4 = switch_class("Room_3")  # 룸 넘버
        gate4.switch_set("board_1", "gate_5", "GA50", gate7_room3)  # 보드 넘버, 모듈 넘버, 스테이트
        self.lcdNumber_room3_gate7.setText('OFF')

    def gate8_on_3(self):
        global gate8_room3
        gate4 = switch_class("Room_3")  # 룸 넘버
        gate4.switch_set("board_1", "gate_5", "GA41", gate8_room3)  # 보드 넘버, 모듈 넘버, 스테이트
        self.lcdNumber_room3_gate8.setText('ON')

    def gate8_off_3(self):
        global gate8_room3
        gate4 = switch_class("Room_3")  # 룸 넘버
        gate4.switch_set("board_1", "gate_5", "GA50", gate8_room3)  # 보드 넘버, 모듈 넘버, 스테이트
        self.lcdNumber_room3_gate8.setText('OFF')

    def firebase_data(self):
        global Fan_1_room2
        global Fan_2_room2
        global Fan_1_room3
        global Fan_123_room1
        global psy_room1
        global light_room1
        global gate1_room3
        global gate2_room3
        global gate3_room3
        global gate4_room3
        global gate5_room3
        global gate6_room3
        global gate7_room3
        global gate8_room3

        # 참조 주소

        room1 = db.reference('Room_1')
        room2 = db.reference('Room_2')
        room3 = db.reference('Room_3')

        # 자식 주소

        while True:
            # 1번방의 데이터 가져 오기
            humi_room1 = room1.child('board_1').child('humidity').get()
            temp_room1 = room1.child('board_1').child('temperature').get()

            Fan_123_room1 = room1.child('board_1').child('Fan_123').get()
            light_room1 = room1.child('board_1').child('light').get()
            psy_room1 = room1.child('board_1').child('psychic').get()

            pm1_room1 = room1.child('board_2').child('PM1').get()
            pm10_room1 = room1.child('board_2').child('PM10').get()
            pm25_room1 = room1.child('board_2').child('PM25').get()

            self.lcdNumber_room1_temp.setText(str(temp_room1))
            self.lcdNumber_room1_humi.setText(str(humi_room1))

            if Fan_123_room1 == 'FA02':
                self.lcdNumber_room1_Fan_123.setText('AUTO')
            elif Fan_123_room1 == 'FA02':
                self.lcdNumber_room1_Fan_123.setText('ON')
            else:
                self.lcdNumber_room1_Fan_123.setText('OFF')

            if light_room1 == 'LI01':
                self.lcdNumber_room1_light.setText('ON')
            else:
                self.lcdNumber_room1_light.setText('OFF')

            if psy_room1 == 'SA01':
                self.lcdNumber_room1_psyche.setText('ON')
            else:
                self.lcdNumber_room1_psyche.setText('OFF')

            self.lcdNumber_room1_pm1.setText(str(pm1_room1))
            self.lcdNumber_room1_pm10.setText(str(pm10_room1))
            self.lcdNumber_room1_pm25.setText(str(pm25_room1))
            QTest.qWait(1000)

            # 2번방의 데이터 가져 오기
            humi_room2 = room2.child('board_1').child('humidity').get()
            temp_room2 = room2.child('board_1').child('temperature').get()
            Fan_1_room2 = room2.child('board_1').child('Fan_1').get()
            Fan_2_room2 = room2.child('board_1').child('Fan_2').get()
            self.lcdNumber_room2_temp.setText(str(temp_room2))
            self.lcdNumber_room2_humi.setText(str(humi_room2))
            self.lcdNumber_room2_Fan_1.setText(str(Fan_1_room2))
            self.lcdNumber_room2_Fan_1.setText(str(Fan_1_room2))
            QTest.qWait(1000)

            # 3번방의 데이터 가져 오기
            humi_room3 = room3.child('board_1').child('humidity').get()
            temp_room3 = room3.child('board_1').child('temperature').get()
            Fan_1_room3 = room3.child('board_1').child('Fan_1').get()

            gate1_room3 = room3.child('board_1').child('gate_1').get()
            gate2_room3 = room3.child('board_1').child('gate_2').get()
            gate3_room3 = room3.child('board_1').child('gate_3').get()
            gate4_room3 = room3.child('board_1').child('gate_4').get()

            gate1_room3 = room3.child('board_1').child('gate_5').get()
            gate2_room3 = room3.child('board_1').child('gate_6').get()
            gate3_room3 = room3.child('board_1').child('gate_7').get()
            gate4_room3 = room3.child('board_1').child('gate_8').get()

            self.lcdNumber_room3_temp.setText(str(temp_room3))
            self.lcdNumber_room3_humi.setText(str(humi_room3))
            self.lcdNumber_room3_Fan_1.setText(str(Fan_1_room3))

            self.lcdNumber_room3_pm1.setText(str(Fan_1_room3))  # 수정전
            self.lcdNumber_room3_pm25.setText(str(Fan_1_room3))  # 수정전
            self.lcdNumber_room3_pm10.setText(str(Fan_1_room3))  # 수정전

            self.lcdNumber_room3_gate1.display(gate1_room3)
            self.lcdNumber_room3_gate2.display(gate2_room3)
            self.lcdNumber_room3_gate3.display(gate3_room3)
            self.lcdNumber_room3_gate4.display(gate4_room3)

            QTest.qWait(1000)

    def pm25(self, api_pm25=0, api_pm10=0, api_humi=0, api_temp=0):
        while True:
            api_pm25 = api1.pm25_value  # 초미세먼지
            api_pm10 = api1.pm10_value  # 미세먼지
            api_humi = api1.api_humidity  # 습도
            api_temp = api1.weather_data  # 온도
            QTest.qWait(1000)
            self.lcdNumber_api_pm25.setText(str(api_pm25))
            self.lcdNumber_api_humidity.setText(str(api_humi))
            self.lcdNumber_api_temperature.setText(str(api_temp))
            self.lcdNumber_api_pm10.setText(str(api_pm10))


######################################################
######################################################
if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MyWindow()
    # window.showMaximized()  #전체화면
    window.show()
    sys.exit(app.exec_())
