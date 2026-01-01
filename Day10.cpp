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
lli GetMoves(lli mask, vector<lli> values){
    priority_queue<pair<lli, lli>, vector<pair<lli, lli>>, greater<pair<lli, lli>>> pq;
    map<lli, lli> dist;
    pq.push({0, 0}); // {cost, node}

    while(!pq.empty()){
        pair<lli, lli> curr = pq.top();
        pq.pop();

        if(dist.count(curr.ss)) continue;
        dist[curr.ss] = curr.ff;
        if(curr.ss == mask) return curr.ff;
        for(auto& it : values){
            lli n_node = curr.ss ^ it;
            if(dist.count(n_node)) continue;
            pq.push({curr.ff + 1, n_node});
        }
    }
    return dist[mask];
}
lli GetMaskSymbol(string& s){
    lli ret = 0;
    for(int i = 1; i < s.size()- 1; i++){
        if(s[i] =='#'){
            ret |= (1 << (i-1));
        }
    }
    return ret; 
}

lli GetMaskNumber(string& s){
    s.pop_back();
    s.erase(s.begin());
    // dbg(s);
    lli ret = 0;
    vector<string> now = Split(s, ',');
    for(auto& it : now){
        lli v = ToLLI(it);
        
        ret |= (1 << (v));
    }
    return ret;
}
void Part1(vector<string> &lines)
{
    cout << "Part 1: ";
    lli ret = 0;
    lli max_len = 0;
    for(auto& it : lines){
        vector<string> now = Split(it, ' ');
        lli required_mask = GetMaskSymbol(now[0]);
        max_len = max(max_len, (lli)now[0].size()-2);
        vector<lli> values;
        
        for(int i = 1; i < now.size() - 1; i++){
            values.pb(GetMaskNumber(now[i]));
        }
        lli moves = GetMoves(required_mask, values);
        ret += moves;
    }
    cout << ret << endl;
}

void Part2(vector<string> &lines)
{
    cout << "Part 2: ";
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
