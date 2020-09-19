#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void dfs(int node, const vector<vector<int>> &adj_list, vector<int> &ans, vector<bool> &visited) {
  if (!visited[node]) {
    visited[node] = true;
    for (int i = 0; i < adj_list[node].size(); i++) {
      dfs(adj_list[node][i], adj_list, ans, visited);
    }
    ans.push_back(node);
  }
}

vector<int> TopologicalSortByDFS(int N, vector<pair<int, int>> links) {
  vector<vector<int>> adj_list(N);
  for (auto link : links) {
    adj_list[link.first].push_back(link.second);
  }
  vector<int> ans;
  vector<bool> visited(N, false);
  for (int i = 0; i < N; i++) {
    dfs(i, adj_list, ans, visited);
  }
  reverse(ans.begin(), ans.end());
  return ans;
}

vector<int> TopologicalSortByBFS(int N, vector<pair<int, int>> links) {
  vector<vector<int>> adj_list(N);
  vector<int> in(N, 0);
  for (auto link : links) {
    adj_list[link.first].push_back(link.second);
    in[link.second]++;
  }
  queue<int> q;
  for (int i = 0; i < in.size(); i++) {
    if (in[i] == 0) {
      q.push(i);
    }
  }
  vector<int> ans;
  while (!q.empty()) {
    auto f = q.front();
    q.pop();
    ans.push_back(f);
    for (int i = 0; i < adj_list[f].size(); i++) {
      in[adj_list[f][i]]--;
      if (in[adj_list[f][i]] == 0) {
        q.push(adj_list[f][i]);
      }
    }
  }
  return ans;
}

int main() {
  int N = 4;
  vector<pair<int, int>> links{{0, 1}, {0, 2}, {1, 3}, {2, 3}};
  auto dfs_sorted = TopologicalSortByDFS(N, links);
  for (auto val : dfs_sorted) {
    cout << val << " ";
  }
  cout << endl;
  auto bfs_sorted = TopologicalSortByBFS(N, links);
  for (auto val : bfs_sorted) {
    cout << val << " ";
  }
  cout << endl;

  int M = 6;
  vector<pair<int, int>> links_2 = {{5, 0}, {5, 2}, {2, 3}, {4, 0}, {4, 1}, {1, 3}};
  auto dfs_sorted_2 = TopologicalSortByDFS(M, links_2);
  for (auto val : dfs_sorted_2) {
    cout << val << " ";
  }
  cout << endl;
  auto bfs_sorted_2 = TopologicalSortByBFS(M, links_2);
  for (auto val : bfs_sorted_2) {
    cout << val << " ";
  }
  cout << endl;
  return 0;
}
