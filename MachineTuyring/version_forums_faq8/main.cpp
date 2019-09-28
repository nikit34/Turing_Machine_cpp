#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;


// класс исключение
class Exeption{
    public:
        void error(int line){
            cout << "Error in " << line + 1 << " line" << endl;
        }
};

class TuyringMachine {
    private:
        int repeated; // ?
        Exeption ex; // cout errors, when in code
        bool stopped; // flag stop read or write

        // working with file out and in
        string src_filename, in_filename, out_filename, log_filename;
        string line; // buffer for line
        int line_size;
        string now_state; // ?
        vector<string> source; // buffer commands

        void go(); // ?
        void execute_command(string cmd); // ?

        /*
        v - action (l - left, r - right, s - stop(stat))
        q0, q1, q2, ..., qk - stations
        a - alphabet
        */

        // v - l, r, s
        void change_letter(char let);
        void move_left();
        void move_right();
        void stop();

        string get_state(string cmd);  // q0
        string get_read_letter(string cmd);  // a
        string get_write_letter(string cmd);  // a
        string get_next_state(string cmd);  // qk
        string get(string cmd, int k);  // ?

        bool test_execute(string cmd);
        bool validation_command_test(string cmd);
        bool error_test();

    public:
        TuyringMachine(string src_filename_, string in_filename_, string out_filename_);
        TuyringMachine();

        void run();
        void print_result();
};

TuyringMachine::TuyringMachine(string src_filename_, string in_filename_, string out_filename_):src_filename(src_filename_), in_filename(in_filename_), now_state("00"), repeated(0), stopped(false){}

TuyringMachine::TuyringMachine():src_filename("src.txt"), in_filename("input.txt"), now_state("00"), repeated(0), stopped(false){}

void TuyringMachine::run(){
    ifstream src(src_filename.c_str());
    ifstream in(in_filename.c_str());

    while(!in.eof()){
        getline(in, line);
    }

    line_size = line.size();
    line.push_back(' ');

    while(!src.eof()){
        string cmd;
        getline(src, cmd);
        source.push_back(cmd);
    }

    error_test();

    if(!stopped){
        go();
        print_result();
        cout << "Success!" << endl;
    }
}

bool TuyringMachine::error_test(){
    int s = 0;
    for(int i=0; i<source.size(); ++i){
        string state = get_state(source[i]);
        string read_letter = get_read_letter(source[i]);
        string write_letter = get_write_letter(source[i]);
        string next_state = get_next_state(source[i]);

        if(state.size() == 0 || read_letter.size() == 0 || read_letter.size() > 1 || write_letter.size() == 0 || write_letter.size() > 1 || next_state.size() == 0){
            ex.error(i);
            stopped = 1;
            ++s;
        }
    }
    cout << s << " errors" << endl;
}

void TuyringMachine::go(){
    for(int i=0; i<source.size() && !stopped; ++i){
        if(test_execute(source[i])){
            execute_command(source[i]);
            i = 0;
        }

    }
}

string TuyringMachine::get(string cmd,int k){
    int s = 0;
    string tmp;

    for(int i=0; i<cmd.size(); ++i){
        if(cmd[i] == ','){
            ++s; ++i;
        }
        if(s == k && i < cmd.size()){
            tmp.push_back(cmd[i]);
        }
        if(s > k){
            return tmp;
        }
    }
    return tmp;
}

string TuyringMachine::get_state(string cmd){
    return get(cmd, 0);
}
string TuyringMachine::get_read_letter(string cmd){
    return get(cmd, 1);
}
string TuyringMachine::get_write_letter(string cmd){
    return get(cmd, 2);
}
string TuyringMachine::get_next_state(string cmd){
    return get(cmd, 3);
}

bool validation_command_test(string cmd){
    return true;
}

bool TuyringMachine::test_execute(string cmd){
    string state = get_state(cmd);
    string read_latter = get_read_letter(cmd);

    return state == now_state && read_latter[0] == line[line_size];
}

void TuyringMachine::execute_command(string cmd){
    string write_letter = get_write_letter(cmd);
    string next_state = get_next_state(cmd);

    if(write_letter == ">"){
        move_right();
    }
    else if(write_letter == "<"){
        move_left();
    }
    else if(write_letter == "#"){
        stopped = true;
    }
    else {
        change_letter(write_letter[0]);
    }
    now_state = next_state;
    print_result();
}

void TuyringMachine::change_letter(char let){
    line[line_size] = let;
}

void TuyringMachine::move_right(){
    line_size++;
    if(line_size >= line.size()){
        line.push_back(' ');
    }
}

void TuyringMachine::move_left(){
    if(line_size > 0){
        line_size--;
    }
}

void TuyringMachine::print_result(){
    cout << line << endl;
    for(int i=0; i<line_size; ++i){
        cout << " ";
    }
    cout << "^" << endl << endl;
}

int main(){
    TuyringMachine MT = TuyringMachine();
    MT.run();
}
