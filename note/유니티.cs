유니티 

api  레퍼런스 
https://docs.unity3d.com/kr/530/ScriptReference/index.html

픽셀 아트 
https://www.youtube.com/watch?v=7W2na8OKC8U

절차적 생성 알고리즘 참고 
https://vazgriz.com/119/procedurally-generated-dungeons/



유니티의 클래스는 MonoBehavior의 자식들이다. 유니티의 컴포넌트는 MonoBehavior클래스를 상속한다. 오브젝트를 컴포넌트패턴을 이용해서 만든다. 원하는 기능을 제공하는 컴포넌트를 찾아 게임 오브젝트에 붙여서 사용한다. 
프리팹은 재사용 할 수 있는 파일 형태의 오브젝트로 만드는 것이다. 



컴포넌트를 붙였을때 인스펙터 창에서 알 수 있다. 


Tag : 게임 오브젝트를 분류하고 코드에서 게임 오브젝트를 분류 할 때 사용 
//if(other.tag == "Player"){ 태그가 player인 경우 컨트롤러를 가져와라 
//PlayerController playerController= other.GetComponent<PlayerController>();}
Transform : 위치 크기 
//transform.forward  포워드 방향

Mesh Filter : 오브젝트 외곽선 지정
 
Mesh Renderer : 메시를 따라 색을 채워 그래픽 외형을 그린다. 

xxx Collider : 박스, 실린더 등 물체가 부딪힐 수 있는 물리적인 표면을 만든다. 
 //is Trigger 채크 하면 콜라이더를 충돌과 같은 이벤트에 트리거를 만들게 된다. 

Rigidbody : 게임 오브젝트가 물리적인 통제를 받게 한다. 이동할때 Rigidbody 컴포넌트를 생성하고 초기화 한 후에 이동할 코드를 적는다. 


  //Use Gravity 채크를 해제하면 중력에 영향을 받지 않는다. 
   rigidbody 이동에 관한 3가지 방식 
    //1.힘을줘 바로 이동. 
        rigid.AddForce(inputVec);  // playerRigidbody.AddForce(new Vector2(0, jumpForce); 백터2 방향에서 위쪽이로 jumpForce만큼 이동(점프)

        //2. 속도를 직접 속도 제어하는 방식  
		bulletRigidbody.velocity = transform.forward * speed;  //리지드 바디 속력은 = 포워드 방향 이동 *속력
        rigid.velocity = inputVec;


        //3.위치 이동
        rigid.MovePosition(rigid.position + inputVec);
		//리지드 바디를 이용한 무브포지션 이동을 하는 이유는 일반 
		//transform.position을 쓰면 컴포넌트가 있더라도 통과를 할 
		//수 있기 때문이다. 리지드 바디는 물리 처리를 하기 때문에
		//벽이 있으면 밀려 날 수 있다. 
		

Rigidbody Inspector창 설정 
 Collision Detection : Discrete는 충돌 감지를 일정 시간 간격으로 끊어서 실행된다 Continuous는 움직이기 이전 위치와 움직인 다음 위치 사이에서 예상되는 충돌까지 함께 감지 한다. 상대적으로 더 정확하지만 성능을 더 요구한다. 

 Angular Drag
 값이 높아지면 물체가 잘 회전하지 않고, 회전해도 금방 멈춘다. 


Time.deltaTime
//이전 프레임과 현제 프레임과의 역수를 취한 값이다. 다시 말해서 
//60프레임으로 동작하는 게임이라면 /60을 해서 자동으로 1초 동안의 프레임에 맞춰 계산해 준다. 


AudioSource 오디오 소스 
//오디오 객체.Player() 오디오 소스 재생
       playerAudio.clip = deathClip;  //오디오 클립을  deathClip로 변경 
        playerAudio.Play();  //오디오 재생 
		
		
		
GameManager	
//public static GameManager instance; // 싱글톤을 할당할 전역 변수 스태틱으로 지정한다. 
		

Text 
텍스트 객체 	


Debug.LoWarning("경고 로그");

	
	
	

	
<시네머신>
인스팩터창 
brain camera 메인 카메라 

virtual camera 서브가 되는 가상 카메라
follow 필드에 할당된 게임 오브젝트를 따라다닌다. 이를 위해 자신의 위치를 변경한다. 
Look At : 필드에 할당된 게임 오브젝트를 주시한다. 이를 위해 자신의 회전을 변경한다. 

시네 머신 virtual camera 컴포넌트의 Look At필드에 플레이어 캐릭터를 할당하는 순간 게임 창에 붉은색과 푸른색으로 그려진 영역과 안내선이 보인다. 
이들은 카메라의 자연스로운 추적을 구현아는 소프트 존과 붉은색 영역인 하드리밋이 있다. 그리고 아주 작은 데드존도 있다 컴포넌트의 숫자값을 변경하거나 게임 창에 그려진 안내선을 드래그해서 조절할 수 있다 
	
Body파라미터는 카메라가 Folliow에 할당된 추적 대상을 어떻게 따라 다닐지 결정한다 

