
# **Overloaded Methods**

**Purpose**:
Overloading allows multiple methods in the same class to share the same name, differing only by their parameter lists (number, type, or both). This provides a way to handle different types of inputs while keeping the method name consistent, thus improving code readability and usability.

#### **Key Points**:

1. **Argument List**:
   - **Overloaded methods MUST change the argument list**: The methods must differ in the type, number, or order of parameters.
   
2. **Return Type**:
   - **Overloaded methods CAN change the return type**: While not necessary, the return type of an overloaded method can differ from the original.
   
3. **Access Modifier**:
   - **Overloaded methods CAN change the access modifier**: Overloaded methods can have different levels of access, such as `public`, `protected`, `private`, or package-private.
   
4. **Exceptions**:
   - **Overloaded methods CAN declare new or broader checked exceptions**: Unlike overriding, where the exceptions are restricted, overloaded methods can throw different exceptions, including broader checked exceptions.

### **Legal Overloads**

#### **Example of a Method to Overload**:
```java
public void changeSize(int size, String name, float pattern) { }
```

#### **Legal Overloads**:
- **Different Number of Parameters**:
  ```java
  public void changeSize(int size, String name) { }
  ```

- **Different Types of Parameters**:
  ```java
  public int changeSize(int size, float pattern) { }
  ```

- **Additional Exceptions**:
  ```java
  public void changeSize(float pattern, String name) throws IOException { }
  ```

### **Distinguishing Overloading from Overriding**

- **Overloading Across Classes**:
  Overloading can occur within a single class or across a class hierarchy. For instance, a subclass can overload a method defined in its superclass, adding a new method with a different parameter list while keeping the original.

- **Example**:
  ```java
  public class Foo {
      public void doStuff(int y, String s) { }
      public void moreThings(int x) { }
  }

  class Bar extends Foo {
      public void doStuff(int y, long s) throws IOException { }
  }
  ```
  In this case, `Bar` overloads `doStuff()` from `Foo` by changing the parameter types, and the added exception is legal because it’s a different method (not overriding the original).

### **Invoking Overloaded Methods**

When a method is invoked, the Java compiler determines which version of an overloaded method to call based on the arguments provided at compile-time. The object type at runtime does not affect this decision; it’s purely based on the reference type of the arguments.

#### **Example**:
```java
class Adder {
    public int addThem(int x, int y) {
        return x + y;
    }

    public double addThem(double x, double y) {
        return x + y;
    }
}

public class TestAdder {
    public static void main(String[] args) {
        Adder a = new Adder();
        int result = a.addThem(27, 3);        // Calls addThem(int, int)
        double doubleResult = a.addThem(22.5, 9.3); // Calls addThem(double, double)
    }
}
```

### **Overloaded Methods with Object References**

If methods are overloaded to accept different object types (e.g., `Animal` and `Horse`), the compiler will select the method based on the reference type provided at compile-time, not the actual object type at runtime.

#### **Example**:
```java
class Animal { }
class Horse extends Animal { }
class UseAnimals {
    public void doStuff(Animal a) {
        System.out.println("In the Animal version");
    }
    public void doStuff(Horse h) {
        System.out.println("In the Horse version");
    }
    public static void main(String[] args) {
        UseAnimals ua = new UseAnimals();
        Animal animalRefToHorse = new Horse();
        ua.doStuff(animalRefToHorse);  // Outputs: "In the Animal version"
    }
}
```

### **Polymorphism and Overloading**

Polymorphism does not influence which overloaded method is invoked. It’s entirely determined by the reference type at compile-time. However, once inside the method, polymorphism can affect how overridden methods are called.

#### **Example of Combined Overloading and Overriding**:
```java
public class Animal {
    public void eat() {
        System.out.println("Generic Animal Eating Generically");
    }
}

public class Horse extends Animal {
    @Override
    public void eat() {
        System.out.println("Horse eating hay");
    }
    public void eat(String s) {
        System.out.println("Horse eating " + s);
    }
}
```
- **Method Invocation**:
  ```java
  Animal a = new Animal();
  a.eat(); // Generic Animal Eating Generically

  Horse h = new Horse();
  h.eat(); // Horse eating hay

  Animal ah = new Horse();
  ah.eat(); // Horse eating hay (Polymorphism in action)

  h.eat("Apples"); // Horse eating Apples (Overloaded method invoked)
  ```
![image](https://github.com/user-attachments/assets/0ef5b8a0-fdd9-4a95-867e-0e3e4df54f69)

### **Key Differences Between Overloading and Overriding**

1. **Arguments**:
   - **Overloading**: Must change.
   - **Overriding**: Must not change.

2. **Return Type**:
   - **Overloading**: Can change.
   - **Overriding**: Can’t change, except for covariant returns.

3. **Exceptions**:
   - **Overloading**: Can change.
   - **Overriding**: Must reduce, eliminate, or not introduce new/broader checked exceptions.

4. **Access**:
   - **Overloading**: Can change.
   - **Overriding**: Must not be more restrictive.

5. **Invocation**:
   - **Overloading**: Determined by reference type at compile time.
   - **Overriding**: Determined by object type at runtime.







### Key Points:
1. **Overloading vs. Overriding:**
   - **Overloading**: Occurs when two or more methods in the same class have the same name but different parameters (either in number, type, or both).
   - **Overriding**: Occurs when a subclass provides a specific implementation of a method that is already defined in its superclass. The method in the subclass must have the same signature (name, parameters) and return type.

2. **Example Explanation:**
   ```java
   public class Foo {
       void doStuff() { }
   }

   class Bar extends Foo {
       void doStuff(String s) { }
   }
   ```

   - In this example, the `Foo` class has a method `doStuff()` with no arguments.
   - The `Bar` class extends `Foo` and adds an overloaded method `doStuff(String s)` with a single `String` argument.
   - **Important:** The `Bar` class does not override `doStuff()`; it only overloads it by adding a new method with a different parameter.

3. **Method Invocation:**
   - **Reference of type `Foo`:** If you have a reference of type `Foo`, you can only call the no-argument version of `doStuff()`, because that's the only version `Foo` knows about.
   - **Reference of type `Bar`:** If you have a reference of type `Bar`, you can call either `doStuff()` (inherited from `Foo`) or `doStuff(String s)` (defined in `Bar`), because `Bar` has access to both methods.

### Example Scenarios:
```java
Foo foo = new Foo();
foo.doStuff();  // Calls Foo's doStuff()

Bar bar = new Bar();
bar.doStuff();  // Calls Foo's doStuff() since it's inherited by Bar
bar.doStuff("Hello");  // Calls Bar's overloaded doStuff(String s)
```

- **Reference Casting:**
  ```java
  Foo fooRef = new Bar();
  fooRef.doStuff();  // Calls Foo's doStuff(), because the reference type is Foo
  // fooRef.doStuff("Hello");  // Compile-time error: Foo doesn't know about the String version
  ```

### Conclusion:
The example emphasizes that overloading and overriding are different concepts. Overloading allows a class to have multiple methods with the same name but different parameters, while overriding involves providing a new implementation for a method inherited from a superclass. Understanding this distinction is crucial to avoid confusion when dealing with polymorphism and method calls in Java.

![image](https://github.com/user-attachments/assets/454c3d45-d7eb-45bd-b479-33507ed65f2e)

