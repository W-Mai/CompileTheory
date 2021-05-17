#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <string>
#include <cctype>
#include <map>
#include <set>

#define MAX 507

#define DEBUG

using namespace std;


//大写字母为非终止符(可以多一个'的标号做区分)，小写字母为终止符,用~代替epsilon
class WF {
public:
    string left;
    set<string> right;

    WF(char s[]) {
        left = s;
    }

    void print() const {
        printf("%s->", left.c_str());
        auto it = right.begin();
        if (right.begin() != right.end()) {
            printf("%s", it->c_str());
            it++;
        }
        for (; it != right.end(); it++)
            printf("|%s", it->c_str());
        puts("");
    }

    void insert(char s[]) {
        right.insert(s);
    }
};

map<string, set<char> > first;
map<string, set<char> > follow;
map<string, int> VN_dic;
vector<WF> VN_set;
bool used[MAX];

void dfs(int x) {
    if (used[x]) return;
    used[x] = true;
    string &left = VN_set[x].left;
    set<string> &right = VN_set[x].right;
    auto it = right.begin();
    for (; it != right.end(); it++)
        for (int i = 0; i < it->length(); i++) {
            if (!isupper(it->at(i)) && it->at(i) != '\'') {
                first[left].insert(it->at(i));
                break;
            }
            if (isupper(it->at(i))) {
                int y;
                if (i != it->length() - 1 && it->at(i + 1) == '\'')
                    y = VN_dic[it->substr(i, 2)] - 1;
                else y = VN_dic[it->substr(i, 1)] - 1;
                string &tleft = VN_set[y].left;
                dfs(y);
                set<char> &temp = first[tleft];
                auto it1 = temp.begin();
                bool flag = true;
                for (; it1 != temp.end(); it1++) {
                    if (*it1 == '~') flag = false;
                    first[left].insert(*it1);
                }
                if (flag) break;
            } else continue;
        }
}

void make_first() {
    memset(used, 0, sizeof(used));
    for (int i = 0; i < VN_set.size(); i++)
        dfs(i);
#ifdef DEBUG
    puts("***************FIRST SET***********************");
    auto it = first.begin();
    for (; it != first.end(); it++) {
        printf("FIRST(%s)={", it->first.c_str());
        set<char> &temp = it->second;
        auto it1 = temp.begin();
        bool flag = false;
        for (; it1 != temp.end(); it1++) {
            if (flag) printf(",");
            printf("%c", *it1);
            flag = true;
        }
        puts("}");
    }
#endif
}

void append(const string &str1, const string &str2) {
    set<char> &from = follow[str1];
    set<char> &to = follow[str2];
    auto it = from.begin();
    for (; it != from.end(); it++)
        to.insert(*it);
}

void make_follow() {
    while (true) {
        bool goon = false;
        for (int i = 0; i < VN_set.size(); i++) {
            string &left = VN_set[i].left;
            set<string> &right = VN_set[i].right;
            auto it = right.begin();
            for (; it != right.end(); it++) {
                bool flag = true;
                const string &str = *it;
                for (int j = it->length() - 1; j >= 0; j--) {
                    if (str[j] == '\'') {
                        int x = VN_dic[it->substr(j - 1, 2)] - 1;
                        if (flag) {
                            int tt = follow[it->substr(j - 1, 2)].size();
                            append(left, it->substr(j - 1, 2));
                            int tt1 = follow[it->substr(j - 1, 2)].size();
                            if (tt1 > tt) goon = true;
                            if (!VN_set[x].right.count("~"))
                                flag = false;
                        }
                        for (int k = j + 1; k < it->length(); k++) {
                            if (isupper(str[k])) {
                                string id;
                                if (k != it->length() - 1 && str[k + 1] == '\'')
                                    id = it->substr(k, 2);
                                else id = it->substr(k, 1);
                                set<char> &from = first[id];
                                set<char> &to = follow[it->substr(j - 1, 2)];
                                int tt = to.size();
                                auto it1 = from.begin();
                                for (; it1 != from.end(); it1++)
                                    if (*it1 != '~')
                                        to.insert(*it1);
                                int tt1 = follow[it->substr(j - 1, 2)].size();
                                if (tt1 > tt) goon = true;
                                if (!VN_set[VN_dic[id] - 1].right.count("~"))
                                    break;
                            } else if (str[k] != '\'') {
                                int tt = follow[it->substr(j - 1, 2)].size();
                                follow[it->substr(j - 1, 2)].insert(str[k]);
                                int tt1 = follow[it->substr(j - 1, 2)].size();
                                if (tt1 > tt)
                                    goon = true;
                                break;
                            } else continue;
                        }
                        j--;
                    } else if (isupper(str[j])) {
                        int x = VN_dic[it->substr(j, 1)] - 1;
                        if (flag) {
                            int tt = follow[it->substr(j, 1)].size();
                            append(left, it->substr(j, 1));
                            if (!VN_set[x].right.count("~"))
                                flag = false;
                            int tt1 = follow[it->substr(j, 1)].size();
                            if (tt1 > tt) goon = true;
                        }
                        for (int k = j + 1; k < it->length(); k++) {
                            if (isupper(str[k])) {
                                string id;
                                if (k != it->length() - 1 && str[k + 1] == '\'')
                                    id = it->substr(k, 2);
                                else id = it->substr(k, 1);
                                set<char> &from = first[id];
                                set<char> &to = follow[it->substr(j, 1)];
                                auto it1 = from.begin();
                                int tt = follow[it->substr(j, 1)].size();
                                for (; it1 != from.end(); it1++)
                                    if (*it1 != '~')
                                        to.insert(*it1);
                                int tt1 = follow[it->substr(j, 1)].size();
                                if (tt1 > tt) goon = true;
                                if (!VN_set[VN_dic[id] - 1].right.count("~"))
                                    break;
                            } else if (str[k] != '\'') {
                                int tt = follow[it->substr(j, 1)].size();
                                follow[it->substr(j, 1)].insert(str[k]);
                                int tt1 = follow[it->substr(j, 1)].size();
                                if (tt1 > tt) goon = true;
                                break;
                            } else continue;
                        }
                    } else flag = false;
                }
            }
        }
        if (!goon) break;
    }
#ifdef DEBUG
    puts("****************FOLLOW SET**********************");
    auto it = follow.begin();
    for (; it != follow.end(); it++) {
        printf("FOLLOW(%s)={", it->first.c_str());
        set<char> &temp = it->second;
        temp.insert('#');
        auto it1 = temp.begin();
        bool flag = false;
        for (; it1 != temp.end(); it1++) {
            if (flag) printf(",");
            printf("%c", *it1);
            flag = true;
        }
        puts("}");
    }
#endif
}

