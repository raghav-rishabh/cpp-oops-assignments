#include <iostream>
#include <string>
#include <limits>
#include <cstring>

using namespace std;


// ---------------- Category + Product ----------------

enum class Category {
    ELECTRONICS,
    CLOTHING,
    GROCERY,
    BOOKS,
    TOYS,
    OTHER
};


// Category to string
string categoryToString(Category category) {

    switch (category) {

        case Category::ELECTRONICS:
            return "Electronics";

        case Category::CLOTHING:
            return "Clothing";

        case Category::GROCERY:
            return "Grocery";

        case Category::BOOKS:
            return "Books";

        case Category::TOYS:
            return "Toys";

        default:
            return "Other";
    }
}


// Represents a store item
class Product {

private:
    int productId;
    string name;
    double price;
    int stock;
    Category category;

public:

    // Default constructor
    Product() {
        productId = 0;
        name = "";
        price = 0;
        stock = 0;
        category = Category::OTHER;
    }


    // Constructor
    Product(int id, string productName, double productPrice,
            int initialStock, Category productCategory) {

        productId = id;
        name = productName;
        price = productPrice;
        stock = initialStock;
        category = productCategory;
    }


    // Getters
    int getProductId() const {
        return productId;
    }

    string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    int getStock() const {
        return stock;
    }

    Category getCategory() const {
        return category;
    }


    // Prints product details
    void displayProduct() const {

        cout << "  [Product #" << productId
             << "] " << name
             << " | Category: " << categoryToString(category)
             << " | Price: Rs. " << price
             << " | Stock: " << stock
             << endl;
    }


    // Adds or removes stock
    bool updateStock(int quantityChange) {

        int newStock = stock + quantityChange;

        if (newStock < 0) {
            return false;
        }

        stock = newStock;

        return true;
    }


    // Checks stock availability
    bool checkAvailability(int quantity) const {

        return stock >= quantity;
    }
};



// ---------------- Customer ----------------

class Customer {

private:
    int customerId;
    string name;
    string email;
    string phone;
    string address;

public:

    // Default constructor
    Customer() {

        customerId = 0;
        name = "";
        email = "";
        phone = "";
        address = "";
    }


    // Constructor
    Customer(int id,
             string customerName,
             string customerEmail,
             string customerPhone,
             string customerAddress) {

        customerId = id;
        name = customerName;
        email = customerEmail;
        phone = customerPhone;
        address = customerAddress;
    }


    // Getters
    int getCustomerId() const {
        return customerId;
    }

    string getName() const {
        return name;
    }

    string getEmail() const {
        return email;
    }

    string getPhone() const {
        return phone;
    }

    string getAddress() const {
        return address;
    }


    // Prints customer details
    void displayCustomer() const {

        cout << "  [Customer #" << customerId
             << "] " << name
             << " | Email: " << email
             << " | Phone: " << phone
             << " | Address: " << address
             << endl;
    }


    // Updates customer details
    void updateDetails(string newName,
                       string newEmail,
                       string newPhone,
                       string newAddress) {

        name = newName;
        email = newEmail;
        phone = newPhone;
        address = newAddress;
    }
};



// ---------------- Order-related enums ----------------

enum class OrderStatus {
    PENDING,
    CONFIRMED,
    CANCELLED,
    DELIVERED
};


enum class PaymentStatus {
    PENDING,
    PAID,
    FAILED,
    REFUNDED
};


enum class PaymentMethod {
    CREDIT_CARD,
    UPI,
    CASH
};



// Order status to string
string orderStatusToString(OrderStatus status) {

    switch (status) {

        case OrderStatus::PENDING:
            return "Pending";

        case OrderStatus::CONFIRMED:
            return "Confirmed";

        case OrderStatus::CANCELLED:
            return "Cancelled";

        case OrderStatus::DELIVERED:
            return "Delivered";
    }

    return "Unknown";
}



