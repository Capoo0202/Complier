# include <stdio.h>
# include <iostream>
# include <vector>
#include <stdio.h>
#include <cstdlib>
using namespace std;

struct TokenStyle {
  string type;
  string name;
  int num;
};

vector<TokenStyle> command;
int count_command = 0;
int now_command = 0;

int iscommand = -1;
bool error = false;

TokenStyle temp;
int num_set = 0;
string name_set;

int store_int = 0;
bool store_bool = false;
int re = 0;

vector<string> store_id;
vector<int> store_id_num;

int iswrong = 0;
bool issame = false;
int same_site = 0;
bool exp();

bool separator(char ch) {
    if ( ch == '\t' || ch == ' ' || ch == '\n' || ch == '\r' || ch == '(' || ch == ')' ) return true;
    else return false;
} // separator(char ch)

bool isnum(char ch) {
    string s;
    char c;
    if ( ch == '0' && separator(cin.peek()) ) {
        num_set = 0;
        return true;
    } // if
    
    else if ( 1 <= ch - '0' && ch - '0' <= 9 ) {
        s = s + ch;
        while ( !separator(cin.peek())  ) {
            cin >> c;
            if ( 0 <= c - '0' && c - '0' <= 9 ) {
                s = s + c;
            } // if
            
            else return false;
        } // while
        
        num_set = atoi(s.c_str());
        return true;
    } // else if
    
    else if ( ch == '-' && !separator(cin.peek()) ) {
        s = s + ch;
        cin >> c;
        if ( 1 <= c - '0' &&  - '0' <= 9 ) {
            s = s + c;
            while ( !separator(cin.peek()) ) {
                cin >> c;
                if ( 0 <= c - '0' && c - '0' <= 9 ) {
                    s = s + c;
                } // if
                
                else return false;
            } // while 
        } // if 
        
        else return false;
        
        num_set = atoi(s.c_str());
        return true;
    } // else if
    
    else return false;
} // isnum()

bool isid(char ch) {
    char c;
    if ( 'a' <= ch && ch <= 'z' ) {
        name_set = name_set + ch;
        while ( !separator(cin.peek()) ) {
            cin >> c;
            if ( 'a' <= c && c <= 'z' ) name_set = name_set + c;
            else if ( 0 <= c - '0' && c - '0' <= 9 ) name_set = name_set + c;
            else if ( c == '-' ) name_set = name_set + c;
            else return false;
        } // while
        
        return true;
    } // if
    
    else return false;
} // isid()

void check_type( char ch) {
    if ( ch == '+' && separator(cin.peek()) ) {
        temp.type = "PLUS";
        temp.name = "+";
        command.push_back(temp);
    } 
    
    else if ( ch == '-' && separator(cin.peek()) ) {
        temp.type = "MINUS";
        temp.name = "-";
        command.push_back(temp);
    } 
    
    else if ( ch == '*' && separator(cin.peek()) ) {
        temp.type = "MUL";
        temp.name = "*";
        command.push_back(temp);
    } 
    
    else if ( ch == '/' && separator(cin.peek()) ) {
        temp.type = "DIV";
        temp.name = "/";
        command.push_back(temp);
    } 
    
    else if ( ch == '>' && separator(cin.peek()) ) {
        temp.type = "GREATER";
        temp.name = ">";
        command.push_back(temp);
    } 
    
    else if ( ch == '<' && separator(cin.peek()) ) {
        temp.type = "SMALLER";
        temp.name = "<";
        command.push_back(temp);
    } 
    
    else if ( ch == '=' && separator(cin.peek()) ) {
        temp.type = "EQUAL";
        temp.name = "=";
        command.push_back(temp);
    } 
    
    else if ( ch == '#' ) {
        if ( cin.peek() == 't' ) {
            char c;
            cin >> c;
            if ( separator(cin.peek()) ) {
                temp.type = "TRUE";
                temp.name = "#t";
                command.push_back(temp);
            } // if
            
            else error = true;
        } // if
        
        else if ( cin.peek() == 'f' ) {
            char c;
            cin >> c;
            if ( separator(cin.peek()) ) {
                temp.type = "FALSE";
                temp.name = "#f";
                command.push_back(temp);
            } // if
            
            else error = true;
        } // else if
        
        else error = true;
    }
    else if ( isnum(ch) ) {
        temp.type = "NUM";
        temp.num = num_set;
        command.push_back(temp);
    } // ')'
    
    else if ( isid(ch) ) {
        if ( name_set == "mod" ) {
            temp.type = "MOD";
        } // if
        
        else if ( name_set == "and" ) {
            temp.type = "AND";
        } // else if
        
        else if ( name_set == "or" ) {
            temp.type = "OR";
        } // else if
        
        else if ( name_set == "not" ) {
            temp.type = "NOT";
        } // else if
        
        else if ( name_set == "print-num" ) {
            temp.type = "PN";
        } // else if
        
        else if ( name_set == "print-bool" ) {
            temp.type = "PB";
        } // else if
        
        else if ( name_set == "if" ) {
            temp.type = "IF";
        } // else if
        
        else if ( name_set == "define" ) {
            temp.type = "DEFINE";
        } // else if
        
        
        
        else temp.type = "ID";
        
        
        temp.name = name_set;
        command.push_back(temp);
    } // ')'
    
    else error = true;
     
    name_set.clear();
    num_set = -1;
    temp.name.clear();
    temp.type.clear();
    temp.num = -1;
} // check_type()

