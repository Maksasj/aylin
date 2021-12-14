function division
    retrieve in to in
    retrieve buf to buf
    retrieve out to out
    

    sum in with buf

    provide in with in

    add 1 to out
    
    provide out with out
    set 0 to out
    if in higher out run division
    
    retrieve out to out

    say out
    
    invert in
    
    provide in with in

    set 10 to out
    provide out with out
    multiplicationbyten
    retrieve in to in
    say in
end

function main
    in 8
    move in to buf
    in 36

    provide in with in
    invert buf
    provide buf with buf
    set -1 to out
    provide out with out

    division
end

function multiplicationbyten
    retrieve in to in
    retrieve out to out
    sum in with in
    provide in with in
    say out
    add -1 to out
    provide out with out
    in 10
    if out higher in run multiplicationbyten
end

main
exit