// Payment status to string
string paymentStatusToString(PaymentStatus status) {

    switch (status) {

        case PaymentStatus::PENDING:
            return "Pending";

        case PaymentStatus::PAID:
            return "Paid";

        case PaymentStatus::FAILED:
            return "Failed";

        case PaymentStatus::REFUNDED:
            return "Refunded";
    }

    return "Unknown";
}



// Payment method to string
string paymentMethodToString(PaymentMethod method) {

    switch (method) {

        case PaymentMethod::CREDIT_CARD:
            return "Credit Card";

        case PaymentMethod::UPI:
            return "UPI";

        case PaymentMethod::CASH:
            return "Cash";
    }

    return "Unknown";
}



// ---------------- Payment info union ----------------

union PaymentInfo {

    char cardLast4[5];
    char upiId[64];

    PaymentInfo() {
        upiId[0] = '\0';
    }
};



// ---------------- Order struct ----------------

struct Order {

    int orderId;
    int customerId;
    int productId;
    int quantity;
    double totalAmount;

    OrderStatus orderStatus;
    PaymentStatus paymentStatus;
    PaymentMethod paymentMethod;

    PaymentInfo paymentInfo;

    bool paymentInfoRecorded;


    // Default constructor
    Order() {

        orderId = 0;
        customerId = 0;
        productId = 0;
        quantity = 0;
        totalAmount = 0;

        orderStatus = OrderStatus::PENDING;
        paymentStatus = PaymentStatus::PENDING;
        paymentMethod = PaymentMethod::CASH;

        paymentInfoRecorded = false;
    }


    // Constructor
    Order(int id,
          int custId,
          int prodId,
          int qty,
          double amount,
          PaymentMethod method) {

        orderId = id;
        customerId = custId;
        productId = prodId;
        quantity = qty;
        totalAmount = amount;

        orderStatus = OrderStatus::PENDING;
        paymentStatus = PaymentStatus::PENDING;
        paymentMethod = method;

        paymentInfoRecorded = false;
    }


    // Prints order details
    void displayOrder() const {

        cout << "  [Order #" << orderId
             << "] Customer #" << customerId
             << " | Product #" << productId
             << " x" << quantity
             << " | Total: Rs. " << totalAmount
             << " | Order Status: "
             << orderStatusToString(orderStatus)
             << " | Payment Status: "
             << paymentStatusToString(paymentStatus)
             << " | Payment Method: "
             << paymentMethodToString(paymentMethod);


        if (paymentInfoRecorded) {

            if (paymentMethod == PaymentMethod::CREDIT_CARD) {

                cout << " | Card ending in: "
                     << paymentInfo.cardLast4;
            }

            else if (paymentMethod == PaymentMethod::UPI) {

                cout << " | UPI ID: "
                     << paymentInfo.upiId;
            }
        }

        cout << endl;
    }
};



// ---------------- OrderManager ----------------

class OrderManager {

private:

    static const int MAX_PRODUCTS = 100;
    static const int MAX_CUSTOMERS = 100;
    static const int MAX_ORDERS = 100;


    // Normal arrays
    Product products[MAX_PRODUCTS];
    Customer customers[MAX_CUSTOMERS];
    Order orders[MAX_ORDERS];


    int productCount;
    int customerCount;
    int orderCount;

    int nextOrderId;


    // Finds product and returns its position
    int findProduct(int productId) {

        for (int i = 0; i < productCount; i++) {

            if (products[i].getProductId() == productId) {
                return i;
            }
        }

        return -1;
    }


    // Finds customer and returns its position
    int findCustomer(int customerId) {

        for (int i = 0; i < customerCount; i++) {

            if (customers[i].getCustomerId() == customerId) {
                return i;
            }
        }

        return -1;
    }


    // Finds order and returns its position
    int findOrder(int orderId) {

        for (int i = 0; i < orderCount; i++) {

            if (orders[i].orderId == orderId) {
                return i;
            }
        }

        return -1;
    }


public:

    // Constructor
    OrderManager() {

        productCount = 0;
        customerCount = 0;
        orderCount = 0;

        nextOrderId = 1;
    }


    // Adds new product
    void addProduct(Product product) {

        if (productCount >= MAX_PRODUCTS) {

            cout << "  [Error] Product limit reached.\n";

            return;
        }

        products[productCount] = product;

        productCount++;
    }


    // Adds new customer
    void addCustomer(Customer customer) {

        if (customerCount >= MAX_CUSTOMERS) {

            cout << "  [Error] Customer limit reached.\n";

            return;
        }

        customers[customerCount] = customer;

        customerCount++;
    }


    // Lists all products
    void displayAllProducts() const {

        cout << "\n--- Products ---\n";

        for (int i = 0; i < productCount; i++) {

            products[i].displayProduct();
        }
    }


    // Lists all customers
    void displayAllCustomers() const {

        cout << "\n--- Customers ---\n";

        for (int i = 0; i < customerCount; i++) {

            customers[i].displayCustomer();
        }
    }


    // Updates existing customer
    bool updateCustomerDetails(int customerId,
                               string name,
                               string email,
                               string phone,
                               string address) {

        int index = findCustomer(customerId);


        if (index == -1) {

            cout << "  [Error] No customer found with ID "
                 << customerId << ".\n";

            return false;
        }


        customers[index].updateDetails(
            name,
            email,
            phone,
            address
        );


        cout << "  Customer #" << customerId
             << " updated successfully.\n";

        return true;
    }


    // Creates a new order
    int createOrder(int customerId,
                    int productId,
                    int quantity,
                    PaymentMethod method) {


        // Check customer
        int customerIndex = findCustomer(customerId);

        if (customerIndex == -1) {

            cout << "  [Error] Cannot create order - no customer found with ID "
                 << customerId << ".\n";

            return -1;
        }


        // Check product
        int productIndex = findProduct(productId);

        if (productIndex == -1) {

            cout << "  [Error] Cannot create order - no product found with ID "
                 << productId << ".\n";

            return -1;
        }


        // Check quantity
        if (quantity <= 0) {

            cout << "  [Error] Cannot create order - quantity must be at least 1.\n";

            return -1;
        }


        // Check stock
        if (!products[productIndex].checkAvailability(quantity)) {

            cout << "  [Error] Cannot create order - '"
                 << products[productIndex].getName()
                 << "' only has "
                 << products[productIndex].getStock()
                 << " unit(s) in stock, but "
                 << quantity
                 << " were requested.\n";

            return -1;
        }


        // Check order limit
        if (orderCount >= MAX_ORDERS) {

            cout << "  [Error] Order limit reached.\n";

            return -1;
        }


        // Remove stock
        products[productIndex].updateStock(-quantity);


        // Calculate total
        double total =
            products[productIndex].getPrice() * quantity;


        // Create order ID
        int newOrderId = nextOrderId++;


        // Create order
        orders[orderCount] = Order(
            newOrderId,
            customerId,
            productId,
            quantity,
            total,
            method
        );


        orderCount++;


        cout << "  Order #" << newOrderId
             << " created successfully. Total: Rs. "
             << total << "\n";


        return newOrderId;
    }