X,Y,Z Damping 은 급격한 변화를 꺽어 이전 값과 이후 값을 부드럽게 이어주는 비율이다. 

	
	
Aim파라메터 
Tracked Object Offset 필드는 원래 추적 대상에서 얼마나 더 떨어진 곳을 조준할지 결정한다. y값을 높여 실제 보다 높게 조준할 수 도 있다. 

Horizonatal Damping Veritical Damping 
회전 속도에 제동값 가로 세로를 설정 할 수 있다. 0으로 변경하면 카메라가 제동없이 회전한다 	
	

Action
입력과 출력이 없는 메서드를 가리킬 수 있는 델리게이트(함수 포인터 같은것)이다. Action은 함수포인터의 동적 배열처럼 동작 하는것 같다. 
Action Funch += 메서드 를 계속 넣어서 인덱스 값으로 접근하거나. foreach문으로 접근 할 수 있을것 같다. 아마도 다. 

event
델리게이트 타입의 변수는 event 키워드를 붙여 선언할 수 있다. 어떤 델리게이트 변수를 event 로 선언하면 클래스 외부에서는 해당 델리게이트를 실행할 수 없게 된다. 

event를 사용하면 이벤트를 소유하지 않은 측에서 멋대로 이벤트를 발동하는 것을 막을수 있다. Action에 protected 지정자를 넣는것과 비슷한 효과 같다. 

public event Action aaa; 라고 하면 같은 클래스에서는 실행이 되고 

다른 클래스에서 생성된 bbb.aaa()를 하면 실행이 되지 않는다. 




	
IDamageable 
공격당할 수 있는 모든 대상은 IDameaeable인터페이스를 상속한다. 임으로 만든 인터페이스이다. 
인터페이스를 상속하는 클래스는 OnDamage()메서드를 반드시 구현해야 한다. OnDamage()메서드
damage :데미지 크기 
hitPoint : 공격 당한 위치
hitNormal : 공격당한 표면의 방향
공격당한 오브젝트가 IDmageable을 상속했다면 해당 오브젝트의 OnDamage()메서드를 실행하기만 하면 된다. 
	
	
	
<라인랜더러>
라인 렌더러는 주어진 점들을 이은 선을 그리는 컴포넌트이다. 총을 솔때 탈알의 궤적을 그려 따라가게 하는 것들이라고 보면된다. 

인스팩터 창에서 
라인의 크기나 
 lighting창은 오브젝트에 빛이나 그림자를 끄거나 키는 설정을 할 수 이싸. 

	
<이벤트 메서드> 

Start() 게임이 시작될때 자동으로 한번 실행된다. 
Update() 실시간 갱신 
OnCollision xxx(Collision collision) //일반 충돌 : 일반적인 콜라이더를 가진 두 게임 오브젝트가 충돌할 때 자동으로 실행. 충돌한 콜라이더는 
//서로 통과하지 않고 밀어 낸다. 
//OnCollisionEnter() 충돌한 순간. OnCollisionStay() 충돌하는 동알 OnCollisionExit() 충돌했다가 분리되는 순간 
//메서드가 실행될 때는 메서드 입력으로 충돌 관련 정보가 Collision 타입으로 들어 온다. Collison타입은 충돌 관련 정보를 담아두는 단순한 컨테이너이다. 이것을 통해 충돌한 상대방 게임 오브젝트, 충돌 지점, 충돌 표면의 방향을 알 수 있다. 


FixedUpdate()  //리지드 바디 처럼 물리 연산에 대해서 호출되는 생명 주기 함수
물리 정보 갱신주기(기본 0.02초 )에 맞춰 실행된다. 이동과 회전을 update메서드에서 실행해도 되지만 물리 주기에 맞춰서 실행되는 FixedUpdate에 실행할 경우 오차가 날 확률이 상대적으로 줄어 들게 도니다 .



OnTrigger xxx(Collider other) //충돌한 두게임 오브젝트의 콜라이더가 최소 하나가 트리거 콜라이더라면 자동 실행. 
//xxx == Enter 충돌한 순간, Stay 충돌하는 동안 , Exit 충돌했다가 분리되는 순간 
//트리거 충돌은 통과 한다. 
//충돌한 상대방 게임 오브젝트의 콜라이더 컴포넌트가 collider 타입으로 들어 온다. 

Destroy(bulletRigidbody, 3f);  //오브젝트 파괴 (오브젝트 명칭, 시간) 오브젝트 명칭만 적으면 바로 파괴 된다. 

value = Random.Range(0,3); //012 중 하나가 int값으로 출력  (0f, 3f)하면 0f부터 3f사이의 값이 출력됨 예)0.1

OnEnable()
//Awake()나 Start() 같은 유니티 에벤트 메서드이다. Start()메서드처럼 컴포넌트가 활성되면 실행된다. start는 처음 한번이지만 OnEnable는 활성화 될때마다 매번 실행된다 
//게임 오브젝트가 활성화 될때마다 상태를 리셋하는 기능을 구현할때 주로 이용된다 




