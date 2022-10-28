#include <string>
#include <iterator>
#include <vector>

using namespace std;

string normalize(string_view s) {
    int s_size = s.size();
    int i=0;

    string cur_str = "";
    vector<int> ans;

    if(s_size == 1){
        if(s[0] == '.')
            return ".";
        return "/";
    }else if(s[0] == '.' && s[1] == '.'){
        cur_str.push_back('.');
        cur_str.push_back('.');
        i = 2;
        while(i < s_size && (s[i] == '/' || s[i] == '.')){
            if(s[i] == '.' && s[i - 1] == '.') {
                cur_str.push_back('.');
                cur_str.push_back('.');
            }else if(s[i] == '/')
                cur_str.push_back('/');
            i++;
        }
    }


    int t = 1;
    while(i < s_size){
        if(s[i] == '/'){
            cur_str.push_back('/');
            while(i + t < s_size && (s[i + t] == '.' || s[i + t] == '/')){
                t++;
            }
            i += t;
            t = 1;
        }
        if(i < s_size)
            cur_str.push_back(s[i]);
        i++;
    }
    i = 0;
    int j;
    int cur_str_size = cur_str.size();
    string temp_world, next_world;
    while(i < cur_str_size){
        while(i < cur_str_size && (cur_str[i] == '/' || cur_str[i] == '.'))
            i++;
        if(i < cur_str_size)
            while(i < cur_str_size && cur_str[i] != '/' ) {
                temp_world += cur_str[i];
                j = i;
                i++;
            }
        break;
    }
    while(i < cur_str_size){
        while(i < cur_str_size && (cur_str[i] == '/' || cur_str[i] == '.'))
            i++;
        if(i < cur_str_size)
            while(i < cur_str_size && cur_str[i] != '/' ) {
                next_world += cur_str[i];
                i++;
            }
        if(next_world == temp_world)
            cur_str = string(cur_str, 0, j) + string(cur_str, i, cur_str.size() - i);
        temp_world = next_world;
        j = i;
        next_world ="";

    }

    if(cur_str[cur_str_size- 1] == '/' && cur_str_size > 1)
        cur_str= string(cur_str, 0, cur_str_size - 1);
    return cur_str;

}
