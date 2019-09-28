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

        void move(int &q0, const string &cmd, int &qk, int &pos, vector<vector<int>> &stat_q){

            cout << " ___________________________MOVE___________________________" << endl;
            cout << " state 0               : " << q0 << endl;
            cout << " cmd (for state 0)     : " << cmd << endl;
            cout << " state k               : " << qk << endl;
            cout << " position (in state 0) : " << pos << endl;
            cout << " __________________________________________________________" << endl << endl << endl;

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
        void change(int &q0,  const string &cmd, int &qk, char &a, vector<vector<int>> &stat_q){

        };

        void read(int &q0, int &qk, vector<int> tmp){

        };
        void write(int &q0, int &qk, vector<int> tmp){

        };
};

class Option{
    public:
        void options(vector<vector<int>> &stat_slice){
            cout << " _________________________display_states_________________________" << endl;
            cout << "   " << "  states 0  " << "  positions  " << endl;
            for (int i = 0; i < stat_slice.size(); ++i){
                cout << "       " << stat_slice[i][0] << "            " << stat_slice[i][1] << endl;
            }
            cout << " ________________________________________________________________" << endl << endl << endl;
        }
};

class M_turing: public Move, public Change{
    public:
        Move M;
        Change C;
        Option O;

        void run(int &q0, string &cmd, vector<char> &A, int &qk, vector<vector<int>> &stat_q, int &pos){
            char let = '\0';

            cout << " ___________________________INPUT_DATA___________________________" << endl;
            cout << " Start STATE Q0" << endl;
            cout << " (format: <int -number state>):                              : ";
            cin >> q0;

            cout << " proc. STATE Qk" << endl;
            cout << " (format: <int -number state>):                              : ";
            cin >> qk;

            cout << endl << " COMMAND [ +letter] or only service" << endl;
            cout << " (format: <cmd -{'right', 'left', 'stop', 'read', 'write'}>," << endl;
            cout << "          <letter -optional after 'write'>, " << endl;
            cout << "          <display -service view states>)>:                  : ";
            cin >> cmd;
            if (cmd.compare("write") == 0){
                while (true){
                    cin >> let;
                    for (int i = 0; i < A.size(); ++i){
                        if (let == A[i]){
                            break;
                        }
                    }
                    cout << " letter is not in the alphabet" << endl;
                }
            }
            cout << " ________________________________________________________________" << endl << endl << endl;


            bool push_flag = true;
			for (int i = 0; i < stat_q.size(); ++i){
                if (stat_q[i][0] == q0){
                    push_flag = false;
                    stat_q[i][1] = pos;
                }
			}

            if (push_flag == true){
                stat_q.push_back({q0, pos});
            }

            if ((cmd.compare("right") == 0) || (cmd.compare("left") == 0) || (cmd.compare("stop") == 0)){
                M.move(q0, cmd, qk, pos, stat_q);
            } else if ((cmd.compare("read") == 0) || (cmd.compare("write") == 0)){
                C.change(q0, cmd, qk, let, stat_q);
            } else if (cmd.compare("display") == 0){
                O.options(stat_q);
            } else {
                cout << " Error in command" << endl;
            }

            q0 = qk;
            //vec = q0, pos, let
        };
};


int main(){
    M_turing MT;

    int q0 = 0;
    string cmd;
    vector<char> A;
    int qk = q0;

    int pos = 500;
    vector<vector<int>> stat_q = {{q0, pos}};

    for (char c = 'A'; c <= 'Z'; c++){
        A.push_back(c);
    }

    while (cin){
        MT.run(q0, cmd, A, qk, stat_q, pos);
    }

    cout << "Entered incorrect data." << endl;
    return 0;
}