FindObjerctOfType 
//오브젝트의 컴포넌트를 찾아 가져 오는 메서드 <PlayerController>컴포넌트의 transform정보를 가져와 target에 대입한다. 
//target = FindObjectOfType<PlayerController>().transform;  
//시스템 리소스를 많이 먹기 때문에 update메서드에서 사용을 안하는게 좋다. 복수형 s가 FindObjerctsOfType는 여러 오브젝트를 찾아서 가져 온다. 


GetComponent
//playerObject = GetComponent<Rigidbody>();  //유니티 객체 컴포넌트를 오브젝트에 대입  <>대괄효는 제내릭이다. 제내릭은 메서드나 클래스에 맞춰서 호환되게 하는 동작이다. 


Instantiate(원본, 위치, 회전)
//인스턴스화 한다. 원본을 복제화 한다. 
//Instantiate(복제할 오브젝트, transform.position, transform.rotation); 온 위치와 회정 정보를 생성해서 새로운 bullet로 복제 
Instantiate처럼 오브젝트를 실시간으로 생성하거나 
Destroy메서드처럼 오브젝트를 실시간으로 파괴하는 처리는 성능을 많이 ㅇ구한다. 또한 메모리를 정리하는 가비지 컬렉션을 유발하기 쉽다 .따라서 게임 도중에 오브젝트를 너무 자주 생성하거나 파괴하면 게임 끊김 현상이 생기기 휩다. 
로딩이 긴 게임이 바로 오브젝트를 모두 로딩하고 풀로 관리 하기 때문에 끊김이 없다. 

//
platforms[i] = Instantiate(platformPrefab,  poolPosition, Quaternion.identity);
인스턴스를 생성해 게임 오브젝트에 대입(원본, 위치, 회전값)을 넣고 생성한다. 




PlayerInput
//플레이어 입력을 전달하는 PlayerInput컴포넌트이다. 


LookAt(target)
//복제된 총알이 target 바라 보도록 고정 
//bullet.transform.LookAt(target);


gameObject.SetActive(false);  
//오브젝트가 숨김 처리가 된다. false는 숨김처리이다. 

            platforms[currentIndex].SetActive(false);  //발판 오브젝트를 껐다 켜는것은 해당 발판 게임 오브젝트의 상태를 리셋하기 위해서이다. 
            platforms[currentIndex].SetActive(true);


Input.GetKeyDown(KeyCode.R)
//r키를 누르면 

SceneManager.LoadScene("SampleScene");
//SampleScen을 로드 한다. using UnityEngine.SceneManagement; 로 유니티에 내장된
//씬관리자이다. 씬의 이름을 받아 씬을 로드한다. 기본이 되는 씬을 제외하고는 file -> Build Settings
//에 로드할 scene가 등록되어야 한다. 이외에도 빌드되어야할 씬 순서대로 익덱스 넘버로 로드 할 수도 있다. LoadScene(0);

 SceneManager.LoadScene(SceneManager.GetActiveScene().name);
현재의 활성화된 씬(GetActiveScene().name)이름을 가져온다. 그리고 다시 로드(LoadScene)해서 재시작 한다. 




PlayerPrefs
//Player Preference(플레이어 설정)라고 읽으면 간단한 방식으로 어떤 수치를 로컬에 저장하고 나중에 다시 불러오는 메서드를 //제공하는 유니티 클래스이다. 키-값(피이썬 딕셔너리, c#에서는 해시 테이블 처럼) 데이터를 저장하고, 저장할 때 사용할 키가 //무엇인지 기억하고 있다면 나중에 같은 키를 사용해 저장된 값을 다시 가져올 수 있다. 
//PlayerPrefs.SetFloat(string key, float value)라고 적으면 float 값을 저장할 수 있다. int string도 저장과 로드가 된다. 
//PlayerPrefs.GetFloat(string key)로 가져올 수 있다. 


 Vector3.Distance(currentPos, destPos)
 //두 백터간의 거리를 구하는 메서드 
 //float distance = Vector3.Distance(currentPos, destPos); //거리를 구하는 메서드 



Vector3.normalized = 정규화 
//Vector3 a = new(3,3,3);
//Vector3 b = Vector3.normalized;
//(3,3,3)의 방향 백터인 (0.57,0.57,0.57) 생성하지만 실제는 근사값인 0.6이 출력 될수 있다. 

//백터 정규화로 
현재 위치에서 목적지로 향하는 방향 
현재 위치에서 목적지를 향해 10만큼 이동한다고 가정해보자. 


//현재 위치(CurrentPos) 에서 목적지(desPos)꺄지의 거리 구하기 
Vector3 currentPos = new Vector3(1,0,1); //현재 위치 
Vector3 destPos = new Vector3(5,3,5); //목적지 

//currentPos 에서 destPos로 향하는 방향 벡터 )
Vector direction = (destPos-currentPos).nomalized;

//목적지를 향해 10만큼 혀내 위치에서 이동한 새로운 위치 
Vector3 newPos = currentPos + direction *10;




Vector3.magnitude; 백터의 크기 
//Vector3 a = new(3,3,3);
//float b = a.magnitude; //b는 5.19가 대력적으로 나옴 