void get_command() {
    char ch;
    while ( cin.peek() != EOF  ) {
        cin >> ch; 
        if ( !separator(ch) ) {
            check_type(ch);
        } // if ( !separator(ch) )
        
        else if ( ch == '(' ) {
            temp.type = "LP";
            temp.name = "(";
            command.push_back(temp);
        
            if ( iscommand == -1 ) iscommand = 1;
            else iscommand = iscommand + 1;
        } 
    
        else if ( ch == ')' ) {
            temp.type = "RP";
            temp.name = ")";
            command.push_back(temp);
        
            iscommand = iscommand - 1; 
        } 
        
        count_command++;
        if ( iscommand == 0 ) break;
    } // while ( ch != '\n' !! ch != EOF )
    
    if ( cin.peek() == EOF && iscommand != 0 ) error = true; 
} // get_command()


bool def_stmt() {
    if ( command[now_command].type == "LP" && command[now_command + 1].type == "DEFINE") {
        now_command = now_command + 2;
        if ( command[now_command].type == "ID" ) {
            now_command++;
            if ( exp () ) {
                if ( command[now_command].type == "RP" ) {
                    now_command++;
                    return true;
                } // if
                    
                else return false;
            } // if
                
            else return false;
        } // if
            
        else return false;
    } // if define
} // def_stmt()

bool if_exp() {
    if ( command[now_command].type == "LP" && command[now_command + 1].type == "IF") {
        now_command = now_command + 2;
        if ( exp() ) {
            if ( exp () ) {
                if ( exp() ) {
                    if ( command[now_command].type == "RP" ) {
                        now_command++;
                        return true;
                    } // if
                    
                    else return false;
                } // if
                    
                else return false;
            } // if
                
            else return false;
        } // if
            
        else return false;
    } // if and
} // if_exp()

bool logical_op() {
    if ( command[now_command].type == "LP" && command[now_command + 1].type == "AND") {
        now_command = now_command + 2;
        if ( exp() ) {
            if ( exp () ) {
                while ( exp() ) ;
                if ( command[now_command].type == "RP" ) {
                    now_command++;
                    return true;
                } // if
                    
                else return false;
            } // if
                
            else return false;
        } // if
            
        else return false;
    } // if and
    
    else if ( command[now_command].type == "LP" && command[now_command + 1].type == "OR") {
        now_command = now_command + 2;
        if ( exp() ) {
            if ( exp () ) {
                while ( exp() ) ;
                if ( command[now_command].type == "RP" ) {
                    now_command++;
                    return true;
                } // if
                    
                else return false;
            } // if
                
            else return false;
        } // if
            
        else return false;
    } // if OR
    
    else if ( command[now_command].type == "LP" && command[now_command + 1].type == "NOT") {
        now_command = now_command + 2;
        if ( exp() ) {
            if ( command[now_command].type == "RP" ) {
                now_command++;
                return true;
            } // if
                    
            else return false;
        } // if
            
        else return false;
    } // if not
    
    else return false;
} // logical_op()

