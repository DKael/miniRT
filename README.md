# miniRT

## 1️⃣ 프로젝트 소개

miniRT는 C 언어 기반의 간단한 레이 트레이서(Ray Tracer) 구현 프로젝트입니다. 광선–도형 교차 연산을 통해 3D 장면을 렌더링하며, 그래픽스 수학과 조명 모델을 실제 코드로 옮기는 것을 목표로 합니다. 기본 요구사항 외에 보너스 과제에서 Phong reflection model의 완성, Checkerboard 패턴, 멀티 라이트, 추가 곡면 객체, Bump map 등을 구현했고, 개인적으로 성능 최적화를 위해 멀티스레드 렌더링과 Supersampling Anti-Aliasing 기능도 추가했습니다.

---

## 2️⃣ 과제 목표
	•	광선 추적 기반 렌더링 엔진 직접 구현
	•	3D 기하 연산(벡터/행렬) 및 광학 모델 이해
	•	MLX 기반 윈도우 및 이미지 출력
	•	보너스 기능 구현을 통한 그래픽스 확장 학습

---

## 3️⃣ 구현 사항

### 기본 구현
	•	Sphere, Plane, Cylinder 등 1차·2차 객체 교차 판정
	•	카메라 FOV와 시점 기반 광선 생성
	•	Ambient + Diffuse 조명 모델
	•	Shadow ray 를 통한 그림자 판정
	•	PPM / MiniLibX 기반 결과 출력

### 보너스 구현
	•	Specular reflection: 하이라이트 반사 계산 → Phong 모델 완성
	•	Checkerboard: 색상 교란 패턴 텍스처 적용
	•	Colored & Multi-spot lights: 다양한 색/위치의 광원 지원
	•	추가 2차 객체: Cone, Hyperboloid, Paraboloid 등 지원
	•	Bump map: 표면의 요철감을 시뮬레이션해 사실적 질감 구현

###  자율 확장 구현
	•	멀티스레드 렌더링: pthread 기반 병렬 처리로 렌더링 속도 대폭 향상
	•	Supersampling Anti-Aliasing (SSAA): 픽셀 단위 다중 샘플링 평균화로 계단현상 최소화

---

## 4️⃣ 배운 점
* 광선-도형 교차 판정 알고리즘 구현 경험
	- Ray-Sphere, Ray-Plane, Ray-Cylinder, Ray-Cone, Ray-Paraboloid 등 방정식을 직접 세우고 판별식을 계산하며 교차 여부를 판정한 경험. 수학적 해석(이차방정식 판별식, 교차점 선택 기준 등)을 코드로 옮기는 과정을 통해 기하학적 문제를 프로그래밍적 사고로 해결하는 능력 강화.
* 벡터/행렬 연산 및 기하학 수학 감각 강화
	- 벡터 내적/외적을 통한 법선 벡터 계산, 정규화(normalization), 행렬 변환을 통한 카메라 방향 제어 등을 반복 구현. 이 과정을 통해 그래픽스 프로그래밍에서 수학 연산이 직관적 도구로 작동한다는 점을 체득.
* Phong reflection model을 통한 조명 효과 이해
	- Ambient, Diffuse, Specular 세 성분의 조합으로 현실적인 광원 효과를 재현. Specular 하이라이트의 지수(shininess coefficient)가 재질 표현에 끼치는 영향을 실습으로 확인하면서, 조명 모델링의 기본 원리를 이해.
* Shadow ray 기반 광원 차폐 판정 로직 습득
	- 객체 표면에서 광원 방향으로 2차 광선을 쏘아, 도달 전에 다른 객체와 교차하는지를 판별. 이 과정에서 self-shadow(자기 그림자) 문제와 epsilon 보정(0.0001 오프셋 적용)의 필요성을 학습.
* Checkerboard 텍스처 매핑과 패턴 계산 경험
	- 좌표계를 정수 그리드 단위로 분할하고, 홀수/짝수 구역에 따라 색상을 교차 적용. 단순한 텍스처라도 UV 좌표계와 패턴 매핑 원리를 구현하는 훈련이 됨.
* 다중 광원 조합과 색상 계산 처리 로직 설계
	- 여러 개의 라이트 소스에 대해 독립적으로 조명 연산을 수행하고 합산. 각각의 색상 성분(RGB)을 개별적으로 계산해 누적하는 로직을 작성하며, 색상 클램핑(255 제한)과 가중치 합성의 중요성을 실습.
