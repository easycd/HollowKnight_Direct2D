# HollowKnight_Direct2D

**C++과 Direct3D 11로 제작한 Hollow Knight 모작 프로젝트입니다.**

플레이어의 이동·점프·대시·공격·회복 동작과 Grimm, Pure Vessel의 보스 패턴을 구성하고, 이를 구동하는 객체·컴포넌트·씬·렌더링 시스템을 직접 구현했습니다. 게임 코드와 엔진 코드를 분리하고, 스프라이트 애니메이션과 HLSL 셰이더를 통해 캐릭터·배경·이펙트를 표현합니다.

## 기술 스택

| 구분 | 사용 기술 |
|---|---|
| 언어 | C++20, HLSL |
| 개발 환경 | Visual Studio 2022, MSVC v143, Windows SDK |
| 윈도우 및 입력 | Win32 API, `GetAsyncKeyState` |
| 렌더링 | Direct3D 11, DXGI |
| 수학 | DirectXMath와 SimpleMath 기반 벡터·행렬·쿼터니언 |
| 텍스처 | DirectXTex |
| 오디오 | FMOD Studio / Core API |
| 자원 관리 | `std::shared_ptr`, `std::unique_ptr`, WRL `ComPtr` |

저장소 이름은 `HollowKnight_Direct2D`이며, 현재 소스의 그래픽 API는 **Direct3D 11**입니다.

## 주요 구성

- **플레이어 동작:** 이동, 점프, 더블 점프, 낙하, 대시, 방향별 공격, FireBall 스킬, Focus 회복.
- **보스 패턴:** Grimm과 Pure Vessel의 상태별 동작, 애니메이션 전이, 공격 오브젝트 생성.
- **스프라이트 표현:** 텍스처 아틀라스, 프레임별 UV, 애니메이션 이벤트, 방향별 이미지.
- **씬 구성:** 타이틀, Dirtmouth, Grimm 전장, Godhome, Pure Vessel 전장.
- **엔진 시스템:** 컴포넌트 기반 객체, 레이어, 씬 관리, 충돌 이벤트, Rigidbody, 입력과 시간 관리.
- **렌더링 시스템:** 카메라, 렌더링 모드별 분류, Z 정렬, 조명, 상수 버퍼와 구조화 버퍼.
- **UI 및 연출:** 체력 아이콘, HUD, Soul 이미지, 이동·공격·회복 이펙트, 보스 등장 연출.
- **개발용 도구:** 그리드와 Collider 디버그 메시, 컴퓨트 셰이더 실험 장면.

## 프로젝트 구조

```text
HollowKnight_Direct2D/
├── Client.sln                 # Visual Studio 솔루션
├── Editer_Window/             # 실행 프로젝트 및 Win32 진입점
├── Engine_SOURCE/             # 엔진 공통 코드
├── GameEngine/                # 게임 객체, 씬, 보스, UI, 이펙트
├── Editer_SOURCE/             # 그리드 및 충돌 디버그 도구
├── Shader_SOURCE/             # HLSL 셰이더
├── Resources/                 # 이미지 및 오디오 자산
├── External/                  # 외부 SDK 헤더와 라이브러리 구성
├── DLL/                       # 런타임 DLL
└── 메모장/                    # 개발 메모 및 코드 기록
```

### 솔루션 구성

| 프로젝트 | 형식 | 역할 |
|---|---|---|
| `Editer_Window` | 실행 파일 | 윈도우 생성, 게임 루프, 엔진 초기화, 디버그 렌더링 호출 |
| `GameEngine` | 정적 라이브러리 | 공통 엔진과 게임 콘텐츠를 컴파일하여 실행 프로젝트에 제공 |
| `Engine_SOURCE` | 공유 프로젝트 | 게임 객체와 엔진 시스템 구현 |
| `Editer_SOURCE` | 공유 프로젝트 | 개발용 디버그 객체와 렌더링 구현 |
| `Shader_SOURCE` | 공유 프로젝트 | 렌더링에 사용하는 셰이더 소스 구성 |

## 실행 흐름

프로그램의 진입점은 `Editer_Window/main.cpp`의 `wWinMain`입니다. 윈도우를 생성한 뒤 Application, 씬, 디버그 도구를 초기화하고 메시지 루프에서 게임 프레임을 실행합니다.

