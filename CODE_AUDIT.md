# HollowKnight 코드 조사

조사일: 2026-10-13. 대상: 현재 클론된 저장소의 소스와 프로젝트 설정.

## 조사 범위와 한계

| 영역 | 소스 파일 수 | 줄 수 | 조사 내용 |
|---|---:|---:|---|
| Engine_SOURCE | 84 | 11,107 | 객체·컴포넌트, 씬, 충돌, 물리, 입력, 시간, 렌더링, 리소스, 오디오 |
| GameEngine | 86 | 9,946 | 플레이어, Grimm, PureVessel, 씬, UI, 투사체, 이펙트 |
| Editer_SOURCE | 8 | 271 | 그리드와 충돌 디버그 렌더링 |
| Editer_Window | 5 | 271 | Win32 진입점과 메시지 처리 |
| Shader_SOURCE | 12 | 452 | VS/PS/CS와 공통 버퍼·조명 |
| 합계 | 195 | 22,047 | C++ 헤더·구현·inl, HLSL 포함 |

프로젝트 파일과 공유 프로젝트의 컴파일 목록도 조사했다. 위 수치는 파일 목록의 규모이며 테스트 커버리지 수치가 아니다. Microsoft SimpleMath에서 유래한 kmMath.h/inl/cpp는 연결 방식과 게임에서 사용하는 수학 연산 중심으로 확인했다. External의 SDK 헤더·DLL·압축 라이브러리는 의존성 구성 대상으로 확인했으며, 제삼자 구현 전체를 감사하지 않았다. Resources의 이미지·오디오는 코드에 적힌 로드 경로와 대조했다. 메모장의 과거 코드 백업은 현행 빌드 대상으로 취급하지 않았다.

빌드·게임 실행·테스트는 하지 않았다. 아래의 종료·화면 이상·동작 영향은 소스 경로를 추적한 판단이며 실행 재현 결과가 아니다. 소스 수정, commit, push는 하지 않았고 이 보고서만 추가했다.

## 구조

저장소 이름에는 Direct2D가 들어 있지만 실제 렌더링은 Direct3D 11이다. VS2022 v143, Windows SDK, C++20 구성이다.

| 구성 | 역할 |
|---|---|
| Client.sln | 실행 프로젝트와 게임 정적 라이브러리, 공유 소스 묶음 |
| Editer_Window | 실행 파일. 전역 Application을 생성하고 Win32 루프에서 게임과 디버그 뷰를 호출 |
| GameEngine | 정적 라이브러리. Engine_SOURCE를 함께 컴파일하고 게임 객체와 씬을 구현 |
| Engine_SOURCE | GameObject에 Transform, Animator, Collider2D, Rigidbody, AudioSource 등을 부착하는 컴포넌트 구조 |
| Editer_SOURCE | 에디터 UI보다는 그리드와 충돌 박스를 그리는 디버그 도구 |
| Shader_SOURCE | 사각형 메시 기반 스프라이트, 아틀라스 애니메이션, 조명, 디버그 셰이더 |
| External / DLL | DirectXTex, FMOD, FW1FontWrapper 관련 파일 |

진입점은 Editer_Window/main.cpp의 wWinMain이다. Application::Run은 Update → LateUpdate → Render → Destroy 순서로 동작한다. Update 안에서는 Time → Input → CollisionManager → SceneManager 순서다. 게임 렌더링 후 Editor::Run, Present를 호출한다.

씬은 LoadScene.h에서 전부 미리 생성하고 TitleScene을 활성화한다. K 키로 TitleScene → Dirtmouth → Boss_Grimm_Stage → Godhome → Boss_PureVessel_Stage를 이동한다. 씬마다 별도 Player를 소유하므로 플레이어 상태를 다음 씬으로 넘기는 구조는 없다. PlayScene은 Zelda/컴퓨트 셰이더 실험용 장면으로 초기화되지만 K 키 이동 경로에는 없다.

## 우선 수정할 빌드·안정성 문제

P1은 빌드 차단, 초기 실행 실패, 메모리 접근 오류 또는 주요 기능 정지 가능성이 있는 항목이다. P2는 특정 동작·패턴·표시가 잘못되거나 장시간 누적되는 항목이다. 같은 원인의 여러 발생 위치는 한 항목으로 묶었다.

### A01 · P1 · 클론만으로 링크할 수 없는 외부 라이브러리 구성

위치: Engine_SOURCE/kmFmod.h:12, Engine_SOURCE/kmTexture.h:10, .gitignore.

FMOD 헤더는 External/Fmod/Library/Debug 및 Release의 .lib를 요구하지만 현재 폴더에는 Include만 있다. DirectXTex도 External/DirectXTex/Lib/Debug 및 Release를 요구하지만 Lib.zip만 존재한다. 저장소에서 펼쳐진 .lib 파일은 발견되지 않았다. DLL만으로 정적 링크를 대신할 수 없다. Debug/Release 폴더를 포괄적으로 무시하는 .gitignore도 의존 라이브러리 누락을 유발할 수 있다. FMOD Release 분기에는 fmod_vc.lib를 Debug 폴더에서 찾는 설정도 있다.

