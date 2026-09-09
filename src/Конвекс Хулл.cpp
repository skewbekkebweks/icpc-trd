vector<point> convex_hull(vector<point> &p) {
    int mn = 0;
    for (int i = 1; i < sz(p); ++i) {
        if (p[mn].y > p[i].y || p[mn].y == p[i].y && p[mn].x > p[i].x)
            mn = i;
    }
    point p0 = p[mn];
    p.erase(find(p.begin(), p.end(), p0));
    for (auto &i: p)
        i = i - p0;
    point add = p0;
    p0 = {0, 0};
    sort(p.begin(), p.end(), [](point a, point b) {
        return (a ^ b) > 0 || (a ^ b) == 0 && a.len() > b.len();
    });
    p.push_back(p0);
    vector<point> hull;
    for (auto &i: p) {
        while (sz(hull) > 1 && ((hull.back() - hull[sz(hull) - 2]) ^ (i - hull.back())) <= 0) {
            hull.pop_back();
        }
        hull.push_back(i);
    }
    for (auto &i: hull)
        i = i + add;
    return hull;
}
