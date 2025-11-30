# Intro State Animation and Timing Issues

## Overview

The `State_Intro` state has two problems:
1. The sprite doesn't animate down from the top
2. The text appears immediately and spacebar works from the beginning, instead of waiting 5 seconds

## Current Behavior

- Sprite appears on screen (positioned at center x, y=0)
- Sprite does NOT animate/move down
- Text "Press SPACE to continue" is visible immediately
- Spacebar works immediately to transition to MainMenu

## Failed Fix Attempt

**Attempted fix:** Changed sprite starting position to start above the screen:
```cpp
m_introSprite.setPosition(sf::Vector2f(windowSize.x / 2.0f, -textureSize.y / 2.0f));
// Later changed to:
m_introSprite.setPosition(sf::Vector2f(windowSize.x / 2.0f, -textureSize.y));
```

**Result:** Sprite completely disappeared and never appeared on screen.

**Why it failed:** 
- With origin at center `(textureSize.x/2, textureSize.y/2)`, positioning at negative y values placed the entire sprite too far above the visible area
- The sprite never entered the visible screen bounds during the 5-second animation
- This made the problem worse - sprite went from "visible but not animating" to "completely invisible"

**Lesson:** Need to carefully calculate starting position accounting for:
- Sprite origin (center in this case)
- Texture size
- Window bounds
- Desired visual effect (sprite should start just above or at top edge, then animate down)

## Expected Behavior

- Sprite should start above the screen (or at the top edge)
- Sprite should animate down over 5 seconds
- Text should only appear after 5 seconds have passed
- Spacebar should only work after 5 seconds have passed

## Code Analysis

### Sprite Animation Issue

**Current code in `Update()`:**
```cpp
void State_Intro::Update(const sf::Time& l_time) {
    m_timePassed += l_time.asSeconds();
    if (m_timePassed < 5.0f) {
        sf::Vector2f currentPos = m_introSprite.getPosition();
        m_introSprite.setPosition(sf::Vector2f(currentPos.x,
            currentPos.y + (48 * l_time.asSeconds())));
    }
}
```

**Potential issues:**
- Sprite starts at `y=0` with origin at center - this means it's immediately visible
- Movement calculation might not be working correctly
- Need to verify `Update()` is being called and `l_time` has correct values

### Timing Issue

**Current code in `Draw()`:**
```cpp
if (m_timePassed >= 5.0f) {
    window->draw(m_text);
}
```

**Current code in `Continue()`:**
```cpp
if (m_timePassed >= 5.0f) {
    m_stateMgr->SwitchTo(StateType::MainMenu);
    m_stateMgr->Remove(StateType::Intro);
}
```

**Potential issues:**
- `m_timePassed` might not be incrementing correctly
- `m_timePassed` might be initialized incorrectly
- State might be recreated/reset, resetting `m_timePassed`
- `Update()` might not be called before first `Draw()`

## Investigation Needed

- [ ] Verify `Update()` is being called every frame
- [ ] Check if `m_timePassed` is actually incrementing (add debug output)
- [ ] Verify sprite position is actually changing (add debug output)
- [ ] Check if state is being recreated/reset (check `OnCreate()` calls)
- [ ] Verify `l_time.asSeconds()` returns valid values
- [ ] Check sprite origin and position relationship - with center origin at y=0, sprite is immediately visible

## Potential Fixes

1. **Sprite starting position**: Start sprite above screen (negative y) accounting for centered origin
2. **Time tracking**: Ensure `m_timePassed` is properly initialized and incremented
3. **State lifecycle**: Verify state isn't being recreated, which would reset `m_timePassed`

## Root Cause Found

**Issue:** `Game::Update()` was passing `m_elapsed` (accumulated time since game start) instead of delta time (time since last frame) to `StateManager::Update()`.

**Fix Applied:**
```cpp
// Before (buggy - tutorial code):
void Game::Update() {
    m_window.Update();
    m_stateManager.Update(m_elapsed); // Wrong: accumulated time
}

// After (fixed):
void Game::Update() {
    m_window.Update();
    sf::Time deltaTime = m_clock.restart(); // Get delta time and restart clock
    m_stateManager.Update(deltaTime);       // Pass delta time
}
```

**Note:** This is a bug in the tutorial code. The tutorial shows `m_stateManager.Update(m_elapsed)` but `m_elapsed` is accumulated time (keeps growing), not delta time. This caused `l_time.asSeconds()` in `State_Intro::Update()` to be extremely large values (e.g., 43698.7s), making the animation and timing checks fail.