수정 방향: 버전·아키텍처에 맞는 의존성 설치/복원 방법과 경로를 명시하고, 필요한 라이브러리를 패키지 또는 허용된 저장소 구성으로 제공한다.

### A02 · P1 · Release 및 Win32 설정이 Debug x64와 일치하지 않음

위치: GameEngine/GameEngine.vcxproj:100, :137; Editer_Window/Editer_Window.vcxproj:112, :122; Editer_Window/main.cpp:15.

GameEngine의 Release는 pch.h 사용 설정인데 해당 파일과 PCH 생성 소스가 없다. 실행 프로젝트의 GameEngine include 경로 및 DLL 복사는 Debug x64에만 있다. main.cpp와 LoadScene.h의 라이브러리 경로는 플랫폼에 관계없이 x64로 고정된다. 현재 프로젝트에는 네 가지 구성이 표시되지만 동등하게 준비되어 있지 않다.

수정 방향: 우선 사용할 구성부터 정하고 include, PCH, 링크, DLL 복사 설정을 구성별로 맞춘다. ProjectReference와 중복되는 하드코딩 링크 경로도 정리한다.

### A03 · P1 · Transform의 부모 포인터 미초기화

위치: Engine_SOURCE/kmTransform.cpp:9, :51; Engine_SOURCE/kmTransform.h:51.

생성자는 위치·회전·크기만 초기화하고 mParent는 초기화하지 않는다. 모든 GameObject가 Transform을 가지며 LateUpdate에서 if (mParent) 후 부모 행렬을 읽는다. SetParent를 호출하지 않은 일반 객체도 미정의 포인터를 검사·역참조할 수 있다.

수정 방향: mParent를 nullptr로 초기화한다. 부모 객체가 삭제될 때의 연결 해제도 정의한다.

### A04 · P1 · Animator의 활성 애니메이션 포인터 미초기화

위치: Engine_SOURCE/kmAnimator.cpp:6, :107; Engine_SOURCE/kmAnimator.h:59.

생성자에서 mActiveAnimation과 mbLoop를 초기화하지 않는다. 첫 PlayAnimation도 기존 애니메이션이 있는지 검사하고 GetKey를 호출하므로 게임 루프 이전 씬 초기화 과정부터 잘못된 포인터에 접근할 수 있다.

수정 방향: nullptr/false로 초기화하고, 존재하지 않는 애니메이션 이름을 전달했을 때 현재 포인터를 역참조하지 않도록 처리한다.

### A05 · P2 · 텍스처 없는 머티리얼로 잘못된 멤버 함수 호출

위치: Engine_SOURCE/kmMaterial.cpp:34; Engine_SOURCE/kmMeshRenderer.cpp:41; Engine_SOURCE/kmRenderer.cpp의 SpriteAnimaionMaterial, GridMaterial, DebugMaterial 생성부.

Material::Clear는 mTexture->Clear를 무조건 호출한다. 그런데 애니메이션·그리드·디버그 머티리얼에는 텍스처를 설정하지 않는다. 애니메이션은 Animation이 t12에 아틀라스를 바인딩하는 구조다. nullptr로 비정적 멤버 함수를 호출하므로 C++의 미정의 동작이다. 다만 현재 Texture::Clear 본문은 객체 멤버를 읽지 않아 즉시 종료된다고 보장할 수는 없다.

수정 방향: 머티리얼이 실제로 바인딩한 자원과 슬롯을 기준으로 정리한다. Animation의 t12도 그 수명과 바인딩 책임에 맞춰 처리한다.

### A06 · P1 · 그리드 상수 버퍼 업로드가 스택 객체 밖을 읽음

위치: Engine_SOURCE/kmRenderer.cpp:281; GameEngine/kmGridScript.cpp:57; Engine_SOURCE/kmConstantBuffer.cpp:28; Engine_SOURCE/kmGraphicDevice_Dx11.cpp의 SetConstantBuffer.

Grid용 버퍼를 sizeof(TransformCB), 즉 행렬 3개 분량인 192바이트로 생성한다. 실제 전달하는 GridCB는 32바이트다. SetData는 생성 시 ByteWidth 전체를 memcpy하므로 32바이트 스택 객체에서 192바이트를 읽는다. 매 프레임 에디터 그리드 경로가 이 업로드를 수행한다.

수정 방향: sizeof(GridCB)로 생성하고 업로드 API가 입력 데이터 크기를 확인하도록 만든다.

### A07 · P1 · Dark Tentacle 종료 상태에서 삭제된 이펙트 재접근

위치: GameEngine/kmPureVessel.cpp:1770; Engine_SOURCE/kmLayer.cpp의 Destory.

Dark_Tentacle_End는 상태에 머무는 매 프레임 mDark_Tentacle_Effect->Destroy를 호출한다. 첫 호출은 이펙트를 Dead로 표시하고 그 프레임 끝에 Layer가 실제 삭제한다. 종료 애니메이션이 끝나기 전 다음 프레임에는 같은 포인터로 다시 Destroy를 호출한다.

