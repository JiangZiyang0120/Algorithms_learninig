//
// Created by jiang-ziyang on 22-9-5.
//

#include <vector>
#include "../../Include/Supported_Tools.h"
#include <Eigen/Core>
#include <cstdio>

using namespace std;

class MaxSubSequence{
public:
    string getMaxSubSeuqence(string s1, string s2){
        Eigen::MatrixXi M(s1.size()+1,s2.size()+1);
        for(int i = 1; i != s1.size()+1; ++i){
            for(int j = 1; j != s2.size()+1; ++j){
                if(s1[i-1] == s2[j-1]){
                    M(i,j) = M(i-1,j-1)+1;
                } else if(M(i-1,j) >= M(i,j-1)){
                    M(i,j) = M(i-1,j);
                } else{
                    M(i,j) = M(i,j-1);
                }
            }
        }
        string str = "";
        size_t i = s1.size(), j = s2.size();
        while (i != 0 && j != 0){
            if(M(i,j) == M(i-1,j))
                --i;
            else if(M(i,j) == M(i,j-1))
                --j;
            else{
                str += s1[i-1];
                --i;
                --j;
            }
        }
        std::reverse(str.begin(), str.end());
        return str;
    }
};

int main(){
    MaxSubSequence M;
    cout<<M.getMaxSubSeuqence("ABCBDAB","BDCABA")<<endl;
}