func local_vars([num]x) -> [num] {
    let y as num = x * 2;
    let z as num = y + 10;
    return z;
}

let result as num = local_vars(5);
show result;
