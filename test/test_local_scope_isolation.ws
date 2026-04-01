func outer([num]a) -> [num] {
    let b as num = a + 5;
    return b;
}

func inner([num]x) -> [num] {
    let b as num = x * 10;
    return b;
}

let r1 as num = outer(10);
let r2 as num = inner(10);
show r1;
show r2;
