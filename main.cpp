#include <bits/stdc++.h>

using namespace std;

map<string, vector<string>> neighbors;

class StringQueue
{
  queue<string> q;
  set<string> visited;

public:
  // insert a city into queue and mark visited
  void insert_and_mark_visited(const string &city)
  {
    q.push(city);
    visited.insert(city);
  }

  bool is_empty()
  {
    return q.empty();
  }

  string pop_and_get_first()
  {
    string s = q.front();
    q.pop();
    return s;
  }

  bool has_visited(const string &city)
  {
    return visited.find(city) != visited.end();
  }
};

enum solve_state
{
  SUCCESS, // 0
  FAILURE  // 1
};

// bidirectional search starts a search from the initial city and explores all its neighbours
// in the same time a search is also started from the goal city and explores all its neighbours
// if any start (initial or goal) reaches the other => SUCCESS
// if a city is visited by both starts, that means there is a connection => SUCCESS
// if both finish exploring and never meet => FAIL
solve_state bidirectional_search(const string &initial, const string &goal)
{
  StringQueue q_initial, q_goal; // queue initial && queue goal

  q_initial.insert_and_mark_visited(initial);
  q_goal.insert_and_mark_visited(goal);

  while (!q_initial.is_empty() && !q_goal.is_empty())
  {
    // --------- Queue Initial ---------
    string city = q_initial.pop_and_get_first();
    // current city from initial queue is the goal => initial queue has explored goal
    // or queue goal has visited current city from initial queue => intersection
    if (city == goal || q_goal.has_visited(city))
    {
      cout << "Meet in: " << city << endl;
      return solve_state::SUCCESS;
    }

    for (const string &u : neighbors[city])
      if (!q_initial.has_visited(u))
        q_initial.insert_and_mark_visited(u);

    // ---------  Queue Goal  ---------
    city = q_goal.pop_and_get_first();
    if (city == initial || q_initial.has_visited(city))
    {
      cout << "Meet in: " << city << endl;
      return solve_state::SUCCESS;
    }

    for (const string &u : neighbors[city])
      if (!q_goal.has_visited(u))
        q_goal.insert_and_mark_visited(u);
  }

  return solve_state::FAILURE;
}

int main()
{
  freopen("connected.in", "r", stdin); // SUCCESS
  // freopen("disconnected.in", "r", stdin); // FAIL

  string from, to, initial, goal;
  int n_cities, n_neighbors;
  cin >> n_cities;

  for (int i = 0; i < n_cities; i++)
  {
    cin >> from >> n_neighbors;
    for (int j = 0; j < n_neighbors; j++)
    {
      cin >> to;
      neighbors[from].push_back(to);
    }
  }

  cin >> initial >> goal;
  cout << (bidirectional_search(initial, goal) == solve_state::SUCCESS ? "SUCCESS" : "FAIL") << endl;
}