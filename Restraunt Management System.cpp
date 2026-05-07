#include <iostream>
#include <stdexcept>
#include <string>
#include <map>
#include <fstream>
#include <tuple>

using namespace std;

class Ingredient
{
private:
    string name;
    int quantity;

public:
    Ingredient(const string& name, int quantity)
    {
        this->name = name;
        this->quantity = quantity;
    }

    string getName() const
    {
        return name;
    }

    int getQuantity() const
    {
        return quantity;
    }

    void use(int amount)
    {
        if (quantity >= amount)
        {
            quantity -= amount;
            cout << "Used " << amount << " units of " << name << endl;
        }
        else
        {
            throw runtime_error("Not enough " + name + " in stock");
        }
    }

    void restock(int amount)
    {
        quantity += amount;
        cout << "Restocked " << amount << " units of " << name << endl;
    }
};

class Kitchen
{
private:
    map<string, Ingredient> ingredients;

public:
    Ingredient& getIngredient(const string& name)
    {
        return ingredients.at(name);
    }

    void addIngredient(const string& name, int quantity)
    {
        ingredients.emplace(name, Ingredient(name, quantity));
    }

    void useIngredient(const string& name, int amount)
    {
        getIngredient(name).use(amount);
    }

    void restockIngredient(const string& name, int amount)
    {
        getIngredient(name).restock(amount);
    }

    const map<string, Ingredient>& getIngredients() const
    {
        return ingredients;
    }
};

class Manager
{
private:
    Kitchen kitchen;
    string password = "admin";

public:
    bool authenticate(const string& pwd) const
    {
        return pwd == password;
    }

    void addIngredient(const string& name, int quantity)
    {
        kitchen.addIngredient(name, quantity);
    }

    void useIngredient(const string& name, int amount)
    {
        kitchen.useIngredient(name, amount);
    }

    void restockIngredient(const string& name, int amount)
    {
        kitchen.restockIngredient(name, amount);
    }

    void displayIngredients() const
    {
        cout << "Ingredients in stock:" << endl;

        for (const auto& pair : kitchen.getIngredients())
        {
            cout << "Name: " << pair.first
                 << ", Quantity: " << pair.second.getQuantity() << endl;
        }
    }

    void checkInEmployee(const string& employeeName)
    {
        ofstream employeeDataFile("employee_data.txt", ios::app);

        if (employeeDataFile.is_open())
        {
            employeeDataFile << employeeName
                             << " checked in at: 08:00" << endl;

            employeeDataFile.close();
        }
        else
        {
            cerr << "Unable to open file!" << endl;
        }
    }

    void checkOutEmployee(const string& employeeName)
    {
        ofstream employeeDataFile("employee_data.txt", ios::app);

        if (employeeDataFile.is_open())
        {
            employeeDataFile << employeeName
                             << " checked out at: 17:00" << endl;

            employeeDataFile.close();
        }
        else
        {
            cerr << "Unable to open file!" << endl;
        }
    }

    void displayEmployeeDetails() const
    {
        ifstream employeeDataFile("employee_data.txt");

        if (employeeDataFile.is_open())
        {
            string line;

            while (getline(employeeDataFile, line))
            {
                cout << line << endl;
            }

            employeeDataFile.close();
        }
        else
        {
            cerr << "Unable to open file!" << endl;
        }
    }
};

class PizzaMenu
{
private:
    map<string, pair<string, double>> pizzas;

public:
    PizzaMenu()
    {
        pizzas["Veg"] = make_pair("Margherita", 8.99);
        pizzas["NonVeg"] = make_pair("Pepperoni", 9.99);
    }

    pair<string, double> getPizzaDetails(const string& type) const
    {
        if (pizzas.find(type) != pizzas.end())
        {
            return pizzas.at(type);
        }
        else
        {
            throw runtime_error("Pizza type not found");
        }
    }

    void displayMenu() const
    {
        cout << "Menu:" << endl;

        for (const auto& pizza : pizzas)
        {
            cout << "Type: " << pizza.first
                 << ", Flavor: " << pizza.second.first
                 << ", Price: $" << pizza.second.second << endl;
        }
    }
};