Vector3.Dot(a,b) 백터의 내적
백터 b를 백터 a로 투영한 길이를 구한다. 
//Vector3 a = new Vector3(0,1,0);//위로 향하는 백터
//Vector3 b = new Vector3(1,0,0); //오른쪽으로 향하는 백터 
//flaot c = Vector3.Dot(a,b); //수직인 백터끼리 내적 하면 결과는 0


Vector3.Cross(a,b) 백터의 외적
//두백터 모두에 수직인 백터를 구한다. 
//Vector3.Cross(a,b);

Vector3 a = new Vector3(0,0,1);  //앞쪽으로 1
Vector3 b = new Vector3(1,0,0);  //오른쪽 1이면 외적은 수직역시 1이기에 외적은 (0,1,0)이 나온다. 
Vector3 c = Vector3.Cross(a,b) //c는 0,1,0 앞쪽가 오른쪽 모두 수직은 위쪽 방향 백터 


Quaternion(new Vector3(0.60,0) : 쿼터니언 회전 데이터 생성 
Quaternion rotation  = Quaternion(new Vector3(0.60,0));




rotation.eulerAngles
쿼터니언 회전값을 오일러 각으로 변환 
Quaternion rotation = Quaternion.Euler(new Vector3(0,60,0));

//백터3 타입의 값으로 (0,60,0)이 나옵니다. 
Vector3 eulerRotation = rotation.eulerAngles;  




<using>
using UnityEngine.UI;  //ui
using UnityEngine.SceneManagement;  //씬관리 관련 라이브러리 

<메뉴>
GameManager라 이름을 짓는 스크립트는 게임 오버 상태 표현, 생존 시간 갱신, ui를 표현하고 갱신, 게임오버시 게임 재시작을 담당하다 .

싱글턴 패턴의 필요성 
게임 매니저처럼 관리자 역활을 하는 오브젝트(파일 매니저 몬스터 매니저 점수 매니저 등등)은 일반적으로 프로그램에 단 하나만 존재해야 합니다. 그리고 언제 어디서든 즉시 접근이 가능해야 합니다. 
싱글턴 패턴은 객체의 인스턴스가 오직 1개만 생성되는 패턴을 의미한다


<ParticleSystem>
유니티의 ParticleSystem은 게임 개발에서 자주 사용되는 특수 효과를 생성하기 위한 도구 중 하나입니다. 예를 들어, 불꽃, 연기, 물결 등 다양한 비주얼 이펙트를 구현할 수 있습니다.
Emitter: 입자를 방출하는 위치입니다. 예를 들어, 불꽃이라면 불의 위치를 나타냅니다.

Particle: 입자 자체를 나타내는 것으로, 입자의 크기, 모양, 색상 등을 설정할 수 있습니다.

Renderer: 입자 시스템이 어떻게 렌더링될지를 결정하는 구성 요소입니다. 예를 들어, 입자를 스프라이트로 렌더링할 수 있습니다.

ParticleSystem을 사용하여 입자를 생성하려면, 먼저 ParticleSystem 구성 요소를 씬에 추가하고, 필요한 구성 요소들을 구성해야 합니다. 그리고나서 입자 시스템을 시작하고, 원하는 효과를 구현하기 위해 파라미터를 조정할 수 있습니다. 예를 들어, 입자의 수, 생명 주기, 초기 속도, 중력 등을 설정할 수 있습니다.

또한, ParticleSystem은 C# 스크립트를 사용하여 동적으로 제어할 수 있습니다. 이를 통해 입자의 속도, 크기, 색상 등을 런타임 중에 변경할 수 있습니다.

ParticleSytem은 게임 내 다양한 상황에서 사용될 수 있으며, 예컨대 폭발, 발사체, 기상 상황 등을 구현하는 데 사용될 수 있습니다.


<레이캐스트>
레이캐스트는 보이지 않는 광선을 쐈을때 광선이 다른 콜라이더와 충돌하는지 검사하는 처리
레이캐스트를 실행했을 때 레이가 콜라이더를 가진 게임 오브젝트와 충돌하면  RaycaseHit타입으로 충돌 정보가 생성됩니다. 충돌 정보는 게임오브젝트, 충돌한 위치, 충돌한 표면 방향등을 알 수 있다. 
fps, tps등의 슈터 게임은 대부분 레이캐스트를 이용해 총을 구현한다. 일반적으로 총구에서 레이를 발사해 다른 오브젝트오ㅓㅏ 충돌하는지 검사하고 충돌한 오브젝트를 총에 맞은 것으로 처리하는 방ㅅ힉을 사용한다. 



Physics.RayCast(Vector3 origin, Vector3 direction, out RaycastHit hitInfo,    float maxDistance);
			레이의 시작점   		레이의 방향 	레이가 충돌할 경우 hitInfo에 자세한 충돌 정보가 채워짐, 레이 충돌을 검사할 최대 거리 


<UI>
UGUI의 캔버스는 게임 화면을 기준으로  UI를 배치합니다. 체력 슬라이더는 
캔버스 인스팩터 창의 컴포넌트의 랜더 모드(Renderer mode)를 전역공간(World Space)로 변경합니다. 
단위당 레퍼런스 픽샐은 ui스프라아티의 픽셀 크기와 게임 월드의 유닛 크기가 대응되는 비율을 결정합니다. 

단위당 레퍼런스 필셀이 100이라고 가정할경우 1픽셀이 100유닛에 대응되므로 1유닛당 0.01픽셀이 대응됩니다. 이 값을 1로 변경하면 1유닛이 1픽셀이 대응되므로 유닛당 픽셀 집적도가 높아지고 ui가 깔끔하다. 다시 말해서 해상도를 높이는 것이다. 

Handle Slider Area를 삭제 해도 슬라이더를 드래그 할 수 있다. 
Interactable 채크 해제하면 사용자가 슬라이더를 움직일 수 있다. 
Transition 필드는 UI와 상호작용 시 일어나는 시각 피드백을 설정한다. Color Tint로 설정된 경우 UI요소에 마우스를 가져다 대거나 클릭하면 색이나 투명도가 잠시 변한다. 

슬라이더 컴포넌트는 최소값(Min value) 최대값(Max value) 현재값(value) 필드를 가진다. 

슬라이더 컴포넌트ㅜ는 value값에 따라 Fill Rect필드에 할당된 게임 오브젝트의 크기를 조정. 

네비게이션 창에 
agent radius값과 agent Height값은 에이전트 키와 반지름 값이다. 키와 반지름을 늘리면 니베 메시의 크기가 작게 구워지고, 게임 도중 인공지능이 다닐 수 있는 영역이 좁아진다. 올라가거나 이동하지 못하는 영역을 조정 가능하다. 
Bake를 눌러서 네비메시 에이전트의 이동 가능 영역을 만든다. 



<네비게이션 시스템>
한 위치에서 다른 위치로의 경로를 계산하고 실시간으로 장애물을 파ㅣ하며 이동하는 인공지능을 만드는 네비게이션 시스템을 제공하는

NavMesh :에이전트가 걸어 다닐 수 있는 표면 
NavMesh Agent :  내비메시 위에서 경로를 계산하고 이동하는 캐릭터 또는 컴포넌트 
NavMesh Obstacle :에이전트의 경로를 막는 장애물 
Off Mesh Link :  끊어진 내비메시 영역 사이를 잇는 연결 지점(뛰어넘을 수 있는 울타리나 타고 올라갈 수 있는 담벼락을 구현하는데 사용)





<코루틴>
StartCoroutine(CleaningHouse());

초단위로 쉬기 
 yield return new WaitForSecond(시간);
 
한 프레임만 쉬기 
 yield return null;
 
 StartCoroutine()메서드는 두가지 방법으로 실행할 코루틴 메서드를 입력받습니다. 
  StartCoroutine(SomeCoroutine()); 코루틴 메서드를 실행한 반환값
  StartCoroutine("SomeCoroutine"); //코루틴 메서드 이름 
  둘중 취향껏 쓰는것 같다. 
  
메서드 실행시 ()안에 인수를 넣어도 된다. 

반면 코루틴에 "SomeCoroutine"처럼 string 을 입력하는 방식은 나중에 StopCoroutine()메서드를 사용해 싨행중인 코루틴을 도중에 종류 할 수 있다 .
StopCoroutine("문자열");




<IK>
FK 
캐릭터 애니메이션은 기본적으로 FK(Forward Kinematics : 전진 운동학)로 동작한다. kf에서는 부모 조인트에서 자식 조인트 순서로 움직임을 적용한다. 자식 조인트는 부모 조인트에 종속되어 있기 때문에 부모 조인트가 움직이면 자식 조인트도 함께 움직인다. 
IK
Invrese Kinematics(역운동학)은 자식 조인트 위치를 먼저 결정하고 부모 조인트가 거기에 맞춰 변형 된다. 
ik로 물건을 결정하는 것은 손의 위치를 물건 위치로 만들고, 팔이 손의 위치에 맞춰 움직이고, 어깨가 팔의 위치에 맞춰 움직이는 것이다. 
ik를 움직이려먼 애니메이터 컨크롤러의 레이어에서 IK Pass설정이 켜져 있어야 한다 .
 Ik 정보를 갱신할 때마다. OnAnimatorIk메시지가 발생한다 스크립트에서 IK정보가 갱싲ㄴ할때마다. 자동 실행되는 OnAnimatorIk메서드를 구현하면 IK를 어떻게 사용할지 코드로 작성할 수 있다. 
 
 
 
plaeyrAnimator.GetIKHIintPosition(AvatarIKHint)타입으로 부위를 입력 받아 해당 부위의 현재 위치를 가져온다. 

AvatarIKHint.LeftElbow : 역운동학으로 제어 하는 왼쪽 팔꿈치 
AvatarIKHint.RightEblow : 역운동학 제어 하는 오른쪽 팔꿈치 
AvatarIKHint.LeftKnee;  왼쪽 무릎
AvatarIKHint.RightKnee;  오른쪽 무릎 

playerAnimator.SetIKpositionWeight(AvatarIKGoal.LeftHand, 1.0f) 왼손의 위치와 회전을 leftHandMount의 위치와 회전으로 변경, 그리고 왼손 IK에 대한 위치와 회전 가중치를 1.0(100%)으로 변경 한다. 

위치 가중치를 설정 하는 것을 SetIKpositionWeight)_
회전 가중치는 SetIKRotationWeight()이다. 정
AvatarIKGoal. 타입은 대상의 현재 부위를 말한다. 
AvatarIKGoal.LeftElbow 는 왼쪽 무릎 대상을 가리킨다 

