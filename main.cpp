#include <iostream>
#include <sstream>

std::string runlengthEncode1(const std::string &in){
    if(in.size()<2) return in;

    std::string buf;

    char c = in.at(0);
    int cnt = 1;
    size_t idx = 1;
    while (idx < in.size()) {

        while (idx < in.size() && in.at(idx)==c ) {
            cnt++;
            idx++;
        }
        /////////////////////////////
        buf.append(1,c);
        if(cnt>1) {
            buf.append(std::to_string(cnt));
        }
        /////////////////////////////
        if(idx < in.size()){
            c = in.at(idx);
        }
        cnt = 1;
        idx++;
    }

    return buf;
}

std::string runlengthEncode2(const std::string &in){
    if(in.size()<2) return in;

    std::string buf;

    std::stringstream ss;
    ss<<in;

    char head;
    ss>>head;

    char c = head;
    int cnt = 1;
    while (ss>>c) {
        while(c == head && ss>>c) {
            cnt++;
        }

        if(!ss){
            cnt++;
        }
        /////////////////////////////
        buf.append(1,head);
        if(cnt>1) {
            buf.append(std::to_string(cnt));
        }
        /////////////////////////////
        if(c!=head) head = c;
        cnt = 1;
    }

    return buf;
}

std::string runlengthDecode(const std::string &in){
    std::string buf;

    std::stringstream ss;
    ss<<in;

    char c;
    while(ss>>c){
        size_t cnt;
        if(ss>>cnt){
            buf.append(cnt,c);
        } else {
            ss.clear();
            buf.append(1,c);
        }
    }

    return buf;
}

void printParenthesesList(int n){

}

int main()
{
    {
        std::string test = "aaasjjjjjffgddddsddffgrrrr";
        std::cout <<test<<":\t"<< runlengthEncode1(test)<< std::endl;
    }
    {
        std::string test = "aaasjjjjjffgddddsddffgrrrr";
        std::cout <<test<<":\t"<< runlengthEncode2(test)<< std::endl;
    }
    {
        std::string test = "a3sj5f2gd4sd2f2gr4";
        std::cout <<test<<":\t"<< runlengthDecode(test)<< std::endl;
    }
    return 0;
}