수정 방향: 종료 상태의 첫 진입에서만 삭제를 예약하고 포인터를 비운다. 현재 기본 패턴은 Roar에 고정되어 있어 이 문제는 Dark Tentacle 패턴을 활성화할 때 드러나는 경로다.

### A08 · P1 · 아직 재생하지 않은 오디오 채널 접근

위치: Engine_SOURCE/kmAudioSource.cpp:21; Engine_SOURCE/kmAudioClip.cpp:42.

AudioSource::LateUpdate는 모든 클립에 Set3DAttributes를 호출한다. AudioClip의 mChannel은 Play 전에 nullptr인데 Set3DAttributes는 이를 바로 역참조한다. Player는 초기화 때 걷기·점프·대시 등 여러 소스를 만들고 일부만 실제 재생하므로 첫 플레이어 씬 LateUpdate에서 이 경로에 도달한다. Stop/SetVolume/SetMute도 채널 유효성을 확인하지 않는다.

수정 방향: 클립과 채널 유효성을 확인하고 채널 생성 이후에 속성을 적용한다.

### A09 · P1 · 리소스 로드 실패를 성공으로 취급

위치: Engine_SOURCE/kmTexture.cpp:96, :101, :106; Engine_SOURCE/kmAudioClip.cpp:24; Engine_SOURCE/kmResources.h:39; Engine_SOURCE/kmRenderer.cpp:427.

Texture와 AudioClip은 실패할 때 S_FALSE를 반환한다. Resources는 FAILED로 검사하기 때문에 S_FALSE를 실패로 인식하지 못하고 불완전한 리소스를 캐시에 넣는다. renderer는 현재 존재하지 않는 Resources/UI/MPUI/HUD/HUD.png를 초기 로딩에서 요구한다. 현재 UI 자산에는 HUD/HUD_Flame.png 등이 있지만 위 경로의 파일은 없다. Texture의 SRV 생성 결과도 검사 없이 바로 mSRV를 사용한다.

수정 방향: 실패 HRESULT를 그대로 전달하고 성공한 리소스만 등록한다. 누락된 HUD 로드의 용도를 결정하고 유효 경로로 교체하거나 사용하지 않는 로드를 제거한다.

### A10 · P1 · 셰이더·그래픽 장치 실패가 다음 포인터 접근으로 이어짐

위치: Engine_SOURCE/kmShader.cpp:27; Engine_SOURCE/kmComputeShader.cpp:20; Engine_SOURCE/kmGraphicDevice_Dx11.cpp:26, CompileFromfile, SetConstantBuffer, BindBuffer.

셰이더 컴파일 결과를 확인하지 않고 blob을 역참조한다. CompileFromfile은 실제 컴파일 결과와 관계없이 false를 반환한다. 장치 생성 결과를 확인하지 않으며 모든 구성에 D3D11_CREATE_DEVICE_DEBUG를 요청한다. 디버그 런타임이 없는 배포 환경에서는 장치 생성 실패 가능성이 있고 이후 QueryInterface 경로가 장치를 사용한다. GPU 버퍼 Map 실패도 확인하지 않고 pData에 memcpy한다.

수정 방향: 실제 반환값을 전달하고 실패한 초기화는 상위 Application까지 전파한다. Debug 장치 플래그를 구성에 맞추고 버퍼 Map도 성공 후 복사한다.

## 동작·물리·리소스 문제

### B01 · P2 · 충돌 중심 오프셋이 판정에서 빠짐

위치: Engine_SOURCE/kmCollisionManager.cpp:119; Engine_SOURCE/kmCollider2D.cpp:43.

SetCenter는 디버그 박스 위치에 반영되지만 Intersect는 Transform 위치만 중심으로 사용한다. PlayerEffet, PureVessel, DarkWhip 등이 사용하는 오프셋이 실제 타격 판정에는 적용되지 않는다. 화면에 그린 충돌 박스와 판정이 다르다.

수정 방향: 크기·회전·부모·중심을 포함한 동일한 충돌 월드 변환을 판정과 디버그 렌더링에서 공유한다.

### B02 · P2 · 충돌 판정의 위치와 축이 서로 다른 프레임에 해당

위치: Engine_SOURCE/kmApplication.cpp:42; Engine_SOURCE/kmTransform.cpp:28; Engine_SOURCE/kmCollisionManager.cpp:121, :147.

충돌은 Scene Update와 Transform LateUpdate보다 먼저 수행된다. Intersect는 GetMatrix의 이전 LateUpdate 행렬로 축을 만들면서 GetPosition은 현재 저장된 값을 사용한다. 초기 배치 이후 첫 충돌, 순간이동, 크기·회전 변경에는 축과 중심이 일치하지 않으며 움직임 충돌도 한 프레임 늦게 반영된다.

