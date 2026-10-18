/*
 * Smart Warehouse and Inventory Management System
 * Data Structures used:
 * 1. Array - for warehouse zones
 * 2. Vector - to store product list
 * 3. Linked List - to maintain recent transaction log
 * 4. Priority Queue - to prioritize emergency reorders
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

// Array for fixed warehouse storage zones
string zones[4] = {"Zone A - Electronics", "Zone B - Machinery", "Zone C - Safety", "Zone D - Daily Goods"};

// Structure for inventory item
struct Item {
    string id;
    string name;
    string category;
    int stock;
    float cost;
    float price;
    int lead_time;
    string supplier;
    int demand;
};

// Vector to store all products
vector<Item> items;

// Node for singly linked list (to keep track of recent actions)
struct Node {
    string msg;
    Node* next;
};

Node* head = NULL;

// Add log message to linked list
void add_log(string message) {
    Node* temp = new Node();
    temp->msg = message;
    temp->next = head;
    head = temp;
}

// Display linked list logs
void view_logs() {
    cout << "\n--- Recent Activity Log ---\n";
    if (head == NULL) {
        cout << "No transactions yet.\n";
        return;
    }
    Node* curr = head;
    int count = 1;
    while (curr != NULL) {
        cout << count << ". " << curr->msg << endl;
        curr = curr->next;
        count++;
    }
}

// Structure for priority queue
struct ReorderItem {
    int priority; // 2 = out of stock (emergency), 1 = low stock
    string id;
    string name;
    int stock;
    int rop;
    int order_qty;

    // Overloading < operator for max-heap
    bool operator<(const ReorderItem& other) const {
        return priority < other.priority;
    }
};

// Load items from CSV file
void load_data() {
    ifstream file("data/inventory_database.csv");
    if (!file.is_open()) {
        cout << "Database file not found, starting with empty list.\n";
        return;
    }

    items.clear();
    string line;
    getline(file, line); // skipping header row

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        Item it;
        string s_stock, s_cost, s_price, s_lead, s_demand;

        getline(ss, it.id, ',');
        getline(ss, it.name, ',');
        getline(ss, it.category, ',');
        getline(ss, s_stock, ',');
        getline(ss, s_cost, ',');
        getline(ss, s_price, ',');
        getline(ss, s_lead, ',');
        getline(ss, it.supplier, ',');
        getline(ss, s_demand, ',');

        it.stock = stoi(s_stock);
        it.cost = stof(s_cost);
        it.price = stof(s_price);
        it.lead_time = stoi(s_lead);
        it.demand = stoi(s_demand);

        items.push_back(it);
    }
    file.close();
}

// Save items back to CSV file
void save_data() {
    ofstream file("data/inventory_database.csv");
    if (!file.is_open()) {
        cout << "Error opening file to save.\n";
        return;
    }

    file << "SKU,Name,Category,Stock,Cost,Price,LeadTime,Supplier,Demand\n";
    for (int i = 0; i < (int)items.size(); i++) {
        file << items[i].id << ","
             << items[i].name << ","
             << items[i].category << ","
             << items[i].stock << ","
             << items[i].cost << ","
             << items[i].price << ","
             << items[i].lead_time << ","
             << items[i].supplier << ","
             << items[i].demand << "\n";
    }
    file.close();
    cout << "Changes successfully saved to database!\n";
}

// Display all items
void view_items() {
    cout << "\n--- Current Warehouse Inventory ---\n";
    cout << "ID\t\tStock\tCost\tPrice\tName\n";
    cout << "------------------------------------------------------------\n";
    for (int i = 0; i < (int)items.size(); i++) {
        cout << items[i].id << "\t"
             << items[i].stock << "\t$"
             << items[i].cost << "\t$"
             << items[i].price << "\t"
             << items[i].name << endl;
    }
}

// Search item by SKU or Name
void search_item() {
    cout << "Enter SKU or product name to search: ";
    string key;
    cin >> key;

    bool found = false;
    for (int i = 0; i < (int)items.size(); i++) {
        if (items[i].id.find(key) != string::npos || items[i].name.find(key) != string::npos) {
            cout << "Found: " << items[i].id << " | " << items[i].name
                 << " | Stock: " << items[i].stock
                 << " | Cost: $" << items[i].cost
                 << " | Supplier: " << items[i].supplier << endl;
            found = true;
        }
    }
    if (!found) cout << "No matching product found.\n";
}

// Inbound stock receipt
void receive_stock() {
    cout << "Enter SKU: ";
    string id;
    cin >> id;

    cout << "Enter quantity received: ";
    int qty;
    cin >> qty;

    for (int i = 0; i < (int)items.size(); i++) {
        if (items[i].id == id) {
            items[i].stock += qty;
            cout << "Stock updated! New balance: " << items[i].stock << endl;
            add_log("Received " + to_string(qty) + " units of " + items[i].name);
            return;
        }
    }
    cout << "Product ID not found.\n";
}

// Outbound stock dispatch
void dispatch_stock() {
    cout << "Enter SKU: ";
    string id;
    cin >> id;

    cout << "Enter quantity to dispatch: ";
    int qty;
    cin >> qty;

    for (int i = 0; i < (int)items.size(); i++) {
        if (items[i].id == id) {
            if (items[i].stock >= qty) {
                items[i].stock -= qty;
                cout << "Stock dispatched! Remaining: " << items[i].stock << endl;
                add_log("Dispatched " + to_string(qty) + " units of " + items[i].name);
            } else {
                cout << "Not enough stock available. Current stock: " << items[i].stock << endl;
            }
            return;
        }
    }
    cout << "Product ID not found.\n";
}

// Add a new product
void add_item() {
    Item it;
    cout << "Enter SKU: "; cin >> it.id;
    cin.ignore();
    cout << "Enter Name: "; getline(cin, it.name);
    cout << "Enter Category: "; getline(cin, it.category);
    cout << "Enter Initial Stock: "; cin >> it.stock;
    cout << "Enter Cost Price ($): "; cin >> it.cost;
    cout << "Enter Selling Price ($): "; cin >> it.price;
    cout << "Enter Lead Time (days): "; cin >> it.lead_time;
    cin.ignore();
    cout << "Enter Supplier: "; getline(cin, it.supplier);
    cout << "Enter Monthly Demand: "; cin >> it.demand;

    items.push_back(it);
    cout << "New product added successfully!\n";
    add_log("Added new item " + it.name + " (" + it.id + ")");
}

// Management menu
void management_menu() {
    int choice;
    cout << "\n=== 1. WAREHOUSE MANAGEMENT ===\n";
    cout << "1. View All Products\n";
    cout << "2. Search Product\n";
    cout << "3. Inbound Stock (Receive)\n";
    cout << "4. Outbound Stock (Dispatch)\n";
    cout << "5. Add New Product\n";
    cout << "6. View Activity Logs (Linked List)\n";
    cout << "7. View Storage Zones (Array)\n";
    cout << "8. Return to Main Menu\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
        case 1: view_items(); break;
        case 2: search_item(); break;
        case 3: receive_stock(); break;
        case 4: dispatch_stock(); break;
        case 5: add_item(); break;
        case 6: view_logs(); break;
        case 7:
            cout << "\nWarehouse Zones (Fixed Array):\n";
            for (int i = 0; i < 4; i++) {
                cout << i + 1 << ". " << zones[i] << endl;
            }
            break;
        default: break;
    }
}

// 1. Demand Analysis
void demand_analysis() {
    cout << "\n=== DEMAND ANALYSIS & FORECASTING ===\n";
    cout << "SKU\t\tDemand\tPattern\t\tNext Forecast\tName\n";
    cout << "------------------------------------------------------------------\n";
    for (int i = 0; i < (int)items.size(); i++) {
        int d = items[i].demand;
        string pattern = (d >= 120) ? "Smooth" : (d >= 40) ? "Moderate" : "Erratic";
        int forecast = (int)(d * 1.05); // simple 5% expected growth
        cout << items[i].id << "\t"
             << d << "\t"
             << pattern << "\t\t"
             << forecast << " units\t"
             << items[i].name << endl;
    }
}

// 2. ABC Analysis using Bubble Sort
void abc_analysis() {
    cout << "\n=== ABC ANALYSIS (PARETO 80/20 RULE) ===\n";
    cout << "Class A: High Value | Class B: Moderate | Class C: Low Value\n\n";

    // Copy to temporary vector
    vector<Item> temp_list = items;

    // Bubble sort descending by annual consumption value (demand * 12 * cost)
    for (int i = 0; i < (int)temp_list.size() - 1; i++) {
        for (int j = 0; j < (int)temp_list.size() - i - 1; j++) {
            float val1 = temp_list[j].demand * 12 * temp_list[j].cost;
            float val2 = temp_list[j + 1].demand * 12 * temp_list[j + 1].cost;
            if (val1 < val2) {
                swap(temp_list[j], temp_list[j + 1]);
            }
        }
    }

    // Total value
    float total_val = 0;
    for (int i = 0; i < (int)temp_list.size(); i++) {
        total_val += (temp_list[i].demand * 12 * temp_list[i].cost);
    }

    cout << "Class\tSKU\t\tAnnual Value\tCumulative %\tName\n";
    cout << "------------------------------------------------------------------\n";

    float running = 0;
    for (int i = 0; i < (int)temp_list.size(); i++) {
        float val = temp_list[i].demand * 12 * temp_list[i].cost;
        running += val;
        float pct = (total_val > 0) ? (running / total_val) * 100.0f : 0;

        char category = 'C';
        if (pct <= 75.0f) category = 'A';
        else if (pct <= 95.0f) category = 'B';

        cout << "[" << category << "]\t"
             << temp_list[i].id << "\t$"
             << (int)val << "\t\t"
             << (int)pct << "%\t\t"
             << temp_list[i].name << endl;
    }
}

// 3. Stock Risk Detection
void stock_risk() {
    cout << "\n=== STOCK RISK DETECTION ===\n";
    cout << "Status\t\tSKU\t\tStock\tDays Supply\tName\n";
    cout << "------------------------------------------------------------------\n";
    for (int i = 0; i < (int)items.size(); i++) {
        float daily = items[i].demand / 30.0f;
        int days = (daily > 0) ? (int)(items[i].stock / daily) : 999;

        string risk = "HEALTHY";
        if (items[i].stock <= 0) {
            risk = "OUT_OF_STOCK";
        } else if (days < items[i].lead_time) {
            risk = "CRITICAL_LOW";
        } else if (days > 180) {
            risk = "OVERSTOCK";
        }

        if (risk != "HEALTHY") {
            cout << risk << "\t"
                 << items[i].id << "\t"
                 << items[i].stock << "\t"
                 << days << " days\t"
                 << items[i].name << endl;
        }
    }
}

// 4. Reorder Recommendations using Priority Queue
void reorder_recommendation() {
    cout << "\n=== REORDER RECOMMENDATIONS (PRIORITY QUEUE) ===\n";

    priority_queue<ReorderItem> pq;

    for (int i = 0; i < (int)items.size(); i++) {
        float daily = items[i].demand / 30.0f;
        int safety_stock = (int)(daily * 5); // 5 days buffer
        int rop = (int)(daily * items[i].lead_time) + safety_stock; // Reorder Point

        if (items[i].stock <= rop) {
            int priority = (items[i].stock <= 0) ? 2 : 1; // 2 = urgent out of stock
            int qty = (rop - items[i].stock + safety_stock) * 2;
            if (qty < 50) qty = 50;

            pq.push({priority, items[i].id, items[i].name, items[i].stock, rop, qty});
        }
    }

    if (pq.empty()) {
        cout << "All items have sufficient stock.\n";
        return;
    }

    cout << "Urgency\t\tSKU\t\tStock\tROP\tOrder\tName\n";
    cout << "------------------------------------------------------------------\n";
    while (!pq.empty()) {
        ReorderItem top = pq.top();
        pq.pop();

        string tag = (top.priority == 2) ? "[EMERGENCY]" : "[LOW STOCK]";
        cout << tag << "\t"
             << top.id << "\t"
             << top.stock << "\t"
             << top.rop << "\t"
             << top.order_qty << " units\t"
             << top.name << endl;
    }
}

// Smart Analysis Submenu
void smart_analysis_menu() {
    int choice;
    cout << "\n=== 2. SMART ANALYSIS ===\n";
    cout << "1. Demand Analysis\n";
    cout << "2. ABC Analysis (Pareto 80/20)\n";
    cout << "3. Stock Risk Detection\n";
    cout << "4. Reorder Recommendations (Priority Queue)\n";
    cout << "5. Run All Analyses\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
        case 1: demand_analysis(); break;
        case 2: abc_analysis(); break;
        case 3: stock_risk(); break;
        case 4: reorder_recommendation(); break;
        case 5:
            demand_analysis();
            abc_analysis();
            stock_risk();
            reorder_recommendation();
            break;
        default: break;
    }
}

// Generate Executive Report
void generate_reports() {
    cout << "\n=== 3. WAREHOUSE EXECUTIVE REPORT ===\n";
    cout << "Total Products (SKUs)   : " << items.size() << endl;

    float total_val = 0;
    int out_of_stock = 0;
    int reorders_needed = 0;

    for (int i = 0; i < (int)items.size(); i++) {
        total_val += (items[i].stock * items[i].cost);
        if (items[i].stock <= 0) out_of_stock++;

        float daily = items[i].demand / 30.0f;
        int rop = (int)(daily * items[i].lead_time) + (int)(daily * 5);
        if (items[i].stock <= rop) reorders_needed++;
    }

    cout << "Total Inventory Value   : $" << (int)total_val << endl;
    cout << "Out of Stock Items      : " << out_of_stock << endl;
    cout << "Items Below Reorder Pnt : " << reorders_needed << endl;
}

int main() {
    // Load existing items from file
    load_data();

    cout << "=========================================\n";
    cout << "  Smart Warehouse & Inventory Management \n";
    cout << "=========================================\n";
    cout << "Loaded " << items.size() << " products from database.\n";

    int choice = 0;
    do {
        cout << "\n------- MAIN MENU -------\n";
        cout << "1. Management\n";
        cout << "2. Smart Analysis\n";
        cout << "3. Generate Reports\n";
        cout << "4. Save Data\n";
        cout << "5. EXIT\n";
        cout << "-------------------------\n";
        cout << "Enter choice (1-5): ";
        cin >> choice;

        switch (choice) {
            case 1:
                management_menu();
                break;
            case 2:
                smart_analysis_menu();
                break;
            case 3:
                generate_reports();
                break;
            case 4:
                save_data();
                break;
            case 5:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Enter 1-5.\n";
                break;
        }
    } while (choice != 5);

    return 0;
}
