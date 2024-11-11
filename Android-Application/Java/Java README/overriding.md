

# Java Polymorphism, Method Overriding, and Overloading

## **Polymorphism in Java**

### **Definition**
Polymorphism in Java allows objects of different classes to be treated as objects of a common superclass. It provides the ability to invoke methods on an object without knowing its exact subclass type at compile time. Polymorphism is achieved through method overriding and interface implementation.

### **Key Concepts**
1. **IS-A Relationship**: Polymorphism is based on inheritance. An object is considered polymorphic if it passes more than one IS-A test. For instance, a `PlayerPiece` object is:
   - An instance of `PlayerPiece`
   - An instance of `GameShape` (its superclass)
   - An instance of `Object` (the root class of all Java classes)
   - An instance of any interface it implements, such as `Animatable`

2. **Reference Variables**:
   - A reference variable can be of only one type.
   - The reference variable's type determines which methods can be invoked.
   - A reference variable can reference objects of its type or any subclass of its type.

3. **Method Invocation**:
   - The method that can be invoked is determined at compile-time based on the reference type.
   - However, the actual method that gets executed is determined at runtime based on the object's actual class. This is known as **dynamic method dispatch**.

### **Example**:
```java
class GameShape {
    public void displayShape() {
        System.out.println("Displaying shape");
    }
}

interface Animatable {
    void animate();
}

class PlayerPiece extends GameShape implements Animatable {
    public void movePiece() {
        System.out.println("Moving game piece");
    }
    
    @Override
    public void animate() {
        System.out.println("Animating...");
    }
}

public class PolymorphismExample {
    public static void main(String[] args) {
        PlayerPiece player = new PlayerPiece();
        Object o = player;
        GameShape shape = player;
        Animatable mover = player;
        
        // Method calls
        shape.displayShape();  // Legal, as GameShape has displayShape()
        mover.animate();        // Legal, as Animatable has animate()
    }
}
```

### **Key Points**:
- `PlayerPiece` can be treated as `Object`, `GameShape`, `PlayerPiece`, or `Animatable`.
- Only methods in the reference type (`GameShape` or `Animatable`) can be called, not methods specific to `PlayerPiece`.

## **Method Overriding**

### **Definition**
Method overriding occurs when a subclass provides a specific implementation of a method that is already defined in its superclass.

### **Rules for Overriding**:
1. **Same Signature**: The overriding method must have the same name and argument list as the method in the superclass.
2. **Return Type**:
   - The return type must be the same or a subtype (covariant return) of the method in the superclass.
3. **Access Level**:
   - The overriding method cannot be less accessible than the method it overrides.
   - For example, a public method cannot be overridden with a protected or private method.
4. **Exceptions**:
   - The overriding method cannot throw broader checked exceptions than the method it overrides.
   - It can throw narrower or fewer checked exceptions, or even no exceptions at all.
5. **Instance Methods**:
   - Only instance methods can be overridden; static methods cannot be overridden (they can be hidden).
6. **final Methods**:
   - A final method cannot be overridden.

### **Examples**:

#### **Basic Overriding Example**:
```java
class Animal {
    public void eat() {
        System.out.println("Generic Animal Eating Generically");
    }
}

class Horse extends Animal {
    @Override
    public void eat() {
        System.out.println("Horse eating hay, oats, and horse treats");
    }
}

public class TestAnimals {
    public static void main(String[] args) {
        Animal a = new Animal();
        Animal b = new Horse(); // Animal reference, but a Horse object

        a.eat(); // Calls Animal's eat()
        b.eat(); // Calls Horse's eat() due to dynamic method dispatch
    }
}
```

#### **Access Modifier Example**:
```java
class Animal {
    protected void eat() {
        System.out.println("Animal is eating");
    }
}

class Dog extends Animal {
    @Override
    public void eat() {  // Legal override, can make it public
        System.out.println("Dog is eating");
    }
}

class Cat extends Animal {
    @Override
    private void eat() {  // Illegal override, access modifier more restrictive
        System.out.println("Cat is eating");
    }
}
```

### **Invoking Superclass Method**:
If you want to use the superclass's version of a method in addition to the subclass's version, you can use the `super` keyword.
```java
class Animal {
    public void eat() {
        System.out.println("Animal is eating");
    }
}

class Dog extends Animal {
    @Override
    public void eat() {
        super.eat(); // Calls Animal's eat() method
        System.out.println("Dog is eating");
    }
}
```

### **Final Methods**:
A `final` method in a superclass cannot be overridden:
```java
class Animal {
    public final void sleep() {
        System.out.println("Animal is sleeping");
    }
}

class Dog extends Animal {
    @Override
    public void sleep() {  // Compile-time error
        System.out.println("Dog is sleeping");
    }
}
```

### **Static Methods and Overriding**:
Static methods are not overridden but hidden:
```java
class Animal {
    public static void doSomething() {
        System.out.println("Animal does something");
    }
}

class Dog extends Animal {
    public static void doSomething() {  // Hides the static method in Animal
        System.out.println("Dog does something");
    }
}
```

## **Method Overloading**

### **Definition**
Method overloading occurs when two or more methods in the same class have the same name but different parameters (different type, number, or both).

### **Rules for Overloading**:
1. **Different Parameter List**: The overloaded methods must have different parameters. It can differ in:
   - Number of parameters.
   - Type of parameters.
   - Order of parameters.
2. **Return Type**:
   - Overloaded methods can have the same or different return types.
3. **Access Modifiers**:
   - Overloaded methods can have different access modifiers.
4. **Exceptions**:
   - Overloaded methods can throw different exceptions.

### **Examples**:

#### **Basic Overloading Example**:
```java
class Example {
    public void print(int a) {
        System.out.println("Integer: " + a);
    }

    public void print(String b) {
        System.out.println("String: " + b);
    }
    
    public void print(int a, String b) {
        System.out.println("Integer: " + a + ", String: " + b);
    }
}

public class TestOverloading {
    public static void main(String[] args) {
        Example ex = new Example();
        ex.print(10);          // Calls print(int)
        ex.print("Hello");     // Calls print(String)
        ex.print(10, "Hello"); // Calls print(int, String)
    }
}
```

### **Overloading vs. Overriding**:
- **Overloading**: Same method name, different parameters, within the same class.
- **Overriding**: Same method name, same parameters, but in a subclass.

### **Common Mistakes**:
- Confusing method overloading with method overriding.
- Expecting overloaded methods to work polymorphically like overridden methods.


![image](https://github.com/user-attachments/assets/09ba715a-e481-46be-b039-bab2869339fd)
