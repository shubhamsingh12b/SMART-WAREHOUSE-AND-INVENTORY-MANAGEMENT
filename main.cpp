#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Product record for Amazon Seller Services
struct Product {
    int id;
    string name;
    int stock;
    int sold;
    int reorderLevel;
    double price;
};

// Supplier record
struct Supplier {
    int id;
    string name;
};

// Order record
struct Order {
    int productId;
    int quantity;
};

// Data structures
vector<Product> products;
list<Supplier> suppliers;
queue<Order> orders;
stack<string> actions;

// Find product using ID
int findProduct(int id) {
    for (int i = 0; i < (int)products.size(); i++) {
        if (products[i].id == id)
            return i;
    }
    return -1;
}

// 1. Add product
void addProduct() {
    Product p;
    cout << "Enter product ID: ";
    cin >> p.id;
    if (findProduct(p.id) != -1) {
        cout << "Product ID already exists!\n";
        return;
    }
    cout << "Enter product name (use _ for spaces): ";
    cin >> p.name;
    cout << "Enter current stock: ";
    cin >> p.stock;
    cout << "Enter quantity sold: ";
    cin >> p.sold;
    cout << "Enter reorder level: ";
    cin >> p.reorderLevel;
    cout << "Enter price: ";
    cin >> p.price;
    if (p.stock < 0 || p.sold < 0 ||
        p.reorderLevel < 0 || p.price < 0) {
        cout << "Invalid values!\n";
        return;
    }
    products.push_back(p);
    actions.push("Product added: " + p.name);
    cout << "Product added successfully!\n";
}

// 2. Display inventory
void displayProducts() {
    if (products.empty()) {
        cout << "No products available.\n";
        return;
    }
    cout << "\nID\tName\t\t\t\t\tStock\tSold\tPrice\n";
    cout << "--------------------------------------------------------------------------------\n";
    for (const Product &p : products) {
        cout << left << setw(8) << p.id
             << setw(40) << p.name
             << setw(8) << p.stock
             << setw(8) << p.sold
             << "$" << fixed << setprecision(2) << p.price << "\n";
    }
}

// 3. Update stock
void updateStock() {
    int id, quantity;
    cout << "Enter product ID: ";
    cin >> id;
    int index = findProduct(id);
    if (index == -1) {
        cout << "Product not found!\n";
        return;
    }
    cout << "Enter quantity to add: ";
    cin >> quantity;
    if (quantity <= 0) {
        cout << "Quantity must be positive!\n";
        return;
    }
    products[index].stock += quantity;
    actions.push("Stock updated for product ID " + to_string(id));
    cout << "Stock updated successfully!\n";
}

// 4. Add supplier (linked list)
void addSupplier() {
    Supplier s;
    cout << "Enter supplier ID: ";
    cin >> s.id;
    for (const Supplier &supplier : suppliers) {
        if (supplier.id == s.id) {
            cout << "Supplier ID already exists!\n";
            return;
        }
    }
    cout << "Enter supplier name (use _ for spaces): ";
    cin >> s.name;
    suppliers.push_back(s);
    actions.push("Supplier added: " + s.name);
    cout << "Supplier added successfully!\n";
}

// Display suppliers
void displaySuppliers() {
    if (suppliers.empty()) {
        cout << "No suppliers available.\n";
        return;
    }
    cout << "\nSupplier ID\tSupplier Name\n";
    cout << "--------------------------------------------------------\n";
    for (const Supplier &s : suppliers)
        cout << s.id << "\t\t" << s.name << "\n";
}

// 5. Place customer order (queue)
void placeOrder() {
    int id, quantity;
    cout << "Enter product ID: ";
    cin >> id;
    if (findProduct(id) == -1) {
        cout << "Product not found!\n";
        return;
    }
    cout << "Enter order quantity: ";
    cin >> quantity;
    if (quantity <= 0) {
        cout << "Quantity must be positive!\n";
        return;
    }
    orders.push({id, quantity});
    cout << "Order added to queue!\n";
}

// Process oldest order first
void processOrder() {
    if (orders.empty()) {
        cout << "No pending orders.\n";
        return;
    }
    Order o = orders.front();
    int index = findProduct(o.productId);
    if (index == -1) {
        orders.pop();
        cout << "Invalid order removed.\n";
        return;
    }
    if (products[index].stock < o.quantity) {
        cout << "Insufficient stock! Order remains pending.\n";
        return;
    }
    products[index].stock -= o.quantity;
    products[index].sold += o.quantity;
    cout << "Order processed successfully!\n";
    actions.push("Order processed for product ID " + to_string(o.productId));
    orders.pop();
}

// 6. Demand and stock-out risk analysis
void demandAnalysis() {
    if (products.empty()) {
        cout << "No products available.\n";
        return;
    }
    cout << "\n--- DEMAND AND STOCK RISK ---\n";
    for (const Product &p : products) {
        cout << "\nProduct: " << p.name;
        cout << "\nUnits sold: " << p.sold;
        if (p.sold >= 50)
            cout << "\nDemand: HIGH";
        else if (p.sold >= 20)
            cout << "\nDemand: MEDIUM";
        else
            cout << "\nDemand: LOW";

        if (p.stock == 0)
            cout << "\nRisk: STOCK-OUT";
        else if (p.stock <= p.reorderLevel)
            cout << "\nRisk: HIGH";
        else if (p.stock <= p.reorderLevel * 2)
            cout << "\nRisk: MEDIUM";
        else
            cout << "\nRisk: LOW";
        cout << "\n";
    }
}