    // Updates order quantity
    bool updateOrderQuantity(int orderId,
                             int newQuantity) {

        int orderIndex = findOrder(orderId);


        if (orderIndex == -1) {

            cout << "  [Error] No order found with ID "
                 << orderId << ".\n";

            return false;
        }


        // Order must be pending
        if (orders[orderIndex].orderStatus !=
            OrderStatus::PENDING) {

            cout << "  [Error] Order #" << orderId
                 << " can only be updated while it is still Pending "
                 << "(current status: "
                 << orderStatusToString(
                        orders[orderIndex].orderStatus
                    )
                 << ").\n";

            return false;
        }


        // Check quantity
        if (newQuantity <= 0) {

            cout << "  [Error] Quantity must be at least 1.\n";

            return false;
        }


        // Find product
        int productIndex =
            findProduct(orders[orderIndex].productId);


        if (productIndex == -1) {

            cout << "  [Error] The product for this order no longer exists.\n";

            return false;
        }


        // Difference in quantity
        int quantityDifference =
            newQuantity - orders[orderIndex].quantity;


        // Check additional stock
        if (quantityDifference > 0 &&
            !products[productIndex].checkAvailability(
                quantityDifference)) {

            cout << "  [Error] Not enough stock to increase quantity - only "
                 << products[productIndex].getStock()
                 << " more unit(s) available.\n";

            return false;
        }


        // Update stock
        products[productIndex].updateStock(
            -quantityDifference
        );


        // Update order
        orders[orderIndex].quantity = newQuantity;


        orders[orderIndex].totalAmount =
            products[productIndex].getPrice()
            * newQuantity;


        cout << "  Order #" << orderId
             << " updated. New total: Rs. "
             << orders[orderIndex].totalAmount
             << "\n";


        return true;
    }


    // Records a payment
    bool makePayment(int orderId,
                     bool paymentSucceeded,
                     string paymentDetail) {

        int orderIndex = findOrder(orderId);


        if (orderIndex == -1) {

            cout << "  [Error] No order found with ID "
                 << orderId << ".\n";

            return false;
        }


        // Cancelled order check
        if (orders[orderIndex].orderStatus ==
            OrderStatus::CANCELLED) {

            cout << "  [Error] Cannot process payment - order #"
                 << orderId
                 << " has already been cancelled.\n";

            return false;
        }


        // Store payment information
        if (orders[orderIndex].paymentMethod ==
            PaymentMethod::CREDIT_CARD) {


            string last4;


            if (paymentDetail.size() >= 4) {

                last4 = paymentDetail.substr(
                    paymentDetail.size() - 4
                );
            }

            else {

                last4 = paymentDetail;
            }


            strncpy(
                orders[orderIndex].paymentInfo.cardLast4,
                last4.c_str(),
                4
            );


            orders[orderIndex].paymentInfo.cardLast4[4] =
                '\0';
        }


        else if (orders[orderIndex].paymentMethod ==
                 PaymentMethod::UPI) {


            strncpy(
                orders[orderIndex].paymentInfo.upiId,
                paymentDetail.c_str(),
                63
            );


            orders[orderIndex].paymentInfo.upiId[63] =
                '\0';
        }


        orders[orderIndex].paymentInfoRecorded = true;


        // Update payment status
        if (paymentSucceeded) {

            orders[orderIndex].paymentStatus =
                PaymentStatus::PAID;
        }

        else {

            orders[orderIndex].paymentStatus =
                PaymentStatus::FAILED;
        }


        cout << "  Payment for order #" << orderId
             << " recorded as "
             << paymentStatusToString(
                    orders[orderIndex].paymentStatus
                )
             << ".\n";


        return true;
    }


    // Confirms an order
    bool confirmOrder(int orderId) {

        int orderIndex = findOrder(orderId);


        if (orderIndex == -1) {

            cout << "  [Error] No order found with ID "
                 << orderId << ".\n";

            return false;
        }


        // Cancelled order check
        if (orders[orderIndex].orderStatus ==
            OrderStatus::CANCELLED) {

            cout << "  [Error] Cannot confirm order #"
                 << orderId
                 << " - it has already been cancelled.\n";

            return false;
        }


        // Payment must be successful
        if (orders[orderIndex].paymentStatus !=
            PaymentStatus::PAID) {

            cout << "  [Error] Cannot confirm order #"
                 << orderId
                 << " - payment status is '"
                 << paymentStatusToString(
                        orders[orderIndex].paymentStatus
                    )
                 << "', but it must be 'Paid' first.\n";

            return false;
        }


        orders[orderIndex].orderStatus =
            OrderStatus::CONFIRMED;


        cout << "  Order #" << orderId
             << " confirmed.\n";


        return true;
    }


