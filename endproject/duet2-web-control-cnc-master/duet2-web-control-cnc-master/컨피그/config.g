;  Configuration file for Duet CNC
; HANGMAN 펌웨어 버전 1.0.0  2019-06-06
;한글로 써도 작동 되는지 확인 해 본다.


; 기본 환경설정
;M80 ;5V 릴레이로 대기모드 전원 작동 하려면 주석 제거 
G90 ;절대 좌표
M453 P1 R2400 F400 ;CNC모드로 전환 히터 1번 핀 씀. 
;M452 ;레이저 각인기 모드 전환인데 메크로로 쓸 것이라서 쓰지는 않을것 같음. 
M117 CNC 기본 설정 완료. 

; 네트웍 설정.
M550 PHANGMAN			        ; Set machine name
M552 S1                           ; Enable network
;M587 S뒤에 와이파이 이름 P뒤에 비밀번호. 와이파를 안쓰니 필요 없음.
M586 P0 S1                        ; P(숫자)프로토콜 방식 HTTP 사용 아래 나머지 사용하지 않음
M586 P1 S0                        ; Disable FTP
M586 P2 S0                        ; Disable Telnet
M117 네트웍 설정 확인 할것. 


; 드라이버 
M569 P0 S0                        ; P(숫자 드라이브 번호)S1정방향 2역방향
M569 P1 S1                        ; 역방향 확인할 것. 
M569 P2 S0			              ; Drive 2 goes forwards
M569 P3 S0   					  ;이것은 나중에 작동 확인후 수정
M584 X0 Y1:3 Z2                   ; 드라이버 매핑을 다시 해야함. Y에 1번과 3번 2개를 쓰는 것을 기준으로 수정. Z는 2번
M350 X16 Y16 Z16 E16 I1  ; 16분주로 사용. 
M906 X2400 Y2400 Z2400 I100       ; 모터 전류값 (mA로 표시) I는 대기 전류값(100ma최대). 작동 후 값을 늘려 볼것. 
M92 X53.334 Y53.334 Z400    ;스탭값 설정. M92코드가 584코드보다 앞에 있으면 안됨. M350 코드 앞에 있을수는 있음.
M566 X500 Y500 Z500               ; Set maximum instantaneous speed changes (mm/min)
M203 X10000 Y10000 Z2500          ; Set maximum speeds (mm/min)
M201 X150 Y150 Z150               ; Set accelerations (mm/s^2)
M117 드라이버 설정 확인할 것. 


; Axis Limits
M208 X0 Y0 Z0 S1                   ; Set axis minima
M208 X820 Y1270 Z100 S0             ; 워크 에이리어 보고 설정. 값은 실측 해봐야함. 

; Endstops
M574 X1 Y1 S3                ; Set active low endstops. 로우로 설정 되어 있음
;나중에 엔드 스톱 스위치 말고 핀다 같은 센서에 대해서 고민해 볼것. S3번은 모터 부하 감지 방식임. 
;https://duet3d.dozuki.com/Wiki/Connecting_endstop_switches 페이지 참조
; Stallgaurd Sensitivy 모터 부하 방식을 시험하기 위해 넣음. 574코드가 S3이면 아래 주석 제거. 
;M915 X S3				  ; -64 ~ +63사이의 값으로 민감도를 설 정 할 수 있음. 기본이 3
;M915 Y S3				  ; Set y axis Sensitivity
;M915 Z S3          ;;(이건 함부로 주석 제거 하지 말것.)

; Z-probe  핀다 센서나 터치식 센서를 쓴다면 주석 제거 하고 쓸것.   
M574 Z2 S3                         ;일단 모터 부하 방식을 먼저 시험 함. 센서를 쓴다면 주석 제거. 돈이 안드니까. 
;M558 P4 C4 H5 I1 F600 T600 A1            ;핀다는 엔드 스톱 스위치에 연결을 기본으로 셋팅해 놓음 558코드는 학습이 필요할것 같음
;일단 써봐야 알 것 같음. C구문이 맞는지 잘 모르겠음. H5는 높이 I1은 배드 히팅을 쓰지 않으니 꺼놓음. F,T는 실험해본후 적정 속도. 센서는 한번만 측정 하기 위해 A1
;G31 P500 X200 Y200 Z1                     ; Set Z probe trigger value, offset and trigger height
;M557 X1:820 Y1:1270 S500                  ; 반경과 센서 간격. 

; Tools
M563 P1 S"XYZ-Probe"		      ; 터치 프로브 

; Custom settings 워크비 복사해옴. 
M564 S1 H1				          ;원점 복구 되지 않아도 이동 허용
M140 H-1						  ; Disable heated bed
M501    						  ; 매게 변수 설정  sys / config-override.g 파일을 로드

; Automatic power saving
M911 S21 R22 P"M913 X0 Y0 G91 M83 G1 Z3 F1000" ; Set voltage thresholds and actions to run on power loss