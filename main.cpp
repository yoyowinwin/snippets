#include <iostream>
#include <sstream>
#include <vector>

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
    buf.append(1,c);

    return buf;
}

std::string runlengthEncode2(const std::string &in){
    if(in.size()<2) return in;

    std::string buf;

    std::stringstream ss;
    ss<<in;

    char a;
    ss>>a;
    /////////////////////////////
    char b;
    while (ss>>b) {
        static int cnt = 1;
        if(a!=b){
            buf.append(1,a);
            if(cnt>1) {
                buf.append(std::to_string(cnt));
            }
            cnt = 1;
            a=b;
        } else {
            cnt++;
        }
    }
    buf.append(1,b);

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

void printParenthesesList(size_t n){
    // wrong . TOBE FIX
    static std::vector<std::vector<std::string> > buf = {{"9"},{"()"}};
    std::cout << std::endl;
    if(n<1){
        std::cout <<""<<std::endl;
        return;
    } else if(n==1){
        std::cout <<"()"<<std::endl;
        std::cout <<std::string(30,'=')<<1<<","<<1<<std::endl;
        return;
    }

    std::vector<std::string> buf_n;
    if(buf.size() == n){
        /////////////////////////////
        for(size_t i=0;i<n;++i){
            for(size_t j=0;j<buf.at(i).size();++j){
                for(size_t k=0;k<buf.at(n-1-i).size();++k){
                    std::string one = buf.at(i).at(j).append(buf.at(n-1-i).at(k));
//                    if(j==0&&k==0) one = "("+one + ")";
                    buf_n.push_back(one);
                    std::cout<< one<<std::endl;
                }
            }
        }
        buf.push_back(buf_n);
        std::cout <<std::string(30,'=')<<buf.size()-1<<","<<buf_n.size()<<std::endl;
    }
}

int main()
{
    {
        std::string test = "aaasjjjjjffgddddsddffgrrrrf";
        std::cout <<test<<":\t"<< runlengthEncode1(test)<< std::endl;
    }
    {
        std::string test = "aaasjjjjjffgddddsddffgrrrrf";
        std::cout <<test<<":\t"<< runlengthEncode2(test)<< std::endl;
    }
    {
        std::string test = "a3sj5f2gd4sd2f2gr4f";
        std::cout <<test<<":\t"<< runlengthDecode(test)<< std::endl;
    }

//    for(size_t i=1;i<4;++i)  printParenthesesList(i);
    return 0;
}
