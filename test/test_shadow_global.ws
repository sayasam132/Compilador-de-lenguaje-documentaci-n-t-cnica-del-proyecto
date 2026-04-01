func shadow_global() -> [num] {
    let x as num = 100;
    return x;
}

let x as num = 5;
let global as num = x;
let local as num = shadow_global();
show global;
show local;
