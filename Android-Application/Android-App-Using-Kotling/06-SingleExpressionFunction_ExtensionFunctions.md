### Single-Expression Function

In Kotlin, for simplicity, when a function only returns a **single expression**, you can omit the curly brackets `{}` and directly assign the expression after an `=` symbol. This helps make the code more concise.

Here are three variations of the same function:

1. **Regular function with a block body:**
   ```kotlin
   fun double(x: Int): Int {
       return x * 2
   }
   ```

2. **Single-expression function:**
   ```kotlin
   fun double(x: Int): Int = x * 2
   ```

3. **Type inference in single-expression function:**
   Since Kotlin can infer the return type automatically based on the expression, the return type (`Int` in this case) can be omitted:
   ```kotlin
   fun double(x: Int) = x * 2
   ```

> **Note**: Kotlin does **not** infer return types for functions with block bodies. You need to specify the return type explicitly in such cases.

---

### Extension Functions

**Extension functions** allow you to add new functionality to an existing class **without modifying the class itself** or using inheritance/design patterns. They are a powerful feature in Kotlin, especially useful for utility/helper functions.

#### Key Points:

1. **Extension functions don't modify the original class**. They just allow you to "extend" the class by adding new methods that look like they belong to that class.

2. **Declaration**: You define an extension function by prefixing its name with a **receiver type**—the type of the class you're extending.

   **Syntax:**
   ```kotlin
   fun ReceiverType.functionName(params): ReturnType {
       // Function logic
   }
   ```

3. **`this` keyword**: Inside the extension function, `this` refers to the receiver object, i.e., the instance of the class on which the function is called.

#### Example:

Here’s an example of an extension function for the `String` class:

```kotlin
fun String.addGreeting(): String {
    return "Hello, $this!"
}

fun main() {
    val name = "Mina"
    println(name.addGreeting())  // Output: Hello, Mina!
}
```

In this example, we extend the `String` class by adding a new function `addGreeting()`. When called on any `String` object, it adds a greeting to the string.

---

### Static Dispatch in Extension Functions

1. **Statically Dispatched**: Extension functions are **dispatched statically**, meaning they do **not** behave like virtual functions that depend on the actual type of the object at runtime. Instead, they are resolved based on the type of the expression at **compile time**.

   ```kotlin
   open class Animal
   class Dog : Animal()

   fun Animal.makeSound() = "Animal Sound"
   fun Dog.makeSound() = "Bark"

   fun main() {
       val animal: Animal = Dog()
       println(animal.makeSound())  // Output: Animal Sound
   }
   ```

   Here, even though `animal` is actually a `Dog`, the extension function for `Animal` is called, because extension functions are **not virtual**.

2. **Member Functions Take Precedence**: If a class has a **member function** and an **extension function** with the same name and applicable arguments, the **member function** takes precedence over the extension function.

   ```kotlin
   class Example {
       fun display() = "Member Function"
   }

   fun Example.display() = "Extension Function"

   fun main() {
       val ex = Example()
       println(ex.display())  // Output: Member Function
   }
   ```

3. **Overloading**: Extension functions can overload member functions if they have the **same name but different signatures** (e.g., different parameters).

   ```kotlin
   class Example {
       fun display() = "Member Function"
   }

   fun Example.display(message: String) = "Extension Function with $message"

   fun main() {
       val ex = Example()
       println(ex.display())          // Output: Member Function
       println(ex.display("Hello"))   // Output: Extension Function with Hello
   }
   ```

This demonstrates how extension functions can enhance functionality without altering the class itself, making code more flexible and readable.