bool num_op() {
    if ( command[now_command].type == "LP" && command[now_command + 1].type == "PLUS") {
        now_command = now_command + 2;
        if ( exp() ) {
            if ( exp () ) {
                while ( exp() ) ;
                    
                if ( command[now_command].type == "RP" ) {
                    now_command++;
                    return true;
                } // if
                    
                else return false;
            } // if
                
            else return false;
        } // if
            
        else return false;
    } // if +
        
    else if ( command[now_command].type == "LP" && command[now_command + 1].type == "MINUS") {
        now_command = now_command + 2;
        if ( exp() ) {
            if ( exp () ) {
                if ( command[now_command].type == "RP" ) {
                    now_command++;
                    return true;
                } // if
                    
                else return false;
            } // if
                
            else return false;
        } // if
            
        else return false;
    } // if -
        
    else if ( command[now_command].type == "LP" && command[now_command + 1].type == "MUL") {
        now_command = now_command + 2;
        if ( exp() ) {
            if ( exp () ) {
                while ( exp() ) ;
                if ( command[now_command].type == "RP" ) {
                    now_command++;
                    return true;
                } // if
                    
                else return false;
            } // if
                
            else return false;
        } // if
            
        else return false;
    } // if * 
        
    else if ( command[now_command].type == "LP" && command[now_command + 1].type == "DIV") {
        now_command = now_command + 2;
        if ( exp() ) {
            if ( exp () ) {
                if ( command[now_command].type == "RP" ) {
                    now_command++;
                    return true;
                } // if
                    
                else return false;
            } // if
                
            else return false;
        } // if
            
        else return false;
    } // if / 
        
    else if ( command[now_command].type == "LP" && command[now_command + 1].type == "MOD") {
        now_command = now_command + 2;
        if ( exp() ) {
            if ( exp () ) {
                if ( command[now_command].type == "RP" ) {
                    now_command++;
                    return true;
                } // if
                    
                else return false;
            } // if
                
            else return false;
        } // if
            
        else return false;
    } // if mod 
        
    else if ( command[now_command].type == "LP" && command[now_command + 1].type == "GREATER") {
        now_command = now_command + 2;
        if ( exp() ) {
            if ( exp () ) {
                if ( command[now_command].type == "RP" ) {
                    now_command++;
                    return true;
                } // if
                    
                else return false;
            } // if
                
            else return false;
        } // if
            
        else return false;
    } // if > 
        
    else if ( command[now_command].type == "LP" && command[now_command + 1].type == "SMALLER") {
        now_command = now_command + 2;
        if ( exp() ) {
            if ( exp () ) {
                if ( command[now_command].type == "RP" ) {
                    now_command++;
                    return true;
                } // if
                    
                else return false;
            } // if
                
            else return false;
        } // if
            
        else return false;
    } // if <
        
    else if ( command[now_command].type == "LP" && command[now_command + 1].type == "EQUAL") {
        now_command = now_command + 2;
        if ( exp() ) {
            if ( exp () ) {
                while ( exp() ) ;
                if ( command[now_command].type == "RP" ) {
                    now_command++;
                    return true;
                } // if
                    
                else return false;
            } // if
                
            else return false;
        } // if
            
        else return false;
    } // if <
    
    else return false;
} // num-op()

bool exp() {
    if ( command[now_command].type == "TRUE" ) {
        now_command++;
        return true;
    } // if
    
    else if ( command[now_command].type == "FALSE" ) {
        now_command++;
        return true;
    } // else if
    
    else if ( command[now_command].type == "NUM" ) {
        now_command++;
        return true;
    } // else if
    
    else if ( command[now_command].type == "ID" ) {
        now_command++;
        return true;
    } // else if
    
    else if ( num_op() ) {
        return true;
    } // else if
    
    else if ( logical_op() ) {
        return true;
    } // else if
    
    else if ( if_exp() ) {
        return true;
    } // else if
    
    else return false;
} // exp()

bool print_stmt() {
    if ( command[now_command].type == "LP" && command[now_command + 1].type == "PN" ) {
        now_command = now_command + 2;
        if ( exp() ) {
            if ( command[now_command].type == "RP" ) {
                now_command++;
                return true;
            } // if
            
            else return false;
        } // if
        
        else return false;
    } // IF
    
    else if ( command[now_command].type == "LP" && command[now_command + 1].type == "PB" ) {
        now_command = now_command + 2;
        if ( exp() ) {
            if ( command[now_command].type == "RP" ) {
                now_command++;
                return true;
            } // if
            
            else return false;
        } // if
        
        else return false;
    } // IF
    
    else return false;
} // print-stmt()

