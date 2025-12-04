# SFML 3.x macOS OpenGL Crash - Fix

## Status

✅ **RESOLVED** - Restart Fixed the Issue

**SOLUTION:** Restarting the computer restored OpenGL functionality. The OpenGL framework was likely in a corrupted or unloaded state, and the restart reloaded it properly.

**ROOT CAUSE (Historical):** The OpenGL framework binary appeared to be missing from `/System/Library/Frameworks/OpenGL.framework/OpenGL`. However, restarting macOS resolved the issue, suggesting the framework was in a bad state rather than actually deleted.

## Fix Attempts

### Attempt 1: Non-OpenGL Module Test ✅

- **Date:** 2024-11-21
- **Result:** ✅ Non-OpenGL modules (`sf::Clock`, `sf::Time`, `sf::sleep`) work correctly
- **Conclusion:** Issue is isolated to OpenGL/graphics module

### Attempt 2: Explicit Logging ✅

- **Date:** 2024-11-21
- **Result:** Confirmed crash occurs exactly during `sf::RenderWindow` constructor
- **Logs:**
  ```
  === Starting SFML test ===
  Before RenderWindow construction
  About to create RenderWindow...
  [CRASH - no further output]
  ```

### Attempt 3: Cross-Library Testing ✅ **CRITICAL FINDING**

- **Date:** 2024-11-21
- **Test:** Tried raylib (lib1) in network-snake project
- **Result:** ❌ **Same crash in same OpenGL framework location**
- **Evidence:**
  - raylib loads and initializes successfully
  - Crash occurs at: `OpenGL`\_\_\_lldb_unnamed_symbol319 + 748
  - Same crash address: `0xbad4007`
  - Same `EXC_BAD_ACCESS` error
- **Conclusion:** **This is NOT an SFML bug - it's a macOS OpenGL/Metal compatibility layer issue affecting all OpenGL-based graphics libraries**

### Attempt 4: Minimal OpenGL Test ✅

- **Date:** 2024-11-21
- **Test:** Created minimal OpenGL/GLUT program (no graphics libraries)
- **Code:** Direct OpenGL calls: `glutInit()`, `glutCreateWindow()`
- **Result:** ❌ **Same crash in exact same location**
- **Evidence:**
  - Minimal code with only GLUT and OpenGL frameworks
  - Crash at: `OpenGL`\_\_\_lldb_unnamed_symbol319 + 748
  - Same crash address: `0xbad4007`
  - Crashes during `glutCreateWindow()` - OpenGL context creation

### Attempt 5: System File Investigation ✅ **ROOT CAUSE FOUND**

- **Date:** 2024-11-21
- **Discovery:** User mentioned it worked 10 days ago, installed Unity, may have deleted files
- **Investigation:** Checked OpenGL framework structure
- **Result:** ✅ **Found missing binary**
- **Evidence:**
  - `/System/Library/Frameworks/OpenGL.framework/OpenGL` - **FILE MISSING**
  - Symlink exists: `OpenGL -> Versions/Current/OpenGL`
  - `Versions/Current -> Versions/A`
  - `Versions/A/OpenGL`: **DOES NOT EXIST**
  - Framework directory structure exists, but binary is gone
- **Conclusion:** **The OpenGL framework binary was accidentally deleted. This explains why it worked 10 days ago and doesn't work now.**

## Solution Steps

### Step 1: Update macOS (Recommended First Step)

```bash
sudo softwareupdate -i "macOS Sonoma 14.8.2-23J126"
```

- May restore missing system files including OpenGL framework
- Requires restart
- Safest and easiest option

### Step 2: Verify OpenGL Framework Restored

After update, verify the file exists:

```bash
ls -la /System/Library/Frameworks/OpenGL.framework/OpenGL
file /System/Library/Frameworks/OpenGL.framework/OpenGL
```

### Step 3: Test SFML Program

```bash
cd lab/sfml
make clean && make
./sfml-app
```

## Alternative Solutions (If Update Doesn't Work)

1. **Restore from Time Machine**

   - If Time Machine backups are enabled
   - Restore `/System/Library/Frameworks/OpenGL.framework/` from backup before deletion

2. **Reinstall macOS**

   - Reinstall macOS without erasing data
   - Will restore all system files including OpenGL framework
   - Most thorough but time-consuming

3. **Test SDL3 (lib4) as Workaround**
   - SDL3 may use Metal/Vulkan instead of OpenGL
   - If SDL3 works, can use it as temporary workaround
   - Doesn't fix the root cause but allows development to continue

## Working Solutions

### ✅ Solution: Restart macOS

**What Worked:** Simply restarting the computer fixed the issue.

**What Happened:**

- OpenGL framework was likely in a corrupted or unloaded state
- Restart reloaded the framework properly
- SFML, raylib, and GLUT all work correctly now

**If it happens again:**

1. Try restarting first (simplest solution)
2. If restart doesn't work, then try macOS update
3. Last resort: Restore from Time Machine or reinstall macOS

### Potential Workarounds (Not Yet Tested)

1. **Use Metal-based libraries**

   - Try SDL3 with Metal backend
   - Use native Metal rendering instead of OpenGL

2. **Force OpenGL version**

   - Try explicitly requesting OpenGL 2.1 or 3.3
   - May avoid problematic OpenGL 4.x paths

3. **Use different windowing backend**
   - Some libraries support multiple backends
   - Try GLFW directly instead of through SFML/raylib

## Notes

- See `SFML_3x_macOS_OpenGL_crash_debug.md` for full investigation details
- **Resolution:** Restarting macOS fixed the issue
- **What happened:** OpenGL framework was in a corrupted/unloaded state, restart reloaded it
- **Timeline:** Worked 10 days ago, stopped after Unity installation, fixed after restart
- **Affected:** SFML, raylib, and minimal GLUT code all crashed (now all working)
- **System:** macOS 14.4.1 (Sonoma) on Apple Silicon (arm64)
- **Network snake build pipeline works perfectly; OpenGL now works correctly**
- **Lesson learned:** Try restarting first before assuming system files are missing
