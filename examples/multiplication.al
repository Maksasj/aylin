function multiplication
    retrieve in to in
    retrieve buf to buf
    retrieve out to out

    add -1 to buf
    sum in with out

    provide in with in
    provide buf with buf
    
    in 1
    copy in to out
    if buf higher out run multiplication
end

function main
    in 5
    move in to buf
    in 5

    provide in with in
    provide buf with buf
    provide out with in

    multiplication
    retrieve in to buf
    say buf
end

main
exit