bool stmts() {
    if ( exp() ) return true;
    else if ( def_stmt() ) return true;
    else if ( print_stmt() ) return true;
    else return false;
} // stmts()

bool program() {
    if ( stmts() ) return true;
    else return false;
} // program()

void do_command() {
    int sum = 0;
    bool b = false;
    
    int first = 0;
    int second = 0;
    bool f = false;
    bool s = false;
    
    bool issecond = false;
    
    bool isif = false;
    while ( command[now_command].type != "RP" ) {
        if ( command[now_command].type == "LP" ) {
            now_command++;
            do_command();
        } // if (
        
        else if ( command[now_command].type == "PLUS" ) {
            now_command++;
            while ( command[now_command].type != "RP" ) {
                if ( command[now_command].type == "NUM" ) {
                    if ( issecond == false ) {
                        sum =  command[now_command].num;
                        issecond = true;
                    }
                    else  sum = sum + command[now_command].num;
                    if ( re > 0 ) store_int = sum;
                    now_command++;
                } // IF NUM
                
                else if ( command[now_command].type == "ID" ) {
                    for ( int i = 0; i < store_id.size() ; i++ ) {
                        if (command[now_command].name == store_id[i] ) {
                            if ( issecond == false ) {
                                sum =  store_id_num[i];
                                issecond = true;
                            }
                            else  sum = sum + store_id_num[i];
                        } // if
                    } // for
                    
                    if ( re > 0 ) store_int = sum;
                    now_command++;
                } // IF id
                
                else if ( command[now_command].type == "LP" ) {
                    re++;
                    now_command++;
                    do_command();
                    if ( issecond == false ) {
                        sum = store_int;
                        issecond = true;
                    }
                    else  sum = sum + store_int;
                    if ( re > 0 ) store_int = sum;
                } // if (
                
            } // while
            
        } // if +
        
        else if ( command[now_command].type == "MINUS" ) {
            now_command++;
            while ( command[now_command].type != "RP" ) {
                if ( command[now_command].type == "NUM" ) {
                    if ( issecond == false ) {
                        sum =  command[now_command].num;
                        issecond = true;
                    }
                    else  sum = sum - command[now_command].num;
                    if ( re > 0 ) store_int = sum;
                    now_command++;
                } // IF NUM
                
                else if ( command[now_command].type == "ID" ) {
                    for ( int i = 0; i < store_id.size() ; i++ ) {
                        if (command[now_command].name == store_id[i] ) {
                            if ( issecond == false ) {
                                sum =  store_id_num[i];
                                issecond = true;
                            }
                            else  sum = sum - store_id_num[i];
                        } // if
                    } // for
                    
                    if ( re > 0 ) store_int = sum;
                    now_command++;
                } // IF id
                
                else if ( command[now_command].type == "LP" ) {
                    re++;
                    now_command++;
                    do_command();
                    if ( issecond == false ) {
                        sum = store_int;
                        issecond = true;
                    }
                    else  sum = sum - store_int;
                    if ( re > 0 ) store_int = sum;
                } // if (
                
            } // while
            
        } // if -
        
        else if ( command[now_command].type == "MUL" ) {
            now_command++;
            while ( command[now_command].type != "RP" ) {
                if ( command[now_command].type == "NUM" ) {
                    if ( issecond == false ) {
                        sum = command[now_command].num;
                        issecond = true;
                    }
                    else sum = sum * command[now_command].num;
                    if ( re > 0 ) store_int = sum;
                    now_command++;
                } // IF NUM
                
                else if ( command[now_command].type == "ID" ) {
                    for ( int i = 0; i < store_id.size() ; i++ ) {
                        if (command[now_command].name == store_id[i] ) {
                            if ( issecond == false ) {
                                sum =  store_id_num[i];
                                issecond = true;
                            }
                            else  sum = sum * store_id_num[i];
                        } // if
                    } // for
                    
                    if ( re > 0 ) store_int = sum;
                    now_command++;
                } // IF id
                
                else if ( command[now_command].type == "LP" ) {
                    re++;
                    now_command++;
                    do_command();
                    if ( issecond == false ) {
                        sum = store_int;
                        issecond = true;
                    }
                    
                    else sum = sum * store_int;
                    if ( re > 0 ) store_int = sum;
                } // if (
                
            } // while
            
        } // if *
        
        else if ( command[now_command].type == "DIV" ) {
            now_command++;
            while ( command[now_command].type != "RP" ) {
                if ( command[now_command].type == "NUM" ) {
                    if ( issecond == false ) {
                        sum = command[now_command].num;
                        issecond = true;
                    }
                    else sum = sum / command[now_command].num;
                    if ( re > 0 ) store_int = sum;
                    now_command++;
                } // IF NUM
                
                else if ( command[now_command].type == "ID" ) {
                    for ( int i = 0; i < store_id.size() ; i++ ) {
                        if (command[now_command].name == store_id[i] ) {
                            if ( issecond == false ) {
                                sum =  store_id_num[i];
                                issecond = true;
                            }
                            else  sum = sum / store_id_num[i];
                        } // if
                    } // for
                    
                    if ( re > 0 ) store_int = sum;
                    now_command++;
                } // IF id
                
                else if ( command[now_command].type == "LP" ) {
                    re++;
                    now_command++;
                    do_command();
                    if ( issecond == false ) {
                        sum = store_int;
                        issecond = true;
                    }
                    else sum = sum / store_int;
                    if ( re > 0 ) store_int = sum;
                } // if (
                
            } // while
            
        } // if /
        
        else if ( command[now_command].type == "MOD" ) {
            now_command++;
            while ( command[now_command].type != "RP" ) {
                if ( command[now_command].type == "NUM" ) {
                    if ( issecond == false ) {
                        sum = command[now_command].num;
                        issecond = true;
                    }
                    else sum = sum % command[now_command].num;
                    if ( re > 0 ) store_int = sum;
                    now_command++;
                } // IF NUM
                
                else if ( command[now_command].type == "ID" ) {
                    for ( int i = 0; i < store_id.size() ; i++ ) {
                        if (command[now_command].name == store_id[i] ) {
                            if ( issecond == false ) {
                                sum =  store_id_num[i];
                                issecond = true;
                            }
                            else  sum = sum % store_id_num[i];
                        } // if
                    } // for
                    
                    if ( re > 0 ) store_int = sum;
                    now_command++;
                } // IF id
                
                else if ( command[now_command].type == "LP" ) {
                    re++;
                    now_command++;
                    do_command();
                    if ( issecond == false ) {
                        sum = store_int;
                        issecond = true;
                    }
                    else sum = sum % store_int;
                    if ( re > 0 ) store_int = sum;
                } // if (
                
            } // while
            
        } // if mod
        
        else if ( command[now_command].type == "PN" ) {
            now_command++;
            while ( command[now_command].type != "RP" ) {
                if ( command[now_command].type == "NUM" ) {
                    cout << command[now_command].num << endl;
                    now_command++;
                } // IF NUM
                
                else if ( command[now_command].type == "ID" ) {
                    for ( int i = 0; i < store_id.size() ; i++ ) {
                        if (command[now_command].name == store_id[i] ) {
                            cout << store_id_num[i] << endl;
                        } // if
                    } // for
                    now_command++;
                } // IF id
                
                else if ( command[now_command].type == "LP" ) {
                    re++;
                    now_command++;
                    do_command();
                    cout << store_int << endl;
                } // if (
                
            } // while
            
        } // if print-num
        
        else if ( command[now_command].type == "GREATER" ) {
            now_command++;
            while ( command[now_command].type != "RP" ) {
                if ( command[now_command].type == "NUM" ) {
                    if ( issecond == false ) {
                        first = command[now_command].num;
                        issecond = true;
                    }
                    else {
                        second = command[now_command].num;
                        if ( first > second ) b = true;
                        else b = false;
                    } 
                    if ( re > 0 ) store_bool = b;
                    now_command++;
                } // IF NUM
                
                else if ( command[now_command].type == "LP" ) {
                    re++;
                    now_command++;
                    do_command();
                    if ( issecond == false ) {
                        first = store_int;
                        issecond = true;
                    }
                    else {
                       second =  store_int;
                       if ( first > second ) b = true;
                       else b = false;
                    }
                    if ( re > 0 ) store_bool = b;
                } // if (
                
            } // while
            
        } // if >
        
        else if ( command[now_command].type == "SMALLER" ) {
            now_command++;
            while ( command[now_command].type != "RP" ) {
                if ( command[now_command].type == "NUM" ) {
                    if ( issecond == false ) {
                        first = command[now_command].num;
                        issecond = true;
                    }
                    else {
                        second = command[now_command].num;
                        if ( first < second ) b = true;
                        else b = false;
                    }
                    
                    if ( re > 0 ) store_bool = b;
                    now_command++;
                } // IF NUM
                
                else if ( command[now_command].type == "LP" ) {
                    re++;
                    now_command++;
                    do_command();
                    if ( issecond == false ) {
                        first = store_int;
                        issecond = true;
                    }
                    else {
                       second =  store_int;
                       if ( first < second ) b = true;
                       else b = false;
                    }
                    if ( re > 0 ) store_bool = b;
                } // if (
                
            } // while
            
        } // if <
        
        else if ( command[now_command].type == "EQUAL" ) {
            now_command++;
            while ( command[now_command].type != "RP" ) {
                if ( command[now_command].type == "NUM" ) {
                    if ( issecond == false ) {
                        first = command[now_command].num;
                        issecond = true;
                    }
                    else {
                        second = command[now_command].num;
                        if ( first == second ) b = true;
                        else b = false;
                    }
                    
                    if ( re > 0 ) store_bool = b;
                    now_command++;
                } // IF NUM
                
                else if ( command[now_command].type == "LP" ) {
                    re++;
                    now_command++;
                    do_command();
                    if ( issecond == false ) {
                        first = store_int;
                        issecond = true;
                    }
                    else {
                       second =  store_int;
                       if ( first == second ) b = true;
                       else b = false;
                    }
                    if ( re > 0 ) store_bool = b;
                } // if (
                
            } // while
            
        } // if =
        
        else if ( command[now_command].type == "AND" ) {
            now_command++;
            while ( command[now_command].type != "RP" ) {
                if ( command[now_command].type == "TRUE" ) {
                    if ( issecond == false ) {
                        f = true;
                        issecond = true;
                    }
                    else {
                        s = true;
                        if ( f == true && s == true ) b = true;
                        else b = false;
                    }
                    
                    if ( re > 0 ) store_bool = b;
                    now_command++;
                } // IF #T
                
                else if ( command[now_command].type == "FALSE" ) {
                    if ( issecond == false ) {
                        f = false;
                        issecond = true;
                    }
                    else {
                        s = false;
                        b = false;
                    }
                    
                    if ( re > 0 ) store_bool = b;
                    now_command++;
                } // IF #f
                
                else if ( command[now_command].type == "LP" ) {
                    re++;
                    now_command++;
                    do_command();
                    if ( issecond == false ) {
                        f = store_bool;
                        issecond = true;
                    }
                    else {
                       s =  store_bool;
                       if ( f == true && s == true ) b = true;
                        else b = false;
                    }
                    if ( re > 0 ) store_bool = b;
                } // if (
                
            } // while
            
        } // if and
        
        else if ( command[now_command].type == "OR" ) {
            now_command++;
            while ( command[now_command].type != "RP" ) {
                if ( command[now_command].type == "TRUE" ) {
                    if ( issecond == false ) {
                        f = true;
                        issecond = true;
                    }
                    else {
                        s = true;
                        if ( f == true || s == true ) b = true;
                        else b = false;
                    }
                    
                    if ( re > 0 ) store_bool = b;
                    now_command++;
                } // IF #T
                
                else if ( command[now_command].type == "FALSE" ) {
                    if ( issecond == false ) {
                        f = false;
                        issecond = true;
                    }
                    else {
                        s = false;
                        if ( f == true || s == true ) b = true;
                        else b = false;
                    }
                    
                    if ( re > 0 ) store_bool = b;
                    now_command++;
                } // IF #f
                
                else if ( command[now_command].type == "LP" ) {
                    re++;
                    now_command++;
                    do_command();
                    if ( issecond == false ) {
                        f = store_bool;
                        issecond = true;
                    }
                    else {
                       s =  store_bool;
                       if ( f == true || s == true ) b = true;
                       else b = false;
                    }
                    if ( re > 0 ) store_bool = b;
                } // if (
                
            } // while
            
        } // if or
        
        else if ( command[now_command].type == "NOT" ) {
            now_command++;
            while ( command[now_command].type != "RP" ) {
                if ( command[now_command].type == "TRUE" ) {
                    b = false;
                    if ( re > 0 ) store_bool = b;
                    now_command++;
                } // IF #T
                
                else if ( command[now_command].type == "FALSE" ) {
                    b = true;
                    if ( re > 0 ) store_bool = b;
                    now_command++;
                } // IF #f
                
                else if ( command[now_command].type == "LP" ) {
                    re++;
                    now_command++;
                    do_command();
                    if ( store_bool == true ) b = false;
                    else b = true;
                    if ( re > 0 ) store_bool = b;
                } // if (
                
            } // while
            
        } // if not
        
        else if ( command[now_command].type == "PB" ) {
            now_command++;
            while ( command[now_command].type != "RP" ) {
                if ( command[now_command].type == "TRUE" ) {
                    cout << "#t" << endl;
                    now_command++;
                } // IF #t
                
                else if ( command[now_command].type == "FALSE" ) {
                    cout << "#f" << endl;
                    now_command++;
                } // IF #f
                
                else if ( command[now_command].type == "LP" ) {
                    re++;
                    now_command++;
                    do_command();
                    if ( store_bool == true ) cout << "#t" << endl;
                    else cout << "#f" << endl;
                } // if (
                
            } // while
            
        } // if print-bool
        
        else if ( command[now_command].type == "IF" ) {
            now_command++;
            while ( command[now_command].type != "RP" ) {
                if ( command[now_command].type == "TRUE" ) {
                    b = true;
                    isif = true;
                    if ( re > 0 ) store_bool = b;
                    now_command++;
                } // IF #T
                
                else if ( command[now_command].type == "FALSE" ) {
                    b = false;
                    isif = true;
                    if ( re > 0 ) store_bool = b;
                    now_command++;
                } // IF #f
                
                else if ( command[now_command].type == "NUM" ) {
                    
                    if ( issecond == false ) {
                        first = command[now_command].num;
                        issecond = true;
                    }
                    
                    else {
                        second = command[now_command].num;
                        if ( b == true ) sum = first;
                        else sum = second;
                    }
                    
                    if ( re > 0 ) store_int = sum;
                    now_command++;
                } // IF NUM
                
                else if ( command[now_command].type == "LP" ) {
                    re++;
                    now_command++;
                    do_command();
                    if ( isif == false ) {
                        b = store_bool;
                        isif = true;
                    }
                    else {
                        if ( issecond == false ) {
                            first = store_int;
                            issecond = true;
                        }
                        else {
                            second = store_int;
                            if ( b == true ) sum = first;
                            else sum = second;
                        } // else
                    }
                    
                    if ( re > 0 ) store_int = sum;
                } // if (
                
            } // while
            
        } // if if
        
        else if ( command[now_command].type == "DEFINE" ) {
            now_command++;
            while ( command[now_command].type != "RP" ) {
                if ( command[now_command].type == "ID" ) {
                    for ( int i = 0; i < store_id.size() ; i++ ) {
                        if (command[now_command].name == store_id[i] ) {
                            issame = true;
                            same_site = i;
                        } // if
                    } // for
                    
                    if( issame == false ) store_id.push_back(command[now_command].name);
                    issecond = true;
                    now_command++;
                } // IF id
                
                else if (command[now_command].type == "NUM") {
                    if ( issecond == true ) {
                        if( issame == true ) {
                            store_id_num[same_site] = command[now_command].num;
                        } // if
                        else store_id_num.push_back(command[now_command].num);
                    }
                    
                    if ( re > 0 ) store_int = sum;
                    now_command++;
                } // if num
                
                else if ( command[now_command].type == "LP" ) {
                    re++;
                    now_command++;
                    do_command();
                    if ( issecond == false ) {
                        store_id.push_back(command[now_command].name);
                        issecond = true;
                    }
                    else {
                        store_id_num.push_back(store_int);
                    } // else
                    
                    if ( re > 0 ) store_int = sum;
                } // if (
                
            } // while
            
        } // if define
        
    }  // while
    
    if ( re > 0 ) {
        re--;
        now_command++;
    }
} // do_command()

int main() {
    char ch;
    while ( cin.peek() != EOF ) {
        get_command();
        if ( error == false  && program() ) {
            now_command = 0;
            if ( command[now_command].type == "LP" ) now_command++;
            do_command();
        } // if
        else {
            if ( iswrong == 0 ) cout << "syntax error" << endl;    
        } 
        
        iswrong = 0;
        count_command = 0; 
        now_command = 0;
        iscommand = -1;
        error = false;
        num_set = 0;
        command.clear();
        issame  = false;
        same_site = 0;
    } // while ( ch != EOF )
} // main
