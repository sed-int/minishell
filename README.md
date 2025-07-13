# 🐚 Minishell

**42 서울 과제 | 우리만의 작은 shell 만들기**

[![42Seoul](https://img.shields.io/badge/42-Seoul-black?style=flat-square&logo=42)](https://42seoul.kr)

---

## 🌟 주요 기능

Minishell은 Bash와 유사한 경험을 제공하는 간단한 셸입니다. 다음은 저희가 구현한 주요 기능들입니다.

-   **명령어 실행**: 시스템에 설치된 모든 프로그램을 실행할 수 있습니다.
-   **파이프 (`|`)**: 여러 명령어를 연결하여 한 명령어의 출력을 다른 명령어의 입력으로 전달합니다.
-   **리다이렉션 (`<`, `>`, `<<`, `>>`)**: 파일 디스크립터를 제어하여 입출력을 파일로 전환합니다.
-   **Here Document (`<<`)**: 사용자의 입력을 특정 문자열이 나올 때까지 읽어와 다른 명령어의 입력으로 사용합니다.
-   **환경 변수 확장 (`$VAR`)**: `$USER`와 같은 환경 변수를 실제 값으로 치환합니다. `$?`를 통해 이전 명령어의 종료 코드를 확인할 수 있습니다.
-   **따옴표 처리 (`'`, `"`):** 텍스트를 그룹화하고 특수 문자의 해석을 제어합니다.
-   **시그널 처리 (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)**: 인터럽트, 종료, 셸 종료 시그널을 적절히 처리합니다.
-   **내장 명령어**: 셸의 동작을 제어하는 자체 명령어를 포함합니다.

---

## 🛠️ 빌드 및 실행 방법

**현재 macOS만 지원합니다**

1.  **저장소 클론:**
    ```bash
    git clone https://github.com/your_username/minishell.git
    cd minishell
    ```
1. **의존성 설치**
    ```bash
    brew install readline
    ```
1.  **빌드:**
    `Makefile`을 사용하여 프로젝트를 컴파일합니다. `readline` 라이브러리가 필요할 수 있습니다.
    ```bash
    make
    ```

1.  **실행:**
    컴파일이 완료되면 `minishell` 실행 파일이 생성됩니다.
    ```bash
    ./minishell
    ```

---

## 🚀 사용 예시

```bash
# 기본적인 명령어
/bin/ls -l

# 파이프 사용
cat file1 | grep "hello" | wc -l

# 리다이렉션
echo "Hello World" > outfile.txt
cat < infile.txt

# Here Document
cat << EOF
hello
world
EOF

# 환경 변수
echo "Current user is $USER"
```

---

## 🔧 내장 명령어

| 명령어      | 설명                                       |
| :---------- | :----------------------------------------- |
| `echo`      | 주어진 텍스트를 출력합니다. (`-n` 옵션 지원) |
| `cd`        | 현재 작업 디렉토리를 변경합니다.           |
| `pwd`       | 현재 작업 디렉토리의 전체 경로를 출력합니다. |
| `export`    | 새로운 환경 변수를 추가하거나 기존 변수를 수정합니다. |
| `unset`     | 환경 변수를 제거합니다.                    |
| `env`       | 현재 설정된 모든 환경 변수를 출력합니다.   |
| `exit`      | Minishell을 종료합니다.                    |