수정 방향: 이동/물리와 월드 변환 갱신 이후 충돌을 수행하거나 충돌 전용 최신 변환을 계산한다.

### B03 · P2 · 충돌 초기화가 행렬 첫 행만 비움

위치: Engine_SOURCE/kmCollisionManager.cpp:189.

mMatrix는 bitset 배열인데 mMatrix->reset은 첫 원소만 비운다. Clear 이후에도 대부분의 레이어 조합이 남는다. 또한 현재 씬 초기화는 전역 충돌 행렬에 조합을 누적하고 OnEnter에서 씬별로 재구성하지 않는다.

수정 방향: 배열 전체를 순회해 초기화하고 씬별 충돌 설정의 적용 시점을 정한다.

### B04 · P2 · 비활성/삭제 객체와의 충돌 종료 및 이력 정리 누락

위치: Engine_SOURCE/kmCollisionManager.cpp:37, :60; Engine_SOURCE/kmLayer.cpp의 Destory.

Paused/Dead 객체를 발견하면 판정을 건너뛰므로 이전에 충돌 중이던 상대에게 Exit를 주지 않는다. 상대의 mCollisionCount나 Ground_Check가 남을 수 있다. mCollisionMap에는 충돌 여부와 무관하게 조사한 쌍을 넣고 객체 삭제 시 제거하지 않아 오래 플레이하면 투사체·이펙트 ID 쌍이 누적된다.

수정 방향: 객체 비활성화·삭제·씬 이동에서 충돌 쌍을 종료하고 해당 이력을 지운다.

### B05 · P2 · 중복 초기화로 Collider와 Transform이 중복 부착됨

위치: GameEngine/kmDirtmouth.cpp의 Ground 생성; GameEngine/kmBoss_Grimm_Stage.cpp의 Ground/Wall 생성; GameEngine/Boss_PureVessel_Stage.cpp:79; Editer_SOURCE/guiEditor.cpp:30.

Instantiate는 Initialize를 이미 호출하는데 씬에서 ground/Wall의 Initialize를 다시 호출해 Collider를 추가한다. 에디터 DebugObject는 GameObject 생성자가 Transform을 붙인 뒤 다시 Transform을 추가한다. GetComponent는 첫 컴포넌트만 반환해 중복 부착이 의미 있게 사용되지 않고 비용과 관리 혼란을 만든다.

수정 방향: 객체 초기화 호출을 한 곳으로 통일하고 유일해야 하는 컴포넌트의 중복을 막는다.

### B06 · P2 · Player 상태 초기화 누락

위치: GameEngine/kmPlayer.cpp:29, :202; GameEngine/kmPlayer.h:65.

생성자와 Initialize에서 Player의 mState를 설정하지 않는데 첫 Update가 이를 switch로 읽는다. 이후 Fall 상태를 설정하는 코드가 있어도 첫 읽기의 미정의 동작을 해결하지 않는다.

수정 방향: 생성 또는 Initialize에서 Idle/Fall 등 의도한 시작 상태를 명시한다.

### B07 · P2 · PureVessel 첫 Idle의 방향 초기화 누락

위치: GameEngine/kmPureVessel.cpp:26, :841.

인트로 완료 콜백이 Idle로 진입하지만 그 전에 mDirection을 설정하는 경로가 없다. 매 프레임 계산하는 Live_Direction은 별도 멤버다. Idle의 두 방향 분기가 모두 실패하면 인트로 완료 애니메이션에서 진행이 멈출 수 있다.

수정 방향: 시작 방향을 명시하고 상태 진입에서 Live_Direction을 mDirection으로 고정한다.

### B08 · P2 · 아래 공격과 회복 상태 전이가 다른 상태를 지정

위치: GameEngine/kmPlayer.cpp:815, :931, :913.

DownAttack이 mState를 UpAttack으로 바꾼다. 다음 업데이트는 위 공격 로직으로 들어가 아래 공격을 덮어쓸 수 있다. Focus도 mState를 FocusStart로 설정하므로 Update가 Focus를 호출하지 않아 Focus 안의 키 해제 처리가 지속 실행되지 않는다. FocusStart의 키 해제 검사는 최초 진입 플래그 안에 있어 이후 해제 입력을 놓친다.

수정 방향: 각 상태 함수는 자신의 상태를 유지하고 취소 입력을 최초 진입 처리 밖에서 감지한다.

### B09 · P2 · 공중 행동 상태를 공통 Fall 처리로 덮어씀

위치: GameEngine/kmPlayer.cpp:253, :763, :802, :841, :886.

공중 공격·스킬 진입 시 Fall_Delay를 켜지만 행동 함수는 완료 전에 이를 false로 바꾼다. Update 끝의 공통 조건은 그 프레임에 mState를 Fall로 다시 바꿀 수 있다. 공격 상태와 실제 재생 애니메이션, 입력 가능 여부가 분리된다.

수정 방향: 공중 여부와 행동 상태를 구분하고 행동 완료/취소 시에만 이동 상태로 전환한다.

### B10 · P2 · HP 범위와 마지막 체력 회복 표시 처리 누락