```text
wWinMain
  └─ InitInstance
      ├─ Application::SetWindow
      ├─ Application::Initialize
      ├─ InitializeScenes
      └─ Editor::Initialize

메시지 루프
  ├─ Win32 메시지 처리
  └─ 게임 프레임
      ├─ Application::Run
      │   ├─ Update
      │   ├─ LateUpdate
      │   ├─ Render
      │   └─ Destroy
      ├─ Editor::Run
      └─ Application::Present
```

| 단계 | 처리 내용 |
|---|---|
| `Update` | 시간·입력 갱신, 충돌 검사, 활성 씬의 객체와 게임 로직 갱신 |
| `LateUpdate` | 월드 행렬과 카메라 행렬 갱신, 카메라·조명 등록, 디버그 메시 수집 |
| `Render` | 렌더 타깃 초기화, 조명 바인딩, 카메라별 객체 렌더링 |
| `Destroy` | 삭제 대상으로 표시된 객체를 레이어에서 제거하고 메모리 해제 |
| `Editor::Run` | 개발용 그리드와 충돌 디버그 메시 렌더링 |
| `Present` | DXGI Swap Chain을 통해 화면 출력 |

## 엔진 설계

### 객체와 컴포넌트

`GameObject`는 객체 상태와 컴포넌트·스크립트 목록을 관리합니다. 기본 Transform을 가지며, 템플릿 함수로 필요한 컴포넌트를 부착하거나 조회합니다.

| 클래스 | 역할 |
|---|---|
| `Entity` | 이름과 ID 관리 |
| `GameObject` | 객체 생명주기, 활성 상태, 컴포넌트와 스크립트 관리 |
| `Component` | 소유 객체와 컴포넌트 종류, 공통 생명주기 인터페이스 |
| `Script` | 객체의 동작과 충돌 이벤트를 구현하는 스크립트 기반 클래스 |
| `Transform` | 위치·회전·크기, 부모 Transform, 월드 행렬 관리 |
| `MeshRenderer` | 메시·머티리얼·애니메이션을 연결하여 렌더링 |
| `Animator` | 애니메이션 생성·선택·재생과 이벤트 관리 |
| `Collider2D` | 충돌 크기·중심 설정, 충돌 이벤트 전달, 디버그 메시 생성 |
| `Rigidbody` | 힘·질량·속도·중력·마찰 및 지면 상태 처리 |
| `Camera` | 뷰·투영 행렬, 레이어 마스크, 렌더링 대상 관리 |
| `Light` | 조명 종류·색상·위치·방향·반경 관리 |
| `AudioSource` / `AudioListener` | 사운드 재생과 공간 오디오 속성 설정 |

`AddComponent<T>()`, `GetComponent<T>()`, `GetComponents<T>()`를 사용해 객체 기능을 조합합니다. 객체는 `Active`, `Paused`, `Dead` 상태로 관리됩니다.

### 씬과 레이어

`SceneManager`는 이름을 키로 씬을 등록하고 활성 씬을 전환합니다. 각 씬은 여러 Layer를 가지며, Layer가 객체 목록과 업데이트·삭제를 관리합니다.

| 레이어 | 주요 용도 |
|---|---|
| `Ground`, `Wall` | 지면과 벽 |
| `Player`, `Skill`, `Effect` | 플레이어, 스킬, 이펙트 |
| `Monster`, `Boss`, `BossObj` | 적, 보스, 보스 공격 오브젝트 |
| `Npc` | NPC와 관중 |
| `Camera`, `Light` | 카메라와 조명 |
| `UI`, `BG`, `Grid` | UI, 배경, 개발용 그리드 |

`object::Instantiate<T>()`가 객체를 생성하고 씬 레이어에 등록합니다. `object::Destroy()`는 객체를 삭제 대상으로 표시하고, 프레임의 삭제 단계에서 Layer가 정리합니다.

### 충돌과 물리

`CollisionManager`는 레이어 간 충돌 허용 정보를 비트 행렬로 관리합니다. 충돌 대상의 사각형을 Transform 행렬로 변환하고, 축 투영을 이용해 교차 여부를 계산합니다.

