/*
    JAI JAGANNATH!
*/
//@Author : zanj0

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

// #define LOCAL  // ← enable locally via -DLOCAL; keep commented for AoC
#define ff first
#define ss second
#define pb push_back
#define MOD 1000000007
#define inf 1000000000000000000LL
#define ps(x, y) fixed << setprecision(y) << x
#define w(x)  \
    int x;    \
    cin >> x; \
    while (x--)
#define endl "\n"
#define timetaken cerr << "Time : " << 1000 * (long double)clock() / (long double)CLOCKS_PER_SEC << "ms\n"

typedef long long int lli;

#ifdef LOCAL
#define dbg(x) cerr << "[DBG] " << #x << " = " << (x) << '\n'
template <class A, class B>
ostream &operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ',' << p.second << ')'; }
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    os << '[';
    for (size_t i = 0; i < v.size(); ++i)
    {
        if (i)
            os << ',';
        os << v[i];
    }
    return os << ']';
}
template <class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &mp)
{
    os << '{';
    bool first = true;
    for (const auto &kv : mp)
    {
        if (!first)
            os << ',';
        first = false;
        os << kv.first << ':' << kv.second;
    }
    return os << '}';
}
template <class K, class V>
ostream &operator<<(ostream &os, const unordered_map<K, V> &mp)
{
    os << '{';
    bool first = true;
    for (const auto &kv : mp)
    {
        if (!first)
            os << ',';
        first = false;
        os << kv.first << ':' << kv.second;
    }
    return os << '}';
}
#else
#define dbg(x) ((void)0)
#endif

// Fast IO setup, optionally redirects stdin to input.txt in LOCAL mode
void zanj0()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
}

// --------------------------- String helpers ---------------------------

// Removes leading whitespace from string (in-place)
inline void LTrim(string &s)
{
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch)
                               { return !isspace(ch); }));
}

// Removes trailing whitespace from string (in-place)
inline void RTrim(string &s)
{
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch)
                    { return !isspace(ch); })
                .base(),
            s.end());
}

// Returns a copy of string with leading and trailing spaces removed
inline string Trim(string s)
{
    LTrim(s);
    RTrim(s);
    return s;
}

// Splits string by a single character delimiter
vector<string> Split(string &s, char delim)
{
    vector<string> res;
    string cur;
    for (char c : s)
    {
        if (c == delim)
        {
            if (!cur.empty())
                res.pb(cur);
            cur.clear();
        }
        else
        {
            cur.push_back(c);
        }
    }
    if (!cur.empty())
        res.pb(cur);
    return res;
}

// Splits string on whitespace (like >> for words)
vector<string> SplitWS(string &s)
{
    vector<string> res;
    string cur;
    stringstream ss(s);
    while (ss >> cur)
        res.pb(cur);
    return res;
}

// Checks if s starts with prefix pref
bool StartsWith(string &s, string &pref)
{
    if (pref.size() > s.size())
        return false;
    return equal(pref.begin(), pref.end(), s.begin());
}

// Checks if s ends with suffix suf
bool EndsWith(string &s, string &suf)
{
    if (suf.size() > s.size())
        return false;
    return equal(suf.rbegin(), suf.rend(), s.rbegin());
}

// Replaces all occurrences of 'from' with 'to' in string
string ReplaceAll(string s, string &from, string &to)
{
    if (from.empty())
        return s;
    size_t pos = 0;
    while ((pos = s.find(from, pos)) != string::npos)
    {
        s.replace(pos, from.length(), to);
        pos += to.length();
    }
    return s;
}

// Joins vector of lli into a single string separated by sep
string Join(vector<lli> &v, string &sep)
{
    string out;
    for (size_t i = 0; i < v.size(); ++i)
    {
        if (i)
            out += sep;
        out += to_string(v[i]);
    }
    return out;
}

// --------------------------- Parsing helpers ---------------------------

// Converts string to lli (supports +/- and arbitrary base up to 36)
lli ToLLI(string &s, int base = 10)
{
    lli x = 0;
    bool neg = false;
    size_t i = 0;
    while (i < s.size() && isspace((unsigned char)s[i]))
        ++i;
    if (i < s.size() && (s[i] == '-' || s[i] == '+'))
    {
        neg = (s[i] == '-');
        ++i;
    }
    for (; i < s.size(); ++i)
    {
        char c = s[i];
        if (isspace((unsigned char)c))
            break;
        int d;
        if ('0' <= c && c <= '9')
            d = c - '0';
        else if ('a' <= c && c <= 'z')
            d = c - 'a' + 10;
        else if ('A' <= c && c <= 'Z')
            d = c - 'A' + 10;
        else
            break;
        if (d >= base)
            break;
        x = x * base + d;
    }
    return neg ? -x : x;
}