위치: GameEngine/kmPlayer.cpp:327, :970; GameEngine/kmPlayerHP_State.cpp:48.

Q 감소와 FocusOn 증가에 0~5 제한이 없다. HP가 6 이상 또는 음수가 되면 UI의 0~5 분기에 걸리지 않는다. HP_State에는 HP_00을 손상시키는 분기는 있지만 0에서 1로 회복할 때 HP_00을 채우는 분기가 없다.

수정 방향: 최대/최소 HP를 모델에서 보장하고 이전/현재 HP 차이를 기반으로 UI를 갱신한다.

### B11 · P2 · HP UI 업데이트가 두 번 실행됨

위치: GameEngine/kmPlayerHP.cpp:54, :56.

PlayerHP::Update가 GameObject::Update를 연달아 두 번 호출해 Animator도 한 프레임에 두 번 진행한다. 다른 애니메이션에 비해 HP Idle/Break/Refill 타이밍이 빨라진다.

수정 방향: 중복 호출을 제거한다.

### B12 · P2 · 오른쪽 공격 이펙트가 왼쪽 아틀라스를 재생

위치: GameEngine/kmPlayerEffet.cpp:139, :151.

UP_Slash_Right와 Down_Slash_Right가 각각 UP_Slash_Left, Down_Slash_Left 이름을 PlayAnimation에 전달한다. 오른쪽 텍스처와 애니메이션은 따로 생성되어 있다.

수정 방향: 오른쪽 함수에서 오른쪽 이름을 사용한다.

### B13 · P2 · 다른 이미지에 같은 리소스 키를 재사용

위치: GameEngine/kmGirmm_Hand.cpp:29; GameEngine/FireBallSkill_Effect.cpp:29; GameEngine/kmGuidLight.cpp:28; GameEngine/kmRoarEffect.cpp:28.

Hand_Out에 FireBallEffect_Left 키를 사용해 플레이어 스킬 이펙트와 충돌한다. 먼저 로드된 이미지가 나중 호출에도 반환된다. GuidLight의 00/01/02 이미지도 모두 LightGuid_On 키라서 전부 00 텍스처를 받는다. RoarEffect의 End 이미지도 Start 키로 등록된다.

수정 방향: 실제 리소스를 식별하는 고유 키를 사용한다. Resources가 같은 키의 경로 불일치를 진단하도록 하면 이런 복사 오류를 찾기 쉽다. 대소문자가 다른 Up_Slash/UP_Slash 키는 std::map에서 별개이므로 이 항목에 포함하지 않았다.

### B14 · P2 · 플레이어 FireBallSkill이 계속 남음

위치: GameEngine/kmFireBallSkill.cpp:45, :95.

Destroy 함수는 있으나 Update, 충돌 또는 완료 콜백에서 호출하지 않는다. 초기 애니메이션이 끝나면 Loop로 바꾸고 계속 이동한다. C 입력마다 생성되는 객체가 화면 밖에도 남아 업데이트·렌더 분류·충돌 탐색 비용을 누적시킨다.

수정 방향: 수명, 화면/월드 경계 또는 충돌 종료 기준을 정하고 삭제한다.

### B15 · P2 · Grimm Spike의 대기 시간 미초기화

위치: GameEngine/kmSpike_Object.cpp:13, :71; GameEngine/kmSpike_Object.h:32.

mSpike_On_Delay만 초기화하고 mSpike_Loop_Delay는 초기화하지 않는다. Loop 진입 후 처음 +=를 수행할 때 불확정 값을 읽어 가시 제거 시간이 들쭉날쭉하거나 진행하지 않을 수 있다. 메모장/버그.txt의 오브젝트 타이밍 메모와 연관될 수 있지만 실행으로 같은 원인임을 입증한 것은 아니다.

수정 방향: 타이머를 생성 때 0으로 초기화하고 각 상태 진입에서 다시 설정한다.

### B16 · P2 · FMOD의 프레임 업데이트 호출 누락

위치: Engine_SOURCE/kmFmod.cpp; Engine_SOURCE/kmApplication.cpp:42.

FMOD 시스템 초기화·재생·리스너 속성 설정은 있지만 활성 코드에 시스템 update 호출이 없다. 유일하게 보이는 update는 초기화 예제의 주석이다. FMOD의 주기적 처리와 3D 속성 반영을 위한 호출 경로가 빠져 있다.

수정 방향: 프레임 오디오 갱신 함수를 만들고 게임 루프에서 호출한다.

### B17 · P2 · 여러 AudioSource가 하나의 재생 채널을 공유

위치: Engine_SOURCE/kmAudioClip.h:26; Engine_SOURCE/kmAudioClip.cpp:31; Engine_SOURCE/kmResources.h:28.

Resources가 AudioClip을 공유하고 AudioClip이 마지막 재생 Channel을 소유한다. 여러 씬의 Player도 같은 WalkSound 등의 키를 사용한다. 같은 클립의 중첩 재생이나 두 소스 재생에서는 채널 포인터가 덮어써져 Stop/볼륨/위치가 의도와 다른 재생에 적용된다. 위치 갱신에서는 forward 방향 벡터를 velocity로 전달한다.