ik가중치는 0~1까지이다. ik가중치는 해당 부위의 원래 위치와 Ik에 의한 목표 위치 사이에서 실제로 적용할 중간값을 결정합니다. 예를 들어서 IK가중치가 0.5(50%)라면 원래 위치와 IK목표 위차가 절반씩 섞여 적용된다. 

그럼 왼속 I의 목표 위치와 목표 회전을 LeftHandMount의 위치와 회전으로 지정합니다. 애니메이터의 SetIKPosition()과 SetIKRotation()은 IK대상이 사용할 모표 위치와 목표 회전을 서정한다. 



 


<스크립터블 오브젝트>
스크립터블 오브젝트는 유니티 프로젝트의 에셋 형태로 데이터를 담을 수 있는 타입이다. 씬 위의 게임 오브젝트가 아닌 형태로 존재해야 한다. 
여러 오브젝트가 공유하여 사용할 데이터를 에셋형태로 분리 
데이터를 유니티 인스팩터 창에서 편집 가능한 형태로 관리 

데이터를 단순 텍스트, xml,json포멧 등의 텍스트 파일로 저장할 수 있다. 
하지만 이 경우 해당 데이터는 유니티 에디터의 인스팩터 창에서 바로 편집할 수 없다. 

public class GunData : ScriptableObject
//GunData가 스테이블 오브젝트를 상속할 수 있게 짜여져 있다. 


