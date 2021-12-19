# Aylin-REPO
Aylin - simple [esoteric programming language](https://en.wikipedia.org/wiki/Esoteric_programming_language) , made just for fun. 

# Syntax

`exit` - Means end of file. After that, the interpreter will not read

`[value]` - Always integer 
  - `1` - Just integer
  - `in` - value from local `in` cell (also can be `buf` or `out`)
  - `parent in` - value from parent function (`buf` , `out` included) 
  - `global in` - same with parent , but returns value from global cell
  - `func [name] in` - returns selected value from specific function, where:
    - `func` - Key word
    - `[name]` - Name of selected function
    - `in` - same with usual in. Ofcourse can be (`buf` or `out`) 

`function [name]` - Declares a function
  - `[name]` - name of urs function

`end` - Means end of function

`say [value]` - Prints value in terminal

`endline` - Just ends line , adds line break

`wait [value]` - Stops function for specific time

`reset` - Resets local cells to 0

`invert [value]` - Invert value , multiplies value by -1

`set [value1] to [value2]` - Set specific value in specific cell. Also can set values in other functions
  - `[value1]` - Where value what u want set
  - `[value2]` - In what cell u want set value

`add [value1] to [value2] into [value3]` - Add two values together , and stores them in specific cell
  - `[value1]` - First term
  - `[value2]` - Second term
  - `[value3]` - Cell in what u want store result

`if [value1] [condition] [value2] run [function]` - Checks for a condition, and if the condition is true runs the function
  - `[value1]` - First Value
  - `[value2]` - Second Value
  - `[condition]` - Condition , can be: `equal` , `higher` , `lower`
  - `[function]` - Name of function what u want run , if statement true





 
