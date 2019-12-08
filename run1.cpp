#include <bits/stdc++.h>
using namespace std;


void gen_SAT_input(vector<vector<int>>& G1, vector<vector<int>>& G2, int G1_edges, int G2_edges) {
	ofstream fout; 
    string line; 
    fout.open("test.satinput");
    int i,j,k,l;
    int n = G1.size();
    int m = G2.size();
    int num_vars = m*n;
    int num_clauses = n + m*n*(n-1)/2 + (m*(m-1) - G2_edges)*G1_edges + (n*(n-1) - G1_edges)*G2_edges;
    fout << "p cnf " << num_vars << " " << num_clauses << endl;

    // each node of G1 is assigned to some node of G2
    for(i = 0; i < n; i++){
    	for(j = 0; j < m; j++){
    		fout << i*m + j+1 << " ";
    	}
    	fout << 0 << endl;
    }
    // no two nodes of G1 are assigned to the same node in G2
    for(i = 0; i < n; i++){
    	for(j = i+1; j < n; j++){
    		for(k = 0; k < m; k++){
    			fout << -1*(i*m + k+1) << " " << -1*(j*m + k+1) << " 0" << endl;
    		}
    	}
    }
    // an edge in G1 is not mapped to a non edge in G2 and vice-versa
    for(i = 0; i < n; i++){
    	for(j = 0; j < n; j++){
    		if(i == j) continue;
    		for(k =0; k < m; k++){
    			for(l = 0; l < m; l++){
    				if(k == l) continue;
    				if((G1[i][j] == 1 && G2[k][l] == 0) || (G1[i][j] == 0 && G2[k][l] == 1)){
    					fout << -1*(i*m + k+1) << " " << -1*(j*m + l+1) << " 0" << endl;
    				}
    			}
    		}
    	}
    }
    fout.close();

    ofstream fout2;
    fout2.open("graph.txt");
    fout2 << n << " " << m << endl;
    fout2.close();
}


int main(int argc, char const *argv[]) {
	ifstream fin;
	// fin.open(argv[1]);
    fin.open("test.graph");
	int n,m;
	int a,mx;
	fin >> a;
	mx = a;
	while(a){
		if(mx < a) mx = a;
		fin >> a;
	}
	m = mx;
	fin >> a;
	fin >> a;
	mx = a;
	while(fin){
		if(mx < a) mx = a;
		if(fin) fin >> a;
	}
	n = mx;
	fin.close();

	vector<int> temp1(m, 0);
	vector<int> temp2(n, 0);
	vector<vector<int>> G1(m, temp1);
	vector<vector<int>> G2(n, temp2);

	// fin.open(argv[1]);
    fin.open("test.graph");
	int i,j;
	int G1_edges, G2_edges;
	G1_edges = G2_edges = 0;
	fin >> i >> j;
	while(i){
		G1[i-1][j-1] = 1;
		G1_edges++;
		fin >> i >> j;
	}

	fin >> i >> j;
	while(fin){
		G2[i-1][j-1] = 1;
		G2_edges++;
		if(fin) fin >> i >> j;
	}
	fin.close();
	if(m < n) gen_SAT_input(G1, G2, G1_edges, G2_edges);
	else gen_SAT_input(G2, G1, G2_edges, G1_edges);
	return 0;
}