[CreateAssetMenu(menuName = "메뉴 경로", fileName = "기본 파일명", order = 메뉴 상에서 순서)]
[CreateAssetMenu(menuName = "Scriptable/GunData", fileName = "Gun Data")]
//메뉴 상에서 순서는 생략하고 메뉴 경로는 Scriptable/GunData로 생성될 에셋에 기본 할당될 파일명은 GunData로 명시 했다. 
이후 프로젝트 창에서  +- Create 메뉴에 진입하면 GunData에셋 생성 메뉴가 있다. 



<좌표>

xyz x가 좌우 y가 위아래, z가 앞뒤 
0,0에서 -1.5,2까지의 거리라면 
|A| = |(-1.5, 2)| = 2.5
백터는 방향과 크기를 동시에 표현한다. 어떤 벡터의 방향과 크기(속력)를 직관적으로 파악하기 쉽게 나누어 표현할 때는 방향백터*스칼라곱 으로 표현할 수 있다. 이때 사용되는 방향 벡터는 어떤 벡터의 크기를 1로 늘리거나 줄이는 정규화를 통해 얻을 수 있다. 정규화 백터는 크기가 1인 백터이다. 방향은 유지한체 1로 바뀌기 때문에  방향 백터라고도 한다. 

백터는 유니티 라이브러리 내에서 구조체로 선언되어 있다. 

Vector2(x,y) , Vector3(x,y,z), Vector4(x,y,z,w);

Vector3 a = new Vector3(1,2,3);
 a.x = 10;
 a.y = 20;
 a.z = 30;

a*10 = (100,200,300)의 좌표가 된다. 
+ 와 - 역시 각각의 좌표에 더해지거나 빼진다. 

Vector3 응용

두점사이 거리 

//현재 위치(CurrentPos) 에서 목적지(desPos)꺄지의 거리 구하기 
Vector3 currentPos = new Vector3(1,0,1); //현재 위치 
Vector3 destPos = new Vector3(5,3,5); //목적지 

//currentPos에서 destPos 로 향하는 벡터 
Vector3 delta = desPos - currentPos;

//currentPos에서 destPos까지의 거리(크기 )ㅣ;
float distance = deleta.magnitude;

하지만 두 벡터사이의 거리를 계산하는 Distance()메서드가 Vector3 타입에 내장되어 있기 때문에

 //현재 위치(CurrentPos) 에서 목적지(desPos)꺄지의 거리 구하기 
Vector3 currentPos = new Vector3(1,0,1); //현재 위치 
Vector3 destPos = new Vector3(5,3,5); //목적지 

float distance = Vector3.Distance(currentPos, destPos); //거리를 구하는 메서드 




