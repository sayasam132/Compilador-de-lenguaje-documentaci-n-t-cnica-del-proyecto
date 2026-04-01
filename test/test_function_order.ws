func second([num]x) -> [num] {
    return x + 10;
}

func first([num]x) -> [num] {
    return x * 2;
}

func third([num]x) -> [num] {
    return x - 5;
}

let r1 as num = first(5);
let r2 as num = second(10);
let r3 as num = third(20);
show r1;
show r2;
show r3;
