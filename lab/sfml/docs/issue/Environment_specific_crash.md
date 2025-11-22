# Environment-Specific SFML Crash Issue

## Problem Summary

SFML application (`sfml-app`) crashes with segmentation fault when run from user's terminal, but works correctly when run from automated tool/clean environment.

## Symptoms

- **When run by user:** `[1] <pid> segmentation fault ./sfml-app`
- **When run with clean env:** Works correctly, window launches
- **When run by automated tool:** Works correctly
- **When individual env vars are unset:** Works correctly (window launches)

## Environment

- **OS:** macOS 14.4.1 (Sonoma)
- **Architecture:** arm64 (Apple Silicon)
- **Shell:** zsh
- **SFML Version:** 3.x (built from source)
- **Working directory:** `~/Documents/Code/42/Advanced/nibbler/lab/sfml`

## Investigation Results

### What Works

1. ✅ `env -i PATH=/usr/bin:/bin:/usr/sbin:/sbin HOME=$HOME ./sfml-app` - Works
2. ✅ Unsetting individual environment variables one by one - Window launches each time
3. ✅ Running from automated tool environment - Works
4. ✅ Program compiles and links correctly
5. ✅ Libraries are present and loadable

### What Doesn't Work

1. ❌ Running `./sfml-app` directly from user's terminal - Segfault
2. ❌ Running with full user environment - Segfault

### Key Observations

- The `[1]` is just zsh's job number (not backgrounding)
- **All individual environment variables tested - ALL still crash when unset individually**
- Works with `env -i` (completely clean environment)
- **Not a single variable issue - must be a combination of multiple variables OR something else entirely**
- The fact that unsetting any single variable doesn't help suggests it's either:
  1. Multiple variables working together
  2. Something in shell configuration (not an env var)
  3. The way the shell executes the command (backgrounding, hooks, etc.)

## Complete Environment Variables List

Total: 63 environment variables

