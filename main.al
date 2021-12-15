function main
    set 500 to global in
    set global in to out
    set out to global buf
    invert global buf
    say global buf
    f1
end

function f1
    set parent out to out
    f2
end

function f2
    wait parent out
    say parent out
end

main
exit