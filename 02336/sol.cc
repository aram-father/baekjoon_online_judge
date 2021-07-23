#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

const size_t kMaxNumberOfStudents = 500000;

class Exam
{
public:
  static const size_t k1st = 0;
  static const size_t k2nd = 1;
  static const size_t k3rd = 2;

  size_t ranks_[3];

  bool operator<(const Exam& exam) const
  {
    return ranks_[k1st] < exam.ranks_[k1st];
  }
};

class RankTree
{
private:
  size_t size_;
  size_t node_[kMaxNumberOfStudents * 4];

  size_t Update(const size_t root, const size_t root_left, const size_t root_right, const size_t update_index,
                const size_t update_value)
  {
    if (update_index < root_left || root_right < update_index)
    {
      return node_[root];
    }

    if (root_left == root_right)
    {
      return (node_[root] = update_value);
    }

    const size_t root_mid = (root_left + root_right) / 2;
    const size_t left = Update(2 * root, root_left, root_mid, update_index, update_value);
    const size_t right = Update(2 * root + 1, root_mid + 1, root_right, update_index, update_value);

    return (node_[root] = min(left, right));
  }

  size_t Query(const size_t root, const size_t root_left, const size_t root_right, const size_t query_left,
               const size_t query_right)
  {
    if (query_right < root_left || root_right < query_left)
    {
      return kMaxNumberOfStudents + 1;
    }

    if (query_left <= root_left && root_right <= query_right)
    {
      return node_[root];
    }

    const size_t root_mid = (root_left + root_right) / 2;
    const size_t left = Query(2 * root, root_left, root_mid, query_left, query_right);
    const size_t right = Query(2 * root + 1, root_mid + 1, root_right, query_left, query_right);

    return min(left, right);
  }

public:
  RankTree(const size_t size) : size_(size)
  {
    memset(node_, kMaxNumberOfStudents + 1, size_ * 4 * sizeof(size_t));
  }

  void Update(const size_t index, const size_t value)
  {
    Update(1, 1, size_, index, value);
  }

  size_t Query(const size_t left, const size_t right)
  {
    if (left > right)
    {
      return kMaxNumberOfStudents + 1;
    }

    return Query(1, 1, size_, left, right);
  }
};

size_t number_of_students;
vector<Exam> exam;
RankTree* rank_tree;

int main(void)
{
  // For faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read input
  cin >> number_of_students;

  exam.assign(number_of_students, Exam());

  for (size_t rank = 1; rank <= number_of_students; ++rank)
  {
    size_t student_no;
    cin >> student_no;
    exam[student_no - 1].ranks_[Exam::k1st] = rank;
  }

  for (size_t rank = 1; rank <= number_of_students; ++rank)
  {
    size_t student_no;
    cin >> student_no;
    exam[student_no - 1].ranks_[Exam::k2nd] = rank;
  }

  for (size_t rank = 1; rank <= number_of_students; ++rank)
  {
    size_t student_no;
    cin >> student_no;
    exam[student_no - 1].ranks_[Exam::k3rd] = rank;
  }

  // Preprocess
  sort(exam.begin(), exam.end());
  rank_tree = new RankTree(number_of_students);

  // Solve
  size_t tremendous = 0;

  for (size_t idx = 0; idx < number_of_students; ++idx)
  {
    if (rank_tree->Query(1, exam[idx].ranks_[Exam::k2nd] - 1) > exam[idx].ranks_[Exam::k3rd])
    {
      ++tremendous;
    }

    rank_tree->Update(exam[idx].ranks_[Exam::k2nd], exam[idx].ranks_[Exam::k3rd]);
  }

  cout << tremendous << "\n";

  return 0;
}
