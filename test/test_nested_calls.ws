func add([num]x, [num]y) -> [num] {
    return x + y;
}

func multiply([num]x, [num]y) -> [num] {
    return x * y;
}

func subtract([num]x, [num]y) -> [num] {
    return x - y;
}

let r1 as num = multiply(add(2, 3), 4);
let r2 as num = add(multiply(3, 4), 5);
let r3 as num = subtract(multiply(10, 2), add(5, 5));
show r1;
show r2;
show r3;
