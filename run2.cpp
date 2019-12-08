#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[]) {
	ifstream fin;
    ofstream fout;
	fin.open("graph.txt");
    fout.open("test.mapping");
    int n,m;
    fin >> n >> m;
    fin.close();
    fin.open("test.satoutput");
    int i,j;
    int x;
    string temp;
    fin >> temp;
    if(temp == "UNSAT") {
        fout << 0;
    }
    else {
       for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                fin >> x;
                if(x > 0) {
                    fout << i+1 << " " << x-(i*m) << endl;
                }
            }
        } 
    }
    
    fin.close();
    fout.close();
	return 0;
}