쿼터니언
쿼터니언은 회전을 나타낸다. 트랜스폼 컴포넌트의 rotition(회전)의 타입은 Quaternion
오일럭각 체계에서는 회전을 한번에 계산하지 않고 세번에 나누어서 계산하기 때문에 축이 겹쳐지는 문제가 있다. 
쿼터니언은 원소로 x,y,z외에도 w를 가지는 값으로 사원수라고 부르도 한다. 
쿼터니언은 한번에 회전하는 방ㅅ힉이기 때문에 오릴러각과 달리 짐벌락 현상이 ㅇ벗으므로 90도 회전을 제대로 ㅍ쵸현할 수 있다. 
따라서 게임에서 회전을 구현할 때는 쿼터니언을 사용한다. 하지만 쿼터니언은 복잡한 계산을 기반으로 하기 때문에 직관적으로 이해하고 사용하기 힘들다. 그래서 
유니티 내부에서는 쿼터니언으로 처리하지만 인스펙터 창에서는 트랜스폼 컴포넌트의 회전을 Vector3(오릴러각)으로 다루고 있다. 같은 이유로 유니티는 코드상에서
쿼터니언을 직접 생성하고, 쿼터니언 내부를 직접 수정하는 것을 허용하지 않고 메서드를 제공한다. 

예제)
Quaternion.Euler(Vector3);
(0,60,0) 회전을 표현하는 쿼터니언 회전 데이터를 생성하는 코드는 다음과 같다. 


쿼터니언 회전 데이터 생성 
Quaternion rotation  = Quaternion(new Vector3(0.60,0));



회전을 Vector3(오일러각)로 가져오기 
쿼터니언 타입은 저장된 회전값을 Vector3타입의 오일러 각으로 변환한 변수 delerAngles를 제공한다. 

Quaternion rotation = Quaternion.Euler(new Vector3(0,60,0));

//백터3 타입의 값으로 (0,60,0)이 나옵니다. 
Vector3 eulerRotation = rotation.eulerAngles;



현재 회전에서 더 회전하기 
(30,0,0)만큼 회전한 상태에서 (0,60,0) 만큼 회전한 상태를 표현해보자. 
이때 회전은 (30,60,0)과는 회전이 다르다는 것을 알아야 한다. 

Quaternion a = Quaternion.Euler(30,0,0);
Quaternion b = Quaternion.Euler(0,60,0);

//a만큼 회전한 상태에서 b만큼 더 회전한 회전값을 표현 
Quaternion rotation = a*b;  //여기서 중요한 것은 a에서 b만큼 더 회전한 것을 곱셈으로 펴현한다. 이는 쿼터니언 사이의 연산은 행렬을 사용하기 때문이다. 


//자식의 지역위치를 0,2,0으로 변경 
 childTransform.localPosition = new Vector3(0, 2, 0);

        transform.position = new Vector3(0, -1, 0); //위치가 -1로 이동된다. 

        //자식의 지역 위치를 (0,2,0)으로 변경 하이어라키 창의 자식 오브젝트를 인스펙텨 뷰의 스크립의 chardTransform에 드래그 해서 넣는 것을 잊지  말아야 한다. 
        childTransform.localPosition = new Vector3(0, 2, 0);

        //자식의 전역 회전을 (0,0,30)으로 변경 
        transform.rotation = Quaternion.Euler(new Vector3(0, 0, 30));

        //자식의 지역 회전을(0,60,0)으로 변경 
        childTransform.localRotation = Quaternion.Euler(new Vector3(0, 60, 0));

