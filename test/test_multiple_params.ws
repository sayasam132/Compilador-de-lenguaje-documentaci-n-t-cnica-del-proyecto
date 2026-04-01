func sum_three([num]a, [num]b, [num]c) -> [num] {
    return a + b + c;
}

func sum_four([num]w, [num]x, [num]y, [num]z) -> [num] {
    return w + x + y + z;
}

let r1 as num = sum_three(10, 20, 30);
let r2 as num = sum_four(5, 10, 15, 20);
show r1;
show r2;
