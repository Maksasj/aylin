#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>

int g_in = 0;
int g_out = 0;
int g_buf = 0;

struct Function {
    std::string name;
    int word_n;
    int in , buf , out = 0;
    int pointer;

    Function(int x_point) {
        pointer = x_point;
        in = 0;
        buf = 0;
        out = 0;
    }

    void changevarfromstr(std::vector<std::string> lines, int value) {
        
        if (lines[pointer] == "global") {
            pointer++;
            if (lines[pointer] == "in") {
                g_in = value;
            } else if (lines[pointer] == "buf") {
                g_buf = value;
            } else if (lines[pointer] == "out") {
                g_out = value;
            }
        } else {
            if (lines[pointer] == "in") {
                in = value;
            } else if (lines[pointer] == "buf") {
                buf = value;
            } else if (lines[pointer] == "out") {
                out = value;
            }
        }
        pointer++;
    }

    int returnint(std::vector<std::string> lines, std::vector<int> parent, std::vector<Function>& Functions) {
        std::string line = lines[pointer];
        if (isdigit(line[0])) {
            int val = stoi(lines[pointer]);
            pointer++;
            return val;
        } else {
            if (lines[pointer] == "parent") {
                pointer++;
                if (lines[pointer] == "in") { pointer++; return parent[0];
                } else if (lines[pointer] == "buf") { pointer++; return parent[1];
                } else if (lines[pointer] == "out") { pointer++; return parent[2];  }
            } else
            if (lines[pointer] == "func") {
                pointer++;
                for (auto& function : Functions) {
                    if (lines[pointer] == function.name) {                  
                        pointer++;
                        if (lines[pointer] == "in") { pointer++; return function.in;
                        } else if (lines[pointer] == "buf") { pointer++; return function.buf;
                        } else if (lines[pointer] == "out") { pointer++; return function.out;  }
                    }
                }
            } else 
            if (lines[pointer] == "global") {
                pointer++;
                if (lines[pointer] == "in") { pointer++; return g_in;
                } else if (lines[pointer] == "buf") { pointer++; return g_buf;
                } else if (lines[pointer] == "out") { pointer++; return g_out; }
            } else {
                if (lines[pointer] == "in") {  pointer++; return in;
                } else if (lines[pointer] == "buf") { pointer++; return buf;
                } else if (lines[pointer] == "out") { pointer++; return out;  }
            } 
        }
    }

    void run(std::vector<std::string> lines, std::vector<Function>& Functions, std::vector<int> parent) {
        
        bool end_fun_running = false;
        while (end_fun_running == false) {

            //Ends Execution function
            if (lines[pointer] == "end") {
                break;
            } else 
            
            // Prints in Terminal value (in , buf or out)
            if (lines[pointer] == "say") {
                pointer++;
                std::cout << returnint(lines, parent, Functions) << std::endl;
            } else 
            
            // Wait some time
            if (lines[pointer] == "wait") {
                pointer++;
                Sleep(returnint(lines, parent, Functions));
            } else 
     
            //Set global (in, buf or out) value from local
            if (lines[pointer] == "provide") {
                pointer++;
                int x = returnint(lines, parent, Functions);   
                pointer++;
                changevarfromstr(lines, x);
                
            } else
            
            //Get value from global (in, buf or out)
            if (lines[pointer] == "retrieve") {
                pointer++;
                
                int x = returnint(lines, parent, Functions);
                pointer++;
                changevarfromstr(lines, x);
            } else

            //Checks if values equal , higher or lower. runs function if needed
            if (lines[pointer] == "if") {
                
                pointer++;
                int x = returnint(lines, parent, Functions);

                if (lines[pointer] == "equal") {
                    pointer++;
                    int y = returnint(lines, parent, Functions);

                    if (x == y) {
                        pointer++;
                        for (auto& function : Functions) {
                            if (lines[pointer] == function.name) {
                                if (name == function.name) {
                                    parent = {in , buf, out};
                                    pointer = word_n + 2;
                                } else {
                                    std::vector<int> parent_d = {in , buf, out};
                                    function.run(lines, Functions, parent_d);
                                    pointer++;
                                }                      
                            }          
                        }
                    }
                } else if (lines[pointer] == "higher") {
                    pointer++;
                    int y = returnint(lines, parent,Functions);
                    if (x > y) {
                        pointer++;
                        for (auto& function : Functions) {
                            if (lines[pointer] == function.name) {
                                if (name == function.name) {
                                    parent = {in , buf, out};
                                    pointer = word_n + 2;
                                } else {
                                    std::vector<int> parent_d = {in , buf, out};
                                    function.run(lines, Functions, parent_d);
                                    pointer++;
                                }                      
                            }          
                        }
                    }
                } else if (lines[pointer] == "lower") {
                    pointer++;
                    int y = returnint(lines, parent, Functions);
                    if (x < y) {
                        pointer++;
                        for (auto& function : Functions) {
                            if (lines[pointer] == function.name) {
                                if (name == function.name) {
                                    parent = {in , buf, out};
                                    pointer = word_n + 2;
                                } else {
                                    std::vector<int> parent_d = {in , buf, out};
                                    function.run(lines, Functions, parent_d);
                                    pointer++;
                                }                      
                            }          
                        }
                    }
                }

            } else

            if (lines[pointer] == "reset") {
                pointer++;
                in = 0;
                out = 0;
                buf = 0;
            } else

            //Inverts value in, buf or out
            if (lines[pointer] == "invert") {    
                pointer++;
                int x = returnint(lines, parent, Functions);
                pointer++;
                changevarfromstr(lines, -x);  
            } else 

            //Set value to (in, buf or out)
            if (lines[pointer] == "set") {   
                pointer++;
                int x = returnint(lines, parent, Functions);
                pointer++;
                changevarfromstr(lines, x);
            } else

            //Add value to (in, buf or out)
            if (lines[pointer] == "add") {        
                pointer++;     
                int x = returnint(lines, parent, Functions);
                pointer++;
                int y = returnint(lines, parent, Functions);
                pointer++;
                changevarfromstr(lines, (x+y));
            } else
            
            // Run Function
            {
                for (auto& function : Functions) {
                    if (lines[pointer] == function.name) {
                        if (name == function.name) {
                            parent = {in , buf, out};
                            pointer = word_n + 2;
                        } else {
                            std::vector<int> parent_d = {in , buf, out};
                            function.run(lines, Functions, parent_d);
                            pointer++;
                        }                      
                    }          
                }
            }
        }
    }
};

int main() {
    std::vector<Function> Functions;
    std::vector<std::string> lines;
    std::string line;

    std::ifstream fd ("main.al");
    bool exit = false;
    
    //Write each word in lines vector
    while(exit == false) {
        fd >> line;
        lines.push_back(line);
        if (line == "exit") { exit = true; }
    }
    
    fd.close();

    //Declarate Functions
    for (int x = 0; x < lines.size(); x++) {
        if (lines[x] == "function") {
            Function function(x+2);
            function.name = lines[x+1];
            function.word_n = x;
            Functions.push_back(function);
        }
    }

    //Start Executing Functions
    for (int x = 0; x < lines.size(); x++) {
        if (lines[x] == "function") {
            bool skip_f_dec = false;
            while (skip_f_dec == false) {
                x++;
                if (lines[x] == "end") {skip_f_dec = true;}
            }
        } else {
            for (auto& function : Functions) {
                if (lines[x] == function.name) {
                    function.run(lines, Functions, {0, 0, 0});
                }
            }
        }
    }

    
    system("pause");
    return 0;
}