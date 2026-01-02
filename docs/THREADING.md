# workers

robot worker:
  control_mutex (read)
  state_mutex (write)

world worker:
  state_mutex (read)
  sensor_mutex (write)

reporter worker:
  state_mutex (read)
  state_mutex (write)

mutex is a lock on memory you know you have to share between workers

# virtual keyword

Because C++ is statically compiled and does not assume runtime polymorphism by default, you must mark the destructor virtual to tell the compiler to perform dynamic dispatch when deleting through a base pointer.

# destructors

If a thread’s lifetime can outlive a scope, the owner needs a destructor.
If the lifetime is fully contained e.g. in a function, you don’t.

# protected keyword

Private is actually private to even subclasses, protected is private to any outside classes (shared between subclasses).

# inheritance in c++

Inheritance is different to Python, an object of a subclass contains inside of it a smaller parent object area
So every object you make of a child class creates two objects, one child and inside that child a parent.
+-----------------------------+
| WorkerBase subobject        |
|  - running_                 |
|  - thread_                  |
|  - (vptr)                   |
+-----------------------------+
| RobotWorker object          |
|  - (RobotWorker members)    |
+-----------------------------+

# mutable keyword

mutable variables can be changed even in functions that are const (right const)

void func() const {
    my_mutable_variable += 1;
}
