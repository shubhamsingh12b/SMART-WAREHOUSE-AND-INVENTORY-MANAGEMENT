# Smart Warehouse and Inventory Management System

A clean C++ project developed for College Lab and Project Submission.

---

## 📌 Data Structures Used
1. **Array (`string zones[4]`)**: To store fixed storage zones in the warehouse.
2. **Vector (`vector<Item> items`)**: To store dynamic list of products.
3. **Linked List (`struct Node`)**: To maintain dynamic transaction activity history (Inbound / Outbound actions).
4. **Priority Queue (`priority_queue<ReorderItem> pq`)**: To prioritize emergency restock orders (Out of stock items come out first).

---

## 📌 Features & Workflow
1. **Management**:
   - View all products
   - Search by SKU or Name
   - Receive stock (Inbound receipt)
   - Dispatch stock (Outbound shipping)
   - Add new product
   - View recent transaction logs (Linked List)
   - View warehouse zones (Array)
2. **Smart Analysis**:
   - Demand Analysis (Sales velocity and simple 5% growth forecast)
   - ABC Analysis (Pareto 80/20 rule using Bubble Sort: Class A, B, C)
   - Stock Risk Detection (Out of stock, low stock, overstock)
   - Reorder Recommendations (Priority Queue)
3. **Generate Reports**:
   - Total products, total valuation, out of stock count, and pending reorders.
4. **Save Data**:
   - Saves all updates back to `data/inventory_database.csv`.
5. **Exit**:
   - Clean exit from the program.

---

## 💻 How to Run

```bash
# Compile
make

# Run
make run
```