수정 방향: Sound 자원은 공유하되 Channel은 AudioSource별로 관리하고 실제 속도를 사용한다.

### B18 · P2 · 애니메이션이 낮은 FPS에서 느려짐

위치: Engine_SOURCE/kmAnimation.cpp:30.

duration을 넘겨도 한 프레임만 전진하고 mTime을 0으로 버린다. 예를 들어 프레임 duration 0.02초에 게임 프레임이 0.05초 걸리면 두 프레임 이상 진행해야 하지만 하나만 진행한다. 플레이어 공격·점프 종료와 보스 상태 전이가 애니메이션 완료에 묶여 있어 게임 동작 시간도 FPS에 따라 달라진다.

수정 방향: 초과 시간을 유지하고 필요한 프레임만큼 진행한다. 마지막 프레임의 완료와 콜백은 한 번만 처리한다.

### B19 · P2 · 완료 이벤트가 반복 애니메이션에서만 호출됨

위치: Engine_SOURCE/kmAnimator.cpp:35.

completeEvent가 IsComplete && mbLoop 안에 있다. loop=false로 재생한 애니메이션은 완료되어도 완료 이벤트를 받지 않는다. 현재 상당수 일회성 이펙트가 true를 써서 삭제 이벤트를 받는 것은 이 구조의 우회다.

수정 방향: 완료 이벤트와 반복 여부를 독립적으로 처리하고 콜백이 활성 애니메이션을 바꾸는 경우 이전/새 애니메이션의 reset 순서를 명시한다.

### B20 · P2 · 조명 버퍼 증설 시 그 프레임 데이터를 업로드하지 않음

위치: Engine_SOURCE/kmStructedBuffer.cpp:38; Engine_SOURCE/kmRenderer.cpp의 BindLights; Shader_SOURCE/SpritePS.hlsl:27.

현재 Create(size, stride) 구현은 size를 요소 바이트 크기, stride를 요소 개수로 사용한다. SetData는 개수가 기존 용량을 넘으면 버퍼를 새로 생성하고 데이터 복사는 else에서만 한다. 세 번째 조명을 추가하는 프레임은 데이터가 업로드되지 않는다. 픽셀 셰이더는 조명 개수와 관계없이 항상 두 개만 읽어 한 개짜리 씬에서는 이전 요소 값이 남을 수 있고 세 개 이상은 무시된다.

수정 방향: 요소 크기·개수 이름과 용도를 명확히 하고 증설 후에도 업로드한다. 실제 조명 개수를 전달하거나 빈 요소를 초기화한다.

### B21 · P2 · 씬과 맞지 않는 디버그 카메라/카메라 마스크

위치: GameEngine/kmPlayScene.cpp의 mainCamera 설정; GameEngine/kmTitleScene.cpp:45; Editer_SOURCE/guiEditor.cpp:43, :124.

에디터 그리드는 초기화 때 renderer::cameras[0]을 저장하고 이후 씬 전환 시 교체하지 않는다. 그 카메라는 초기 PlayScene 카메라다. TitleScene과 Godhome도 OnEnter에서 renderer::mainCamera를 갱신하지 않는다. TitleScene의 두 번째 카메라는 UI 전용 마스크가 아니라 Player만 제외한 기본 전체 마스크여서 배경이 두 번 그려진다.

수정 방향: 활성 씬의 카메라를 기준으로 에디터 참조를 갱신하고 UI 카메라에는 UI만 허용한다.

### B22 · P2 · 창 크기 변경·최소화와 GPU 대상 크기가 불일치

위치: Editer_Window/main.cpp의 WndProc; Engine_SOURCE/kmGraphicDevice_Dx11.cpp:481; Engine_SOURCE/kmCamera.cpp:102.

WM_SIZE에서 ResizeBuffers와 렌더/깊이 대상 재생성을 하지 않고 매 프레임 viewport만 클라이언트 크기로 바꾼다. 창 크기가 바뀌면 viewport와 실제 백버퍼 크기가 다르다. 최소화 시에는 카메라가 높이 0으로 aspect ratio와 투영행렬을 계산한다.

수정 방향: 유효한 크기 변경에 맞춰 GPU 대상을 재생성하고 최소화 중에는 렌더링을 건너뛴다.

### B23 · P2 · 충돌 디버그 색상용 상수 버퍼 미연결

위치: Shader_SOURCE/DebugPS.hlsl:23; Shader_SOURCE/globals.hlsli의 Col; Engine_SOURCE/kmRenderer.h의 ColCB; Editer_SOURCE/guiEditor.cpp의 DebugRender.

Collider의 mCollisionCount는 DebugMesh에 전달되지만 DebugRender는 ColCB를 업로드하지 않는다. eCBType에도 b4에 해당하는 충돌 버퍼 항목이 없어 DebugPS의 c_ColCount를 정상적으로 갱신하는 경로가 없다.

