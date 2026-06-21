Here are **clear, minimal, mechanical renaming rules** you can give Cursor so it can refactor the file **consistently**.

They avoid ambiguity and do not require the AI to “interpret style,” only to apply rules.

---

## Variable Renaming Rules (to apply to this file)

### 1. Member variables → snake_case + trailing underscore

Rename every member variable of `EventManager` and `Binding` from:

```
m_hasFocus → has_focus_
m_currentState → current_state_
m_bindings → bindings_
m_callbacks → callbacks_
m_details → details_
m_events → events_
m_name → name_
m_size → size_
m_mouse → mouse_
m_keyCode → key_code_
m_textEntered → text_entered_
m_mouseWheelDelta → mouse_wheel_delta_
...
```

Rule:
**Remove the `m_` prefix, convert to snake_case, append `_`.**

Example transformation:
`m_mouseWheelDelta` → `mouse_wheel_delta_`

---

### 2. Parameters → snake_case, no prefixes

Rename function parameters like:

```
l_focus → has_focus
l_state → state
l_name → name
l_event → event
l_binding → binding
```

Rule:
**Remove the `l_` prefix and convert to snake_case.**

---

### 3. Local variables → snake_case, no prefixes

Rename locals such as:

```
b_itr → binding
e_itr → event_pair
itr → it
itr2 → it2
keystream → key_stream
keyval → key_val
```

Rule:
**Convert to snake_case, give descriptive names, no prefixes.**

---

### 4. Functions remain unchanged unless requested

Keep functions like `HandleEvent`, `Update`, `LoadBindings`, etc.
Only variables change in this pass.

---

### 5. No Hungarian notation anywhere

Do **not** encode type information in names.

---

### 6. No renaming of enums or enum values

Only rename variables and members.

---

### 7. Replace all member accesses consistently

Example:

Before:

```cpp
m_hasFocus = l_focus;
bind->m_details.m_keyCode = l_event.keyCode;
```

After:

```cpp
has_focus_ = has_focus;
binding->details_.key_code_ = event.key_code;
```

---

## Short version (to paste directly into Cursor)

**Cursor instructions:**

Apply these renaming rules across the file:

1. Rename all member variables: remove `m_` prefix, convert to snake_case, append `_`.
   Example: `m_currentState` → `current_state_`.

2. Rename all parameters: remove `l_` prefix, convert to snake_case.
   Example: `l_event` → `event`.

3. Rename all local variables to snake_case, no prefixes.
   Example: `b_itr` → `binding`.

4. Do not rename enum names or enum values.

5. Do not change function names in this pass.

6. Replace all old names everywhere they appear.
