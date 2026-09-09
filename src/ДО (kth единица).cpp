int kth(int k, int x, int lx, int rx) {
	if (rx - lx == 1) {
		return x - size + 1;
	}
	int m = (lx + rx) / 2;
	if (tree[2 * x + 1] <= k) {
		return kth(k - tree[2 * x + 1], 2 * x + 2, m, rx);
	} else {
		return kth(k, 2 * x + 1, lx, m);
	}
}

int kth(int k) {
	return kth(k, 0, 0, size);
}