// Extracts all (possibly negative) integers from a string
vector<lli> ExtractAllNums(string &s)
{
    vector<lli> res;
    lli cur = 0;
    int sign = 1;
    bool in_num = false;
    for (size_t i = 0; i <= s.size(); ++i)
    {
        char c = (i < s.size() ? s[i] : ' ');
        if (c == '-' && !in_num)
        {
            in_num = true;
            sign = -1;
            cur = 0;
        }
        else if ('0' <= c && c <= '9')
        {
            if (!in_num)
            {
                in_num = true;
                sign = 1;
                cur = c - '0';
            }
            else
            {
                cur = cur * 10 + (c - '0');
            }
        }
        else
        {
            if (in_num)
            {
                res.pb(sign * cur);
                in_num = false;
                cur = 0;
                sign = 1;
            }
        }
    }
    return res;
}

// --------------------------- I/O helpers ---------------------------

// Reads all lines from given stream into vector<string>
vector<string> ReadLines(istream &in = cin)
{
    vector<string> lines;
    string s;
    while (getline(in, s))
        lines.pb(s);
    return lines;
}

// Splits lines into blocks separated by blank lines
vector<vector<string>> SplitBlocks(vector<string> &lines)
{
    vector<vector<string>> blocks;
    vector<string> cur;
    for (auto &ln : lines)
    {
        if (ln.empty())
        {
            if (!cur.empty())
            {
                blocks.pb(cur);
                cur.clear();
            }
        }
        else
        {
            cur.pb(ln);
        }
    }
    if (!cur.empty())
        blocks.pb(cur);
    return blocks;
}

// --------------------------- Math helpers ---------------------------

// Returns ceil(a / b) for integers
lli CeilDiv(lli a, lli b)
{
    if (b < 0)
        a = -a, b = -b;
    if (a >= 0)
        return (a + b - 1) / b;
    return a / b;
}

// Returns floor(a / b) for integers
lli FloorDiv(lli a, lli b)
{
    if (b < 0)
        a = -a, b = -b;
    if (a >= 0)
        return a / b;
    return -((-a + b - 1) / b);
}

// Computes Manhattan distance between two integer points
lli Manhattan(pair<lli, lli> a, pair<lli, lli> b)
{
    return llabs(a.ff - b.ff) + llabs(a.ss - b.ss);
}

// Returns x^2 for generic numeric type
template <class T>
T Sqr(T x) { return x * x; }

// (a + b) mod m with proper handling of negatives
lli Add(lli a, lli b, lli m)
{
    a %= m;
    if (a < 0)
        a += m;
    b %= m;
    if (b < 0)
        b += m;
    a += b;
    if (a >= m)
        a -= m;
    return a;
}

// (a * b) mod m using 128-bit intermediate
lli Mul(lli a, lli b, lli m)
{
    __int128 res = (__int128)a * b % m;
    if (res < 0)
        res += m;
    return (lli)res;
}

// a^e mod m using fast exponentiation
lli FastPow(lli a, lli e, lli m)
{
    a %= m;
    if (a < 0)
        a += m;
    lli r = 1 % m;
    while (e > 0)
    {
        if (e & 1)
            r = Mul(r, a, m);
        a = Mul(a, a, m);
        e >>= 1;
    }
    return r;
}

// GCD for lli (non-negative result)
lli GCD(lli a, lli b)
{
    if (a < 0)
        a = -a;
    if (b < 0)
        b = -b;
    while (b)
    {
        lli t = a % b;
        a = b;
        b = t;
    }
    return a;
}

// LCM for lli, handles zero safely
lli LCM(lli a, lli b)
{
    if (a == 0 || b == 0)
        return 0;
    return (a / GCD(a, b)) * b;
}

// --------------------------- Grid helpers ---------------------------

// 4-direction deltas (up, right, down, left)
const int DX4[4] = {-1, 0, 1, 0};
const int DY4[4] = {0, 1, 0, -1};

