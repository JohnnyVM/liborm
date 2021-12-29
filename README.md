# LibORM - C/C++ library based in sqlalchemy

## Driver

---

A driver must implement the classes Connection, Cursor, TypeFactory and engine

### Conventions

---

- Assume optimistic allocation; alloc can't fail;
- The C api is stable, C++ no (and it will change); No support for any direct call to the C++ classes
