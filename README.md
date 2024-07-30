# Interpreter Implementation: Elements of Declarative and Functional Styles

## Features

The interpreter supports the following features:
- Basic Arithmetic Operations: The interpreter can handle standard arithmetic operations, including addition (+), subtraction (-), multiplication (*), and division (/).
- Function Definitions: Users can define functions with two parameters. 
- The interpreter comes with built-in functions such as:
    - pow(a, b): Computes a raised to the power of b.
    - abs(x): Returns the absolute value of x.
    - max(a, b): Returns the maximum of a and b.
    - min(a, b): Returns the minimum of a and b.
- Expression Combinations: The interpreter can evaluate complex expressions that combine arithmetic operations and function calls.
- Function Calls: Users can call functions, including built-in and user-defined functions, with specific arguments.
- Variables: The interpreter allows users to define variables and use them in expressions. For example, var a = pow(2, 4) assigns the value 16 to the variable a.

## Usage Examples

#### Basic Arithmetic:
```python
> 5 + 3 * 2
> 11
```
#### Function Calls:
```python
> max(5, 2)
> 5
> min(3, 4)
> 3
```
#### Complex Expressions:
```python
> max(min(3 * 2, 4), 2)
> 4
```
#### Variables:
```python
> var a = max(min(3 * 2, 2), 2)
> a + 3
> 5
```
#### User-Defined Functions:
```python
> def myfunc(a, b) { min(a, b) + max(a, b) }
> myfunc(3, 4)
> 7
```

## Testing

To test the interpreter, a Python script is provided. This script executes the interpreter with various input combinations and verifies the correctness of the outputs. The test cases cover basic arithmetic operations, function calls, complex expressions, variable assignments, and user-defined functions.

## Conclusion

This project demonstrates the implementation of a simple interpreter in C++ with a focus on declarative and functional programming styles. The interpreter provides a platform for evaluating arithmetic expressions, managing variables, and defining and calling functions, making it a versatile tool for both educational and practical applications in programming languages and interpreters.
