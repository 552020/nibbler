# Request: Metal Backend Support for SFML 3.x on macOS

## Problem Summary

SFML 3.x on macOS currently only supports OpenGL, which is deprecated and has system-level issues on modern macOS (especially Apple Silicon). The OpenGL framework has a broken symlink (`/System/Library/Frameworks/OpenGL.framework/Versions/A/OpenGL` does not exist), causing segmentation faults when SFML applications are launched from interactive shells.

## Current Situation

- **SFML Version:** 3.1.0 (built from source, master branch)
- **OS:** macOS 26.1 (Apple Silicon, arm64)
- **Backend:** OpenGL only (deprecated on macOS)
- **Issue:** OpenGL framework binary is missing, causing crashes

## Attempted Solution

Tried to build SFML with Metal backend using CMake flags:

```cmake
-DSFML_METAL=ON -DSFML_OPENGL=OFF
```

**Result:** CMake warning:
```
CMake Warning:
  Manually-specified variables were not used by the project:
    SFML_METAL
    SFML_OPENGL
```

These CMake variables do not exist in SFML 3.x.

## Why Metal Support is Needed

1. **OpenGL is deprecated on macOS** - Apple deprecated OpenGL in macOS 10.14 and removed it in macOS 14+
2. **System-level issues** - The OpenGL framework has broken symlinks on some systems
3. **Apple Silicon optimization** - Metal is the native graphics API for Apple Silicon
4. **Future-proofing** - OpenGL support may be completely removed in future macOS versions

## Technical Details

### Current SFML 3.x macOS Implementation

From `src/SFML/Window/CMakeLists.txt` (lines 310-313):

```cmake
else()
    find_package(OpenGL REQUIRED COMPONENTS OpenGL)
    target_link_libraries(sfml-window PRIVATE OpenGL::GL)
endif()
```

SFML always links against OpenGL on macOS (non-iOS), with no option to use Metal.

### macOS Platform Files

SFML uses OpenGL-specific files on macOS:
- `SFOpenGLView.mm` - OpenGL view implementation
- `SFContext.mm` - OpenGL context management
- All windowing code assumes OpenGL context

## Request

**Add Metal backend support for SFML 3.x on macOS**, allowing users to choose between:
- OpenGL (legacy, for compatibility)
- Metal (modern, recommended for Apple Silicon)

### Proposed CMake Options

```cmake
# macOS rendering backend selection
if(SFML_OS_MACOS)
    sfml_set_option(SFML_RENDER_BACKEND "OpenGL" STRING "Rendering backend: OpenGL or Metal")
    if(SFML_RENDER_BACKEND STREQUAL "Metal")
        # Use Metal backend
        find_package(Metal REQUIRED)
        target_link_libraries(sfml-window PRIVATE "-framework Metal" "-framework MetalKit")
    else()
        # Use OpenGL backend (default for compatibility)
        find_package(OpenGL REQUIRED COMPONENTS OpenGL)
        target_link_libraries(sfml-window PRIVATE OpenGL::GL)
    endif()
endif()
```

### Implementation Requirements

1. **Metal view implementation** - Replace or complement `SFOpenGLView` with a Metal view
2. **Metal context management** - Implement Metal rendering context
3. **Backend abstraction** - Ensure Graphics module works with both backends
4. **CMake configuration** - Add option to select backend at build time
5. **Documentation** - Update build instructions for Metal option

## Workaround (Current)

Until Metal support is added, the only workaround is to launch SFML applications with a clean environment:

```bash
env -i PATH=/usr/bin:/bin:/usr/sbin:/sbin HOME="$HOME" TERM="$TERM" ./sfml-app
```

This bypasses the broken OpenGL framework issue but doesn't solve the underlying problem.

## Related Issues

- OpenGL framework broken symlink on macOS (system-level issue)
- Environment-specific crashes when launching from interactive shell
- Deprecated OpenGL API on macOS

## References

- SFML 3.x source: `src/SFML/Window/CMakeLists.txt`
- macOS OpenGL deprecation: [Apple Developer Documentation](https://developer.apple.com/metal/)
- Current issue documentation: `docs/issue/Environment_specific_crash.md`

## Additional Context

This is part of the Nibbler project, which requires dynamic library loading at runtime. The project builds SFML from source, so having Metal as a build option would directly solve the OpenGL-related crashes.

---

**Priority:** High (for macOS/Apple Silicon users)  
**Complexity:** Medium-High (requires significant backend implementation)  
**Impact:** Enables SFML to work reliably on modern macOS systems


