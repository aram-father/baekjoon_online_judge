#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <memory>

using namespace std;

struct Edge
{
  int source_;
  int destination_;
  int capacity_;
  int flow_;
  int cost_;
  Edge* reverse_;

  static void AddEdge(vector<vector<shared_ptr<Edge> > >& adjacent_list, const int source, const int destination,
                      const int capacity, const int cost)
  {
    Edge* forward = new Edge();
    Edge* reverse = new Edge();

    forward->source_ = source;
    forward->destination_ = destination;
    forward->capacity_ = capacity;
    forward->flow_ = 0;
    forward->cost_ = cost;

    reverse->source_ = destination;
    reverse->destination_ = source;
    reverse->capacity_ = 0;
    reverse->flow_ = 0;
    reverse->cost_ = -cost;

    forward->reverse_ = reverse;
    reverse->reverse_ = forward;

    adjacent_list[source].emplace_back(forward);
    adjacent_list[destination].emplace_back(reverse);
  }
};

static const int kMaxV = 1000;
static const int kMaxCost = 100;
static const int kMaxDistance = kMaxV * kMaxCost + 1;

int V, E;
vector<vector<shared_ptr<Edge> > > ADJACENT_LIST;

int Spfa(const int source, const int sink, vector<Edge*>& edges)
{
  edges.assign(2 * V, nullptr);

  vector<bool> is_queued(2 * V, false);
  vector<int> distances(2 * V, kMaxDistance);
  queue<int> q;

  is_queued[source] = true;
  distances[source] = 0;
  q.push(source);

  while (!q.empty())
  {
    int here = q.front();
    q.pop();

    is_queued[here] = false;

    for (const auto& edge : ADJACENT_LIST[here])
    {
      int there = edge->destination_;
      int residual = edge->capacity_ - edge->flow_;
      if (residual > 0 && distances[there] > distances[here] + edge->cost_)
      {
        distances[there] = distances[here] + edge->cost_;
        edges[there] = edge.get();
        if (!is_queued[there])
        {
          is_queued[there] = true;
          q.push(there);
        }
      }
    }
  }

  if (edges[sink] == nullptr)
  {
    return 0;
  }

  int min_residual = kMaxV;
  int current = sink;
  while (current != source)
  {
    min_residual = min(min_residual, edges[current]->capacity_ - edges[current]->flow_);
    current = edges[current]->source_;
  }

  return min_residual;
}

int Solve(const int source, const int sink)
{
  int ret = 0;

  while (true)
  {
    vector<Edge*> edges;
    const int min_residual = Spfa(source, sink, edges);

    if (min_residual == 0)
    {
      break;
    }

    int current = sink;
    while (current != source)
    {
      ret += min_residual * edges[current]->cost_;
      edges[current]->flow_ += min_residual;
      edges[current]->reverse_->flow_ -= min_residual;
      current = edges[current]->source_;
    }
  }

  return ret;
}

int main(void)
{
  // For faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  while (cin >> V >> E)
  {
    const int kSource = 0;
    const int kSink = 2 * V - 1;

    ADJACENT_LIST.assign(2 * V, vector<shared_ptr<Edge> >());

    Edge::AddEdge(ADJACENT_LIST, kSource, kSource + 1, 2, 0);
    Edge::AddEdge(ADJACENT_LIST, kSink - 1, kSink, 2, 0);

    for (int v = 1; v < V - 1; ++v)
    {
      int in = 2 * v;
      int out = in + 1;
      Edge::AddEdge(ADJACENT_LIST, in, out, 1, 0);
    }

    for (int it = 0; it < E; ++it)
    {
      int a, b, c;
      cin >> a >> b >> c;

      int out = 2 * (a - 1) + 1;
      int in = 2 * (b - 1);

      Edge::AddEdge(ADJACENT_LIST, out, in, 1, c);
    }

    cout << Solve(kSource, kSink) << "\n";
  }

  return 0;
}
