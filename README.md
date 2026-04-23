# Compilador — Lenguaje de Programación en Español

Compilador/intérprete completo mas o menos completo un lenguaje de programación con sintaxis en español, implementado con Flex, Bison y C.
---

## Características del Lenguaje

- Sintaxis en español: `si`, `otra`, `mostrar`, `retorna`, `verdad`, `no`
- Tipos primitivos: `num`, `dec`, `car`, `pal`, `bool`
- Operadores aritméticos: `+`, `-`, `*`, `/`
- Operadores de comparación: `==`, `!=`, `<`, `>`, `<=`, `>=`
- Funciones con parámetros tipados y valor de retorno
- Condicionales `si / otra`
- Sistema de ámbitos (scopes) anidados con shadowing
- Comentarios de línea `--` y de bloque `--- ... ---`

---

## Ejemplo de Código

```
let edad    as num  = 22;
let precio  as dec  = 9.99;
let inicial as car  = 'K';
let saludo  as pal  = "Hola mundo";
let activo  as bool = verdad;

let suma as num = edad + 8;
mostrar suma;

func sumar([num]a, [num]b) -> [num] {
    retorna a + b;
}

si (suma > 10) {
    mostrar saludo;
} otra {
    mostrar edad;
}
```

---

## Compilación y Ejecución

```bash
make clean                    # Borra archivos generados anteriores
make                          # Compila todo el proyecto
./compiler archivo.español    # Ejecuta el compilador
make test                     # Corre todos los tests automatizados

 for f in test/*.español; do  # corre todos los archivos de los test con resultados
    echo "=== $(basename $f .español) ==="
    ./compiler "$f"
```

---

## Estructura de Archivos

```
├── lexer.l                  # Analizador léxico (Flex)
├── parser.y                 # Analizador sintáctico (Bison)
├── Makefile                 # Automatización de compilación
├── source.español           # Archivo de prueba principal
├── src/
│   ├── main.c               # Punto de entrada
│   ├── ast.c / ast.h        # Construcción del AST
│   ├── interpreter.c / .h   # Evaluación del AST
│   ├── scope.c / scope.h    # Pila de ámbitos
│   ├── symbols.c / symbols.h# Tabla de símbolos
│   └── type_coercion.c / .h # Conversión de tipos e impresión
└── test/
    ├── *.español            # Casos de prueba
    ├── run_tests.sh         # Script de pruebas automatizadas
    └── EXPECTED_OUTPUTS.txt # Salidas esperadas por cada test
```

---

## Arquitectura del Pipeline

```
Código Fuente (.español)
        │
        ▼
  LEXER (Flex)
  lexer.l → lex.yy.c
  Convierte texto en tokens
        │
        ▼
  PARSER (Bison)
  parser.y → y.tab.c
  Valida gramática y construye el AST
        │
        ▼
  INTÉRPRETE
  interpreter.c
  Recorre el AST y ejecuta cada nodo
        │
        ▼
  Salida en pantalla
```

---

## Módulos

### lexer.l
Tokeniza el código fuente usando expresiones regulares. Reconoce palabras reservadas, tipos, literales, operadores y comentarios. `FLT_NUM` va antes que `INT_NUM` para que `3.14` no se lea como entero.

### parser.y
Define la gramática del lenguaje y construye el AST mediante acciones semánticas. Usa dos estructuras internas: `g_stmts` para sentencias globales y `f_stmts` como pila para cuerpos de funciones y bloques anidados.

Precedencia de operadores (menor a mayor):
```
1. == !=
2. < > <= >=
3. + -
4. * /
5. - (unario)
```

### ast.c / ast.h
Define todos los tipos de nodo del AST y sus constructores. Usa el patrón `type + union`: el campo `type` indica cuál campo de `data` es válido leer. `ast_free` libera el árbol recursivamente (hijos antes que el padre).

