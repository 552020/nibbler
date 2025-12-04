# SFML 3.x macOS OpenGL Crash Debug

## Investigation Notes

## Problem Summary

Graphics libraries (SFML, raylib) compile successfully but crash with a segmentation fault during OpenGL context creation on macOS (arm64). **Root cause identified: The OpenGL framework binary is missing from the system.**

**Critical Context:** This worked 10 days ago. User installed Unity and may have deleted files to make space, which likely removed the OpenGL framework binary.

## Symptoms

- **Compilation:** ✅ Successful
- **Linking:** ✅ Successful
- **Library loading:** ✅ Dynamic loader resolves all SFML and system library dependencies; the program starts and only crashes when creating the first SFML window
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
- **SFML Version:** SFML 3.x (current master / development branch, built from source)
- **Build Type:** Release
- **Library Format:** dylib (dynamic libraries)
- **Compiler:** g++ (Command Line Tools) - Note: On macOS, `g++` is actually `clang++` (Apple's LLVM compiler)
- **C++ Standard:** C++17

## Build Configuration

- SFML built from source using CMake
- Build flags: `-DSFML_BUILD_EXAMPLES=OFF -DSFML_BUILD_DOC=OFF -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON`
- Libraries properly linked and copied to working directory
- `@rpath` correctly set to `@loader_path`

**Note:** For the Nibbler project we require dynamic libraries (\*.dylib) that can be loaded at runtime; frameworks are not an option, which is why we are focusing on dylib builds and rpath handling rather than .framework bundles.

## Verified Facts

These are confirmed observations, not hypotheses:

1. ✅ Code is minimal and correct: `RenderWindow` creation on main thread using standard SFML 3.x API
2. ✅ Build/link/runtime search paths are correct: No loader errors, `otool -L` shows all dependencies resolve correctly
3. ✅ Crash is an `EXC_BAD_ACCESS` inside Apple's OpenGL framework during context creation
4. ✅ Both binary and SFML dylibs are arm64 (verified with `file` command)
5. ✅ Compiler is Apple clang via `g++` (toolchain is correct)
6. ✅ Architecture matches: Both executable and libraries are arm64, no mismatch
7. ✅ Library loading verified: All dependencies resolve correctly via `@rpath` and `@loader_path`
8. ✅ SFML libraries link to correct macOS frameworks (OpenGL, AppKit, Foundation, etc.)
9. ✅ Non-OpenGL SFML modules work correctly: `sf::Clock`, `sf::Time`, `sf::sleep` all function properly
10. ✅ Crash is isolated to OpenGL/graphics module: Explicit logging confirms crash occurs exactly during `sf::RenderWindow` constructor call
11. ✅ **Cross-library test:** raylib (lib1) exhibits the same crash in the same OpenGL framework location
12. ✅ **Network snake build pipeline works:** All libraries compile and link successfully
13. ✅ **Both libraries load correctly:** SFML and raylib both initialize successfully before crashing
14. ✅ **Minimal OpenGL test:** Even basic GLUT/OpenGL code crashes identically
15. ✅ **Root cause identified:** `/System/Library/Frameworks/OpenGL.framework/OpenGL` binary is **MISSING**
16. ✅ **Timeline:** Worked 10 days ago, stopped working after Unity installation and possible file deletion
17. ✅ **Framework structure:** OpenGL framework directory exists, symlinks exist, but the actual binary file is missing

## Debugging Results

**lldb backtrace shows:**

```
frame #0: 0x00000001ed705ab8 OpenGL`___lldb_unnamed_symbol319 + 748
stop reason = EXC_BAD_ACCESS (code=1, address=0xbad4007)
```

**Key observation:** Crash occurs inside Apple's OpenGL framework during context initialization; it is unclear whether the root bug is in SFML's usage, the framework, or the compatibility layer.

## Root Cause - CONFIRMED ✅

**The OpenGL framework binary is missing from the system.**

### Investigation Results

1. **Missing Binary:**

   - Path: `/System/Library/Frameworks/OpenGL.framework/OpenGL`
   - Status: Symlink exists but target file is missing
   - Symlink points to: `Versions/Current/OpenGL`
   - `Versions/Current` → `Versions/A`
   - `Versions/A/OpenGL`: **FILE DOES NOT EXIST**

2. **Framework Structure:**

   - Framework directory exists: ✅
   - Symlinks exist: ✅
   - Libraries directory exists: ✅
   - **OpenGL binary: ❌ MISSING**

3. **Timeline:**

   - Worked 10 days ago
   - User installed Unity
   - User may have deleted files to make space
   - OpenGL framework binary was likely deleted

4. **Why All Libraries Crash:**
   - SFML, raylib, and GLUT all try to load OpenGL framework
   - Missing binary causes `EXC_BAD_ACCESS` when framework is accessed
   - Same crash location because all code paths lead to the missing binary

### Previous Hypotheses (Superseded)

The earlier hypotheses about macOS system bugs or library issues were incorrect. The real issue is a **missing system file** that was accidentally deleted.

## Next Steps to Investigate

### Priority 1: Verify Environment with SFML 2.6.x

1. **Test SFML 2.6.x to confirm environment is okay**
   - If 2.6.x works fine, confirms the issue is SFML 3.x specific
   - If 2.6.x also crashes, indicates a deeper system/configuration issue

### Priority 2: Test SFML Official Examples

2. **Run the SFML 3.x official examples from the same build**
   - If they crash in the same way → environment / SFML bug
   - If they work → compare CMake options / compile flags to identify differences

### Priority 3: Debug Build Investigation

3. **Try building everything with Debug instead of Release**

   - `-DCMAKE_BUILD_TYPE=Debug` for SFML
   - Remove `-O2` in Makefile and add `-g`
   - See if stacktrace becomes clearer, or if behavior changes

4. **Explicitly log before any SFML call in `main`**
   - Add `std::puts("before RenderWindow");` and `std::puts("after RenderWindow");`
   - Confirms the crash is exactly on `RenderWindow` construction (screenshot in issue is persuasive)

### Priority 4: Isolate Graphics Module ✅ COMPLETED

5. **Try a trivial non-OpenGL SFML module first** ✅
   - ✅ Tested `sf::Clock`, `sf::Time`, `sf::sleep` - all work correctly
   - ✅ Confirmed issue is OpenGL/graphics-specific, not broader SFML issue

### Priority 4b: Cross-Library Testing ✅ COMPLETED

6. **Test with other OpenGL libraries** ✅
   - ✅ Tested raylib (lib1) - **exhibits same crash**
   - ✅ Same crash location in OpenGL framework
   - ✅ **Conclusion:** Issue affects multiple OpenGL libraries, suggesting macOS system-level problem

### Priority 4c: Minimal OpenGL Test ✅ COMPLETED - **DEFINITIVE PROOF**

7. **Test OpenGL in isolation (no graphics libraries)** ✅
   - ✅ Created minimal GLUT/OpenGL program
   - ✅ **Same crash at exact same location** (`OpenGL`\_\_\_lldb_unnamed_symbol319 + 748)
   - ✅ **Same crash address** (`0xbad4007`)
   - ✅ Crashes during `glutCreateWindow()` - OpenGL context creation
   - ✅ **Conclusion:** **This is definitively a macOS system-level OpenGL framework bug, not a library issue**

### Priority 5: Try Different SFML 3.x Versions

7. **Test different SFML 3.x commits/branches**
   - Try tagged releases if available
   - Try latest master branch (may have fixes for macOS OpenGL issues)
   - Compare behavior across versions

### Priority 6: Test SDL3 (lib4)

8. **Test SDL3 library if available**
   - SDL3 may use different rendering backend (Metal/Vulkan)
   - If SDL3 works, confirms OpenGL-specific issue
   - If SDL3 also crashes, suggests broader graphics stack problem

### Priority 7: Restore Missing OpenGL Framework ✅ IDENTIFIED

9. **Restore OpenGL framework binary** ✅ ROOT CAUSE FOUND
   - ✅ Confirmed: `/System/Library/Frameworks/OpenGL.framework/OpenGL` is missing
   - **Solution 1:** Update macOS (may restore missing system files)
     - `sudo softwareupdate -i "macOS Sonoma 14.8.2-23J126"`
   - **Solution 2:** Restore from Time Machine backup (if enabled)
   - **Solution 3:** Reinstall macOS without erasing data (last resort)

## Notes

- The code itself is correct and follows SFML 3.x best practices
- The issue is almost certainly not in the user C++ code
- **Frameworks vs dylibs:** Not the core problem. Dylibs are correct for Nibbler project.
- **Static vs dynamic:** Known crash exists with static linking on macOS, but doesn't apply here (using dylibs).
- **Root cause:** Missing OpenGL framework binary (`/System/Library/Frameworks/OpenGL.framework/OpenGL`)
- **Why it worked before:** System file was present 10 days ago
- **What happened:** Likely deleted when user freed up space (possibly during Unity installation cleanup)
- **Network snake project:** Build pipeline works perfectly; all libraries compile and link. Runtime crash occurs because OpenGL framework binary is missing.
- **Solution:** Restore the missing system file via macOS update, Time Machine, or macOS reinstall