// 7. Smart reorder recommendations
void reorderAnalysis() {
    // Priority: largest stock shortage first
    priority_queue<pair<int, int>> pq;
    for (const Product &p : products) {
        if (p.stock <= p.reorderLevel) {
            int shortage = p.reorderLevel - p.stock + 1;
            pq.push({shortage, p.id});
        }
    }
    cout << "\n--- SMART REORDER RECOMMENDATIONS ---\n";
    if (pq.empty()) {
        cout << "No products require reordering.\n";
        return;
    }
    while (!pq.empty()) {
        int shortage = pq.top().first;
        int id = pq.top().second;
        pq.pop();
        int index = findProduct(id);
        cout << "Product: " << products[index].name
             << " | Current stock: " << products[index].stock
             << " | Suggested order quantity: " << shortage
             << "\n";
    }
}

// 8. ABC inventory classification
void abcAnalysis() {
    if (products.empty()) {
        cout << "No products available.\n";
        return;
    }
    vector<pair<double, int>> values;
    double totalValue = 0;
    for (int i = 0; i < (int)products.size(); i++) {
        double value = products[i].stock * products[i].price;
        values.push_back({value, i});
        totalValue += value;
    }
    // Sort from highest inventory value to lowest
    for (int i = 0; i < (int)values.size(); i++) {
        for (int j = i + 1; j < (int)values.size(); j++) {
            if (values[j].first > values[i].first) {
                swap(values[i], values[j]);
            }
        }
    }
    double cumulative = 0;
    cout << "\n--- ABC ANALYSIS ---\n";
    for (auto item : values) {
        cumulative += item.first;
        double percentage = 0;
        if (totalValue > 0)
            percentage = cumulative / totalValue * 100;
        char category;
        if (totalValue == 0 || percentage <= 80)
            category = 'A';
        else if (percentage <= 95)
            category = 'B';
        else
            category = 'C';
        cout << left << setw(38) << products[item.second].name
             << " | Inventory value: $" << setw(10) << fixed << setprecision(2) << item.first
             << " | Class: " << category << "\n";
    }
}

// 9. Generate inventory report
void generateReport() {
    int totalStock = 0;
    double totalValue = 0;
    cout << "\n--- INVENTORY REPORT ---\n";
    for (const Product &p : products) {
        totalStock += p.stock;
        totalValue += p.stock * p.price;
    }
    cout << "Total products: " << products.size() << "\n";
    cout << "Total suppliers: " << suppliers.size() << "\n";
    cout << "Total units in stock: " << totalStock << "\n";
    cout << "Total inventory value: $"
         << fixed << setprecision(2) << totalValue << "\n";
    cout << "Pending orders: " << orders.size() << "\n";
}

// 10. Display recent actions (stack)
void showActions() {
    if (actions.empty()) {
        cout << "No actions recorded.\n";
        return;
    }
    stack<string> temp = actions;
    cout << "\n--- RECENT ACTIONS ---\n";
    while (!temp.empty()) {
        cout << temp.top() << "\n";
        temp.pop();
    }
}

// 11. Save products and suppliers to files
void saveData() {
    ofstream pf("products.txt");
    for (const Product &p : products) {
        pf << p.id << " " << p.name << " "
           << p.stock << " " << p.sold << " "
           << p.reorderLevel << " " << p.price << "\n";
    }
    pf.close();
    ofstream sf("suppliers.txt");
    for (const Supplier &s : suppliers)
        sf << s.id << " " << s.name << "\n";
    sf.close();
    cout << "Data saved successfully!\n";
}

// 12. Load saved data
void loadData() {
    products.clear();
    suppliers.clear();

    ifstream pf("products.txt");
    Product p;
    while (pf >> p.id >> p.name >> p.stock
              >> p.sold >> p.reorderLevel >> p.price) {
        products.push_back(p);
    }
    pf.close();

    ifstream sf("suppliers.txt");
    Supplier s;
    while (sf >> s.id >> s.name)
        suppliers.push_back(s);
    sf.close();
}

// Main menu
int main() {
    loadData();
    int choice;
    do {
        cout << "\n===== SMART WAREHOUSE SYSTEM (AMAZON SELLER SERVICES) =====\n";
        cout << "1. Add Product\n";
        cout << "2. Display Inventory\n";
        cout << "3. Update Stock\n";
        cout << "4. Add Supplier\n";
        cout << "5. Display Suppliers\n";
        cout << "6. Place Order\n";
        cout << "7. Process Order\n";
        cout << "8. Demand and Stock Risk Analysis\n";
        cout << "9. Smart Reorder Recommendation\n";
        cout << "10. ABC Analysis\n";
        cout << "11. Generate Report\n";
        cout << "12. View Recent Actions\n";
        cout << "13. Save Data\n";
        cout << "0. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addProduct(); break;
            case 2: displayProducts(); break;
            case 3: updateStock(); break;
            case 4: addSupplier(); break;
            case 5: displaySuppliers(); break;
            case 6: placeOrder(); break;
            case 7: processOrder(); break;
            case 8: demandAnalysis(); break;
            case 9: reorderAnalysis(); break;
            case 10: abcAnalysis(); break;
            case 11: generateReport(); break;
            case 12: showActions(); break;
            case 13: saveData(); break;
            case 0:
                saveData();
                cout << "Thank you! Exiting system.\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
