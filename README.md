# Inventory-Management-System

Description
This C program implements an inventory management system using a hash table with separate chaining to handle collisions. The system allows users to buy, sell, and update prices of items, while tracking the available cash and operational complexity. The program is designed to efficiently manage a large number of items and transactions.

Features
Buy Item: Add items to the inventory or update the quantity of existing items. The total available cash decreases accordingly.
Sell Item: Remove items from the inventory based on their quantity. If the requested quantity is larger than available, it sells only what is in stock. The total available cash increases.
Change Price: Modify the sale price of an existing item in the inventory.
Track Complexity: Tracks the complexity of operations based on the number of hash table accesses.

How It Works
The program initializes a hash table to store items by name.
The user inputs a series of commands (buy, sell, change_price) to manage the inventory.
The system updates the inventory and displays the current state (e.g., remaining quantity and total cash).
After all operations, the program outputs the total cash on hand and the total computational complexity of the operations.
