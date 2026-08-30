# E-Commerce Order Management System

A basic C++ console program made to practice Object Oriented Programming.

## Approach

The program is divided into a few main parts:

- `Product` class stores product details and manages stock.
- `Customer` class stores customer details.
- `Order` stores order and payment information.
- `OrderManager` manages products, customers and orders.
- `enum class` is used for categories, order status, payment status and payment methods.
- `union` is used to store card or UPI payment information.
- Arrays are used to store products, customers and orders.

When an order is created, the program checks whether the customer and product exist and whether enough stock is available.

Stock is reduced when an order is created.

Payment must be successful before an order can be confirmed.

A confirmed order can then be marked as delivered.

## Features

- View all products
- View all customers
- Update customer details
- Create a new order
- Update order quantity
- Make a payment
- Confirm an order
- Cancel an order
- Mark an order as delivered
- View a single order
- View all orders

## Execution

### Compile

```bash
g++ main.cpp -o main
```

### Run

```bash
./main
```

After running, select an option from the menu and follow the instructions.

## Concepts Used

- Classes and Objects
- Constructors
- Encapsulation
- Arrays
- Functions
- Enum Class
- Union
- Loops
- Conditional Statements
- Basic Input and Output

## Note

This is a basic console-based project made for learning C++ and OOP.

The payment system is only a simulation and does not process real payments.