수정 방향: b4 버퍼 생성·업로드·PS 바인딩을 연결하거나 색을 다른 디버그 데이터 경로로 전달한다.

### B24 · P2 · 실행 위치에 의존하는 자산 경로

위치: Engine_SOURCE/kmShader.cpp:29; Engine_SOURCE/kmComputeShader.cpp:22; GameEngine 전반의 Resources::Load.

셰이더는 current_path().parent_path()/Shader_SOURCE, 게임 자산은 ../Resources를 기준으로 찾는다. Visual Studio에서 특정 working directory로 실행하는 경우와 exe를 더블클릭하는 경우의 기준 디렉터리가 다르다. x64/Debug에서 직접 실행하면 현재 경로 규칙은 저장소 루트의 Resources/Shader_SOURCE와 맞지 않을 수 있다.

수정 방향: 실행 파일 또는 명시적인 자산 루트를 기준으로 경로를 구성하고 배포 폴더 구조를 정의한다.

## 미구현·실험 단계인 기능

아래는 코드를 읽고 확인한 기능 상태다. 완성 요구사항이 제공되지 않았으므로 모두를 버그로 단정하지 않는다.

| 기능 | 현행 상태 | 관련 위치 |
|---|---|---|
| 플레이어 피해 | Ground 접촉만 처리. HP 감소는 Idle의 Q 키 디버그 입력 | kmPlayer.cpp:285, :324 |
| 보스 피해·HP·승리 | Grimm/PureVessel에 HP 감소와 승리 전이 없음. Death는 상태만 지정하거나 빈 함수 | kmGrimm.cpp의 Death, kmPureVessel.cpp:632, :1894 |
| 타격 연결 | Effect/Skill/BossObj와 전투 대상의 레이어 조합이 활성화되지 않고 피해 콜백도 없음 | 각 씬 Initialize와 kmCollisionManager |
| MP/Soul | SoulGauge는 이미지 표시. 스킬·회복 비용과 자원 증감 모델 없음 | kmSoulGauge.cpp, kmPlayer.cpp의 Skill/FocusOn |
| Grimm 패턴 선택 | PatternState=4 고정. 난수 선택 코드는 주석 | kmGrimm.cpp 생성자 및 Pattern |
| PureVessel 패턴 선택 | mPattern=4 고정으로 Roar 반복. 페이즈 분기는 주석 | kmPureVessel.cpp:41, :759 |
| PureVessel Counter | Cast → Loop → End 완료 이벤트/시간 전이가 연결되지 않음. 활성화하면 Cast에 머물 수 있음 | kmPureVessel.cpp:858 |
| Grimm Balloon 탄막 | Set5/6/7 이동이 비어 있고 Set0의 세 if가 같은 프레임에 연속 수행됨 | kmFIreBall.cpp:62 |
| PureVessel Knife Spread | 가이드 라이트만 생성. Spear 생성·발사 연결 없음 | kmPureVessel.cpp:1973, kmSpear.cpp |
| 더블 점프 횟수 | 완료 때 Double_Jump_Check를 다시 켜므로 착지 전에도 반복 가능 | kmPlayer.cpp:710, :1046 |
| 플레이어 사망·리스폰 | Death 빈 함수, HP 0 전이 없음 | kmPlayer.cpp:1121 |
| 에디터 조작 UI | Widget 빈 클래스. 편집/저장 인터페이스 없음 | guiWidget.h |
| Ground 컴포넌트 | 실제 충돌 처리는 주석. 활성 게임은 GroundScript GameObject 사용 | Engine_SOURCE/kmGround.cpp |
| 옛 GrimmScript | 프로젝트 컴파일 목록에 없는 구형 코드. 누락된 kmPlayerScript.h include, 미초기화 mPlayer 사용 | kmGrimmScript.cpp:11, Update |
| PureVesselScript | 빈 클래스 | kmPureVesselScript.h |

GrimmScript의 옛 AirDash_Stop 이미지 두 경로는 현재 Resources에 없다. 현행 빌드 목록에서 빠져 있으므로 게임 시작 경로의 누락 자산과 구분한다.

## 추가 유지보수 관찰

