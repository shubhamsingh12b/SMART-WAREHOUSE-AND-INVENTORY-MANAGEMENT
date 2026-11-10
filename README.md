# Smart Warehouse & Inventory Management System
## (Amazon Seller Services Edition)

A college-level C++ project built using fundamental Data Structures and Algorithms (DSA) to model an Amazon Seller Services (FBA / Marketplace) warehouse inventory and order fulfillment pipeline.

---

## 📌 Core Data Structures Used

| Data Structure | Implementation | Purpose in Warehouse System |
| :--- | :--- | :--- |
| **Vector** | `vector<Product> products` | Dynamic product inventory catalog with instant index access |
| **Linked List** | `list<Supplier> suppliers` | Flexible supplier database for adding and iterating seller vendors |
| **Queue (FIFO)** | `queue<Order> orders` | Customer order fulfillment queue (First-In-First-Out order processing) |
| **Stack (LIFO)** | `stack<string> actions` | Audit trail of recent warehouse activities (Last-In-First-Out activity log) |
| **Priority Queue (Max-Heap)** | `priority_queue<pair<int, int>> pq` | Smart restock recommendation engine (prioritizes largest stock shortages first) |

---

## 🛒 Amazon Seller Services Dataset

The system is pre-loaded with official Amazon marketplace categories, top-selling SKUs, and registered Amazon fulfillment vendor accounts:

### 1. Products (`products.txt`)
* **Amazon Devices & Electronics:** Echo Dot 5th Gen, Fire TV Stick 4K, Kindle Paperwhite, boAt Airdopes, Anker PowerCore, Portronics USB-C Hub, Noise Bluetooth Headset.
* **AmazonBasics Range:** Fast Charging Cable, HighSpeed HDMI Cable, Microfiber Cleaning Cloth Pack, Non-Stick Cookware Set, Ergonomic Wireless Mouse, Yoga Mat with Strap.
* **Home & Daily Essentials:** Solimo Stainless Steel Flask, Prestige Induction Cooktop, Philips Smart LED Bulb, Memory Foam Orthopedic Pillow.

### 2. Sellers & Suppliers (`suppliers.txt`)
* `201` Amazon_Fulfillment_Services_India
* `202` Cloudtail_India_Private_Limited
* `203` Appario_Retail_Private_Limited
* `204` Cocoblu_Retail_Limited
* `205` AnkerDirect_Official_Store
* `206` Spigen_India_Distributors

---

## ⚡ Main Features

1. **Add Product**: Insert new SKU with stock, reorder level, units sold, and price.
2. **Display Inventory**: Formatted table view of all products with quantities and prices.
3. **Update Stock**: Restock any product by ID with audit log tracking.
4. **Supplier Management**: Add and display Amazon seller vendors using a Linked List.
5. **Customer Order Queue**: Place orders into a FIFO queue and process them in order.
6. **Demand & Stock-out Risk Analysis**: Evaluates sales velocity (High/Medium/Low) and stockout vulnerability (Stock-Out, High, Medium, Low).
7. **Smart Reorder Recommendations**: Uses a Max-Heap Priority Queue to suggest immediate restock quantities for the most critical shortages first.
8. **ABC Inventory Classification**: Pareto 80/20 analysis ranking items by total inventory valuation into Class A, Class B, and Class C.
9. **Executive Inventory Report**: Shows total SKUs, active suppliers, total units in stock, and total valuation ($).
10. **Recent Actions (Stack)**: Displays latest actions in reverse chronological order.
11. **File Persistence**: Saves and loads directly to/from `products.txt` and `suppliers.txt`.

---

## 🚀 How to Compile and Run

```bash
# Compile using Makefile
make

# Run the program
./smart_warehouse
```
