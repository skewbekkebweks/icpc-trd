#include <bits/stdc++.h>

using namespace std;
#define sz(v) (int)(v).size()
const double EPS = 1e-9;
const double PI = 3.141592653;

int eq(double a, double b) {
    return abs(a - b) < EPS;
}

struct Point{
    double x, y;

    Point(double x = 0, double y = 0): x(x), y(y) {}

    Point operator + (Point other) const {
        return {x+other.x,y+other.y};
    }

    Point operator - (Point other) const {
        return {x-other.x,y-other.y};
    }

    Point operator * (double k) const {
        return {x * k, y * k};
    }

    Point operator / (double k) const {
        return {x / k, y / k};
    }

    double operator ^ (Point other) const {
        return x*other.y - y*other.x;
    }

    double operator % (Point other) const {
        return x*other.x + y*other.y;
    }

    bool operator == (Point other) const {
        return eq(x, other.x) && eq(y, other.y);
    }

    bool operator != (Point other) const {
        return !eq(x, other.x) || !eq(y, other.y);
    }

    bool operator < (Point other) const {
        return x<other.x-EPS || eq(x, other.x) && y<other.y;
    }
    double len() const {
        return sqrt(x*x + y*y);
    }
};
istream& operator >> (istream& is, Point &p) {
    is >> p.x >> p.y;
    return is;
}
ostream& operator << (ostream& os, Point &p) {
    os << p.x << ' ' << p.y;
    return os;
}
struct line{
    double a, b, c;
};
void out(Point p) {
    cout << p.x << ' ' << p.y << '\n';
}
line get_line(Point p1, Point p2) {
    return { p2.y-p1.y, p1.x-p2.x, -(p1^p2) };
}
int parallel(line l1, line l2) {
    return eq(l1.a, 0) && eq(l2.a, 0) && -l1.c / l1.b != -l2.c / l2.b ||
           eq(l1.b, 0) && eq(l2.b, 0) && -l1.c / l1.a != -l2.c / l2.a ||
           eq(l1.a / l2.a, l1.b / l2.b) && (!(eq(l1.c, 0) && eq(l2.c, 0)) || !eq(l1.a / l2.a, l1.c / l2.c));
}
int Point_on_line(Point p, Point a, Point b) {
    return eq((b-a)^(p-a), 0);
}
int Point_on_line2(Point p, line l) {
    return eq(l.a*p.x + l.b*p.y + l.c, 0);
}
int Point_on_ray(Point p, Point a, Point b) {
    return Point_on_line(p, a, b) && ((b-a)%(p-a) >= 0);
}
int Point_on_segment(Point p, Point a, Point b) {
    return Point_on_line(p, a, b) && ((a-p)%(b-p) <= 0);
}
int Point_in_corner(Point p, Point a, Point o, Point b) {
    Point v1 = a-o, v2 = b-o, v3 = p-o;
    return (v1^v2)*(v1^v3) >= 0 && (v2^v1)*(v2^v3) >= 0;
}
double dist_Point_Point(Point p1, Point p2) {
    return (p1-p2).len();
}
double dist_Point_line(Point p, Point a, Point b) {
    return abs((p-a)^(p-b)) / (a-b).len();
}
double dist_Point_line2(Point p, line l) {
    return abs(l.a*p.x + l.b*p.y + l.c) / sqrtl(l.a*l.a+l.b*l.b);
}
double dist_Point_ray(Point p, Point a, Point b)
{
    return ((b-a)%(p-a) >= 0? dist_Point_line(p, a, b) : dist_Point_Point(a, p));
}
double dist_Point_segment(Point p, Point a, Point b)
{
    return ((b-a)%(p-a) >= 0 && (a-b)%(p-b) >= 0? dist_Point_line(p, a, b) : min(dist_Point_Point(a, p),dist_Point_Point(b, p)));
}
double dist_line_line2(line l1, line l2)
{
    Point p;
    if (l1.b == 0) p = { -l1.c / l1.a, 0 };
    else p = { 0, -l1.c / l1.b };
    return dist_Point_line2(p, l2);
}
double dist_line_line(Point a, Point b, Point c, Point d)
{
    line ab = get_line(a, b);
    line cd = get_line(c, d);
    if (!parallel(ab, cd))
        return 0;
    return dist_line_line2(ab, cd);
}
Point intersection_line_line(line l1, line l2)
{
    return {(l2.c*l1.b - l1.c*l2.b) / (l1.a*l2.b - l2.a*l1.b),
            (l2.c*l1.a - l1.c*l2.a) / (l2.a*l1.b - l1.a*l2.b)};
}
set <Point> intersection_seg_seg(Point a, Point b, Point c, Point d)
{
    set <Point> ans;
    if (eq((b - a) ^ (d - c), 0))
    {
        if (Point_on_segment(a, c, d)) ans.insert(a);
        if (Point_on_segment(b, c, d)) ans.insert(b);
        if (Point_on_segment(c, a, b)) ans.insert(c);
        if (Point_on_segment(d, a, b)) ans.insert(d);
    }
    else
    {
        line ab = get_line(a, b), cd = get_line(c, d);
        Point p = intersection_line_line(ab, cd);
        if (Point_on_segment(p, a, b) && Point_on_segment(p, c, d)) ans.insert(p);
    }
    return ans;
}
double dist_seg_seg(Point a, Point b, Point c, Point d)
{
    line ab = get_line(a, b);
    line cd = get_line(c, d);
    if (parallel(ab, cd))
        return min({dist_Point_segment(c, a, b), dist_Point_segment(d, a, b),
                    dist_Point_segment(a, c, d), dist_Point_segment(b, c, d)});
    Point p = intersection_line_line(ab, cd);
    if (Point_on_segment(p, a, b) && Point_on_segment(p, c, d))
        return 0;
    return min({dist_Point_segment(c, a, b), dist_Point_segment(d, a, b),
                dist_Point_segment(a, c, d), dist_Point_segment(b, c, d)});
}
double dist_seg_ray(Point a, Point b, Point c, Point d)
{
    line ab = get_line(a, b);
    line cd = get_line(c, d);
    if (parallel(ab, cd))
        return min({dist_Point_ray(a, c, d), dist_Point_ray(b, c, d), dist_Point_segment(c, a, b)});
    Point p = intersection_line_line(ab, cd);
    if (Point_on_segment(p, a, b) && Point_on_ray(p, c, d))
        return 0;
    return min({dist_Point_ray(a, c, d), dist_Point_ray(b, c, d), dist_Point_segment(c, a, b)});
}
double dist_seg_line(Point a, Point b, Point c, Point d)
{
    line ab = get_line(a, b);
    line cd = get_line(c, d);
    if (parallel(ab, cd))
        return min(dist_Point_line(a, c, d), dist_Point_line(b, c, d));
    Point p = intersection_line_line(ab, cd);
    if (Point_on_segment(p, a, b) && Point_on_line(p, c, d))
        return 0;
    return min(dist_Point_line(a, c, d), dist_Point_line(b, c, d));
}
double dist_ray_ray(Point a, Point b, Point c, Point d)
{
    line ab = get_line(a, b);
    line cd = get_line(c, d);
    if (parallel(ab, cd))
        return min(dist_Point_ray(a, c, d), dist_Point_ray(c, a, b));
    Point p = intersection_line_line(ab, cd);
    if (Point_on_ray(p, a, b) && Point_on_ray(p, c, d))
        return 0;
    return min(dist_Point_ray(a, c, d), dist_Point_ray(c, a, b));
}
double dist_ray_line(Point a, Point b, Point c, Point d)
{
    line ab = get_line(a, b);
    line cd = get_line(c, d);
    if (parallel(ab, cd))
        return dist_Point_line(a, c, d);
    Point p = intersection_line_line(ab, cd);
    if (Point_on_ray(p, a, b) && Point_on_line(p, c, d))
        return 0;
    return dist_Point_line(a, c, d);
}
Point projection(line l, Point p)
{
    Point normal = { l.a, l.b };
    double d = dist_Point_line2(p, l);
    normal = normal / normal.len() * d;
    Point base = p + normal;
    if (!eq(l.a*base.x + l.b*base.y + l.c, 0))
        base = base - normal * 2;
    return base;
}
pair<int, int> tangent_polygon(Point a, vector<Point> &p) {
    int p1 = 0, p2 = 0, n = sz(p);
    for (int i = 20; i >= 0; --i) {
        {
            int nxt = (p1 + (1 << i)) % n, prev = ((p1 - (1 << i)) % n + n) % n;
            if (((p[p1] - a) ^ (p[nxt] - a)) > 0) {
                p1 = nxt;
            }
            if (((p[p1] - a) ^ (p[prev] - a)) > 0) {
                p1 = prev;
            }
        }
        {
            int nxt = (p2 + (1 << i)) % n, prev = ((p2 - (1 << i)) % n + n) % n;
            if (((p[p2] - a) ^ (p[nxt] - a)) < 0) {
                p2 = nxt;
            }
            if (((p[p2] - a) ^ (p[prev] - a)) < 0) {
                p2 = prev;
            }
        }
    }
    return {p1, p2};
}
vector <Point> tangent_circle(Point o, double r, Point m) {
    if (r > dist_Point_Point(o, m)) {
        return {};
    }
    if (eq(r, dist_Point_Point(o, m))) {
        return { m };
    }
    double d = r*r / dist_Point_Point(o, m);
    Point om = m-o;
    Point oh = om / om.len() * d;
    Point h = o + oh;
    line l = get_line(o, m);
    Point normal = { l.a, l.b };
    d = sqrtl(r*r - oh.len()*oh.len());
    normal = normal / normal.len() * d;
    return { h+normal, h-normal };
}
vector <Point> intersection_circle_circle(Point o1, double r1, Point o2, double r2) {
    double d = dist_Point_Point(o1, o2);
    if (o1 == o2 && eq(r1, r2)) {
        return {};
    }
    if (d > r1+r2 || d < abs(r1-r2)) {
        return {};
    }
    if (eq(d, r1+r2)) {
        Point v = o2 - o1;
        v = v / v.len() * r1;
        return { o1 + v };
    }
    if (eq(d, abs(r1-r2))) {
        if (r1 > r2) {
            swap(r1, r2);
            swap(o1, o2);
        }
        Point v = o1-o2;
        v = v / v.len() * r2;
        return { o2 + v };
    }
    double o1h_len = (d*d + r1*r1 - r2*r2) / (2*d);
    Point v = o2-o1;
    Point o1h = v / v.len() * o1h_len;
    Point h = o1 + o1h;
    line l = get_line(o1, o2);
    Point normal = { l.a, l.b };
    double dist = dist_Point_Point(o1, h);
    d = sqrtl(r1*r1 - dist*dist);
    normal = normal / normal.len() * d;
    return { h+normal, h-normal };
}
void reorder(vector<Point> &p) {
    int mn = 0;
    for (int i = 1; i < sz(p); ++i) {
        if (p[i] < p[mn]) {
            mn = i;
        }
    }
    rotate(p.begin(), p.begin() + mn, p.end());
}
vector<Point> sum_of_polygons(vector<Point> a, vector<Point> b) {
    vector<Point> sum;
    reorder(a), reorder(b);
    a.push_back(a[0]), b.push_back(b[0]);
    a.push_back(a[1]), b.push_back(b[1]);
    int i = 0, j = 0;
    while (i < sz(a) - 2 || j < sz(b) - 2) {
        sum.push_back(a[i] + b[j]);
        auto cross = ((a[i + 1] - a[i]) ^ (b[j + 1] - b[j]));
        if ((cross > 0 || eq(cross, 0)) && i < sz(a) - 2) {
            ++i;
        }
        if ((cross < 0 || eq(cross, 0)) && j < sz(b) - 2) {
            ++j;
        }
    }
    return sum;
}