- Scene::FindObjectsOfType는 vector<Layer>를 Layer*로 순회한다. 이 템플릿을 사용하면 타입 불일치가 문제 된다. Layer&로 순회해야 한다. 위치: Engine_SOURCE/kmScene.h:31.
- 몇몇 게임 헤더는 Animator/Rigidbody/VectorR 등 타입을 직접 선언·포함하지 않고 이전 include 순서에 기대고 있다. Debug의 Unity 빌드가 이런 의존성을 가릴 수 있다. 헤더가 독립적으로 필요한 선언을 갖도록 정리할 필요가 있다.
- ConstantBuffer::Create는 생성 결과를 확인하지 않고 항상 false를 반환한다. 호출부가 현재 이를 무시하지만 반환값 계약이 잘못됐다.
- Rigidbody는 질량 기본값이 0인데 force/mass를 바로 수행한다. 현재 Player는 SetMass(0.1f)를 호출한다. 범용 컴포넌트로 사용하려면 양의 질량을 보장해야 한다. 계산한 제한 속도 성분을 최종 mVelocity에 다시 합치지 않아 제한도 실제 이동에 적용되지 않는다.
- VectorR::operator!=는 x와 y가 모두 달라야 true라서 한 축만 다른 벡터를 같은 것으로 취급한다. 현재 Rigidbody는 이 연산자를 쓰지 않으므로 현행 이동 버그로 확대하지 않았다.
- SceneManager::CreateScene은 중복 이름 검사 전에 new를 수행해 중복 생성 요청이 누수된다. Release는 map을 비우거나 활성 씬을 해제하지 않는다. 현재 시작/종료 한 번 경로와 재초기화 사용을 구분해야 한다.
- Layer가 객체 벡터를 순회할 때 동일 레이어에 Instantiate/AddGameObject를 하면 iterator가 무효화될 수 있다. 현재 대표 패턴은 다른 레이어에 생성한다. 새 생성 경로 추가 시 지연 등록 구조가 안전하다.
- PlayerHP_State는 HP 1 이상 급변에 대한 전체 UI 재동기화가 없고, 플레이어 상태가 씬마다 별개다. 저장/이어하기 기능을 추가할 때 하나의 플레이어 모델을 먼저 정하는 편이 좋다.
- AudioClip Sound 해제는 주석 처리되어 있다. 현재 전체 FMOD 시스템 종료가 뒤따르지만 개별 자산 해제/교체 시 소유권 정책이 불명확하다. 종료 순서와 Resources 정리도 명시하는 편이 좋다.
- UI는 별도 화면 좌표계 대신 월드 카메라 위치를 따라간다. UI 레이어가 Camera 레이어보다 뒤에서 업데이트되므로 이전 프레임 카메라 위치를 읽는다.
- TitleScene/Godhome의 mainCamera, 에디터가 저장한 카메라, 각 씬의 렌더 카메라가 별도 관리되어 있다. 카메라 접근 API를 하나로 모으면 씬 전환 오류를 줄일 수 있다.
- AirDash_Loop 등은 방향 벡터의 x/y를 3D 회전 각도로 전달한다. 2D Z 회전을 원한다면 atan2 기반 각도와 축을 명시해야 한다. 현재 크기 z=0과 결합되어 시각·충돌 축을 왜곡할 수 있다.
- PureVessel CircleObj는 마지막 가이드의 시간을 2.2초로 설정한 직후 2.4초로 덮어쓰며 Guid_On도 중복 호출한다. 마지막 호출은 플래그로 막히지만 시간은 최종 값만 사용된다.
- 리소스 로드와 애니메이션 생성, 여러 투사체의 생성·배치가 복사 코드로 반복된다. 오류를 먼저 수정한 뒤 데이터 배열과 상태별 진입/갱신/종료 처리로 정리할 수 있다.
- CraeteDepthStencilView, SpriteAnimaionMaterial, LSHFIT, DsahEffect 같은 오타는 사용처가 일치하는 경우 이름만으로 결함이 아니다. 이번 조사에서는 오타 자체를 빌드 오류로 계산하지 않았다.
- CameraScript는 멤버 기본값을 명시하지 않았지만 현행 AddComponent의 new T()와 암시적 기본 생성자 조합에서는 값 초기화로 mTarget/mHight가 0이 된다. 사용자 정의 생성자를 가진 Transform/Animator/Player와 구분했으며, 현행 카메라 포인터를 미초기화 결함으로 계산하지 않았다.

## 수정 순서

1. A01/A02: 새 PC에서도 사용할 빌드 구성을 복원한다.
2. A03~A06/A08~A10: 초기화와 첫 프레임의 메모리·리소스 문제를 먼저 수정한다. A07은 Dark Tentacle 활성화 전에 함께 수정한다.
3. B01~B05: 충돌 좌표·순서·이력과 중복 초기화를 정리한다.
4. B06~B19: 플레이어 상태, 보스 시작 방향, HP/이펙트, 자산 키, 투사체 수명과 오디오·애니메이션 시간을 정리한다.
5. 전투 완성이 목표라면 피해·무적 시간·보스 HP·승리/사망·Soul 비용을 모델로 구현하고 모든 패턴을 선택 가능하게 연결한다.
6. 렌더/조명/디버그/창 크기 변경과 배포 경로를 마무리한다. 이후 반복 상태 코드를 데이터로 정리한다.

수정 뒤 필요한 확인도 해당 문제와 직접 연관된 경로로 한정하면 된다. 우선 한 가지 빌드 구성으로 시작 → K 씬 이동 → 첫 프레임 표시, 회복 취소/아래 공격, 투사체 삭제, Dark Tentacle 종료, 저FPS 애니메이션, 창 크기 변경을 확인하는 것이 유효하다. 이번 조사 중에는 이 검증을 실행하지 않았다.
