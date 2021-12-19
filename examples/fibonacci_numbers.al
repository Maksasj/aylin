function first end
function second end

function main
    set 0 to func first in
    set 1 to func second in

    loop
end

function loop
    say func first in endline
    set func first in to buf
    add func first in to func second in into func first in
    set buf to func second in
    loop
end

main
exit