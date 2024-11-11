
### 1. **Passing Lambdas to a Function**
A lambda is simply an anonymous function that can be passed as an argument to other functions. Let's start with how to pass a single lambda to a function.

```kotlin
// Define a function that takes a lambda as a parameter
fun doOperation(x: Int, operation: (Int) -> Int): Int {
    return operation(x)
}

// Call the function with a lambda
val result = doOperation(5) { it * 2 }
println(result) // Output: 10
```

Here, the lambda `{ it * 2 }` is passed as the second argument to `doOperation`. This lambda takes an `Int` and returns its double.

### 2. **Returning Multiple Arguments from a Lambda**
A lambda can only return one value, but you can return multiple values by using a **Pair** or a **data class** to hold the results.

```kotlin
// Return a Pair from a lambda
val calculate = { x: Int, y: Int -> Pair(x + y, x * y) }
val (sum, product) = calculate(4, 5)
println("Sum: $sum, Product: $product") // Output: Sum: 9, Product: 20
```

If you want more complex data, you can create a data class:

```kotlin
data class Result(val sum: Int, val product: Int)

// Use a data class to return multiple values
val complexCalculation = { x: Int, y: Int -> Result(x + y, x * y) }
val result = complexCalculation(4, 5)
println(result) // Output: Result(sum=9, product=20)
```

### 3. **Passing More Than One Lambda to a Function**
You can pass multiple lambdas to a function by defining multiple lambda parameters in the function signature.

```kotlin
// Function that accepts two lambdas
fun executeOperations(x: Int, add: (Int) -> Int, multiply: (Int) -> Int): Pair<Int, Int> {
    return Pair(add(x), multiply(x))
}

// Pass two different lambdas
val result = executeOperations(5, { it + 3 }, { it * 2 })
println(result) // Output: (8, 10)
```

### 4. **Passing Lambda and Anonymous Function to the Same Function**
You can combine lambdas and anonymous functions in the same function call. Lambdas are usually shorter, while anonymous functions allow you to define a more complex block of logic.

```kotlin
// Function that takes both a lambda and an anonymous function
fun performActions(
    x: Int,
    lambda: (Int) -> Int,
    anonymousFunction: (Int) -> Int
): Pair<Int, Int> {
    return Pair(lambda(x), anonymousFunction(x))
}

// Lambda expression
val lambda = { it * 2 }

// Anonymous function
val anonymousFunction = fun(x: Int): Int {
    return x + 3
}

val result = performActions(5, lambda, anonymousFunction)
println(result) // Output: (10, 8)
```

### 5. **Single Parameter Lambdas and `it` Keyword**
If your lambda has a single parameter, Kotlin allows you to skip specifying the parameter and refer to it using `it`.

```kotlin
val double = { it: Int -> it * 2 }
println(double(4)) // Output: 8
```

### 6. **Using Lambdas with Multiple Parameters**
Lambdas can have multiple parameters, and you define them inside the curly braces:

```kotlin
val add: (Int, Int) -> Int = { a, b -> a + b }
val result = add(3, 4)
println(result) // Output: 7
```

### 7. **Infix Notation with Lambdas**
When you use `infix`, you can call a lambda like an operator. Here's an example of an infix function:

```kotlin
infix fun Int.add(b: Int): Int = this + b
val sum = 5 add 3
println(sum) // Output: 8
```

### 8. **Returning Lambdas from Functions**
You can return a lambda from a function as well:

```kotlin
fun getOperation(): (Int) -> Int {
    return { it * 2 } // Returns a lambda that multiplies the input by 2
}

val operation = getOperation()
println(operation(5)) // Output: 10
```

### 9. **Higher-Order Functions (Passing Functions as Arguments or Returning Them)**
A **higher-order function** is one that takes another function as a parameter or returns a function.

```kotlin
fun higherOrderFunction(x: Int, operation: (Int) -> Int): Int {
    return operation(x)
}

val doubled = higherOrderFunction(5) { it * 2 }
println(doubled) // Output: 10
```

### Summary
- **Single Parameter**: `{ it -> it * 2 }` can be simplified to `{ it * 2 }`.
- **Multiple Lambdas**: You can pass multiple lambdas as arguments to functions.
- **Returning Multiple Values**: Use a `Pair` or `data class` to return multiple values from a lambda.
- **Anonymous Functions and Lambdas**: You can mix both when passing to functions.
- **Higher-Order Functions**: You can pass or return functions (including lambdas) as parameters.

These are some common scenarios for working with lambdas in Kotlin. Let me know if you'd like to explore more specific examples or other aspects!