ld_ = "ld"
sav_ = "sav"
swp_ = "swp"

add_ = "add"
sub_ = "sub"
mul_ = "mul"
div_ = "div"

and_ = "and"
or_ = "or"
xor_ = "xor"
inv_ = "inv"
lsh_ = "lsh"
rsh_ = "rsh"

jmp_ = "jmp"
jez_ = "jez"
jnz_ = "jnz"

mem_ = "mem" # not used here
mem_inc = "inc"
mem_dec = "dec"
mem_set = "set"
read_ = "read"
write_ = "write"

hlt_ = "hlt"


instruction_code_map = {
    # register manipulating
    ld_: 0x01,
    sav_: 0x02,
    swp_: 0x03,

    # math
    add_: 0x11,
    sub_: 0x12,
    mul_: 0x13,
    div_: 0x14,

    # logic
    and_: 0x20,
    or_ : 0x21,
    xor_: 0x22,
    inv_: 0x23,
    lsh_: 0x27,
    rsh_: 0x28,

    # memory
    jmp_: 0x30,
    jez_: 0x31,
    jnz_: 0x32,
    mem_inc: 0x36,
    mem_dec: 0x37,
    mem_set: 0x38,
    read_: 0x39,
    write_: 0x3a,

    hlt_: 0xff,
}

instruction_code_map_mod = {
    # register manipulating
    ld_: 0x04,
    sav_: 0x05,
    swp_: 0x06,

    # math
    add_: 0x15,
    sub_: 0x16,
    mul_: 0x17,
    div_: 0x18,

    # logic
    and_: 0x24,
    or_ : 0x25,
    xor_: 0x26,
    lsh_: 0x29,
    rsh_: 0x2a,

    # memory
    jmp_: 0x33,
    jez_: 0x34,
    jnz_: 0x35,
}