    // Cancels an order
    bool cancelOrder(int orderId) {

        int orderIndex = findOrder(orderId);


        if (orderIndex == -1) {

            cout << "  [Error] No order found with ID "
                 << orderId << ".\n";

            return false;
        }


        // Can't cancel delivered order
        if (orders[orderIndex].orderStatus ==
            OrderStatus::DELIVERED) {

            cout << "  [Error] Cannot cancel order #"
                 << orderId
                 << " - it has already been delivered.\n";

            return false;
        }


        // Already cancelled
        if (orders[orderIndex].orderStatus ==
            OrderStatus::CANCELLED) {

            cout << "  [Error] Order #" << orderId
                 << " is already cancelled.\n";

            return false;
        }


        // Return stock
        int productIndex =
            findProduct(orders[orderIndex].productId);


        if (productIndex != -1) {

            products[productIndex].updateStock(
                orders[orderIndex].quantity
            );
        }


        // Cancel order
        orders[orderIndex].orderStatus =
            OrderStatus::CANCELLED;


        // Refund if payment was made
        if (orders[orderIndex].paymentStatus ==
            PaymentStatus::PAID) {

            orders[orderIndex].paymentStatus =
                PaymentStatus::REFUNDED;
        }


        cout << "  Order #" << orderId
             << " cancelled.\n";


        return true;
    }


    // Marks order delivered
    bool markDelivered(int orderId) {

        int orderIndex = findOrder(orderId);


        if (orderIndex == -1) {

            cout << "  [Error] No order found with ID "
                 << orderId << ".\n";

            return false;
        }


        // Must be confirmed
        if (orders[orderIndex].orderStatus !=
            OrderStatus::CONFIRMED) {

            cout << "  [Error] Order #" << orderId
                 << " must be Confirmed before it can be marked Delivered "
                 << "(current status: "
                 << orderStatusToString(
                        orders[orderIndex].orderStatus
                    )
                 << ").\n";

            return false;
        }


        orders[orderIndex].orderStatus =
            OrderStatus::DELIVERED;


        cout << "  Order #" << orderId
             << " marked as delivered.\n";


        return true;
    }


    // Shows single order
    void displayOrder(int orderId) {

        int orderIndex = findOrder(orderId);


        if (orderIndex == -1) {

            cout << "  [Error] No order found with ID "
                 << orderId << ".\n";

            return;
        }


        orders[orderIndex].displayOrder();
    }


    // Shows all orders
    void displayAllOrders() const {

        cout << "\n--- Orders ---\n";


        if (orderCount == 0) {

            cout << "  (no orders yet)\n";

            return;
        }


        for (int i = 0; i < orderCount; i++) {

            orders[i].displayOrder();
        }
    }
};



// ---------------- Console menu ----------------

int readInt(string prompt) {

    int value;

    cout << prompt;


    while (!(cin >> value)) {

        cin.clear();

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );

        cout << "  Please enter a valid number: ";
    }


    cin.ignore(
        numeric_limits<streamsize>::max(),
        '\n'
    );


    return value;
}



string readLine(string prompt) {

    string value;

    cout << prompt;

    getline(cin, value);

    return value;
}



// Loads sample data
void seedSampleData(OrderManager& manager) {

    manager.addProduct(
        Product(
            101,
            "Wireless Mouse",
            799.0,
            25,
            Category::ELECTRONICS
        )
    );


    manager.addProduct(
        Product(
            102,
            "Cotton T-Shirt",
            499.0,
            0,
            Category::CLOTHING
        )
    );


    manager.addProduct(
        Product(
            103,
            "The C++ Primer",
            1299.0,
            10,
            Category::BOOKS
        )
    );


    manager.addProduct(
        Product(
            104,
            "Basmati Rice 5kg",
            650.0,
            40,
            Category::GROCERY
        )
    );


    manager.addCustomer(
        Customer(
            1,
            "Aditi Sharma",
            "aditi@example.com",
            "9876543210",
            "Delhi, India"
        )
    );


    manager.addCustomer(
        Customer(
            2,
            "Rohan Mehta",
            "rohan@example.com",
            "9123456780",
            "Mumbai, India"
        )
    );
}



