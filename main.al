function width set 120 to in end
function hight set 30 to in end

function x_axis_c set 0 to in end
function y_axis_c set 0 to in end

function loop_c set 0 to in end

function output set 0 to in end

function main
    loop
end

function test
    say 9
    set 9 to func x_axis_c in
end

function liner
    set 1 to func output in
end

function loop
    add 1 to func x_axis_c in into func x_axis_c in
    if func x_axis_c in equal 120 run x_axis_c
    

    if func x_axis_c in equal 120 run test
    if func x_axis_c in equal 20 run liner
    if func x_axis_c in equal 21 run output

    add 1 to func loop_c in into func loop_c in

    say func output in
    if func loop_c in lower 3600 run loop 
end

main
exit