Collider ID 쌍의 이전 충돌 상태를 보관하여 `OnCollisionEnter`, `OnCollisionStay`, `OnCollisionExit`를 전달합니다. 이벤트는 객체와 부착된 Script에서 처리할 수 있습니다.

`Rigidbody`는 누적 힘과 질량으로 가속도를 계산하고, Delta Time을 적용해 속도와 위치를 갱신합니다. `VectorR`와 `rigidmath`는 이동 방향, 정규화, 내적·외적 등의 2D 연산을 제공합니다.

### 입력과 시간

`Input`은 키 상태를 `Down`, `Pressed`, `Up`, `None`으로 관리하고 마우스의 클라이언트 좌표를 제공합니다. `Time`은 `QueryPerformanceCounter` 기반 Delta Time을 계산하며 윈도우 제목에 FPS를 표시합니다.

## 렌더링과 애니메이션

### Direct3D 11 렌더링

`GraphicDevice_Dx11`이 Device, Device Context, Swap Chain, 렌더 타깃, 깊이 버퍼와 Viewport를 관리합니다. 캐릭터와 배경은 사각형 메시 위에 텍스처를 표시하는 방식으로 구성합니다.

`Camera`는 레이어 마스크로 렌더링 대상을 선택하고 `Opaque`, `CutOut`, `Transparent` 모드로 분류합니다. CutOut과 Transparent 객체는 Z 위치를 기준으로 정렬합니다.

| 자원 | 역할 |
|---|---|
| `Mesh` | 정점·인덱스 버퍼와 DrawIndexed 호출 |
| `Texture` | 이미지 로딩, 텍스처와 GPU 뷰, 셰이더 리소스 바인딩 |
| `Material` | 셰이더·텍스처·렌더링 모드 조합 |
| `Shader` | 셰이더 컴파일과 그래픽 파이프라인 상태 바인딩 |
| `ConstantBuffer` | Transform, Grid, Animator 등의 데이터 전달 |
| `StructedBuffer` | 조명 속성 배열 전달 |
| `ComputeShader` / `PaintShader` | UAV 텍스처를 대상으로 컴퓨트 작업 실행 |

### 셰이더 구성

| 셰이더 | 용도 |
|---|---|
| `TriangleVS/PS` | 기본 메시와 텍스처 렌더링 |
| `SpriteVS/PS` | 스프라이트와 2D 조명 표현 |
| `SpriteAnimationVS/PS` | 아틀라스 UV 기반 애니메이션과 조명 표현 |
| `GridVS/PS` | 카메라와 해상도 정보에 따른 개발용 그리드 |
| `DebugVS/PS` | 충돌 영역 디버그 렌더링 |
| `PaintCS` | 텍스처에 색상을 기록하는 컴퓨트 셰이더 |
| `globals.hlsli` | 공통 상수 버퍼, 텍스처, 샘플러와 조명 계산 |

### 스프라이트 애니메이션

`Animation`은 아틀라스의 시작 위치, 프레임 크기, 프레임 수, 오프셋, 재생 시간을 저장합니다. 프레임 정보를 정규화된 UV로 변환해 셰이더에 전달합니다.

`Animator`는 이름별 애니메이션과 `StartEvent`, `CompleteEvent`, `EndEvent`를 관리합니다. 게임 코드는 완료 이벤트에 상태 전이와 이펙트 삭제 함수를 연결하여 연출을 구성합니다.

## 게임 콘텐츠

### 플레이어

`kmPlayer`는 상태별 함수로 입력과 동작을 처리합니다. 좌우 방향에 따라 서로 다른 스프라이트를 재생하고 Rigidbody 속도와 이펙트 생성을 제어합니다.

| 동작 | 관련 구성 |
|---|---|
| 대기·이동·낙하 | Idle, Move, Fall 상태와 방향별 애니메이션 |
| 점프·더블 점프 | Jump, DoubleJump 상태, 점프 사운드와 DoubleJump_Effect |
| 대시 | Dash 상태와 DsahEffect |
| 기본·위·아래 공격 | Attack, UpAttack, DownAttack 상태와 PlayerEffet |
| FireBall 스킬 | 시전 애니메이션, FireBallSkill 투사체, FireBallSkill_Effect |
| Focus 회복 | 시작·반복·회복·종료 상태, Focus_Effect와 Focus_On_Effect |

### Grimm