// Prints menu options
void printMenu() {

    cout << "\n============================================\n";

    cout << " E-COMMERCE ORDER MANAGEMENT SYSTEM\n";

    cout << "============================================\n";

    cout << " 1. View all products\n";
    cout << " 2. View all customers\n";
    cout << " 3. Update customer details\n";
    cout << " 4. Create a new order\n";
    cout << " 5. Update order quantity\n";
    cout << " 6. Make a payment for an order\n";
    cout << " 7. Confirm an order\n";
    cout << " 8. Cancel an order\n";
    cout << " 9. Mark an order as delivered\n";
    cout << "10. View a single order\n";
    cout << "11. View all orders\n";
    cout << " 0. Exit\n";

    cout << "============================================\n";
}



int main() {

    OrderManager manager;

    seedSampleData(manager);


    cout << "Welcome to our ecommerce shop";


    bool running = true;


    while (running) {

        printMenu();


        int choice =
            readInt("Enter your choice: ");


        switch (choice) {

            case 1:

                manager.displayAllProducts();

                break;


            case 2:

                manager.displayAllCustomers();

                break;


            case 3: {

                int id =
                    readInt("Customer ID to update: ");

                string name =
                    readLine("New name: ");

                string email =
                    readLine("New email: ");

                string phone =
                    readLine("New phone: ");

                string address =
                    readLine("New address: ");


                manager.updateCustomerDetails(
                    id,
                    name,
                    email,
                    phone,
                    address
                );

                break;
            }


            case 4: {

                int custId =
                    readInt("Customer ID: ");

                int prodId =
                    readInt("Product ID: ");

                int qty =
                    readInt("Quantity: ");

                int methodChoice =
                    readInt(
                        "Payment method "
                        "(1=Credit Card, 2=UPI, 3=Cash): "
                    );


                PaymentMethod method =
                    PaymentMethod::CASH;


                if (methodChoice == 1) {

                    method =
                        PaymentMethod::CREDIT_CARD;
                }

                else if (methodChoice == 2) {

                    method =
                        PaymentMethod::UPI;
                }


                manager.createOrder(
                    custId,
                    prodId,
                    qty,
                    method
                );

                break;
            }


            case 5: {

                int orderId =
                    readInt("Order ID: ");

                int qty =
                    readInt("New quantity: ");


                manager.updateOrderQuantity(
                    orderId,
                    qty
                );

                break;
            }


            case 6: {

                int orderId =
                    readInt("Order ID: ");

                int successChoice =
                    readInt(
                        "Did the payment succeed? "
                        "(1=Yes, 0=No): "
                    );


                string detail =
                    readLine(
                        "Card last 4 digits / UPI ID "
                        "(leave blank for Cash): "
                    );


                manager.makePayment(
                    orderId,
                    successChoice == 1,
                    detail
                );

                break;
            }


            case 7: {

                int orderId =
                    readInt("Order ID: ");

                manager.confirmOrder(orderId);

                break;
            }


            case 8: {

                int orderId =
                    readInt("Order ID: ");

                manager.cancelOrder(orderId);

                break;
            }


            case 9: {

                int orderId =
                    readInt("Order ID: ");

                manager.markDelivered(orderId);

                break;
            }


            case 10: {

                int orderId =
                    readInt("Order ID: ");

                manager.displayOrder(orderId);

                break;
            }


            case 11:

                manager.displayAllOrders();

                break;


            case 0:

                running = false;

                cout << "Goodbye!\n";

                break;


            default:

                cout << "  Please choose a valid menu option.\n";
        }
    }


    return 0;
}