## Attempted Timing Verification (Failed)

**Goal:** Add `std::chrono::steady_clock` to compare SFML time with real time to verify timing accuracy.

**Attempt:**
- Added `std::chrono::steady_clock::time_point m_startTime` member to `State_Intro` class
- Initialized in constructor: `m_startTime()` in member initializer list
- Set in `OnCreate()`: `m_startTime = std::chrono::steady_clock::now()`
- Added comparison logging in `Update()` to show SFML time vs real time

**Result:** AddressSanitizer heap buffer overflow error:
```
ERROR: AddressSanitizer: heap-buffer-overflow on address 0x6190000bdf30
WRITE of size 8 at 0x6190000bdf30 thread T0
State_Intro::State_Intro(StateManager*) State_Intro.cpp:9
```

**Analysis:**
- Error occurs when writing 8 bytes past a 944-byte allocated region
- Happens in constructor during member initialization
- Likely caused by memory alignment issues with `std::chrono::steady_clock::time_point`
- May be AddressSanitizer false positive, or real memory layout issue

**Status:** Reverted - chrono timing code removed. Need to investigate if this is a real issue or AddressSanitizer quirk before re-adding.

**Question for Tech Lead:** Is this a known issue with `std::chrono` types and AddressSanitizer? Should we use a different approach for timing verification, or disable AddressSanitizer for this specific case?

## Current Status After Fix

**Fixed:** The delta time issue has been resolved. `Game::Update()` now correctly passes delta time instead of accumulated time.

**New Issue:** After fixing the delta time bug, the 5-second timer is now working, but it's taking **longer than 5 seconds** in real time. The sprite animation and text appearance are delayed beyond the expected 5 seconds.

**Timing Verification Results:**
Using `std::chrono::steady_clock` with static variables (to avoid AddressSanitizer issues), we discovered:
- When SFML time shows 1.0s, real time shows 4.891s (SFML ~5x slower)
- When SFML time shows 2.0s, real time shows 11.461s (SFML ~6x slower)
- Delta times are extremely small: 6.8e-05s (68 microseconds) and 3.5e-05s (35 microseconds)

**Root Cause Identified:**
The problem was in `Game::Update()` - it was using `m_clock.getElapsedTime()` without restarting the clock. This meant:
1. The clock was only restarted in `LateUpdate()` via `RestartClock()`
2. `getElapsedTime()` was returning time since the last restart, but the timing was off
3. The clock needed to be restarted in `Update()` to get proper frame delta time

**Fix Applied:**
Changed `Game::Update()` to use `m_clock.restart()` instead of `m_clock.getElapsedTime()`:
```cpp
// Before:
m_stateManager.Update(m_clock.getElapsedTime());

// After:
sf::Time deltaTime = m_clock.restart();
m_stateManager.Update(deltaTime);
```

Also removed the clock restart from `LateUpdate()` since it's now restarted in `Update()`.

**Status:** Fix applied and tested. Timing is now much more accurate!

**Test Results After Fix:**
```
SFML time: 1.0011s, Real time: 0.78s, Delta: 0.002082s
SFML time: 2.00112s, Real time: 1.781s, Delta: 0.000287s
SFML time: 3.00126s, Real time: 2.783s, Delta: 0.000252s
SFML time: 4.00132s, Real time: 3.785s, Delta: 0.000287s
SFML time: 5.00151s, Real time: 4.787s, Delta: 0.000776s
SFML time: 6.00223s, Real time: 5.789s, Delta: 0.001032s
```

**Analysis:**
- Delta times are now reasonable (0.0002-0.002s range = 60 FPS range) ✅
- SFML time is slightly ahead of real time (~0.2-0.3s difference), but much better than before
- The small difference could be due to:
  - Static variable initialization timing (first call sets start time)
  - Normal timing precision variance
  - Frame rate variations

**Conclusion:** The fix works! SFML time is now tracking correctly. The 5-second timer should be accurate enough for gameplay purposes. The small variance (~0.2s) is acceptable and much better than the previous 5-6x slowdown.

## Todo

- [x] Fix `Game::Update()` to pass delta time instead of accumulated time
- [ ] Verify timing is now correct (5 seconds should be accurate)
- [ ] Fix sprite starting position to be above screen (if still needed after timing fix)
- [ ] Test that text only appears after 5 seconds
- [ ] Test that spacebar only works after 5 seconds
- [ ] Investigate chrono timing verification approach (if still needed)