vector<map<char, string> > predict_table;

//检查一个字符是否属于一个字符串的FIRST集合
bool check_first(const string &text, char ch) {
    for (int i = 0; i < text.length(); i++) {
        bool hasEmpty = false;
        if (!isupper(text[i]) && text[i] != '\'') {
            if (text[i] != ch) return false;
            else return true;
        } else if (isupper(text[i])) {
            string temp;
            if (i != text.length() - 1 && text[i + 1] == '\'')
                temp = text.substr(i, 2);
            else
                temp = text.substr(i, 1);
            set<char> &dic = first[temp];
            auto it = dic.begin();
            for (; it != dic.end(); it++) {
                if (*it == '~') hasEmpty = true;
                if (*it == ch) return true;
            }
            if (!hasEmpty) break;
        } else continue;
    }
    return false;
}

//检查一个字符是否属于一个字符串的FOLLOW集合
bool check_follow(const string &text, char ch) {
    set<char> &dic = follow[text];
    auto it = dic.begin();
    for (; it != dic.end(); it++)
        if (*it == ch) return true;
    return false;
}

void make_table() {
    map<char, string> temp;
    vector<char> letter;
    bool vis[500];
    memset(vis, 0, sizeof(vis));
    for (auto &i : VN_set) {
        set<string> &right = i.right;
        auto it = right.begin();
        for (; it != right.end(); it++)
            for (char j : *it)
                if (!isupper(j) && j != '\'') {
                    if (vis[j]) continue;
                    vis[j] = true;
                    letter.push_back(j);
                }
    }
    for (auto &i : VN_set) {
        temp.clear();
        string &left = i.left;
        set<string> &right = i.right;
        auto it = right.begin();
        for (; it != right.end(); it++)
            for (char &j : letter) {
                //cout << *it << " " << letter[j] << endl;
                if (check_first(*it, j)) {
                    //cout << "YES" << endl;
                    temp[j] = *it;
                }
                if (it->at(0) == '~' && check_follow(left, j))
                    temp[j] = *it;
            }
        predict_table.push_back(temp);
    }
#ifdef DEBUG
    for (int i = 0; i <= (letter.size() + 1) * 10; i++)
        printf("-");
    puts("");
    printf("|%9s", "|");
    for (char i : letter)
        printf("%5c%5s", i, "|");
    puts("");
    for (int i = 0; i <= (letter.size() + 1) * 10; i++)
        printf("-");
    puts("");
    for (int i = 0; i < VN_set.size(); i++) {
        printf("|%5s%4s", VN_set[i].left.c_str(), "|");
        for (char &j : letter)
            if (predict_table[i].count(j))
                printf("%7s%3s", predict_table[i][j].c_str(), "|");
            else printf("%10s", "|");
        puts("");
        for (int i = 0; i <= (letter.size() + 1) * 10; i++)
            printf("-");
        puts("");
    }
#endif
}

int main() {
    int n;
    char s[MAX];
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; i++) {
            scanf("%s", s);
            int len = strlen(s), j;
            for (j = 0; j < len; j++)
                if (s[j] == '-') break;
            s[j] = 0;
            if (!VN_dic[s]) {
                VN_set.emplace_back(s);
                VN_dic[s] = VN_set.size();
            }
            int x = VN_dic[s] - 1;
            VN_set[x].insert(s + j + 2);
        }
        make_first();
        make_follow();
        make_table();
    }
}

/*
3
T->aA
T->c
A->b

8
E->TE'
E'->+TE'
E'->~
T->FT'
T'->*FT'
T'->~
F->i
F->(E)
*/