// 8-direction deltas (including diagonals)
const int DX8[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int DY8[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

// Checks if (r, c) lies within grid [0..R) x [0..C)
bool IsInside(int r, int c, int R, int C)
{
    return (0 <= r && r < R && 0 <= c && c < C);
}

/*
────────────────────────────────────────────────────────────────────────
    Problem-specific part (edit per day)
────────────────────────────────────────────────────────────────────────
*/
lli GetDistance(vector<lli> a, vector<lli> b)
{
    lli dx = abs(a[0] - b[0]) + 1;
    lli dy = abs(a[1] - b[1]) + 1;

    return dx * dy;
}
void Part1(vector<string> &lines)
{
    cout << "Part 1: ";
    lli n = lines.size();

    vector<vector<lli>> ranges;

    for (auto &it : lines)
    {
        vector<string> now = Split(it, ',');
        vector<lli> temp;

        for (auto &it : now)
        {
            temp.pb(ToLLI(it));
        }
        ranges.pb(temp);
    }
    lli ret = 0;

    for (int i = 0; i < ranges.size(); i++)
    {
        for (int j = i + 1; j < ranges.size(); j++)
        {
            ret = max(ret, GetDistance(ranges[i], ranges[j]));
        }
    }
    // dbg(ranges);

    cout << ret << endl;
}

struct Point
{
    lli x, y;
};

vector<Point> ParsePoints(vector<string> &lines)
{
    vector<Point> ret;
    for (auto &it : lines)
    {
        vector<string> now = Split(it, ',');
        lli x = ToLLI(now[0]);
        lli y = ToLLI(now[1]);

        ret.pb({x, y});
    }
    return ret;
}
// Check if point P(px, py) lies on segment AB (x1,y1)-(x2,y2)
typedef long double ld;
const ld EPSILON = 1e-12L;
bool OnSegment(ld px, ld py, ld x1, ld y1, ld x2, ld y2)
{
    // cross(a,b)=ax​by​−ay​bx​
    // cross=(x2−x1)(py−y1)−(y2−y1)(px−x1)
    ld cross = ((x2 - x1) * (py - y1)) - ((y2 - y1) * (px - x1));

    if (fabsl(cross) > EPSILON)
        return false;

    ld minx = min(x1, x2), maxx = max(x1, x2);
    ld miny = min(y1, y2), maxy = max(y1, y2);

    return (px >= minx - EPSILON && px <= maxx + EPSILON &&
            py >= miny - EPSILON && py <= maxy + EPSILON);
}

bool PointInPoly(ld px, ld py, vector<Point> &poly)
{
    int n = poly.size();

    // Boundary Check
    for (int i = 0; i < n; i++)
    {
        ld x1 = poly[i].x;
        ld x2 = poly[(i + 1) % n].x;

        ld y1 = poly[i].y;
        ld y2 = poly[(i + 1) % n].y;

        if (OnSegment(px, py, x1, y1, x2, y2))
            return true;
    }

    // Ray Casting Algorithm
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        ld x1 = poly[i].x;
        ld x2 = poly[(i + 1) % n].x;

        ld y1 = poly[i].y;
        ld y2 = poly[(i + 1) % n].y;

        bool crosses_vertical_range = (py < y1) != (py < y2);
        if (crosses_vertical_range)
        {
            ld x_intersection = x1 + (py - y1) * (x2 - x1) / (y2 - y1);
            if (px < x_intersection)
                cnt++;
        }
    }
    return cnt & 1;
}

bool RectInside(Point &corner_a, Point &corner_b, vector<Point> &polygon)
{
    lli rect_left_x = min(corner_a.x, corner_b.x);
    lli rect_right_x = max(corner_a.x, corner_b.x);
    lli rect_bottom_y = min(corner_a.y, corner_b.y);
    lli rect_top_y = max(corner_a.y, corner_b.y);

    long double center_x = (static_cast<long double>(rect_left_x) +
                            static_cast<long double>(rect_right_x)) /
                           2.0L;
    long double center_y = (static_cast<long double>(rect_bottom_y) +
                            static_cast<long double>(rect_top_y)) /
                           2.0L;

    if (!PointInPoly(center_x, center_y, polygon))
        return false;

    int num_vertices = (int)polygon.size();
    for (int i = 0; i < num_vertices; i++)
    {
        lli x1 = polygon[i].x;
        lli y1 = polygon[i].y;
        lli x2 = polygon[(i + 1) % num_vertices].x;
        lli y2 = polygon[(i + 1) % num_vertices].y;

        if (x1 == x2 && y1 == y2)
            continue;

        if (x1 == x2)
        {

            lli edge_x = x1;
            lli edge_min_y = min(y1, y2);
            lli edge_max_y = max(y1, y2);

            if (rect_left_x < edge_x && edge_x < rect_right_x)
            {

                lli inter_low = max(edge_min_y, rect_bottom_y);
                lli inter_high = min(edge_max_y, rect_top_y);
                if (inter_low < inter_high)
                    return false;
            }
        }
        else if (y1 == y2)
        {

            lli edge_y = y1;
            lli edge_min_x = min(x1, x2);
            lli edge_max_x = max(x1, x2);

            if (rect_bottom_y < edge_y && edge_y < rect_top_y)
            {

                lli inter_low = max(edge_min_x, rect_left_x);
                lli inter_high = min(edge_max_x, rect_right_x);
                if (inter_low < inter_high)
                    return false;
            }
        }
        else
        {
        }
    }

    return true;
}

void Part2(vector<string> &lines)
{
    cout << "Part 2: ";
    vector<Point> pts = ParsePoints(lines);
    int n = (int)pts.size();

    lli ret = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {

            if (RectInside(pts[i], pts[j], pts))
            {
                ret = max(ret, GetDistance({pts[i].x, pts[i].y}, {pts[j].x, pts[j].y}));
            }
        }
    }

    cout << ret << endl;
}

int32_t main()
{
    zanj0();

    vector<string> lines = ReadLines();

    Part1(lines);

    Part2(lines);

    timetaken;
    return 0;
}

/*
    GOLDEN RULES
    • Solutions are simple.
    • Proofs are simple.
    • Implementations are simple.
*/
