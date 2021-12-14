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
        int in = 0;
        int out = 0;
        int buf = 0;
    }

    void run(std::vector<std::string> lines, std::vector<Function> Functions) {
        bool end_fun_running = false;

        while (end_fun_running == false) {
            
            // Set value for IN cell
            if (lines[pointer] == "in") {
                pointer += 1;
                in = stoi(lines[pointer]);
                pointer += 1;
            
            } else 
            
            // Ends Execution function
            if (lines[pointer] == "end") {
                break;
            } else 
            
            // Prints in Terminal value (in , buf or out)
            if (lines[pointer] == "say") {
                pointer += 1;
                if (lines[pointer] == "in") {
                    std::cout << in << std::endl;
                } else if (lines[pointer] == "buf") {
                    std::cout << buf << std::endl;
                } else if (lines[pointer] == "out") {
                    std::cout << out << std::endl;
                }
                pointer += 1;
            } else 
            
            // Wait some time
            if (lines[pointer] == "wait") {
                pointer++;
                Sleep(stoi(lines[pointer]));
                pointer++;
            } else 
            
            //Moves value (in, buf or out) to another
            if (lines[pointer] == "move") {
                pointer++;
                if (lines[pointer] == "in") { // Move from in
                    pointer += 2;
                    if (lines[pointer] == "in") { // To in
                        in = in;  
                    } else if (lines[pointer] == "buf") { // To buf
                        buf = in;
                        in = 0;
                    } else  if (lines[pointer] == "out") { // To out
                        out = in;
                        in = 0;
                    }
                } else if (lines[pointer] == "buf") { // Move from buf
                    pointer += 2;
                    if (lines[pointer] == "in") { // To in
                        in = buf;  
                        buf = 0;
                    } else if (lines[pointer] == "buf") { // To buf
                        buf = buf;
                    } else  if (lines[pointer] == "out") { // To out
                        out = buf;
                        buf = 0;
                    }
                } else  if (lines[pointer] == "out") { // Move from out
                    pointer += 2;
                    if (lines[pointer] == "in") { // To in
                        in = out;  
                        out = 0;
                    } else if (lines[pointer] == "buf") { // To buf
                        buf = out;
                        out = 0;
                    } else  if (lines[pointer] == "out") { // To out
                        out = out;
                    }
                }
                pointer++;
            } else 

            //Copy value (in, buf or out) to another
            if (lines[pointer] == "copy") {
                pointer++;
                if (lines[pointer] == "in") { // Move from in
                    pointer += 2;
                    if (lines[pointer] == "in") { // To in
                        in = in;  
                    } else if (lines[pointer] == "buf") { // To buf
                        buf = in;
                    } else  if (lines[pointer] == "out") { // To out
                        out = in;
                    }
                } else if (lines[pointer] == "buf") { // Move from buf
                    pointer += 2;
                    if (lines[pointer] == "in") { // To in
                        in = buf;  
                    } else if (lines[pointer] == "buf") { // To buf
                        buf = buf;
                    } else  if (lines[pointer] == "out") { // To out
                        out = buf;
                    }
                } else  if (lines[pointer] == "out") { // Move from out
                    pointer += 2;
                    if (lines[pointer] == "in") { // To in
                        in = out;  
                    } else if (lines[pointer] == "buf") { // To buf
                        buf = out;
                    } else  if (lines[pointer] == "out") { // To out
                        out = out;
                    }
                }
                pointer++;
            } else 
            
            //Set global (in, buf or out) value from local
            if (lines[pointer] == "provide") {
                pointer++;
                if (lines[pointer] == "in") {
                    pointer += 2;
                    if (lines[pointer] == "in") {
                        g_in = in;
                    } else if (lines[pointer] == "buf") {
                        g_in = buf;
                    } else if (lines[pointer] == "out") {
                        g_in = out;
                    }
                } else 
                if (lines[pointer] == "buf") {
                    pointer += 2;
                    if (lines[pointer] == "in") {
                        g_buf = in;
                    } else if (lines[pointer] == "buf") {
                        g_buf = buf;
                    } else if (lines[pointer] == "out") {
                        g_buf = out;
                    }
                } else 
                if (lines[pointer] == "out") {
                    pointer += 2;
                    if (lines[pointer] == "in") {
                        g_out = in;
                    } else if (lines[pointer] == "buf") {
                        g_out = buf;
                    } else if (lines[pointer] == "out") {
                        g_out = out;
                    }
                }
                pointer++;
            } else
            
            //Get value from global (in, buf or out)
            if (lines[pointer] == "retrieve") {
                pointer++;
                if (lines[pointer] == "in") {
                    pointer += 2;
                    if (lines[pointer] == "in") {
                        in = g_in;
                    } else if (lines[pointer] == "buf") {
                        buf = g_in;
                    } else if (lines[pointer] == "out") {
                        out = g_in;
                    }
                } else 
                if (lines[pointer] == "buf") {
                    pointer += 2;
                    if (lines[pointer] == "in") {
                        in = g_buf;
                    } else if (lines[pointer] == "buf") {
                        buf = g_buf;
                    } else if (lines[pointer] == "out") {
                        out = g_buf;
                    }
                } else 
                if (lines[pointer] == "out") {
                    pointer += 2;
                    if (lines[pointer] == "in") {
                        in = g_out;
                    } else if (lines[pointer] == "buf") {
                        buf = g_out;
                    } else if (lines[pointer] == "out") {
                        out = g_out;
                    }
                }
                pointer++;
            } else

            //Checks if values equal , higher or lower. runs function if needed
            if (lines[pointer] == "if") {
                pointer++;
                if (lines[pointer] == "in") {
                    pointer++;
                    if (lines[pointer] == "equal") {
                        pointer++;
                        if (lines[pointer] == "in") {
                            pointer += 2;
                            bool recur = false;
                            if (in == in) {
                                for (auto function : Functions) {
                                    if (lines[pointer] == function.name) {
                                        if (name == function.name) {
                                            pointer = word_n + 2;
                                            recur = true;
                                        } else {
                                            function.run(lines, Functions);
                                        }                      
                                    }          
                                }               
                            }
                            
                            if (recur == false) {pointer++;}
                        
                        } else if (lines[pointer] == "buf") {
                            pointer += 2;
                            bool recur = false;
                            if (in == buf) {
                                for (auto function : Functions) {
                                    if (lines[pointer] == function.name) {
                                        if (name == function.name) {
                                            pointer = word_n + 2;
                                            recur = true;
                                        } else {
                                            function.run(lines, Functions);
                                        }                      
                                    }          
                                }               
                            }
                            
                            if (recur == false) {pointer++;}
                        
                        } else if (lines[pointer] == "out") {
                            pointer += 2;
                            bool recur = false;
                            if (in == out) {
                                for (auto function : Functions) {
                                    if (lines[pointer] == function.name) {
                                        if (name == function.name) {
                                            pointer = word_n + 2;
                                            recur = true;
                                        } else {
                                            function.run(lines, Functions);
                                        }                      
                                    }          
                                }               
                            }
                            if (recur == false) {pointer++;}
                        }
                    } else if (lines[pointer] == "higher") {
                        pointer++;
                        if (lines[pointer] == "in") {
                            pointer += 2;
                            bool recur = false;
                            if (in > in) {
                                for (auto function : Functions) {
                                    if (lines[pointer] == function.name) {
                                        if (name == function.name) {
                                            pointer = word_n + 2;
                                            recur = true;
                                        } else {
                                            function.run(lines, Functions);
                                        }                      
                                    }          
                                }               
                            }
                            
                            if (recur == false) {pointer++;}
                        
                        } else if (lines[pointer] == "buf") {
                            pointer += 2;
                            bool recur = false;
                            if (in > buf) {
                                for (auto function : Functions) {
                                    if (lines[pointer] == function.name) {
                                        if (name == function.name) {
                                            pointer = word_n + 2;
                                            recur = true;
                                        } else {
                                            function.run(lines, Functions);
                                        }                      
                                    }          
                                }               
                            }
                            
                            if (recur == false) {pointer++;}
                        
                        } else if (lines[pointer] == "out") {
                            pointer += 2;
                            bool recur = false;
                            if (in > out) {
                                for (auto function : Functions) {
                                    if (lines[pointer] == function.name) {
                                        if (name == function.name) {
                                            pointer = word_n + 2;
                                            recur = true;
                                        } else {
                                            function.run(lines, Functions);
                                        }                      
                                    }          
                                }               
                            }
                            if (recur == false) {pointer++;}
                        }
                    } else if (lines[pointer] == "lower") {
                        pointer++;
                        if (lines[pointer] == "in") {
                            pointer += 2;
                            bool recur = false;
                            if (in < in) {
                                for (auto function : Functions) {
                                    if (lines[pointer] == function.name) {
                                        if (name == function.name) {
                                            pointer = word_n + 2;
                                            recur = true;
                                        } else {
                                            function.run(lines, Functions);
                                        }                      
                                    }          
                                }               
                            }
                            
                            if (recur == false) {pointer++;}
                        
                        } else if (lines[pointer] == "buf") {
                            pointer += 2;
                            bool recur = false;
                            if (in < buf) {
                                for (auto function : Functions) {
                                    if (lines[pointer] == function.name) {
                                        if (name == function.name) {
                                            pointer = word_n + 2;
                                            recur = true;
                                        } else {
                                            function.run(lines, Functions);
                                        }                      
                                    }          
                                }               
                            }
                            
                            if (recur == false) {pointer++;}
                        
                        } else if (lines[pointer] == "out") {
                            pointer += 2;
                            bool recur = false;
                            if (in < out) {
                                for (auto function : Functions) {
                                    if (lines[pointer] == function.name) {
                                        if (name == function.name) {
                                            pointer = word_n + 2;
                                            recur = true;
                                        } else {
                                            function.run(lines, Functions);
                                        }                      
                                    }          
                                }               
                            }
                            if (recur == false) {pointer++;}
                        }
                    }
                } else if (lines[pointer] == "buf") {
                    pointer++;
                    if (lines[pointer] == "equal") {
                        pointer++;
                        if (lines[pointer] == "in") {
                            pointer += 2;
                            bool recur = false;
                            if (buf == in) {
                                for (auto function : Functions) {
                                    if (lines[pointer] == function.name) {
                                        if (name == function.name) {
                                            pointer = word_n + 2;
                                            recur = true;
                                        } else {
                                            function.run(lines, Functions);
                                        }                      
                                    }          
                                }               
                            }
                            
                            if (recur == false) {pointer++;}
                        
                        } else if (lines[pointer] == "buf") {
                            pointer += 2;
                            bool recur = false;
                            if (buf == buf) {
                                for (auto function : Functions) {
                                    if (lines[pointer] == function.name) {
                                        if (name == function.name) {
                                            pointer = word_n + 2;
                                            recur = true;
                                        } else {
                                            function.run(lines, Functions);
                                        }                      
                                    }          
                                }               
                            }
                            
                            if (recur == false) {pointer++;}
                        
                        } else if (lines[pointer] == "out") {
                            pointer += 2;
                            bool recur = false;
                            if (buf == out) {
                                for (auto function : Functions) {
                                    if (lines[pointer] == function.name) {
                                        if (name == function.name) {
                                            pointer = word_n + 2;
                                            recur = true;
                                        } else {
                                            function.run(lines, Functions);
                                        }                      
                                    }          
                                }               
                            }
                            if (recur == false) {pointer++;}
                        }
                    } else if (lines[pointer] == "higher") {
                        pointer++;
                        if (lines[pointer] == "in") {
                            pointer += 2;
                            bool recur = false;
                            if (buf > in) {
                                for (auto function : Functions) {
                                    if (lines[pointer] == function.name) {
                                        if (name == function.name) {
                                            pointer = word_n + 2;
                                            recur = true;
                                        } else {
                                            function.run(lines, Functions);
                                        }                      
                                    }          
                                }               
                            }
                            
                            if (recur == false) {pointer++;}
                        
                        } else if (lines[pointer] == "buf") {
                            pointer += 2;
                            bool recur = false;
                            if (buf > buf) {
                                for (auto function : Functions) {
                                    if (lines[pointer] == function.name) {
                                        if (name == function.name) {
                                            pointer = word_n + 2;
                                            recur = true;
                                        } else {
                                            function.run(lines, Functions);
                                        }                      
                                    }          
                                }               
                            }
                            
                            if (recur == false) {pointer++;}
                        
                        } else if (lines[pointer] == "out") {
                            pointer += 2;
                            bool recur = false;
                            if (buf > out) {
                                for (auto function : Functions) {
                                    if (lines[pointer] == function.name) {
                                        if (name == function.name) {
                                            pointer = word_n + 2;
                                            recur = true;
                                        } else {
                                            function.run(lines, Functions);
                                        }                      
                                    }          
                                }               
                            }
                            if (recur == false) {pointer++;}
                        }
                    } else if (lines[pointer] == "lower") {
                        pointer++;
                        if (lines[pointer] == "in") {
                            pointer += 2;
                            bool recur = false;
                            if (buf < in) {
                                for (auto function : Functions) {
                                    if (lines[pointer] == function.name) {
                                        if (name == function.name) {
                                            pointer = word_n + 2;
                                            recur = true;
                                        } else {
                                            function.run(lines, Functions);
                                        }                      
                                    }          
                                }               
                            }
                            
                            if (recur == false) {pointer++;}
                        
                        } else if (lines[pointer] == "buf") {
                            pointer += 2;
                            bool recur = false;
                            if (buf < buf) {
                                for (auto function : Functions) {
                                    if (lines[pointer] == function.name) {
                                        if (name == function.name) {
                                            pointer = word_n + 2;
                                            recur = true;
                                        } else {
                                            function.run(lines, Functions);
                                        }                      
                                    }          
                                }               
                            }
                            
                            if (recur == false) {pointer++;}
                        
                        } else if (lines[pointer] == "out") {
                            pointer += 2;
                            bool recur = false;
                            if (buf < out) {
                                for (auto function : Functions) {
                                    if (lines[pointer] == function.name) {
                                        if (name == function.name) {
                                            pointer = word_n + 2;
                                            recur = true;
                                        } else {
                                            function.run(lines, Functions);
                                        }                      
                                    }          
                                }               
                            }
                            if (recur == false) {pointer++;}
                        }
                    }
                } else if (lines[pointer] == "out") {
                    pointer++;
                    if (lines[pointer] == "equal") {
                        pointer++;
                        if (lines[pointer] == "in") {
                            pointer += 2;
                            bool recur = false;
                            if (out == in) {
                                for (auto function : Functions) {
                                    if (lines[pointer] == function.name) {
                                        if (name == function.name) {
                                            pointer = word_n + 2;
                                            recur = true;
                                        } else {
                                            function.run(lines, Functions);
                                        }                      
                                    }          
                                }               
                            }
                            
                            if (recur == false) {pointer++;}
                        
                        } else if (lines[pointer] == "buf") {
                            pointer += 2;
                            bool recur = false;
                            if (out == buf) {
                                for (auto function : Functions) {
                                    if (lines[pointer] == function.name) {
                                        if (name == function.name) {
                                            pointer = word_n + 2;
                                            recur = true;
                                        } else {
                                            function.run(lines, Functions);
                                        }                      
                                    }          
                                }               
                            }
                            
                            if (recur == false) {pointer++;}
                        
                        } else if (lines[pointer] == "out") {
                            pointer += 2;
                            bool recur = false;
                            if (out == out) {
                                for (auto function : Functions) {
                                    if (lines[pointer] == function.name) {
                                        if (name == function.name) {
                                            pointer = word_n + 2;
                                            recur = true;
                                        } else {
                                            function.run(lines, Functions);
                                        }                      
                                    }          
                                }               
                            }
                            if (recur == false) {pointer++;}
                        }
                    } else if (lines[pointer] == "higher") {
                        pointer++;
                        if (lines[pointer] == "in") {
                            pointer += 2;
                            bool recur = false;
                            if (out > in) {
                                for (auto function : Functions) {
                                    if (lines[pointer] == function.name) {
                                        if (name == function.name) {
                                            pointer = word_n + 2;
                                            recur = true;
                                        } else {
                                            function.run(lines, Functions);
                                        }                      
                                    }          
                                }               
                            }
                            
                            if (recur == false) {pointer++;}
                        
                        } else if (lines[pointer] == "buf") {
                            pointer += 2;
                            bool recur = false;
                            if (out > buf) {
                                for (auto function : Functions) {
                                    if (lines[pointer] == function.name) {
                                        if (name == function.name) {
                                            pointer = word_n + 2;
                                            recur = true;
                                        } else {
                                            function.run(lines, Functions);
                                        }                      
                                    }          
                                }               
                            }
                            
                            if (recur == false) {pointer++;}
                        
                        } else if (lines[pointer] == "out") {
                            pointer += 2;
                            bool recur = false;
                            if (out > out) {
                                for (auto function : Functions) {
                                    if (lines[pointer] == function.name) {
                                        if (name == function.name) {
                                            pointer = word_n + 2;
                                            recur = true;
                                        } else {
                                            function.run(lines, Functions);
                                        }                      
                                    }          
                                }               
                            }
                            if (recur == false) {pointer++;}
                        }
                    } else if (lines[pointer] == "lower") {
                        pointer++;
                        if (lines[pointer] == "in") {
                            pointer += 2;
                            bool recur = false;
                            if (out < in) {
                                for (auto function : Functions) {
                                    if (lines[pointer] == function.name) {
                                        if (name == function.name) {
                                            pointer = word_n + 2;
                                            recur = true;
                                        } else {
                                            function.run(lines, Functions);
                                        }                      
                                    }          
                                }               
                            }
                            
                            if (recur == false) {pointer++;}
                        
                        } else if (lines[pointer] == "buf") {
                            pointer += 2;
                            bool recur = false;
                            if (out < buf) {
                                for (auto function : Functions) {
                                    if (lines[pointer] == function.name) {
                                        if (name == function.name) {
                                            pointer = word_n + 2;
                                            recur = true;
                                        } else {
                                            function.run(lines, Functions);
                                        }                      
                                    }          
                                }               
                            }
                            
                            if (recur == false) {pointer++;}
                        
                        } else if (lines[pointer] == "out") {
                            pointer += 2;
                            bool recur = false;
                            if (out < out) {
                                for (auto function : Functions) {
                                    if (lines[pointer] == function.name) {
                                        if (name == function.name) {
                                            pointer = word_n + 2;
                                            recur = true;
                                        } else {
                                            function.run(lines, Functions);
                                        }                      
                                    }          
                                }               
                            }
                            if (recur == false) {pointer++;}
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
                if (lines[pointer] == "in") {
                    in = in * -1;
                } else if (lines[pointer] == "buf") {
                    buf = buf * -1;
                } else if (lines[pointer] == "out") {
                    out = out * -1;
                }
                pointer++;   
            } else
            
            //Add value of 1 var to another
            if (lines[pointer] == "sum") {
                pointer++;
                if (lines[pointer] == "in") {
                    pointer += 2;
                    if (lines[pointer] == "in") {
                    in = in + in;    
                    } else if (lines[pointer] == "buf") {
                    in = in + buf;    
                    } else if (lines[pointer] == "out") {
                    in = in + out;    
                    }
                } else if (lines[pointer] == "buf") {
                    pointer += 2;
                    if (lines[pointer] == "in") {
                    buf = buf + in;    
                    } else if (lines[pointer] == "buf") {
                    buf = buf + buf;    
                    } else if (lines[pointer] == "out") {
                    buf = buf + out;    
                    }
                } else if (lines[pointer] == "out") {
                    pointer += 2;
                    if (lines[pointer] == "in") {
                    out = out + in;    
                    } else if (lines[pointer] == "buf") {
                    out = out + buf;    
                    } else if (lines[pointer] == "out") {
                    out = out + out;    
                    }
                }
                pointer++;
            } else

            //Set value to (in, buf or out)
            if (lines[pointer] == "set") {        
                if (lines[pointer+3] == "in") {
                    in = stoi(lines[pointer+1]);
                    pointer += 4;
                } else if (lines[pointer+3] == "buf") {
                    buf = stoi(lines[pointer+1]);
                    pointer += 4;
                } else if (lines[pointer+3] == "out") {
                    out = stoi(lines[pointer+1]);
                    pointer += 4;
                } 
                
            } else

            //Add value to (in, buf or out)
            if (lines[pointer] == "add") {        
                if (lines[pointer+3] == "in") {
                    in += stoi(lines[pointer+1]);
                    pointer += 4;
                } else if (lines[pointer+3] == "buf") {
                    buf += stoi(lines[pointer+1]);
                    pointer += 4;
                } else if (lines[pointer+3] == "out") {
                    out += stoi(lines[pointer+1]);
                    pointer += 4;
                } 
                
            } else
            
            // Run Function
            {
                for (auto function : Functions) {
                    if (lines[pointer] == function.name) {
                        if (name == function.name) {
                            pointer = word_n + 2;
                        } else {
                            function.run(lines, Functions);
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
            for (auto function : Functions) {
                if (lines[x] == function.name) {
                    function.run(lines, Functions);
                }
            }
        }
    }

    system("pause");
    return 0;
}