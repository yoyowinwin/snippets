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

void printParenthesesList(size_t n){
    static std::vector<std::vector<std::string> > buf = {{"()"}};
//    std::cout << std::endl<<std::string(50,'=')<<buf.size()<<std::endl;
    if(n<1){
        std::cout <<""<<std::endl;
        return;
    } else if(n==1){
        std::cout <<"()"<<std::endl;
        return;
    }
    if(buf.size() == n-1){

        /////////////////////////////
        std::vector<std::string> buf_n;
        for(size_t i=0;i<buf.at(n-2).size();++i){
            std::string one = "(" + buf.at(n-2).at(i) + ")";
            buf_n.push_back(one);
            std::cout<< one<<std::endl;
        }
        /////////////////////////////
        for(size_t i=0;i<n-2;++i){
            for(size_t j=0;j<buf.at(i).size();++j){
                for(size_t k=0;k<buf.at(n-2-i).size();++k){
                    std::string one = buf.at(i).at(j).append(buf.at(n-2-i).at(k));
                    buf_n.push_back(one);
                    std::cout<< one<<std::endl;
                }
            }
        }
        buf.push_back(buf_n);
        std::cout <<std::string(30,'=')<<buf_n.size()<<std::endl;
    }
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

    for(size_t i=1;i<7;++i)
        printParenthesesList(i);
    return 0;
}
