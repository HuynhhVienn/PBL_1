#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>

using namespace std;
int d = 1;
#define E 2.718281828;
#define Pi 3.141592654;
int isdigit(char c){
    if(c >= '0' && c <= '9') return 1;
    return 0;
}
int isoperatorc(char c){
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%') return 1;
    return 0;
}
int isoperator(string c){
    if(c == "+" || c == "-" || c == "*" || c == "/" || c == "^" || c == "%") return 1;
    return 0;
}
int pri(string c){
    if(c == "+" || c == "-") return 1;
    if(c == "*" || c == "/") return 2;
    if(c == "^") return 3;
    if(c == "ln" || c == "log" || c == "sin" || c == "cos" || c == "tan" || c == "cot" || c == "sqrt" || c == "cbrt" || c == "rt") return 4;
    if(c == "ln-" || c == "log-" || c == "sin-" || c == "cos-" || c == "tan-" || c == "cot-" || c == "sqrt-" || c == "cbrt-" || c == "rt-") return 4;
    if(c == "+()" || c == "-()") return 5;
    return 0;
}
int isspecial(string s){
    if(s == "ln" || s == "cos" || s == "sin" || s == "tan" || s == "cot" || s == "log" ||s == "cbrt" || s == "sqrt" || s == "rt" || s == "abs" || s == "+()" || s == "-()") return 1;
    if(s == "atan" || s == "asin" || s == "acos") return 1;
    if(s == "atan-" || s == "asin-" || s == "acos-") return 1;
    if(s == "ln-" || s == "cos-" || s == "sin-" || s == "tan-" || s == "cot-" || s == "log-" || s == "cbrt-" || s == "sqrt-" || s == "rt-" || s == "abs-") return 1;
    return 0;
}
int is_sin(string s){
    if(s == "cos") return 1;
    if(s == "sin") return 1;
    if(s == "tan") return 1;
    if(s == "cot") return 1;  
    if(s == "cos-") return 1;
    if(s == "sin-") return 1;
    return 0;
}
double equalspecial(string s, double tmp){
    if(s == "ln") return log(tmp);
    if(s == "log") return log(tmp) / log(10);
    if(s == "cos") return cos(tmp);
    if(s == "sin") return sin(tmp);
    if(s == "tan") return tan(tmp);
    if(s == "cot") return 1 / tan(tmp);
    if(s == "sqrt") return sqrt(tmp);
    if(s == "cbrt") return cbrt(tmp);
    if(s == "abs") return fabs(tmp);
    if(s == "+()") return tmp;
    if(s == "atan") return atan(tmp);
    if(s == "asin") return asin(tmp);
    if(s == "acos") return acos(tmp);
    if(s == "-()") return -tmp;
    if(s == "ln-") return -log(tmp);
    if(s == "log-") return -log(tmp) / log(10);
    if(s == "cos-") return -cos(tmp);
    if(s == "sin-") return -sin(tmp);
    if(s == "tan-") return -tan(tmp);
    if(s == "cot-") return -1 / tan(tmp);
    if(s == "sqrt-") return -sqrt(tmp);
    if(s == "cbrt-") return -cbrt(tmp);
    if(s == "abs-") return -fabs(tmp);
    if(s == "atan-") return -atan(tmp);
    if(s == "asin-") return -asin(tmp);
    if(s == "acos-") return -acos(tmp);
    return 0;
}
int is_asin(string s){
    if(s == "asin" || s == "atan" || s == "acos" || s == "asin-" || s == "atan-" || s == "acos-") return 1;
    return 0; 
}
int is_alpha(string s){
    if(s == "e" || s == "pi" || s == "e-" || s == "pi-") return 1;
    return 0;
}
double equal(queue<string> q, int mode){
    stack<double> st;
    while(!q.empty()){
        while(!isoperator(q.front()) && !isspecial(q.front()) && !q.empty()){
            if(is_alpha(q.front())){
                if(q.front() == "e") st.push(exp(1));
                else if(q.front() == "e-") st.push(-exp(1));
                else if(q.front() == "pi-") st.push(-M_PI);
                else if(q.front() == "pi") st.push(M_PI);
                q.pop();
            }
            else{
                st.push(stod(q.front()));
                q.pop();
            }
        }
        if(q.empty()) break;
        if(isspecial(q.front())){
            if(q.front() == "log-"){
                double s = st.top();
                st.pop();
                st.top() = -log(s) / log(st.top());
                q.pop();
            }
            else if(q.front() == "log"){
                double s = st.top();
                st.pop();
                st.top() = log(s) / log(st.top());
                q.pop();
            }
            else if(q.front() == "rt"){
                double s = st.top();
                int dau = 0;
                if(s < 0){
                    s = -s;
                    dau = 1;
                }
                st.pop();
                st.top() = pow(s, 1 / st.top());
                if(dau == 1) st.top() = -st.top();
                q.pop();
            }
            else if(q.front() == "rt-"){
                double s = st.top();
                int dau = 0;
                if(s < 0){
                    s = -s;
                    dau = 1;
                }
                st.pop();
                st.top() = -pow(s, 1 / st.top());
                if(dau == 1) st.top() = -st.top();
                q.pop();
            }
            else{       
                if(is_sin(q.front()) && mode == 2) st.top() = st.top() * 180 / M_PI;
                st.top() = equalspecial(q.front(), st.top());
                if(mode == 2 && is_asin(q.front())) st.top() = st.top() * 180 / M_PI;
                q.pop();
            }
        }
        else{
            double s = st.top();
            st.pop();
            if(q.front() == "+") st.top() += s;
            else if(q.front() == "-") st.top() -= s;
            else if(q.front() == "*") st.top() *= s;
            else if(q.front() == "/") st.top() /= s;
            else if(q.front() == "^") st.top() = pow(st.top(), s);
            q.pop();
        }
    }
    return st.top();
}
void xuatqueue(queue<string> q, stack<string> st){
    while(!st.empty()){
        cout  << st.top() << " ";
        st.pop();
    }
    cout << "       ";
    while(!q.empty()){
        cout << q.front() << " ";
        q.pop(); 
    }
    cout << endl;
}
string tinh_value_x(string s, int mode){
    queue<string> q;
    stack<string> st;
    string tmp;
    string sign = "";
    string sign_operator = "";
    for (string::iterator it = s.begin(); it != s.end(); ++it) {
        tmp = "";
        tmp += *it;
        if (tmp == " ") continue;
        else if (isdigit(*it)){
            tmp = "";
            tmp += sign;
            tmp += *it;
            while ((it + 1) != s.end() && (isdigit(*(it + 1)) || *(it + 1) == '.')) {
                ++it;
                tmp += *it;
            }
            q.push(tmp);
            sign = "";
        }
        else if (isoperator(tmp)) {
            if (pri(tmp) == 1) { // operator '+' or '-'
                string::iterator jt = it - 1;
                while(*jt == ' ') jt--;
                if(!isdigit(*jt) && !(*jt <= 'z' && *jt >= 'a') && *jt != ')'){
                    int dem = 0;
                    while (*it == '+' || *it == '-' || *it == ' ') {
                        if (*it == '-') dem++;
                        it++;
                    }
                    if (dem % 2 == 0) {
                        sign = sign;
                    } else {
                        if (sign == "+" || sign == "") sign = "-";
                        else sign = "";
                    }
                    if(*it >= 'a' && *it <= 'z'){
                        sign_operator = sign;
                        sign = "";
                    } 
                    else if(*it == '('){
                        if(sign == "") st.push("+()");
                        else if(sign == "-") st.push("-()");
                        sign = "";
                    }
                    it--;
                    continue;
                } 
                else{
                    int count = 0;
                    while(*it == ' ' || isoperatorc(*it)){
                        if(*it == '-') count++;
                        it++;
                    }
                    if(count % 2 == 0) tmp = "+";
                    else tmp = "-";
                    it--;
                    tryagain:
                    if (st.empty() || st.top() == "(") {
                        st.push(tmp);
                        continue;
                    } else if (pri(tmp) > pri(st.top())) {
                        st.push(tmp);
                    } else {
                        q.push(st.top());
                        st.pop();
                        goto tryagain;
                    }
                }
            } 
            else {
                start:
                if (st.empty() || st.top() == "(") {
                    st.push(tmp);
                    continue;
                } else if (pri(tmp) > pri(st.top())) {
                    st.push(tmp);
                } else {
                    q.push(st.top());
                    st.pop();
                    goto start;
                }
            }
        }
        else if (*it == '(') {
            st.push(tmp);
        }
        else if (*it == ')') {
            while (!st.empty() && st.top() != "(") {
                q.push(st.top());
                st.pop();
            }
            if(!st.empty()) st.pop();
            if(st.top() == "abs" && !st.empty()){
                q.push(st.top());
                st.pop();
            }
        }
        else if (*it == 'l' && *(it + 1) == 'n') {
            ++it;
            string temp = "ln";
            temp += sign_operator;
            st.push(temp);
            sign_operator = "";
        }
        else if (*it == 'l' && *(it + 1) == 'o' && *(it + 2) == 'g') {
            it += 2;
            string temp = "log";
            temp += sign_operator;
            st.push(temp);
            sign_operator = "";
        }
        else if (*it == 'c' && *(it + 1) == 'o' && *(it + 2) == 's') {
            it += 2;
            string temp = "cos";
            temp += sign_operator;
            st.push(temp);
            sign_operator = "";
        }
        else if (*it == 's' && *(it + 1) == 'i' && *(it + 2) == 'n') {
            it += 2;
            string temp = "sin";
            temp += sign_operator;
            st.push(temp);
            sign_operator = "";
        }
        else if (*it == 't' && *(it + 1) == 'a' && *(it + 2) == 'n') {
            it += 2;
            string temp = "tan";
            temp += sign_operator;
            st.push(temp);
            sign_operator = "";
        }
        else if (*it == 'c' && *(it + 1) == 'o' && *(it + 2) == 't') {
            it += 2;
            string temp = "cot";
            temp += sign_operator;
            st.push(temp);
            sign_operator = "";
        }
        else if(*it == 's' && *(it + 1) == 'q' && *(it + 2) == 'r' && *(it + 3) == 't'){
            it += 3;
            string temp = "sqrt";
            temp += sign_operator;
            st.push(temp);
            sign_operator = "";
        }
        else if(*it == 'c' && *(it + 1) == 'b' && *(it + 2) == 'r' && *(it + 3) == 't'){
            it += 3;
            string temp = "cbrt";
            temp += sign_operator;
            st.push(temp);
            sign_operator = "";
        }
        else if(*it == 'r' && *(it + 1) == 't'){
            it++;
            string temp = "rt";
            temp += sign_operator;
            st.push(temp);
            sign_operator = "";
        }
        else if(*it == 'a' && *(it + 1) == 'b' && *(it + 2) == 's'){
            it += 2;
            string temp = "abs";
            temp += sign_operator;
            st.push(temp);
            sign_operator = "";
        }
        else if (*it == 'p' && *(it + 1) == 'i') {
            ++it;
            string temp = "pi";
            temp += sign_operator;
            q.push(temp);
            sign_operator = "";
        }
        else if(*it == 'e'){
            string temp = "e";
            temp += sign_operator;
            q.push(temp);
            sign_operator = "";
        }
        else if(*it == 'a' && *(it + 1) == 't' && *(it + 2) == 'a' && *(it + 3) == 'n'){
            it += 3;
            string temp = "atan";
            temp += sign_operator;
            st.push(temp);
            sign_operator = "";
        }
        else if(*it == 'a' && *(it + 1) == 's' && *(it + 2) == 'i' && *(it + 3) == 'n'){
            it += 3;
            string temp = "asin";
            temp += sign_operator;
            st.push(temp);
            sign_operator = "";
        }
        else if(*it == 'a' && *(it + 1) == 'c' && *(it + 2) == 'o' && *(it + 3) == 's'){
            it += 3;
            string temp = "acos";
            temp += sign_operator;
            st.push(temp);
            sign_operator = "";
        }
    }
    while (!st.empty()) {
        q.push(st.top());
        st.pop();
    }
    return to_string(equal(q, mode));
}
void solve(string s, string value_x, int mode) {
    queue<string> q;
    stack<string> st;
    string tmp;
    string sign = "";
    string sign_operator = "";
    for (string::iterator it = s.begin(); it != s.end(); ++it) {
        tmp = "";
        tmp += *it;
        if (tmp == " ") continue;
        else if (isdigit(*it)){
            tmp = "";
            tmp += sign;
            tmp += *it;
            while ((it + 1) != s.end() && (isdigit(*(it + 1)) || *(it + 1) == '.')) {
                ++it;
                tmp += *it;
            }
            q.push(tmp);
            sign = "";
        }
        else if(*it == 'x'){
            q.push(tinh_value_x(value_x, mode));
        }
        else if (isoperator(tmp)) {
            if (pri(tmp) == 1) { // operator '+' or '-'
                string::iterator jt = it - 1;
                while(*jt == ' ') jt--;
                if(!isdigit(*jt) && !(*jt <= 'z' && *jt >= 'a') && *jt != ')'){
                    int dem = 0;
                    while (*it == '+' || *it == '-' || *it == ' ') {
                        if (*it == '-') dem++;
                        it++;
                    }
                    if (dem % 2 == 0) {
                        sign = sign;
                    } else {
                        if (sign == "+" || sign == "") sign = "-";
                        else sign = "";
                    }
                    if(*it >= 'a' && *it <= 'z'){
                        sign_operator = sign;
                        sign = "";
                    } 
                    else if(*it == '('){
                        if(sign == "") st.push("+()");
                        else if(sign == "-") st.push("-()");
                        sign = "";
                    }
                    it--;
                    continue;
                } 
                else{
                    int count = 0;
                    while(*it == ' ' || isoperatorc(*it)){
                        if(*it == '-') count++;
                        it++;
                    }
                    if(count % 2 == 0) tmp = "+";
                    else tmp = "-";
                    it--;
                    tryagain:
                    if (st.empty() || st.top() == "(") {
                        st.push(tmp);
                        continue;
                    } else if (pri(tmp) > pri(st.top())) {
                        st.push(tmp);
                    } else {
                        q.push(st.top());
                        st.pop();
                        goto tryagain;
                    }
                }
            } 
            else {
                start:
                if (st.empty() || st.top() == "(") {
                    st.push(tmp);
                    continue;
                } else if (pri(tmp) > pri(st.top())) {
                    st.push(tmp);
                } else {
                    q.push(st.top());
                    st.pop();
                    goto start;
                }
            }
        }
        else if (*it == '(') {
            st.push(tmp);
        }
        else if (*it == ')') {
            while (!st.empty() && st.top() != "(") {
                q.push(st.top());
                st.pop();
            }
            if(!st.empty()) st.pop();
            if(st.top() == "abs" && !st.empty()){
                q.push(st.top());
                st.pop();
            }
        }
        else if (*it == 'l' && *(it + 1) == 'n') {
            ++it;
            string temp = "ln";
            temp += sign_operator;
            st.push(temp);
            sign_operator = "";
        }
        else if (*it == 'l' && *(it + 1) == 'o' && *(it + 2) == 'g') {
            it += 2;
            string temp = "log";
            temp += sign_operator;
            st.push(temp);
            sign_operator = "";
        }
        else if (*it == 'c' && *(it + 1) == 'o' && *(it + 2) == 's') {
            it += 2;
            string temp = "cos";
            temp += sign_operator;
            st.push(temp);
            sign_operator = "";
        }
        else if (*it == 's' && *(it + 1) == 'i' && *(it + 2) == 'n') {
            it += 2;
            string temp = "sin";
            temp += sign_operator;
            st.push(temp);
            sign_operator = "";
        }
        else if (*it == 't' && *(it + 1) == 'a' && *(it + 2) == 'n') {
            it += 2;
            string temp = "tan";
            temp += sign_operator;
            st.push(temp);
            sign_operator = "";
        }
        else if (*it == 'c' && *(it + 1) == 'o' && *(it + 2) == 't') {
            it += 2;
            string temp = "cot";
            temp += sign_operator;
            st.push(temp);
            sign_operator = "";
        }
        else if(*it == 's' && *(it + 1) == 'q' && *(it + 2) == 'r' && *(it + 3) == 't'){
            it += 3;
            string temp = "sqrt";
            temp += sign_operator;
            st.push(temp);
            sign_operator = "";
        }
        else if(*it == 'c' && *(it + 1) == 'b' && *(it + 2) == 'r' && *(it + 3) == 't'){
            it += 3;
            string temp = "cbrt";
            temp += sign_operator;
            st.push(temp);
            sign_operator = "";
        }
        else if(*it == 'r' && *(it + 1) == 't'){
            it++;
            string temp = "rt";
            temp += sign_operator;
            st.push(temp);
            sign_operator = "";
        }
        else if(*it == 'a' && *(it + 1) == 'b' && *(it + 2) == 's'){
            it += 2;
            string temp = "abs";
            temp += sign_operator;
            st.push(temp);
            sign_operator = "";
        }
        else if (*it == 'p' && *(it + 1) == 'i') {
            ++it;
            string temp = "pi";
            temp += sign_operator;
            q.push(temp);
            sign_operator = "";
        }
        else if(*it == 'e'){
            string temp = "e";
            temp += sign_operator;
            q.push(temp);
            sign_operator = "";
        }
        else if(*it == 'a' && *(it + 1) == 't' && *(it + 2) == 'a' && *(it + 3) == 'n'){
            it += 3;
            string temp = "atan";
            temp += sign_operator;
            st.push(temp);
            sign_operator = "";
        }
        else if(*it == 'a' && *(it + 1) == 's' && *(it + 2) == 'i' && *(it + 3) == 'n'){
            it += 3;
            string temp = "asin";
            temp += sign_operator;
            st.push(temp);
            sign_operator = "";
        }
        else if(*it == 'a' && *(it + 1) == 'c' && *(it + 2) == 'o' && *(it + 3) == 's'){
            it += 3;
            string temp = "acos";
            temp += sign_operator;
            st.push(temp);
            sign_operator = "";
        }
    }
    while (!st.empty()) {
        q.push(st.top());
        st.pop();
    }
    cout << equal(q, mode) << endl << endl;
    cout << "bieu thuc hau to : ";
    while(!q.empty()){
        string::iterator it = q.front().begin();
        if(isdigit(*it)){
            for(it = q.front().begin();it != q.front().end();it++){
                if(*it == '.'){
                    for(int j = 0; j <= 4;j++){
                        cout << *it;
                        it++;
                    }
                    break;
                }
                else cout << *it;
            }
            cout << " ";
        }
        else cout << q.front() << " ";
        q.pop();
    }
    cout << endl << endl;
}
int main(){
    string c;
    ifstream input_file;
    input_file.open("file_input.txt");
    while(getline(input_file, c)){
        cout << d++ << ": "<< "bieu thuc la : ";
        cout << c;
        string value_x;
        for(string::iterator it = c.begin(); it != c.end(); it++){
            if(*it == 'x'){
                cout << "nhap gia tri cua bien x : ";
                getline(cin, value_x);
                break;
            }
        }
        cout << endl << endl << "chon mode radia or do : " << endl;
        cout << "1. radian " << endl << "2. do " << endl;
        int mode;
        cin >> mode;
        cout << "ket qua la : ";
        solve(c, value_x, mode);
    }
    input_file.close();
}
