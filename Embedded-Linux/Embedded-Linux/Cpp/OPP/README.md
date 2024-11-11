# **OOP**
### 1- Class
```
I- Function
II- Atribute -> variable
```
### 2- Object or instance

```c++
class Dio {
    struct register Dio;
puplic:
    set_PinDirection();
    set_PinMode();
    set_PinValue();
}

int main(void)
{
    Dio ARM();
    return 0;
}
```

## A- Core Concept
### Encapsulation
    Global vaariable -> forbidden
    Oppose the concept of OPP
    share resource in the code

### Inheritence
    class Dio
    add functionality for ARM
    properties main class (Dio)

```c++
class ARM : puplic Dio
```
### **Polymorphism**
* #### Dynamic Polymorphism

* #### Static Polymorphism
```c++
int add(int, int);
float add(float, float);
```

## B- Principles
### 1- Modularity
```
I- Debug
II- maintenance
```
### 2- Abstruction
`input` ---> `output`

---

# **Constructor**
```c++
class Dio
{
    int x = 0; // Default value
    int y = 5;
    puplic:
    /* Default constructor */
    Dio();
    /* Parametrize constructor */
    Dio(int a, int b)
    {
        x = a;
        y = b;
    }

}
```

### 1- Default constructor `implicit`
* Compiler who generation it 
* Attributes `zeros` compiler dependent
* Add `default value` to variable value will be init with it
* Will not created if `Parametrize constructor` is implemented
### 2- Default constructor `explicit`
* Programer implement the default constructor
### 3- Parametrize constructor 
* Programer implement the Parametrize constructor
```c++
class Dio
{
    struct Dio *register;
    puplic:
    /* Parametrize constructor */
    void Dio (struct Dio *reg)
        {
            register = reg;
        }
}
```
---
# **Destructor**
* Memeory Leak, close file, close connection
* Invoke at `End of scope` or `Call delete`
```c++


int main (void)
{

    int *add = (int)malloc(Size); // HEAP
    free(add) // Deallocation

    Dio D1;
    Dio *D2;
    /* code */
    delete D2; // Destructor for D2 will Invoke 
    /* code */

    return 0;

} // Destructor for D1 will Invoke

```

## **Member initialization list** `in class`

```c++
class Dio
{
    const int x = 0; // Default value
    int y = 5;
    puplic:
    /* default constructor */
    /* Intialization of varaible x and y will depend on the arragment in    creation.
     * So X will initialized first then y.
     */
    Dio() x(5), y(0) {} // No Compiler Error Assign to constant value

    /* default constructor */
    Dio() {
        x = 5; // Compiler Error Assign to constant value
    }


    /* Parametrize constructor */
    Dio(int x, int y): x(x), y(y) {}

}
```

# **Delegate constructor**

```c++
class Dio
{
    const int x;
    int y;
    puplic:
    /* default constructor */
    Dio() x(0), y(0) {}

    /* Parametrize constructor */
    Dio(int x, int y): Dio() {}

}
```

# **Copy constructor**
* Compiler will synthesize `Copy constructor` if you did not create one.
* `Default Copy constructor` make Shallow copy.
* Can initialize member variable.

```c++
class Dio
{
    int *ptr;
    int x;
    int y;
    puplic:

    /* default constructor */
    Dio() x(0), y(0) {
        ptr = (int*)malloc(5);
    }

    /* Parametrize constructor */
    Dio(int x, int y): Dio() { }

    /* Copy constructor */
    /* const means did not change the object */
    Dio(const Dio &CopyObject): Dio() { // Invoke Default to allocate new memory
        CopyObject.x = x;
        CopyObject.y = y;
    }
    

    /* Destructor */
    ~Dio() {
        free(ptr);
    }
}
```
---
# **Static**
## Static variable in class 
* Store in `.data`.
* Create at the start of the program regardless create an object or not.
* Shared amoung all object of the class. 
* `Dio::mystatic = 1;`
* Cannot intialize **inside** the class body.
* intialize **outside** the class.
* **Member function** and **special Member function** can access the static variable.

```c++
Dio::mystatic = 1;

class Dio
{
    static int myStatic;
}
```

## Static variable in class 
* Cannot access **Member functions** or **Member variables**.

```c++
Dio::mystatic = 1;

class Dio
{
    static int myStatic;
    static int myStaticFunction(void){
        x = 0; // Compiler Error
        y = 0; // Compiler Error
    }
}
```