`kmGrimm`은 순간이동과 패턴별 상태를 조합하여 보스 동작을 구성합니다.

| 패턴 | 상태·연출 구성 |
|---|---|
| Air Dash | 등장 → 공중 돌진 → 착지 → 지상 공격 → 정지 |
| Balloon | 등장 → 팽창 → 반복 상태와 FireBall 생성 |
| Cap Spike | 등장 → 준비 → 가시 생성 → 종료 |
| Cast | 등장 → 시전 → FlameBat 순차 생성 |
| Slash | 등장 → 준비 → 돌진 공격 → 상단 공격 → 순간이동 |

관련 오브젝트에는 `Spike_Object`, `FlameBat`, `FIreBall`이 있습니다. `Girmm_Hand`는 손 등장·클릭·퇴장 애니메이션을 연결하며, `TrumpNpc`와 `Crowd`가 전장 주변 연출을 구성합니다.

### Pure Vessel

`kmPureVessel`은 단계별 인트로와 방향별 전투 애니메이션을 관리합니다. 상태 정의에는 Counter, Dash, Knife Spike, Slash, Knife Spread, Groggy, Roar, Dark Tentacle과 순간이동이 포함됩니다.

| 구성 | 관련 오브젝트·연출 |
|---|---|
| 인트로 | Idle부터 여러 등장 단계와 종료 단계, BGM 재생 |
| Dash | 등장·준비·돌진·종료 애니메이션 |
| Knife Spike | 공중 등장과 하강, Spike 배치 |
| Slash | 여러 단계의 연속 베기와 단계별 사운드 |
| Knife Spread | 시전 단계와 GuidLight 가이드 연출 |
| Roar | 준비·집중·폭발·대기, LightCircleobj_Guid와 LightCircle |
| Dark Tentacle | 등장·시전·반복·종료, DarkWhip와 Dark_Tentacle_Effect |

### UI와 오디오

`PlayerUI`는 HUD, `PlayerHP`는 개별 체력 아이콘, `PlayerHP_State`는 아이콘 상태 전환을 담당합니다. 체력 아이콘에는 Idle, Empty, Break, Refill 애니메이션이 있습니다. `SoulGauge`는 Soul 이미지를 표시합니다.

FMOD 기반 `AudioClip`과 `AudioSource`를 통해 플레이어 이동·점프·착지·대시·공격 사운드, Pure Vessel의 패턴 사운드와 BGM을 구성합니다. `AudioListener`는 카메라 객체에 부착하여 리스너 위치와 방향을 전달합니다.

## 씬 이동과 조작법

시작 씬은 `TitleScene`입니다. **K 키**를 눌러 다음 순서로 장면을 이동합니다.

```text
TitleScene → Dirtmouth → Boss_Grimm_Stage → Godhome → Boss_PureVessel_Stage
```

| 키 | 동작 |
|---|---|
| `←` / `→` | 좌우 이동 |
| `Z` | 점프 / 공중에서 더블 점프 |
| `Left Shift` | 대시 |
| `X` | 기본 공격 |
| `↑` + `X` | 위 공격 |
| `↓` + `X` | 아래 공격 |
| `C` | FireBall 스킬 |
| `A` | Focus 회복 |
| `K` | 다음 씬 이동 |
| `Q` | 대기 상태에서 체력 감소용 디버그 입력 |

입력은 플레이어의 현재 상태에 따라 처리됩니다.

`PlayScene`에는 기본 메시, 아틀라스 애니메이션, 조명, 충돌과 PaintCS를 살펴볼 수 있는 실험용 구성이 포함되어 있습니다.

## 개발 환경 구성

1. Windows에서 Visual Studio 2022의 **C++를 사용한 데스크톱 개발** 워크로드와 Windows SDK를 준비합니다.
2. `Client.sln`을 엽니다.
3. DirectXTex와 FMOD의 헤더·링크 라이브러리 및 런타임 DLL을 준비합니다. 외부 라이브러리의 아키텍처는 빌드 플랫폼과 맞춥니다.
4. `Editer_Window`를 시작 프로젝트로 지정하고 `Debug / x64` 구성을 선택합니다.
5. 디버깅 작업 디렉터리를 `$(ProjectDir)`로 지정합니다. 자산은 `..\Resources`, 셰이더는 작업 디렉터리의 상위 폴더에 있는 `Shader_SOURCE`를 기준으로 참조합니다.
6. 솔루션을 빌드하고 실행합니다.

