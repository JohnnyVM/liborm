# C++ ORM
---
Library structure:<br>
-> Database declaration<br>
-> Query builder<br>
-> (todo)Database drivers

### Database declaration
---
Define the structure of the database form the poin of view of the program and stored in the metadata class.<br>
The definition is done with the class Table,Column and generator funtion table,column.

### Query builder
---
Using the shcema delared in metadata or passed as parameters build the sql queries