* Cone/Hyperboloid 등 2차 곡면 방정식 교차 판정 구현 능력
	- 단순 구/평면을 넘어 복잡한 곡면의 수학적 정의를 코드로 옮기며, 방정식 해석 능력 강화. 해를 선택할 때 카메라 방향성·표면 노멀 계산이 함께 고려되어야 한다는 점을 학습.
* Bump map을 통한 노멀 벡터 변형 기법 이해
	- 픽셀 단위 텍스처 정보를 샘플링해 표면 노멀 벡터를 변형하여 요철 효과를 구현. 실제 기하 구조를 바꾸지 않고도 질감 표현을 가능하게 하는 기법을 체득.
* 멀티스레드 프로그래밍(pthread)과 workload 분할 경험
	- 이미지 영역을 여러 스레드에 나누어 병렬로 렌더링. Thread-safe한 메모리 접근 관리, race condition 방지, 작업 단위 분할 전략의 중요성을 체감. 이를 통해 CPU 멀티코어 활용 효율성 학습.
* Supersampling Anti-Aliasing 적용으로 화질 개선 및 성능/품질 트레이드오프 체험
	- 한 픽셀을 다중 샘플링 후 평균 색상으로 출력하여 계단 현상을 완화. 화질 향상과 계산량 증가라는 trade-off를 직접 경험하며, 그래픽스 최적화의 현실적인 고려 요소 학습.
* 그래픽스 엔진 개발에서 성능 최적화와 시각 품질의 균형 중요성 인식
	- 단순히 “돌아가는 프로그램”이 아니라, 속도·메모리·품질을 균형 있게 설계해야 실제 사용 가능한 엔진이 된다는 점을 체득. 특히, 멀티스레딩과 안티에일리어싱을 동시에 적용하면서 성능·품질 균형의 구체적 사례 경험.

---

## 5️⃣ 사용 방법
bash
```
# 1. 프로젝트 빌드
make        # 기본 빌드
make bonus  # 보너스 기능 포함 빌드

# 2. 실행
./miniRT scenes/test11.rt
./miniRT scenes/test10.rt
```
* .rt 파일을 입력으로 받아 장면(Scene)을 구성
* 장면 파일(scene.rt)에서 해상도, 광원, 카메라, 객체 등을 설정 가능

---

## 6️⃣ 렌더링 예시 사진

<img width="1392" height="1164" alt="스크린샷 2025-09-10 오후 5 58 10" src="https://github.com/user-attachments/assets/09494ea2-d4fc-47ee-ae28-779a9b2631ae" />

<img width="1392" height="1164" alt="스크린샷 2025-09-10 오후 5 59 50" src="https://github.com/user-attachments/assets/a92d4ca5-f249-4969-9dee-c6ecea98aa73" />

<img width="1392" height="1164" alt="스크린샷 2025-09-10 오후 5 58 21" src="https://github.com/user-attachments/assets/8216a325-18c8-4e86-859e-7328c429ed3d" />

<img width="1392" height="1164" alt="스크린샷 2025-09-10 오후 5 59 38" src="https://github.com/user-attachments/assets/bb332b8b-8b25-4ac5-8b09-f081cf4554dc" />

<img width="1392" height="1164" alt="스크린샷 2025-09-10 오후 5 59 12" src="https://github.com/user-attachments/assets/e16c4827-5ea8-4144-be6a-161fa0111a77" />

<img width="1392" height="1164" alt="스크린샷 2025-09-10 오후 5 59 03" src="https://github.com/user-attachments/assets/675588ed-3939-4efb-9b0a-be1a4dd0fa1b" />

<img width="1392" height="1164" alt="스크린샷 2025-09-10 오후 5 58 52" src="https://github.com/user-attachments/assets/0d60beb6-a10f-4cfe-9cb7-566ae48fa36a" />

<img width="1392" height="1164" alt="스크린샷 2025-09-10 오후 5 59 30" src="https://github.com/user-attachments/assets/87f06231-85f0-45a9-bd57-a6101e42d136" />

<img width="1392" height="1164" alt="스크린샷 2025-09-10 오후 5 58 40" src="https://github.com/user-attachments/assets/8bab7827-88c5-4d91-8916-fdda9a7e6d3e" />


---

## 7️⃣ 기술 스택
	•	언어: C
	•	운영체제/환경: Unix/Linux
	•	빌드 도구: GNU Make
	•	버전관리 도구: Git
	•	Coding Conventions: Norminette
	•	그래픽스 라이브러리: minilibx (X11 기반)
	•	수학/알고리즘: 벡터·행렬 연산, 광선–도형 교차, Phong 모델