| 의존성 | 코드에서 참조하는 구성 |
|---|---|
| DirectXTex | `External/DirectXTex/Include`, `External/DirectXTex/Lib` |
| FMOD | `External/Fmod/Include`, `External/Fmod/Library` |
| 런타임 DLL | `External`, `DLL` |
| 게임 자산 | `Resources` |
| 셰이더 소스 | `Shader_SOURCE` |

## 코드 탐색 가이드

| 살펴볼 내용 | 시작 파일 |
|---|---|
| 프로그램 시작과 프레임 호출 | `Editer_Window/main.cpp`, `Engine_SOURCE/kmApplication.cpp` |
| 객체·컴포넌트 구조 | `Engine_SOURCE/kmGameObject.h`, `Engine_SOURCE/kmComponent.h` |
| 씬 초기화와 전환 | `GameEngine/LoadScene.h`, `Engine_SOURCE/kmSceneManager.cpp` |
| 객체 생성과 삭제 | `Engine_SOURCE/kmObject.h`, `Engine_SOURCE/kmLayer.cpp` |
| 충돌 판정 | `Engine_SOURCE/kmCollisionManager.cpp`, `Engine_SOURCE/kmCollider2D.cpp` |
| 물리 이동 | `Engine_SOURCE/kmRigidbody.cpp`, `Engine_SOURCE/kmRigidbodyMath.h` |
| 그래픽 장치와 자원 초기화 | `Engine_SOURCE/kmGraphicDevice_Dx11.cpp`, `Engine_SOURCE/kmRenderer.cpp` |
| 카메라와 추적 | `Engine_SOURCE/kmCamera.cpp`, `Engine_SOURCE/kmCameraScript.cpp` |
| 애니메이션과 이벤트 | `Engine_SOURCE/kmAnimation.cpp`, `Engine_SOURCE/kmAnimator.cpp` |
| 플레이어 동작 | `GameEngine/kmPlayer.cpp` |
| Grimm 패턴 | `GameEngine/kmGrimm.cpp`, `GameEngine/kmBoss_Grimm_Stage.cpp` |
| Pure Vessel 패턴 | `GameEngine/kmPureVessel.cpp`, `GameEngine/Boss_PureVessel_Stage.cpp` |
| UI | `GameEngine/kmPlayerUI.cpp`, `GameEngine/kmPlayerHP_State.cpp` |
| 사운드 | `Engine_SOURCE/kmFmod.cpp`, `Engine_SOURCE/kmAudioSource.cpp` |
| 디버그 렌더링 | `Editer_SOURCE/guiEditor.cpp`, `GameEngine/kmGridScript.cpp` |

## 원작 및 외부 라이브러리

Hollow Knight를 바탕으로 제작한 학습·포트폴리오용 모작 프로젝트입니다. 원작 캐릭터·이미지·음원의 권리는 해당 권리자에게 있으며, 외부 라이브러리는 각 제공자의 라이선스를 따릅니다.

## 수정 예정 사항

코드 조사에서 확인한 아래 항목은 **수정 예정**입니다. 소스 분석을 기준으로 정리했으며, 실행 재현과 수정 후 확인은 각 작업에서 진행합니다.

### 빌드 및 실행 환경

- [ ] FMOD와 DirectXTex 링크 라이브러리 구성 및 의존성 준비 절차 정리.
- [ ] Debug/Release, x64/Win32별 include·링크·PCH·DLL 복사 설정 정리.
- [ ] 실행 위치에 의존하는 자산 경로를 명시적인 자산 루트 기준으로 변경.
- [ ] 누락된 HUD 이미지 로드 경로 정리.

### 초기화 및 메모리 관리

- [ ] Transform 부모 포인터와 Animator 활성 애니메이션 포인터 초기화.
- [ ] Player 시작 상태와 Pure Vessel의 첫 Idle 방향 초기화.
- [ ] 텍스처가 없는 머티리얼의 자원 정리 처리 개선.
- [ ] Grid 상수 버퍼 생성 크기와 업로드 데이터 크기 일치.
- [ ] Dark Tentacle 종료 중 삭제된 이펙트 재참조 방지.
- [ ] 재생 전 오디오 채널 접근 방지 및 채널 유효성 확인.
- [ ] 리소스 로드·셰이더 컴파일·그래픽 장치 생성·GPU 버퍼 Map 실패 처리 정리.
- [ ] Ground/Wall 초기화와 디버그 객체의 컴포넌트 중복 부착 제거.