class Order
{
private:
    map<string, int> items;
    double total;

public:
    Order()
    {
        total = 0.0;
    }

    void addItem(const string& itemName, int quantity, double price)
    {
        items[itemName] += quantity;
        total += quantity * price;
    }

    void displayOrder() const
    {
        cout << "Order Details:" << endl;

        for (const auto& item : items)
        {
            cout << "Item: " << item.first
                 << ", Quantity: " << item.second << endl;
        }

        cout << "Total: $" << total << endl;
    }

    double getTotal() const
    {
        return total;
    }

    const map<string, int>& getItems() const
    {
        return items;
    }
};

class Customer
{
protected:
    int invoice;

public:
    Customer(int invoice)
    {
        this->invoice = invoice;
    }

    virtual void display() const = 0;

    virtual ~Customer()
    {
    }
};

class DineIn : public Customer
{
public:
    DineIn(int invoice) : Customer(invoice)
    {
    }

    void display() const override
    {
        cout << "Dine-In Customer - Invoice: "
             << invoice << endl;
    }
};

class Takeaway : public Customer
{
public:
    Takeaway(int invoice) : Customer(invoice)
    {
    }

    void display() const override
    {
        cout << "Takeaway Customer - Invoice: "
             << invoice << endl;
    }
};

class Delivery : public Customer
{
private:
    string name;
    string contactNumber;
    string address;

public:
    Delivery(int invoice,
             const string& name,
             const string& contactNumber,
             const string& address)
        : Customer(invoice),
          name(name),
          contactNumber(contactNumber),
          address(address)
    {
    }

    void display() const override
    {
        cout << "Delivery Customer - Invoice: "
             << invoice
             << ", Name: " << name
             << ", Contact Number: " << contactNumber
             << ", Address: " << address << endl;
    }
};

class Employee
{
protected:
    string name;

public:
    Employee(const string& name)
    {
        this->name = name;
    }

    virtual void salary() const = 0;

    virtual ~Employee()
    {
    }
};

class Receptionist : public Employee
{
public:
    Receptionist(const string& name) : Employee(name)
    {
    }

    void salary() const override
    {
        cout << "Receptionist's salary details" << endl;
    }
};

class Waiter : public Employee
{
public:
    Waiter(const string& name) : Employee(name)
    {
    }

    void salary() const override
    {
        cout << "Waiter's salary details" << endl;
    }
};

class Outlet
{
private:
    Receptionist receptionist;
    Waiter waiter;
    PizzaMenu menu;
    ofstream pendingOrdersFile;
    ofstream completedOrdersFile;

public:
    Outlet()
        : receptionist("John"),
          waiter("Alice"),
          pendingOrdersFile("pending_orders.txt"),
          completedOrdersFile("completed_orders.txt")
    {
    }

    void displayEmployees() const
    {
        receptionist.salary();
        waiter.salary();
    }

    void displayMenu() const
    {
        menu.displayMenu();
    }

    Order placeOrder(const string& type,
                     int quantity,
                     const string& itemName,
                     double price) const
    {
        Order order;

        order.addItem(itemName, quantity, price);

        return order;
    }

    pair<string, double> getPizzaDetails(const string& type) const
    {
        return menu.getPizzaDetails(type);
    }

    void generateBill(const Order& order) const
    {
        order.displayOrder();
    }

    void addPendingOrder(const Order& order)
    {
        pendingOrdersFile << "Pending Order:" << endl;

        for (const auto& item : order.getItems())
        {
            pendingOrdersFile << "Item: "
                              << item.first
                              << ", Quantity: "
                              << item.second << endl;
        }

        pendingOrdersFile << "Total: $"
                          << order.getTotal() << endl;
    }

    void addCompletedOrder(const Order& order)
    {
        completedOrdersFile << "Completed Order:" << endl;

        for (const auto& item : order.getItems())
        {
            completedOrdersFile << "Item: "
                                << item.first
                                << ", Quantity: "
                                << item.second << endl;
        }

        completedOrdersFile << "Total: $"
                            << order.getTotal() << endl;
    }

    ~Outlet()
    {
        pendingOrdersFile.close();
        completedOrdersFile.close();
    }
};

