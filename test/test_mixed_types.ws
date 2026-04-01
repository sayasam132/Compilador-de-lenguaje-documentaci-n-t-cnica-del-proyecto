func add_mixed([num]x, [dec]y) -> [dec] {
    return x + y;
}

let i as num = 5;
let d as dec = 2.5;
let result as dec = add_mixed(i, d);
show result;