### 충돌 및 물리

- [ ] Collider 중심 오프셋을 실제 충돌 판정에 반영.
- [ ] 충돌 검사와 Transform 갱신 순서를 정리하여 같은 시점의 좌표와 축 사용.
- [ ] 충돌 설정 초기화 시 전체 레이어 행렬을 초기화하고 씬별 설정 관리.
- [ ] 비활성화·삭제되는 객체의 충돌 종료 이벤트와 충돌 이력 정리.
- [ ] Rigidbody 질량 기본값과 속도 제한 적용, VectorR 비교 연산 정리.

### 플레이어 및 UI

- [ ] 아래 공격과 Focus 회복의 상태 전이 및 회복 취소 입력 수정.
- [ ] 공중 공격·스킬 상태가 공통 Fall 처리로 덮어써지는 흐름 정리.
- [ ] HP 범위 제한과 마지막 체력 아이콘의 회복 표시 처리.
- [ ] HP 아이콘의 중복 Update 호출 제거 및 체력 변화에 따른 UI 동기화.
- [ ] 오른쪽 위·아래 공격 이펙트가 오른쪽 애니메이션을 재생하도록 수정.
- [ ] 플레이어 FireBall 투사체의 수명과 삭제 조건 추가.
- [ ] 착지 기준 더블 점프 횟수 관리.

### 보스 및 전투 기능

- [ ] Grimm Spike 대기 타이머 초기화.
- [ ] 고정된 보스 패턴 선택을 패턴 선택·페이즈 전환 로직으로 연결.
- [ ] Pure Vessel Counter의 Cast → Loop → End 전이 연결.
- [ ] Grimm Balloon 탄막의 이동 분기와 Pure Vessel Knife Spread 발사 오브젝트 연결.
- [ ] 플레이어·보스 피해, 타격 레이어, 보스 HP와 승리 처리 구현.
- [ ] 플레이어 사망·리스폰과 Soul 증감 및 스킬·회복 비용 연결.
- [ ] 보스 가이드 오브젝트의 중복 호출과 시간 설정 정리.

### 애니메이션·오디오·렌더링

- [ ] 낮은 FPS에서도 애니메이션이 경과 시간을 유지하도록 프레임 진행 방식 개선.
- [ ] 일회성 애니메이션의 완료 이벤트를 반복 여부와 독립적으로 처리.
- [ ] 서로 다른 이미지가 같은 리소스 키를 사용하는 부분 수정.
- [ ] FMOD 프레임 업데이트 연결 및 AudioSource별 재생 채널 관리.
- [ ] 공간 오디오에 실제 속도 전달 및 오디오 자원 해제 정책 정리.
- [ ] 조명 버퍼 증설 직후 데이터 업로드와 실제 조명 개수 전달 처리.
- [ ] 씬 전환 시 디버그 카메라 참조 갱신 및 UI 카메라 레이어 마스크 정리.
- [ ] 창 크기 변경에 따른 백버퍼·깊이 버퍼 재생성과 최소화 처리.
- [ ] 충돌 디버그 색상용 상수 버퍼 연결.
- [ ] UI와 카메라 갱신 시점 및 2D 보스 회전 계산 정리.

### 코드 구조 정리

- [ ] 객체 검색 템플릿의 Layer 순회 타입과 헤더의 타입 선언·include 의존성 정리.
- [ ] 버퍼 생성 함수의 반환값과 씬 생성·종료 시 자원 정리 방식 개선.
- [ ] 동일 레이어 순회 중 객체 생성에 대응할 수 있도록 등록 시점 관리.
- [ ] 반복되는 리소스 등록·패턴·오브젝트 배치를 데이터 중심으로 정리.
- [ ] 구형 스크립트와 사용 중인 객체 구현의 역할 정리.

수정은 **빌드 환경 → 초기화·메모리 → 충돌·상태 전이 → 전투 기능 → 연출·코드 정리** 순서로 진행할 예정입니다.
