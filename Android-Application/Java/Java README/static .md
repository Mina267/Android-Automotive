# Static Variables and Methods in Java

#### What Are Static Members?
In Java, the `static` modifier can be applied to variables and methods, profoundly affecting their behavior. Static members belong to the class itself rather than to any particular instance of the class. This means:

- **Static Variables**: There is only one copy of the variable, shared across all instances of the class.
- **Static Methods**: These can be invoked without creating an instance of the class.

#### When to Use Static Members?
Consider scenarios where:

1. **Utility Methods**: If a method’s behavior does not depend on instance-specific data, you can make it static. This avoids the need to create unnecessary objects.

   ```java
   public class Utility {
       public static int getRandomNumber() {
           return (int) (Math.random() * 100);
       }
   }
   ```

2. **Class-wide Data**: If you need to maintain data that is shared across all instances, such as a counter for how many objects have been created, static variables are appropriate.

   ```java
   public class Frog {
       static int frogCount = 0;

       public Frog() {
           frogCount++;
       }
   ```

#### Accessing Static Members

1. **Static Variables**: You can access them directly using the class name.

   ```java
   System.out.println(Frog.frogCount);
   ```

2. **Static Methods**: Similarly, static methods can be invoked using the class name.

   ```java
   int randomNum = Utility.getRandomNumber();
   ```

#### Example: Counting Instances with Static Variables
Here's an example demonstrating how to use a static variable to count the number of instances created:

```java
public class Frog {
    static int frogCount = 0; // Static variable shared by all instances

    public Frog() {
        frogCount++; // Increment the count each time a new Frog is created
    }

    public static void main(String[] args) {
        new Frog();
        new Frog();
        new Frog();
        System.out.println("Frog count is now " + frogCount); // Outputs: Frog count is now 3
    }
}
```

#### Common Mistakes: Static Context
A common error occurs when trying to access instance variables from a static context. For instance, the following code will not compile:

```java
public class Foo {
    int x = 3;

    public static void main(String[] args) {
        System.out.println("x is " + x); // Compiler Error: Cannot make a static reference to the non-static field x
    }
}
```

This error occurs because `main()` is static and thus does not have access to instance variables like `x`.

#### Static Method and Variable Access
Static methods can only access static variables and other static methods directly. They cannot access instance variables or methods unless they do so through an object reference:

```java
public class TestStatic {
    static int staticVar = 10;
    int instanceVar = 20;

    public static void staticMethod() {
        System.out.println("Static var: " + staticVar);
        // System.out.println("Instance var: " + instanceVar); // Error
    }

    public void instanceMethod() {
        System.out.println("Instance var: " + instanceVar);
    }

    public static void main(String[] args) {
        staticMethod(); // Access static method directly

        TestStatic ts = new TestStatic();
        ts.instanceMethod(); // Access instance method through an object
    }
}
```

#### Redefining Static Methods in Subclasses
Static methods cannot be overridden but can be redefined in a subclass. However, the method called is determined by the reference type, not the object type:

```java
class Animal {
    static void doStuff() {
        System.out.print("Animal ");
    }
}

class Dog extends Animal {
    static void doStuff() {
        System.out.print("Dog ");
    }
}

public class TestAnimals {
    public static void main(String[] args) {
        Animal[] animals = {new Animal(), new Dog(), new Animal()};
        for (Animal a : animals) {
            a.doStuff(); // Outputs: Animal Animal Animal
        }
    }
}
```

The `doStuff()` method in this example is redefined in `Dog`, but when invoked, it calls the `Animal` version because static methods are not polymorphic.
