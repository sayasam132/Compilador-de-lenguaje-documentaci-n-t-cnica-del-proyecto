func add_double([dec]x, [dec]y) -> [dec] {
    return x + y;
}

func multiply_double([dec]x, [dec]y) -> [dec] {
    return x * y;
}

let r1 as dec = add_double(3.5, 2.5);
let r2 as dec = multiply_double(2.0, 3.5);
show r1;
show r2;
