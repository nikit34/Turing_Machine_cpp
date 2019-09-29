#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;

class Line{
    public:
        pair<int, int> init(int &pos, pair<int, int> *tmp){
            int lenght = 999;
            int step = 1;
            if (pos >= lenght || pos < 0){
                cout << "errorIndex, exit to boarder" << endl;
            }
            *tmp = make_pair(pos, step);
            return *tmp;
        }
};

class Move: Line{
    public:
        Line L;

        void move(int &q0, const string &cmd, int &qk, char &let, int &pos){

            if (cmd.compare("right") == 0){
                right(pos);
            }
            else if (cmd.compare("left") == 0){
                left(pos);
            }
            else if (cmd.compare("stop") == 0){
                stop(pos);
            }
            cout << " move ready" << endl << endl;

            cout << " ______________________________MOVE________________________________" << endl;
            cout << " state 0               : " << q0 << endl;
            cout << " cmd (for state 0)     : " << cmd << endl;
            cout << " state k               : " << qk << endl;
            cout << " letter (in state 0)   : " << let << endl;
            cout << " position (in state 0) : " << pos << endl;
            cout << " __________________________________________________________________" << endl << endl << endl;
        };

        void right(int &pos){
            pair<int, int> tmp;
            tmp = L.init(pos, &tmp);
            pos = tmp.first + tmp.second;
        };
        void left(int &pos){
            pair<int, int> tmp;
            tmp = L.init(pos, &tmp);
            pos = tmp.first - tmp.second;
        };
        void stop(int &pos){
            pair<int, int> tmp;
            tmp = L.init(pos, &tmp);
            pos = tmp.first;
        };
};

class Change{
    public:
        void change(int &q0, const string &cmd, int &qk, char &let, int &pos, vector<char> &A){

            if (cmd.compare("read") == 0){
                read(q0, let, pos);
            } else if (cmd.compare("write") == 0){
                write(A, let);
            }

            cout << " _____________________________CHANGE_______________________________" << endl;
            cout << " state 0               : " << q0 << endl;
            cout << " cmd (for state 0)     : " << cmd << endl;
            cout << " state k               : " << qk << endl;
            cout << " letter (in state 0)   : " << let << endl;
            cout << " position (in state 0) : " << pos << endl;
            cout << " __________________________________________________________________" << endl << endl << endl;
        };

        void read(int &q0, char &let, int &pos){
            cout << " ______________________output_reading_cell_________________________" << endl;
            cout << " output lerret         : " << let << endl;
            cout << " for state             : " << q0 << endl;
            cout << " in position           : " << pos << endl << endl << endl;
        };
        void write(vector<char> &A, char &let){
            bool write_flag = true;
            while (write_flag){
                cout << endl << " enter letter for write:                                       : ";
                cin >> let;
                for (int i = 0; i < A.size(); ++i){
                    if (let == A[i]){
                        write_flag = false;
                        break;
                    }
                }
                if (write_flag == true){
                    cout << endl << " letter is not in the alphabet" << endl;
                }
            }
        };
};

class Option{
    public:
        void options(string &cmd, vector<vector<int>> &stat_slice){
            if (cmd.compare("display") == 0){
                cout << " _________________________display_states___________________________" << endl;
                cout << "   " << "  states 0  " << "  positions  " <<  "  letter  " << endl;
                for (int i = 0; i < stat_slice.size(); ++i){
                    cout << "       " << stat_slice[i][0] << "            " << stat_slice[i][1] << "         " << (char)stat_slice[i][2] << endl;
                }
                cout << " __________________________________________________________________" << endl << endl << endl;
            } else if (cmd.compare("clear") == 0){
                stat_slice.erase(stat_slice.begin()+1, stat_slice.end()+1);
                cout << " vector statics clear" << endl;
            }
        }

        void recard_stat(vector<vector<int>> & stat_q, int &q0, int &pos, char &let){
            bool push_flag = true;
			for (int i = 0; i < stat_q.size(); ++i){
                if (stat_q[i][0] == q0){
                    push_flag = false;
                    stat_q[i][1] = pos;
                    stat_q[i][2] = let;
                }
            }
            if (push_flag == true){
                stat_q.push_back({q0, pos, let});
            }
        }
};

class M_turing: public Move, public Change{
    public:
        Move M;
        Change C;
        Option O;

        struct input_fields{
            int &q0;
            string &cmd;
            vector<char> &A;
            int &qk;
            vector<vector<int>> &stat_q;
            char &let;
            int &pos;
        };

        struct input_fields input_data(int &q0, string &cmd, vector<char> &A, int &qk, vector<vector<int>> &stat_q, char &let, int &pos){
            string start_point;

            cout << " ____________________________INPUT_DATA____________________________" << endl;
            cout << endl << endl << " service command" << endl;
            cout << " (format:  <'display' -service view states>)>, " << endl;
            cout << "           <'clear'  -service clean states>)>. Or any other    : ";
            cin >> cmd;
            if ((cmd.compare("display") == 0) || (cmd.compare("clear") == 0)){
                O.recard_stat(stat_q, q0, pos, let);
                O.options(cmd, stat_q);
            } else {
                cout << " service commands don`t set";
            }

            cout <<  endl << endl << " Start STATE Q0  (" << q0 << ")" << endl;
            cout << " enter 'start' for set start point. Otherwise, any other       : ";
            cin >> start_point;
            if (start_point.compare("start") == 0){
                cout << " (format: <int -number state>):                                : ";
                cin >> q0;
            } else {
                cout << " start point don`t set";
            }

            cout << endl << endl << " processing STATE Qk" << endl;
            cout << " (format: <int -number state>):                                : ";
            cin >> qk;

            cout << endl << endl << " COMMAND [ +letter]" << endl;
            cout << " (format: <cmd -{" << endl;
            cout << "                   'right'," << endl;
            cout << "                   'left'," << endl;
            cout << "                   'stop'," << endl;
            cout << "                   'read'," << endl;
            cout << "                   'write'" << endl;
            cout << "                 }>," << endl;
            cout << "          <letter -optional after 'write'>,                    : ";
            cin >> cmd;

            cout << endl << " __________________________________________________________________" << endl << endl << endl;
        }

        void run(int &q0, string &cmd, vector<char> &A, int &qk, vector<vector<int>> &stat_q, int &pos, char &let){
            struct input_fields f = input_data(q0, cmd, A, qk, stat_q, let, pos);
            O.recard_stat(stat_q, q0, pos, let);

            if ((cmd.compare("right") == 0) || (cmd.compare("left") == 0) || (cmd.compare("stop") == 0)){
                M.move(q0, cmd, qk, let, pos);
            } else if ((cmd.compare("read") == 0) || (cmd.compare("write") == 0)){
                C.change(q0, cmd, qk, let, pos, A);
            }  else {
                cout << " Error in command" << endl;
            }

            q0 = qk;
        };
};


int main(){
    M_turing MT;

    int q0 = 0;
    string cmd;
    vector<char> A;
    int qk = q0;

    int pos = 500;
    char let = '\0';
    vector<vector<int>> stat_q = {{q0, pos, let}};

    for (char c = 'a'; c <= 'z'; c++){
        A.push_back(c);
    }

    while (cin){
        MT.run(q0, cmd, A, qk, stat_q, pos, let);
    }

    cout << "Entered incorrect data." << endl;
    return 0;
}
