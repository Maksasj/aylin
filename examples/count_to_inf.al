function count
    retrieve in to buf
    say buf
    add 1 to buf
    provide in with buf
    count
end

function main
    in 1
    move in to buf
    provide in with buf
    count
end

main
exit