int main()
{
    int choice;

    Manager manager;
    Outlet domino;

    while (true)
    {
        cout << "1. Management Side" << endl;
        cout << "2. Customer Side" << endl;
        cout << "3. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string pwd;

            cout << "Enter password: ";
            cin >> pwd;

            if (manager.authenticate(pwd))
            {
                int managementChoice;

                cout << "Management Side" << endl;

                while (true)
                {
                    cout << "1. Add Ingredient" << endl;
                    cout << "2. Use Ingredient" << endl;
                    cout << "3. Restock Ingredient" << endl;
                    cout << "4. Display Ingredients" << endl;
                    cout << "5. Check-in Employee" << endl;
                    cout << "6. Check-out Employee" << endl;
                    cout << "7. Display Employee Details" << endl;
                    cout << "8. Exit Management Side" << endl;

                    cout << "Enter your choice: ";
                    cin >> managementChoice;

                    switch (managementChoice)
                    {
                    case 1:
                    {
                        string name;
                        int quantity;

                        cout << "Enter ingredient name: ";
                        cin >> name;

                        cout << "Enter quantity: ";
                        cin >> quantity;

                        manager.addIngredient(name, quantity);

                        break;
                    }

                    case 2:
                    {
                        string name;
                        int quantity;

                        cout << "Enter ingredient name: ";
                        cin >> name;

                        cout << "Enter quantity to use: ";
                        cin >> quantity;

                        manager.useIngredient(name, quantity);

                        break;
                    }

                    case 3:
                    {
                        string name;
                        int quantity;

                        cout << "Enter ingredient name: ";
                        cin >> name;

                        cout << "Enter quantity to restock: ";
                        cin >> quantity;

                        manager.restockIngredient(name, quantity);

                        break;
                    }

                    case 4:
                        manager.displayIngredients();
                        break;

                    case 5:
                    {
                        string employeeName;

                        cout << "Enter employee name: ";
                        cin >> employeeName;

                        manager.checkInEmployee(employeeName);

                        break;
                    }

                    case 6:
                    {
                        string employeeName;

                        cout << "Enter employee name: ";
                        cin >> employeeName;

                        manager.checkOutEmployee(employeeName);

                        break;
                    }

                    case 7:
                        manager.displayEmployeeDetails();
                        break;

                    case 8:
                        cout << "Exiting Management Side" << endl;
                        break;

                    default:
                        cout << "Invalid choice!" << endl;
                    }

                    if (managementChoice == 8)
                    {
                        break;
                    }
                }
            }
            else
            {
                cout << "Authentication failed!" << endl;
            }

            break;
        }

        case 2:
        {
            int customerChoice;

            cout << "Customer Side" << endl;

            while (true)
            {
                cout << "1. Display Menu" << endl;
                cout << "2. Place Order" << endl;
                cout << "3. Generate Bill" << endl;
                cout << "4. Exit Customer Side" << endl;

                cout << "Enter your choice: ";
                cin >> customerChoice;

                switch (customerChoice)
                {
                case 1:
                    domino.displayMenu();
                    break;

                case 2:
                {
                    string type, itemName;
                    int quantity;
                    double price;

                    cout << "Enter pizza type (Veg/NonVeg): ";
                    cin >> type;

                    tie(itemName, price) =
                        domino.getPizzaDetails(type);

                    cout << "Enter quantity: ";
                    cin >> quantity;

                    price *= quantity;

                    Order order =
                        domino.placeOrder(type,
                                          quantity,
                                          itemName,
                                          price);

                    cout << "Order placed successfully!"
                         << endl;

                    domino.addPendingOrder(order);

                    break;
                }

                case 3:
                {
                    Order order;

                    domino.generateBill(order);

                    domino.addCompletedOrder(order);

                    break;
                }

                case 4:
                    cout << "Exiting Customer Side"
                         << endl;
                    break;

                default:
                    cout << "Invalid choice!" << endl;
                }

                if (customerChoice == 4)
                {
                    break;
                }
            }

            break;
        }

        case 3:
            cout << "Exiting Program" << endl;
            return 0;

        default:
            cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}