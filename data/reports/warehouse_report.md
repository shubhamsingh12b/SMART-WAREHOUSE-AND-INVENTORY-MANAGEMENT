# Smart Warehouse & Inventory Management - Executive Analysis Report

> **Generated on:** Pure C++ Standard Template Library Engine

## 1. Executive KPIs

| Metric | Value |
| :--- | :--- |
| **Total SKUs** | 50 |
| **Units on Hand** | 8521 |
| **Total Valuation** | $613525.60 |
| **Warehouse Health Score** | 59.0 / 100 |
| **Stockout Risks** | 5 |
| **Reorder Actions Needed** | 15 |
| **Procurement Budget Required** | $144741.90 |

## 2. ABC Pareto Classification

| Class | SKU Count | SKU % | Total Annual Value | Value % | Policy |
| :---: | :---: | :---: | :---: | :---: | :--- |
| **A** | 13 | 26.0% | $3069530.0 | 73.0% | Tight weekly cycle counting & priority replenishment |
| **B** | 17 | 34.0% | $901298.0 | 21.4% | Bi-weekly review, EOQ batch orders |
| **C** | 20 | 40.0% | $233662.2 | 5.6% | Monthly review, bulk ordering |

## 3. Stock Risk Detection

| SKU | Product Name | Stock | Days Supply | Risk Level | Score | Capital at Risk |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: |
| `WMS-EL-103` | Industrial RFID Tag Pack (1000ct) | 0 | 0d | **OUT_OF_STOCK** | 100 | $7542 |
| `WMS-EL-104` | Heavy Duty Thermal Label Printer | 27 | 7d | **LOW_STOCK** | 55 | $4960 |
| `WMS-EL-106` | PLC Automation Controller Module | 210 | 398d | **DEAD_STOCK** | 75 | $109200 |
| `WMS-EL-107` | Gigabit Managed Switch 24-Port | 85 | 18d | **CRITICAL_LOW** | 85 | $20631 |
| `WMS-IN-203` | Pneumatic Cylinder 50mm Stroke | 0 | 0d | **OUT_OF_STOCK** | 100 | $5174 |
| `WMS-IN-204` | High Tensile Pallet Strapping 16mm | 26 | 6d | **LOW_STOCK** | 55 | $560 |
| `WMS-IN-206` | Overhead Crane Hoist Cable 20m | 210 | 398d | **DEAD_STOCK** | 75 | $45150 |
| `WMS-IN-207` | Safety Emergency Stop Switch | 85 | 18d | **CRITICAL_LOW** | 85 | $868 |
| `WMS-SC-303` | Clear Stretch Wrap Film 500mmx300m | 0 | 0d | **OUT_OF_STOCK** | 100 | $198 |
| `WMS-SC-304` | Steel Toe Safety Boots (Size 10) | 30 | 7d | **LOW_STOCK** | 55 | $2380 |
| `WMS-SC-306` | Packing Bubble Wrap Roll 100m | 210 | 398d | **DEAD_STOCK** | 75 | $4620 |
| `WMS-SC-307` | Barcode Thermal Transfer Ribbon | 85 | 18d | **CRITICAL_LOW** | 85 | $648 |
| `WMS-PH-403` | Sterile Saline Solution IV 500ml | 0 | 0d | **OUT_OF_STOCK** | 100 | $296 |
| `WMS-PH-404` | Insulin Pen Cartridge Storage Box | 27 | 7d | **LOW_STOCK** | 55 | $3825 |
| `WMS-PH-406` | Cryogenic Storage Box 81-Well | 210 | 398d | **DEAD_STOCK** | 75 | $4095 |
| `WMS-PH-407` | Biological Transport Bag Leakproof | 85 | 18d | **CRITICAL_LOW** | 85 | $108 |
| `WMS-FM-503` | Natural Mineral Water 500ml (24pk) | 0 | 0d | **OUT_OF_STOCK** | 100 | $102 |
| `WMS-FM-504` | Dark Chocolate Single Origin 100g | 28 | 7d | **LOW_STOCK** | 55 | $44 |
| `WMS-FM-506` | Organic Oats Rolled 2.5kg | 210 | 398d | **DEAD_STOCK** | 75 | $1428 |
| `WMS-FM-507` | Green Tea Matcha Japanese 100g | 85 | 18d | **CRITICAL_LOW** | 85 | $1794 |

## 4. Reorder Recommendations

| SKU | Supplier | Current Stock | Safety Stock | Reorder Point | EOQ | Recommended Order | Estimated Cost |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: | :---: |
| `WMS-EL-103` | OmniID Supply | 0 | 35 | 136 | 85 | **171** | $20520 |
| `WMS-EL-104` | Printronix Co | 27 | 14 | 43 | 49 | **49** | $15190 |
| `WMS-EL-107` | Cisco Systems | 85 | 154 | 211 | 68 | **280** | $51800 |
| `WMS-IN-203` | SMC Pneumatics | 0 | 27 | 101 | 90 | **128** | $14080 |
| `WMS-IN-204` | Signode Packaging | 26 | 18 | 46 | 160 | **160** | $4480 |
| `WMS-IN-207` | Schneider Electric | 85 | 99 | 123 | 158 | **158** | $5372 |
| `WMS-SC-303` | Berry Global | 0 | 12 | 28 | 243 | **243** | $3888 |
| `WMS-SC-304` | Timberland PRO | 30 | 19 | 65 | 110 | **110** | $7480 |
| `WMS-SC-307` | Zebra Supplies | 85 | 109 | 137 | 242 | **242** | $3509 |
| `WMS-PH-403` | Baxter Healthcare | 0 | 16 | 72 | 489 | **489** | $2054 |
| `WMS-PH-404` | Novo Nordisk | 27 | 22 | 72 | 93 | **93** | $7905 |
| `WMS-PH-407` | Bio-Medical Co | 85 | 109 | 137 | 583 | **583** | $1049 |
| `WMS-FM-503` | Danone Waters | 0 | 11 | 27 | 413 | **413** | $2272 |
| `WMS-FM-504` | Lindt & Sprungli | 28 | 14 | 48 | 556 | **556** | $1223 |
| `WMS-FM-507` | Ito En Tea | 85 | 154 | 211 | 246 | **280** | $3920 |
