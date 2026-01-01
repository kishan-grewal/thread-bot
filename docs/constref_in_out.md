**Passing IN:**
```cpp
void foo(const RobotState& state) {  // ref for efficiency, const for safety
  // read states
}

void bar(RobotState state) {  // copy, can modify locally without affecting caller
  state.pose.x = 999.0f;  // only modifies local copy
}
```

**Returning OUT:**
```cpp
const RobotState& get_state() const {  // ref for efficiency, const for safety
  return state_;
}

RobotState get_state_copy() const {  // copy, caller can modify it
  return state_;  // automatically copied
}
```

**When you need to edit:**
```cpp
// If you need to modify the returned state:
RobotState my_state = robot.get_state_copy();  // get a copy
my_state.pose.x = 999.0f;  // modify the copy, doesn't affect robot
```

**In Robot's case:**
- `get_state()` returns `const RobotState&` — you expose live data, but read-only
- Only `integrate()` can modify state_ — the *intended* way to change physics

So: **ref + const for read-only access, plain value for modifiable copies.**