# SFML 3.x Crash Issue on macOS

## Problem Summary

The SFML tutorial program compiles successfully but crashes with a segmentation fault during window creation on macOS (arm64).

## Symptoms

- **Compilation:** ✅ Successful
- **Linking:** ✅ Successful
- **Library loading:** ✅ Libraries load correctly
- **Runtime:** ❌ Segmentation fault during `sf::RenderWindow` construction

## Error Details

```
[1] <pid> segmentation fault  ./sfml-app
```

The crash occurs **before** any console output, indicating it happens during the `sf::RenderWindow` constructor call, not in user code.

## Code

The program uses standard SFML 3.x API:

```cpp
sf::RenderWindow window(sf::VideoMode({800u, 600u}), "SFML window", sf::Style::Titlebar | sf::Style::Close);
```

This matches the style used in official SFML 3.x examples.

## Environment

- **OS:** macOS (darwin 23.4.0)
- **Architecture:** arm64 (Apple Silicon)
- **SFML Version:** 3.1.0 (built from source)
- **Build Type:** Release
- **Library Format:** dylib (dynamic libraries)
- **Compiler:** g++ (Command Line Tools) - Note: On macOS, `g++` is actually `clang++` (Apple's LLVM compiler)
- **C++ Standard:** C++17

## Build Configuration

- SFML built from source using CMake
- Build flags: `-DSFML_BUILD_EXAMPLES=OFF -DSFML_BUILD_DOC=OFF -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON`
- Libraries properly linked and copied to working directory
- `@rpath` correctly set to `@loader_path`

## What We've Tried

1. ✅ Verified code compiles with correct SFML 3.x API
2. ✅ Checked library dependencies - all load correctly
3. ✅ Rebuilt SFML from scratch with clean build
4. ✅ Verified library architecture matches (arm64) - confirmed with `file` command
5. ✅ Tested minimal window creation - same crash
6. ✅ Compared with SFML examples - same API usage
7. ✅ Verified Makefile generator (recommended for macOS)
8. ✅ Confirmed `g++` is actually `clang++` on macOS (toolchain is correct)
9. ✅ Verified library loading with `otool -L` - all dependencies resolve correctly
10. ✅ Debugged with `lldb` - crash occurs in OpenGL framework, not SFML code

## Root Cause Hypothesis

The crash occurs in **OpenGL framework** during window creation, not in SFML's Cocoa/NSWindow code. **Debugging findings:**

### Debugging Results

**lldb backtrace shows:**

```
frame #0: 0x00000001ed705ab8 OpenGL`___lldb_unnamed_symbol319 + 748
stop reason = EXC_BAD_ACCESS (code=1, address=0xbad4007)
```

**Key observations:**

- ✅ Toolchain is correct: `g++` on macOS is actually `clang++` (Apple's LLVM)
- ✅ Architecture matches: Both executable and libraries are arm64
- ✅ Libraries load correctly: All dependencies resolve via `@rpath`
- ✅ SFML libraries link to correct macOS frameworks (OpenGL, AppKit, Foundation, etc.)
- ❌ Crash happens in OpenGL framework during context initialization
- ❌ Bad pointer access (`0xbad4007`) suggests uninitialized or corrupted OpenGL state

### Most Likely Causes

1. **SFML 3.1.0 OpenGL initialization bug on macOS arm64**

   - OpenGL context creation fails or accesses invalid memory
   - May be related to Metal/OpenGL translation layer on Apple Silicon
   - SFML 3.x may have compatibility issues with macOS's OpenGL implementation

2. **OpenGL context initialization timing issue**

   - Window creation attempts to create OpenGL context before proper initialization
   - Possible race condition or missing initialization step

3. **SFML 3.x regression on macOS**
   - SFML 2.6.x may work fine, but 3.x has a bug
   - Could be related to SFML 3.x's new rendering architecture

## Next Steps to Investigate

### Priority 1: Test SFML 2.6.x (Verify Environment)

1. **Test SFML 2.6.x to confirm environment is okay**
   - If 2.6.x works fine, confirms the issue is SFML 3.x specific
   - If 2.6.x also crashes, indicates a deeper system/configuration issue

### Priority 2: Try Different SFML 3.x Versions

2. **Test SFML 3.0.2 (tagged release)**

   - Current build is 3.1.0, try 3.0.2 to see if it's a 3.1.0 regression
   - Check if 3.0.2 has the same OpenGL crash

3. **Try SFML 3.x master branch**
   - May have fixes for macOS OpenGL issues
   - Could be a known issue with a fix in development

### Priority 3: OpenGL/Metal Compatibility

4. **Check if Metal backend is needed**

   - macOS on Apple Silicon may require Metal instead of OpenGL
   - SFML 3.x may need different rendering backend configuration
   - Check SFML CMake options for Metal/OpenGL selection

5. **Investigate OpenGL context creation**
   - Try creating window with different OpenGL versions
   - Check if explicit OpenGL version specification helps
   - May need to set OpenGL context attributes before window creation

### Priority 4: Report to SFML

6. **Open GitHub issue with findings**
   - Minimal reproducer code
   - Full environment details (macOS version, SFML version, architecture)
   - Complete lldb backtrace
   - Note that crash is in OpenGL framework, not SFML code

### Notes

- **Frameworks vs dylibs:** Not the core problem. Dylibs are correct for Nibbler project.
- **Static vs dynamic:** Known crash exists with static linking on macOS, but doesn't apply here (using dylibs).

## Notes

- The code itself is correct and follows SFML 3.x best practices
- The issue is almost certainly not in the user C++ code, but in either:
  - **SFML 3.x OpenGL initialization on macOS** (most likely)
  - **OpenGL/Metal compatibility on Apple Silicon** (possible)
  - **SFML 3.1.0 regression** (possible)
- For the Nibbler project, dylibs are required (not frameworks) due to dynamic library loading requirements
- **Toolchain is correct:** On macOS, `g++` is actually `clang++` (Apple's LLVM), so the toolchain hypothesis was incorrect
- **Crash location:** The crash occurs in the OpenGL framework during context initialization, not in SFML's Cocoa/NSWindow code
- **Architecture verified:** Both executable and libraries are arm64, no mismatch
- **Library loading verified:** All dependencies resolve correctly via `@rpath` and `@loader_path`