평형 이동 
ransform.Translate(new Vector3(0,1,0)*Time.deltaTime);`


백터의 이동 은 Vector3.up; 처럼 미리 단축키가 있다. up는 (0,1,0)을 말한다. 
압뒤 왼쪽 오른쪽 그리고 forward , right, 도 있다. 

transform.Translate(new Vector3(0,1,0);// 이 코드를 아래의 

transform.Positon = transform.Position+transform.up; //처럼 표현 할수 있다,. 

전역 공간 앞으로 평행 이동

transform.Translate(new Vector3(0,1,0), Space.World); //ranslate라는 메서드를 사용하는 것을 
칸은 동작은 

transform.position = transform.position.Vector3.up*1 ; //로 연산자형식으로 표현 할 수 있다. 




<스프라이트>
여러 스프라이트 시 
Inspector 
 Sprite Mode - Multiple 로 설정 
 Sprite Editor 클릭 에디터로 들어감 
 왼쪽위 슬라이스 화살표 -> 타입 설정 -> Slice누르기 
 스프라이트 잘라짐. 



<애니메이션 컨트롤러>

아래는 나중에 정리 

유한 상태머신
어떤 상황에 따라 어떤 애니메이션 클립을 재생해야 하는지 저장한 지도이며 Finite State Machine 모델을 사용한다. 유한수의 상태가 존재하면 한번의 한 상태만 현재 상태가 되도록 프로그램을 설계하는 모델이다. 
ai의 3가지 상태 탐색 추적 공격에 관한 Ai를 가지는 그러한 샘플이다. 
애니메이션 컨트롤러는 유한 상태 머신을 사용해 재생할 애니메이션을 결정하는 상태도를 표현할 에셋이다. 

기본 상태는 Entry
특정 상태로 즉시 전환 대는 상태 Any State
상태 머신이 종료 Exit


trigger 푸쉬 스위치 같이 상태. 버튼을 누르면 true로 됬다가 바로 다시 false가 된다 .


에니메이션 에로우 마크 
인스팩터 채크 옵션 
has exit time(종료 시간이 있습니다.)채크 하면 하나의 애니메이션이 재생이 끝날때 까지 있다가 다음 애니메이션으로 이동함. 채크를 없에면 이벤트시 다로  애니메이션 재생 중간에 이동함. 
Transition duratior  전환 기간(2개의 애니메이션이 있을 경우 겹쳐지는 기간)
conditions -> + -> 애니메이션 창에 설정했던 파라미터 변수값을 추가 할 수 있음. 

 //애니메이터의 Ground파라미터를 isGrounded값으로 갱신 
        animator.SetBool("Grounded", isGrounded); //
		//grounded,애니메이션 재생 조건은 SetBool값에 의해서 애니메이션 재생 된다. 

animator.SetTrigger("Die") ;//트리거는 이 함수 하나로 바로 재생된다. 



Apply Root Motion 채크 해제 
루트 모션 적용은 게임 오브젝트의 위치와 회전을 에니메이션이 제어하도록 허용한다. 르트 모션 적용을 선택하면 에니메이션을 재생하는 동안 게임 오브젝트의 실제 위치가 이전보다 앞족으로 변경된다. 루트 모션을 사용하지 않으면 제자리에서 걷는 ㅇ니메이션이 재생된다. 스크립트로 제어 하려면 제어를 해제 해야 햔다. 



blader tree에서 여러 애니메이션 클립을 혼합한다. 

avata mask로 동작할 에니메이션에 마스크를 씌울수 있다 .



일반 충돌이 시작된느 순간 실행되는 OnCollisionEnter() 메서드와 충돌한 두 콜라이더가 서로 떨어지는 순간 실행되는 OnCollisionExit() 메서드를 사용합니다. 단, 2D콜라이더에 의한 충돌을 검사할 때는 2D 버전을 사용해야 합니다. 따라서 OnCollisionEnter2D()메서드와 OnCollisionEnter2D메서드를 구현합니다. 
  if(collision.collider.tag == "Player" && !stepped) //충돌한 상대바의 태그그 Player이고 이전에 stepped를 닿지 않았(!)다면 
	  
  
collision.contacts[0].normal.y 라고 한다면 두 물체사이에 여로 충돌 지점 중에서 첫번째 충돌 지점의 y축 정보를 가져온 것이다. 노말 백터의 y값이 1이라면 수직 위방향이고 0.7이라면 대각선 방향일 것이다. -1 이라면 수직 아래일 것이다. 





<캔버스>
모든 ui를 잡아두는 루트 
캔버스는 ui를 잡아두는 틀이기 때문에 캔버스의 크기나 가로 세로 비율이 달라지면 캔버스에 배치된 ui의 모습도 다르게 보인다. 

640*360 해상도를 기준으로 게임 ui를 만들었다고 가정합시다. 이경우 200*200ui 이미지는 세로 방향으로 게임화면 절반 이상을 차지. 그런데 같은 게임을 1280*720해상도로 플레이하면 200*200 크기의 ui이미지는 세로 	방향으로 게임 화면의 절반보다 작은 영역을 차지 한다. 그래서 화면 크기에 따라 스케일 모드를 ui스케일 모드로 변경 해서 사용한다. 
화면 크기에 따라 스케일 모드는 작은 픽셀 크기로 그려진 최종 화면을 강제로 잡아 늘리는 방식이 아니라서 픽셀이 깨지는 현상을 걱정하지 않아도 된다. 

Scale With Screen Size == 화면 크기에 따라서 스케일 조정 모드이다.


<오브젝트 풀링>
초기에 필요한 만큼 오브젝트를 미리 만들어 Pool에 싸아두는 방식이다. 
새로운 오브젝트를 생성하지 않고 풀에 있는 오브젝트를 가져다 쓴다. 오브젝트를 필요 없을때는 파괴화는 대시 비활성화 해서 쓴다. ㅣ


--------------------

클린 코드 깃 
https://gyutts.tistory.com/247
https://github.com/sampaiodias/unity-clean-code


한 번만 필요한 것이라면 프리팹을 생성한 다음 인스턴스화하세요.
여러 번 필요하며 인스턴스와 관련하여 몇 가지 수정이 필요하다면 프리팹을 생성하고 인스턴스화한 다음 일부 설정을 오버라이드하면 됩니다.
여러 인스턴스를 동일하게 설정해야 한다면 프리팹 대신 스크립터블 오브젝트와 소스 데이터를 생성하세요. 

유니티 인터페이스 사용법 영상 
https://www.youtube.com/watch?v=Zzklpdvue3A
데미지를 주는 것들을 인터페이스로 묶어 준다.  
public interface IDameageable{


}

상속시 Monobehaver, IDameaeable 멀티 상속이 가능하다. 



프로퍼티 
변수에 외부 접근 속성과 
get, set 할당자를 추가 한것.

변수 접근 속성과, get set접근 속성을 구분할 수 있다. \
get은 read , set 은 write 기능을 가진다. 