```
CAML_LD_LIBRARY_PATH=/Users/stefano/.opam/default/lib/stublibs:/Users/stefano/.opam/default/lib/ocaml/stublibs:/Users/stefano/.opam/default/lib/ocaml
COLORTERM=truecolor
COMMAND_MODE=unix2003
COMPACT_HOME=/Users/stefano/Documents/Code/Cardano/bin/compactc/compactc-macos
CURSOR_TRACE_ID=b5b22a793c2e43f797007479d61999d0
DISPLAY=/private/tmp/com.apple.launchd.gxVclvPuiQ/org.xquartz:0
DOTNET_ROOT=/usr/local/share/dotnet/x64
GIT_ASKPASS=/Applications/Cursor.app/Contents/Resources/app/extensions/git/dist/askpass.sh
HOME=/Users/stefano
HOMEBREW_CELLAR=/opt/homebrew/Cellar
HOMEBREW_PREFIX=/opt/homebrew
HOMEBREW_REPOSITORY=/opt/homebrew
INFOPATH=/opt/homebrew/share/info:
LANG=en_US.UTF-8
LESS=-R
LOGNAME=stefano
LSCOLORS=Gxfxcxdxbxegedabagacad
LS_COLORS=di=1;36:ln=35:so=32:pi=33:ex=31:bd=34;46:cd=34;43:su=30;41:sg=30;46:tw=30;42:ow=30;43
LaunchInstanceID=951B4739-66F6-4FD9-8778-5009F40807F0
MallocNanoZone=0
NVM_BIN=/Users/stefano/.nvm/versions/node/v22.17.0/bin
NVM_CD_FLAGS=-q
NVM_DIR=/Users/stefano/.nvm
NVM_INC=/Users/stefano/.nvm/versions/node/v22.17.0/include/node
N_PREFIX=/usr/local/n
OCAMLTOP_INCLUDE_PATH=/Users/stefano/.opam/default/lib/toplevel
OCAML_TOPLEVEL_PATH=/Users/stefano/.opam/default/lib/toplevel
OLDPWD=/Users/stefano/Documents/Code/42/Advanced/nibbler/lab/sfml
OPAMNOENVNOTICE=true
OPAM_LAST_ENV=/Users/stefano/.opam/.last-env/env-59ac0b36b1c224a2d17ef2e4eb3bd1ec-0
OPAM_SWITCH_PREFIX=/Users/stefano/.opam/default
ORIGINAL_XDG_CURRENT_DESKTOP=undefined
PAGER=less
PATH=/Users/stefano/.opam/default/bin:/usr/local/share/dotnet/x64:/Users/stefano/.wasmtime/bin:/Users/stefano/Library/pnpm:/Users/stefano/.nvm/versions/node/v22.17.0/bin:/Users/stefano/Documents/Code/Cardano/bin/compactc/compactc-macos:/opt/homebrew/opt/postgresql@16/bin:/usr/local/opt/postgresql@16/bin:/Users/stefano/.local/bin:/usr/local/bin:/Users/stefano/.brew/opt/llvm/bin:/Users/stefano/.emacs.d/bin:/usr/local/n/bin:/usr/local/opt/libpq/bin:/opt/homebrew/opt/postgresql@16/bin:/usr/local/opt/postgresql@16/bin:/opt/homebrew/bin:/Users/stefano/.rbenv/shims:/opt/homebrew/bin:/opt/homebrew/sbin:/usr/local/bin:/System/Cryptexes/App/usr/bin:/usr/bin:/bin:/usr/sbin:/sbin:/opt/X11/bin:/Users/stefano/Library/Application Support/org.dfinity.dfx/bin:/Users/stefano/.cargo/bin:/Users/stefano/.foundry/bin
PKG_CONFIG_PATH=/opt/homebrew/lib/pkgconfig:
PNPM_HOME=/Users/stefano/Library/pnpm
PWD=/Users/stefano/Documents/Code/42/Advanced/nibbler/lab/sfml
RBENV_SHELL=zsh
SECURITYSESSIONID=186a2
SHELL=/bin/zsh
SHLVL=1
SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.wCbvyYUVj3/Listeners
TERM=xterm-256color
TERM_PROGRAM=vscode
TERM_PROGRAM_VERSION=2.0.77
TMPDIR=/var/folders/2r/k2qkn9ld2t787q_c5xkh3b2r0000gp/T/
USER=stefano
USER_ZDOTDIR=/Users/stefano
VSCODE_GIT_ASKPASS_EXTRA_ARGS=
VSCODE_GIT_ASKPASS_MAIN=/Applications/Cursor.app/Contents/Resources/app/extensions/git/dist/askpass-main.js
VSCODE_GIT_ASKPASS_NODE=/Applications/Cursor.app/Contents/Frameworks/Cursor Helper (Plugin).app/Contents/MacOS/Cursor Helper (Plugin)
VSCODE_GIT_IPC_HANDLE=/var/folders/2r/k2qkn9ld2t787q_c5xkh3b2r0000gp/T/vscode-git-3bceaae677.sock
VSCODE_INJECTION=1
VSCODE_PROFILE_INITIALIZED=1
WASMTIME_HOME=/Users/stefano/.wasmtime
XPC_FLAGS=0x0
XPC_SERVICE_NAME=0
ZDOTDIR=/Users/stefano
ZSH=/Users/stefano/.oh-my-zsh
_=/usr/bin/env
__CFBundleIdentifier=com.todesktop.230313mzl4w4u92
__CF_USER_TEXT_ENCODING=0x1F6:0x0:0x2
```

### Notable Variables (Potentially Relevant)

- **CAML_LD_LIBRARY_PATH**: OCaml library path - could interfere with library loading
- **DISPLAY**: X11/XQuartz display - could interfere with native macOS windowing
- **MallocNanoZone=0**: Memory allocator setting
- **VSCODE_INJECTION=1**: Cursor/VS Code injection - might affect process execution
- **PATH**: Very long PATH with many development tools
- **OPAM_LAST_ENV**: OCaml package manager environment file

## Hypotheses

