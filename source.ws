-- ============================================================
-- source.ws — prueba del lenguaje
-- ============================================================
---
-- Tipos de dato basicos
let edad     as num    = 22;
let precio   as dec    = 9.99;
let inicial  as letter = 'K';
let saludo   as word   = "Hola mundo";
let activo   as bool   = yes;
let inactivo as bool   = no;
let error as bool   = hola;

-- Expresiones aritmeticas con + y -
let suma  as num = edad + 8;
let resta as num = 100 - 55;

-- Expresiones con * y /
let producto  as num = 4 * 3;
let resultado as num = (100 - 55) * 2;
let cociente  as dec = 9.0 / 4.0;

-- Mostrar todos los valores
show edad;
show precio;
show inicial;
show saludo;
show activo;
show inactivo;
show suma;
show resta;
show producto;
show resultado;
show cociente;
show error;
---

let x as num = 1;
{
    let x as num = 42;
    {
        let x as num = 99;
        show x;        -- imprime 99
    }
    show x;            -- imprime 42
}
show x;                -- imprime 1