| Nodo | Representa |
|---|---|
| `AST_PROGRAM` | Raíz del árbol |
| `AST_VAR_DECL` | `let nombre as tipo = expr` |
| `AST_SHOW` | `mostrar nombre` |
| `AST_BINARY_OP` | `expr OP expr` |
| `AST_LITERAL` | Valores literales |
| `AST_IDENTIFIER` | Uso de una variable |
| `AST_FUNC_DECL` | Declaración de función |
| `AST_FUNC_CALL` | Llamada a función |
| `AST_BLOCK` | Bloque `{ }` |
| `AST_RETURN` | `retorna expr` |
| `AST_IF` | `si / otra` |

### interpreter.c / interpreter.h
Núcleo de ejecución. La función `eval()` recorre el AST recursivamente. `interpreter_run` hace dos pasadas: primero registra todas las funciones, luego ejecuta el resto. Esto permite llamar funciones antes de donde fueron declaradas.

La bandera `is_return` en `EvalResult` permite que `retorna` burbujee correctamente a través de bloques anidados hasta salir de la función.

### scope.c / scope.h
Implementa una pila de ámbitos. Cada bloque `{ }` o función crea un nivel nuevo con `push_scope()` y lo destruye con `pop_scope()`.

```
current_scope → [bloque interno] → [función] → [global] → NULL
                   x = 99           x = 42       x = 1
```

### symbols.c
Dos operaciones fundamentales:
- `create_entry` — crea una variable en el scope actual. Solo revisa el nivel actual para permitir shadowing.
- `find_entry` — busca una variable subiendo por toda la pila de scopes. Retorna la primera coincidencia.

### type_coercion.c
Maneja la conversión entre tipos y la impresión de valores. Todas las operaciones aritméticas se hacen en `double` y luego se convierten al tipo destino.

| Tipo | Formato de impresión |
|---|---|
| `num` | `%d` → `42` |
| `dec` | `%f` → `3.140000` |
| `car` | `%c` → `A` |
| `pal` | `%s` → `Hola mundo` |
| `bool` | `yes` / `no` |

---

## Ejemplos de Uso

### Operaciones aritméticas
```
let a as num = 5;
let b as num = 3;
let suma      as num = a + b;   -- 8
let diferencia as num = a - b;  -- 2
let producto  as num = a * b;   -- 15
let cociente  as num = a / b;   -- 1 (división entera)
```

> Si al menos un operando es `dec`, el resultado es `dec` y la división no trunca.

### Scopes anidados
```
let x as num = 1;
{
    let x as num = 42;
    {
        let x as num = 99;
        mostrar x;   -- 99
    }
    mostrar x;       -- 42
}
mostrar x;           -- 1
```

### Funciones
```
func exterior([num]a) -> [num] {
    let b as num = a + 5;
    retorna b;
}

func interior([num]x) -> [num] {
    let b as num = x * 10;
    retorna b;
}

let r1 as num = exterior(10);  -- 15
let r2 as num = interior(10);  -- 100
mostrar r1;
mostrar r2;
```

La variable `a` no existe antes de llamar la función. Nace en el momento de la llamada cuando el intérprete evalúa el argumento `10`, crea el scope de la función y registra `a = 10` como parámetro. Al terminar la función, `pop_scope()` la elimina.

---

## Manejo de Errores

| Fase | Error | Mensaje |
|---|---|---|
| Sintáctica | Estructura inválida | `[ERROR] syntax error` |
| Semántica | Variable no declarada | `[ERROR] Variable 'x' no declarada` |
| Semántica | Redeclaración | `[ERROR] Variable 'x' ya declarada en este nivel` |
| Semántica | Función no definida | `[ERROR] Funcion 'f' no definida` |
| Semántica | Argumentos incorrectos | `[ERROR] 'f': esperaba N args, recibio M` |
| Runtime | División entre cero | `[ERROR] Division entre cero` |
| Runtime | String como condición | `[ERROR] No se puede usar word como condicion` |
| Sistema | Archivo no encontrado | `[ERROR] No se pudo abrir: archivo.español` |

---

## Tests Automatizados

Los tests viven en `test/*.español`. Cada uno tiene su salida esperada en `EXPECTED_OUTPUTS.txt`:

```
=== nombre_test ===
salida
esperada
```

`make test` corre todos automáticamente y reporta cuántos pasaron y cuántos fallaron.
