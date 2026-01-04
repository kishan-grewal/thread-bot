### const left const right
const int fn() const { }
  ^                ^
  │                └── "I won't modify my own members"
  └── "I return something you can't modify"

### making variables constant
const must be done at creation, you can't make something const later
the key insight being that when you pass a var into a function, you create an
rvalue, the var inside the function is its own entity

### passing into functions
pass primitives into functions simply, pass larger objects as const . & (const reference)

### hpp free functions
inline functions (hpp functions) should never be more than roughly 30 lines
this only applies to free functions (not inside a struct or class)

### push_back versus emplace_back
push_back for primitives and small objects
emplace_back for large objects (constructs in-place)

### initializer lists
Vec2(float x, float y) : x(x), y(y) {}
  └── faster than assignment in constructor body
  └── direct initialization, not copy then assign