
# LLVM/Clang Demo Project

- > [English README](README.md)

- 본 프로젝트는 **`LLVM`/`Clang` 기반 `C++` 컴파일 환경**, **`VSCode` 개발 설정**, **`C++20~26` 최신 기능을 활용한 예제 코드** 를 포함한 최소/완성형 템플릿입니다.
- `Windows`·`Linux` 에서 공통적으로 동일한 구조로 사용하도록 설계되었습니다.

<br />

---

## 1. 프로젝트 구성 개요

- 이 프로젝트는 다음을 포함합니다:
   - **`CMake` 기반 빌드 시스템**
   - **`clang` / `clang++` 강제 사용 설정**
   - **`C++26` 컴파일 활성화**
   - **`LLD` 링크 사용(`-fuse-ld=lld`)**
   - **`VSCode` 개발 환경 설정 (`IntelliSense`, `clangd`, `LLDB DAP`)**
   - **`C++20`/`23`/`26` 기능을 사용한 예제 코드(`main.cpp`)**

<br />

---

## 2. 주요 파일 설명

### 2.1 `CMakeLists.txt`

- `LLVM_HOME` 환경 변수를 우선 적용
   - `Windows` 환경에서 자동으로 `C:/llvm-package` 사용
- `clang`, `clang++`을 강제 `CMAKE_C_COMPILER` / `CMAKE_CXX_COMPILER`로 설정
- `LLD` 링크 사용 (`-fuse-ld=lld`)
- `C++26` 컴파일 활성화 (`target_compile_features(... cxx_std_26)`)
- `compile_commands.json` 자동 생성

<br />

➡ **VSCode + clangd 사용자의 기본 구조로 매우 이상적입니다.**

<br />

---

### 2.2 예제 (`main.cpp`)

* `C++20` `ranges` / `views` / `std::format`
* `C++23` `std::expected`
* `C++26` `deducing this` 문법 적용 (`Point::move`)
* 고급 예제 포함(필터링·변환·`join view`·구조화된 메시지 생성 등)

<br />

- 이 파일 하나만으로 **`C++20~26` 기능의 실제 실행 예제** 를 모두 확인할 수 있습니다.

<br />

---

### 2.3 `VSCode` 설정 파일

#### 2.3.1 `c_cpp_properties.json`

- `IntelliSense` 엔진을 `clang` 기반으로 설정
- `compile_commands.json`을 자동 참고
- `includePath` 기본 설정

#### 2.3.2 extensions.json

- 다음 확장 자동 추천
   - `ms-vscode.cmake-tools`
   - `ms-vscode.cpptools`
   - `llvm-vs-code-extensions.vscode-clangd`

#### 2.3.3 `launch.json`

- **`LLDB-DAP` 기반 디버깅 설정**
- `OS`별 실행 파일 자동 분기 (`Windows`는 `hello.exe`)

#### 2.3.4 `settings.json`

- `CMake generator = Ninja`
- `clang++`를 `IntelliSense` 기본 컴파일러로 설정
- `editor.formatOnSave` 옵션

#### 2.3.5 `tasks.json`

- `CMake Configure`
- `CMake Build`
- `VSCode` 빌드 자동화 구성

<br />

---

## 3. 빌드 및 실행 방법

### 3.1 `Windows` / `Linux` 공통

```bash
cmake -S . -B build -G Ninja
cmake --build build --config Debug
```

### 3.2 실행

#### `Linux`

```bash
./build/hello
```

#### Windows

```powershell
.\build\hello.exe
```

<br />

---

## 4. 디버깅 (`VSCode`)

- (1) **확장 설치**
   - `ms-vscode.cmake-tools`
   - `llvm-vs-code-extensions.vscode-clangd`
   - `llvm-vs-code-extensions.lldb-dap`

- (2) `VSCode` 왼쪽 실행/디버그 메뉴 → **Debug (lldb-dap)** 실행

<br />

---

## 5. `C++` 예제 코드 특징

* **C++20 / C++23 / C++26 주요 신기능 실제 실행 가능**
* `ranges`, `views`, `format`, `expected` 모두 포함
* "`deducing this`" 문법을 사용한 연산자 체이닝 스타일 사용
* 예제 메시지를 스트링으로 조립하여 `main`에서 출력

<br />

---

## 6. 프로젝트 구조

```
project_root/
│  CMakeLists.txt
│  main.cpp
│
├─ .vscode/
│   ├─ c_cpp_properties.json
│   ├─ extensions.json
│   ├─ launch.json
│   ├─ settings.json
│   └─ tasks.json
│
└─ build/ (cmake가 생성)
```

<br />

---

## 7. 이 템플릿의 사용처

- `LLVM`/`Clang` 개발 환경 테스트
- 최신 `C++` 표준(`C++20~C++26`) 실험
- `VSCode` + `clangd` + `LLDB` 기반 `C++` 프로젝트 기본 구조
- `CMake` 기반 멀티플랫폼 템플릿

<br />

---

## 8. 라이선스

- MIT

