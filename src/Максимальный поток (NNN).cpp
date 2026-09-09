const int INF = 1000*1000*1000;
int main() {
	int n;
	vector < vector<int> > c (n, vector<int> (n));
	int s, t;
	// cin n c t s
	vector<int> e (n);
	vector<int> h (n);
	h[s] = n-1;
	vector < vector<int> > f (n, vector<int> (n));
	for (int i=0; i<n; ++i) {
		f[s][i] = c[s][i];
		f[i][s] = -f[s][i];
		e[i] = c[s][i];
	}
	vector<int> maxh (n);
	int sz = 0;
	for (;;) {
		if (!sz)
			for (int i=0; i<n; ++i)
				if (i != s && i != t && e[i] > 0) {
					if (sz && h[i] > h[maxh[0]])
						sz = 0;
					if (!sz || h[i] == h[maxh[0]])
						maxh[sz++] = i;
				}
		if (!sz)  break;
		while (sz) {
			int i = maxh[sz-1];
			bool pushed = false;
			for (int j=0; j<n && e[i]; ++j)
				if (c[i][j]-f[i][j] > 0 && h[i] == h[j]+1) {
					pushed = true;
					int addf = min (c[i][j]-f[i][j], e[i]);
					f[i][j] += addf,  f[j][i] -= addf;
					e[i] -= addf,  e[j] += addf;
					if (e[i] == 0)  --sz;
				}
			if (!pushed) {
				h[i] = INF;
				for (int j=0; j<n; ++j)
					if (c[i][j]-f[i][j] > 0 && h[j]+1 < h[i])
						h[i] = h[j]+1;
				if (h[i] > h[maxh[0]]) {
					sz = 0;
					break;
				}
			}
		}
	} 
}
