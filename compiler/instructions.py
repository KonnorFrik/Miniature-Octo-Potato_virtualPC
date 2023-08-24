ld_ = "ld"
add_ = "add"
sub_ = "sub"
mul_ = "mul"
div_ = "div"
and_ = "and"
or_ = "or"
xor_ = "xor"
inv_ = "inv"
hlt_ = "hlt"


instruction_code_map = {
    # register manipulating
    ld_: 0x01,

    # math
    add_: 0x11,
    sub_: 0x12,
    mul_: 0x13,
    div_: 0x14,

    #logic
    and_: 0x20,
    or_ : 0x21,
    xor_: 0x22,
    inv_: 0x23,

    hlt_: 0xff,
}


