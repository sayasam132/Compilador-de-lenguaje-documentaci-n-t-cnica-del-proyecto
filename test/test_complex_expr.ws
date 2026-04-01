func add([num]x, [num]y) -> [num] {
    return x + y;
}

func multiply([num]x, [num]y) -> [num] {
    return x * y;
}

func divide([num]x, [num]y) -> [num] {
    return x / y;
}

let r1 as num = add(multiply(2, 3), divide(10, 2));
let r2 as num = multiply(add(5, 5), add(2, 3));
show r1;
show r2;