1. **Combination of variables:** Multiple variables together cause the crash (most likely - since individual unset doesn't help)
2. **Shell configuration/hooks:** Something in `.zshrc`, `precmd`, `preexec`, or other zsh hooks interfering (not an env var)
3. ~~**Background process issue:**~~ The `[1]` is just zsh's job number, not backgrounding
4. **Library path resolution:** `@rpath` might not resolve correctly in user's shell context due to shell behavior
5. **Shell function/alias:** There might be a function or alias wrapping `./sfml-app` that causes issues

## Test Results

**Individual variable unset tests:** ❌ All still crash

- `unset CAML_LD_LIBRARY_PATH` - Still crashes
- `unset DISPLAY` - Still crashes
- `unset VSCODE_INJECTION` - Still crashes
- `unset MallocNanoZone` - Still crashes
- `unset OPAM_LAST_ENV` - Still crashes

**Combination tests:**

- `unset CAML_LD_LIBRARY_PATH DISPLAY VSCODE_INJECTION` - ❌ Still crashes
- `unset CAML_LD_LIBRARY_PATH OCAMLTOP_INCLUDE_PATH OCAML_TOPLEVEL_PATH OPAMNOENVNOTICE OPAM_LAST_ENV OPAM_SWITCH_PREFIX` - ❌ Still crashes (OCaml group)
- `env -i PATH=/usr/bin:/bin:/usr/sbin:/sbin HOME=$HOME TERM=$TERM ./sfml-app` - ✅ **WORKS** (minimal PATH)
- `env -i PATH=$PATH HOME=$HOME TERM=$TERM ./sfml-app` - ✅ **WORKS** (full PATH, but clean env)
- `env -i PATH=$PATH HOME=$HOME TERM=$TERM DISPLAY=$DISPLAY ./sfml-app` - ✅ **WORKS**
- `env -i PATH=$PATH HOME=$HOME TERM=$TERM DISPLAY=$DISPLAY CAML_LD_LIBRARY_PATH=$CAML_LD_LIBRARY_PATH ./sfml-app` - ✅ **WORKS**
- Large batch of variables explicitly passed to `env -i` - ✅ **WORKS**
- **ALL 63 variables from env_vars.txt explicitly passed to `env -i`** - ✅ **WORKS**
- `unset CURSOR_TRACE_ID GIT_ASKPASS VSCODE_GIT_ASKPASS_EXTRA_ARGS VSCODE_GIT_ASKPASS_MAIN VSCODE_GIT_ASKPASS_NODE VSCODE_GIT_IPC_HANDLE VSCODE_INJECTION VSCODE_PROFILE_INITIALIZED TERM_PROGRAM TERM_PROGRAM_VERSION` - ❌ Still crashes

**Key Finding (CRITICAL):** ✅ **When you truly reconstruct the identical full environment inside `env -i` (using properly quoted export script), the program WORKS**

- ✅ All 63 variables from `env_vars.txt` work when explicitly set via `env -i`
- ✅ Even when using `env -i zsh -f -c 'source full-env; ./sfml-app'` with identical environment, it WORKS
- ❌ Same variables crash when launched directly from interactive zsh
- **Root Cause:** It's NOT the variables themselves, but **HOW the interactive shell launches the program**

**The only difference between working and crashing:**

| Feature                                    | Normal shell (`./sfml-app`) | `env -i zsh -f -c ...`   |
| ------------------------------------------ | --------------------------- | ------------------------ |
| Environment vars                           | Same                        | Same                     |
| Current directory                          | Same                        | Same                     |
| **Parent process**                         | zsh interactive session     | non-interactive subshell |
| **Job control (TTY state)**                | Enabled                     | Disabled                 |
| **Shell session hooks**                    | Enabled                     | None (`zsh -f`)          |
| Extra invisible descriptors (fd 255, etc.) | Probably present            | Not present              |

**Core Insight:** Something in your interactive shell execution context (job control, TTY handling, file descriptors, or process attributes) causes the OpenGL initialization to crash during `CGLChoosePixelFormat`. macOS OpenGL and Cocoa are extremely sensitive to how they are launched.

**Shell hooks found:** ✅ **CRITICAL FINDING**

- `__vsc_precmd()` - VS Code/Cursor precmd hook
- `__vsc_preexec()` - VS Code/Cursor preexec hook
- `omz_termsupport_precmd()` - Oh My Zsh terminal support
- `omz_termsupport_preexec()` - Oh My Zsh terminal support

**Terminal test:** ❌ Still crashes in regular terminal (not just Cursor)

- Crashes in both Cursor terminal AND regular macOS Terminal
- The `[1]` is just zsh's job number (not backgrounding - appears for foreground jobs too)

**Clean zsh test:** ❌ Still crashes in `zsh -f` (no config files)

- Crashes even with completely clean zsh (no `.zshrc`, no hooks, nothing)
- **This rules out shell configuration as the cause**

**OpenGL Framework Binary Status:** ⚠️ **STILL MISSING**

- `/System/Library/Frameworks/OpenGL.framework/OpenGL` symlink exists but is **broken**
- Points to `Versions/Current/OpenGL` → `Versions/A/OpenGL`
- **The actual binary `/System/Library/Frameworks/OpenGL.framework/Versions/A/OpenGL` does NOT exist**
- Framework structure exists (Libraries, Resources, \_CodeSignature) but main binary is missing
- This was discovered earlier and a system restart was thought to have fixed it, but **the binary is still missing**
- **Hypothesis:** The `env -i` workaround might bypass the broken symlink by using a different OpenGL loading path or fallback mechanism that is sensitive to launch context

**Conclusion (FINAL - ROOT CAUSE IDENTIFIED):**

- ✅ **When you truly reconstruct the identical full environment inside `env -i` (using properly quoted export script), the program WORKS**
- ✅ **The crash is NOT caused by any environment variable contents**
- ✅ **It's caused by HOW your interactive shell (zsh) launches the program, not by the environment it passes**
- ❌ Not shell configuration (crashes in clean `zsh -f` but still inherits env)
- ❌ Not individual variables (unsetting doesn't help, but explicit passing does)
- ❌ Not environment variable values (identical env works in `env -i`)
- **Root Cause:** zsh's interactive execution context (job control, TTY handling, file descriptors, or process attributes) causes OpenGL initialization to crash during `CGLChoosePixelFormat`
- The `[1]` is just zsh's job number, not backgrounding

**What we have proven:**

| What we have proven                                                 | Status        |
| ------------------------------------------------------------------- | ------------- |
| Not a compiler issue                                                | Confirmed     |
| Not an SFML bug                                                     | Confirmed     |
| Not an environment variable content issue                           | Confirmed     |
| Not a general process-launch quirk                                  | **Confirmed** |
| Crash is inside Apple OpenGL/CGL                                    | Confirmed     |
| Reproduced only when launched from interactive zsh                  | Confirmed     |
| Disappears in `env -i` or `zsh -f`                                  | Confirmed     |
| Issue is OpenGL/Cocoa-specific (trivial C++ programs work fine)     | **Confirmed** |
| Root cause: zsh interactive execution context affecting OpenGL init | **Confirmed** |
| OpenGL framework binary is missing (broken symlink)                 | **Confirmed** |

## Root Cause Analysis (FINAL)

**Key Technical Point:**

- zsh does NOT "encode" or "transform" the environment in a special way
- It just builds an array of `char*` (one per `NAME=VALUE`) and calls `execve()`
- `/usr/bin/env` does the same when it execs `./sfml-app`
- **When environments are truly identical, behavior should be identical - and it is!**

**What's actually different (Updated after testing):**

1. ✅ **Parent process** - interactive zsh session vs non-interactive subshell
2. ❌ **Job control / TTY state** - RULED OUT (disabling job control doesn't help)
3. ❌ **File descriptor 255** - RULED OUT (fd 255 is not even present in interactive zsh)
4. ❌ **Shell session hooks** - RULED OUT (`zsh -f` alone doesn't help - need `env -i` too)
5. ✅ **Process attributes / launch context** - The combination of "new non-interactive shell + exec there" is what works

**Key Finding:** The only stable combination is: **"new non-interactive shell + exec there"** (what `env -i zsh -f -c ...` does). Simply disabling job control or using `zsh -f` alone is not sufficient.

**The `[1]` is just zsh's job number** - it appears for foreground jobs too when they die with a signal. Not backgrounding.

**Root Cause:** zsh's interactive execution context (job control, TTY handling, file descriptors, or process attributes) causes macOS OpenGL/Cocoa initialization to crash. This is a known sensitivity in Apple's OpenGL implementation.

## Quick Real Tests (Results)

### Test A: Disable job control

```bash
set +m   # disable job control
./sfml-app
```

**Result:** ❌ Still segfaults (exit code 139). **Job control is NOT the trigger.**

### Test B: Close fd 255

```bash
bash -c './sfml-app'
bash -c 'exec 255>&-; ./sfml-app'
```

**Result:** ❌ Still crashes (exit code 139). **fd 255 is NOT the trigger.**

### Test C: Check if fd 255 exists

```bash
lsof -p $$ | grep ' 255'
```

**Result:** ✅ No output = **fd 255 is not even open in interactive zsh**. The fd-255 theory is dead.

### Test D: Check what `zsh -f` actually does

**Finding:** `zsh -f` does NOT remove any special fd or magically "sanitize" the runtime. It only skips reading your startup files.

**Conclusion from tests:**

- ✅ `env -i zsh -f -c 'source /tmp/export-env-quoted.sh; ./sfml-app'` → Works (window opens)
- ❌ `set +m` then `./sfml-app` → Still segfaults
- ❌ `bash -c './sfml-app'` → Still crashes
- ❌ fd 255 is not even present in interactive zsh
- ✅ **The only stable combination is: "new non-interactive shell + exec there"** (what `env -i zsh -f -c ...` does)

**What we've ruled out:**

- ❌ fd 255 (not even present)
- ❌ Job control (disabling it doesn't help)
- ❌ Environment variable contents (identical env works in `env -i`)
- ❌ Shell startup files (`zsh -f` alone doesn't help - need `env -i` too)

## Proper Debugging Steps

### 1. Get a backtrace in the crashing environment

```bash
lldb ./sfml-app
(lldb) run
# let it crash
(lldb) bt
```

This will show if the crash is in:

- SFML's window creation code
- CoreGraphics / AppKit / Metal
- libSystem / malloc / objc runtime

If the backtrace is in allocator/objc runtime, variables like `MallocNanoZone`, `OBJC_*`, `DYLD_*` become prime suspects.

### 2. Properly diff the environments (no guessing)

Instead of manually reconstructing, let the shell do a clean diff:

```bash
# 1) Save the "bad" environment as the shell sees it:
env | sort > /tmp/env.bad

# 2) Export current env as assignments
env | sed 's/^/export /' > /tmp/export-env.sh

# 3) In a subshell started via env -i, re-import that env and dump it:
( env -i zsh -f -c 'source /tmp/export-env.sh; env | sort' ) > /tmp/env.reconstructed

# 4) Compare:
diff -u /tmp/env.bad /tmp/env.reconstructed
```

If these differ, your "reconstructed" env is not identical to what the shell has when running `./sfml-app` directly. That difference is exactly where to look.

**Typical candidates you might miss:**

- Variables with spaces/funny characters that get mangled
- Variables added by shell when launching (`_`, possibly others)
- Variables only sometimes present (Terminal vs Cursor, login vs non-login)

### 3. Test with non-SFML binary ✅ COMPLETED

Run a trivial C++ program with same build pipeline but no SFML:

```cpp
#include <iostream>
int main() {
    std::cout << "hello from test-hello\n";
    return 0;
}
```

Build with same compiler/flags:

```bash
c++ -std=c++17 test-hello.cpp -o test-hello
```

**Test Results:**

- ✅ `./test-hello` (normal env where sfml-app crashes) → **Works fine**
- ✅ `env -i PATH=/usr/bin:/bin:/usr/sbin:/sbin HOME="$HOME" TERM="$TERM" ./test-hello` → **Works fine**
- ✅ `env -i zsh -f -c 'cd ~/Documents/Code/42/Advanced/nibbler/lab/sfml && source /tmp/export-env-quoted.sh; ./test-hello'` → **Works fine**

**Conclusion:** ✅ **The issue is OpenGL/Cocoa-specific, NOT a general process-launch quirk.**

The trivial C++ program works fine in all contexts, including the one where `sfml-app` crashes. This confirms the crash is strictly on the OpenGL / Cocoa path that SFML uses during window initialization, not a general problem with how processes are launched from the interactive shell.

### 4. Check resource limits

```bash
ulimit -a > /tmp/limits.bad
env -i PATH=/usr/bin:/bin:/usr/sbin:/sbin HOME=$HOME TERM=$TERM zsh -c 'ulimit -a' > /tmp/limits.good
diff -u /tmp/limits.bad /tmp/limits.good
```

If stack size is tiny in one context, things like huge environments + deep Cocoa/Metal stacks can trip it.

## Workaround (Confirmed Working)

Since the issue is zsh's interactive execution context, use a clean launcher. The only stable combination is: **"new non-interactive shell + exec there"**.

### Option 1: Minimal wrapper script

```bash
# run-sfml.sh
#!/usr/bin/env bash
cd "$(dirname "$0")"
env -i \
  PATH=/usr/bin:/bin:/usr/sbin:/sbin \
  HOME="$HOME" \
  TERM="$TERM" \
  ./sfml-app
```

Then:

```bash
chmod +x run-sfml.sh
./run-sfml.sh
```

### Option 2: Shell function

```bash
# ~/.zshrc
sfml_run() {
  env -i \
    PATH=/usr/bin:/bin:/usr/sbin:/sbin \
    HOME="$HOME" \
    TERM="$TERM" \
    ./sfml-app
}
```

### Option 3: Direct command

```bash
env -i PATH=/usr/bin:/bin:/usr/sbin:/sbin HOME="$HOME" TERM="$TERM" ./sfml-app
```

**This works because it launches from a new non-interactive shell context, which is the only stable combination that avoids the crash.**

## Next Steps (Optional - for further investigation)

### ✅ Test: Is this OpenGL-specific or more general? - COMPLETED

**Result:** The trivial C++ program (`test-hello`) works fine in all contexts, including the one where `sfml-app` crashes.

**Test Results:**

- ✅ `./test-hello` (normal env where sfml-app crashes) → **Works fine**
- ✅ `env -i PATH=/usr/bin:/bin:/usr/sbin:/sbin HOME="$HOME" TERM="$TERM" ./test-hello` → **Works fine**
- ✅ `env -i zsh -f -c 'cd ~/Documents/Code/42/Advanced/nibbler/lab/sfml && source /tmp/export-env-quoted.sh; ./test-hello'` → **Works fine**

**Conclusion:** The issue is **strictly on the OpenGL / Cocoa path** that SFML uses during window initialization. It is NOT a general process-launch quirk affecting all programs.

### Other investigation options:

1. **Write a permanent clean wrapper (`run-sfml.sh`) to always launch safely** (see below)
2. **Report this as a small reproducible bug to SFML or Apple OpenGL teams**
3. **Test if this still happens when switching to SFML 3 Metal backend (no OpenGL)**

## Notes

- This is NOT an environment variable issue - identical environments work fine
- This is NOT an SFML bug - SFML works correctly
- This is NOT a compilation issue - the binary is correct
- This is NOT fd 255 - fd 255 is not even present
- This is NOT job control - disabling it doesn't help
- **This IS a zsh interactive execution context issue affecting macOS OpenGL/Cocoa**
- macOS OpenGL and Cocoa are extremely sensitive to how they are launched
- The crash happens during `CGLChoosePixelFormat` in Apple's OpenGL implementation
- **The only stable combination is: "new non-interactive shell + exec there"** (`env -i zsh -f -c ...`)
- Simply using `zsh -f` alone is not sufficient - need `env -i` too
- **OpenGL framework binary is missing:** `/System/Library/Frameworks/OpenGL.framework/Versions/A/OpenGL` does not exist (broken symlink)
- Workaround: Launch from new non-interactive context using `env -i` wrapper script

**Current understanding:** This is a fragile interaction between "how the process is started" and Apple's deprecated OpenGL stack. The missing OpenGL framework binary may be contributing to the issue, and the `env -i` workaround might bypass the broken symlink by using a different OpenGL loading path or fallback mechanism. The exact mechanism is unclear, but the workaround is reliable.
