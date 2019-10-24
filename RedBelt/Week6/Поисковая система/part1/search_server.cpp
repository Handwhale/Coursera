#include "search_server.h"
#include "iterator_range.h"
#include "profile.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <vector>

vector<string> SplitIntoWords(const string &line)
{
  istringstream words_input(line);
  return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

SearchServer::SearchServer(istream &document_input)
{
  UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream &document_input)
{

  InvertedIndex new_index;

  for (string current_document; getline(document_input, current_document);)
  {
    new_index.Add(move(current_document));
  }

  index = move(new_index);
}

void SearchServer::AddQueriesStream(
    istream &query_input, ostream &search_results_output, SStats &stats) // прокид контекста с рефом на статы
{
  vector<pair<size_t, size_t>> docid_count(50'000, {0, 0});
  for (string current_query; getline(query_input, current_query);)
  {
    // const auto words = SplitIntoWords(current_query);
    vector<string> words;
    {
      // ADD DURATION SPLIT
      ADD_DURATION(stats.split);
      words = SplitIntoWords(current_query);
    }

    {
      // ADD DURATION LOOKUP
      ADD_DURATION(stats.lookup);

      for (const auto &word : words)
      {
        for (const size_t docid : index.Lookup(word))
        {
          docid_count[docid].first = docid;
          docid_count[docid].second++;
        }
      }
    }

    vector<pair<size_t, size_t>> search_results;
    {
      // ADD DURATION SORT
      ADD_DURATION(stats.sort);
      search_results = vector<pair<size_t, size_t>>(
          docid_count.begin(), docid_count.end());

      partial_sort(search_results.begin(), search_results.begin() + 5, search_results.end(),
          [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
            int64_t lhs_docid = lhs.first;
            auto lhs_hit_count = lhs.second;
            int64_t rhs_docid = rhs.first;
            auto rhs_hit_count = rhs.second;
            return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
          });
    }

    auto end_it = find_if(search_results.begin(), search_results.begin() + 5,
                          [](const pair<size_t, size_t> elem) { return elem.second == 0; });

    // ADD DURATION RESULT
    ADD_DURATION(stats.format);
    search_results_output << current_query << ':';
    for (auto [docid, hitcount] : Head(search_results, end_it - search_results.begin()))
    {
      search_results_output << " {"
                            << "docid: " << docid << ", "
                            << "hitcount: " << hitcount << '}';
    }
    search_results_output << endl;

    // clean up vector
    docid_count.assign(50'000, {0, 0});
  }
}

void InvertedIndex::Add(const string &document)
{
  docs.push_back(document);

  const size_t docid = docs.size() - 1;
  for (const auto &word : SplitIntoWords(document))
  {
    index[word].push_back(docid);
  }
}

list<size_t> InvertedIndex::Lookup(const string &word) const
{
  if (auto it = index.find(word); it != index.end())
  {
    return it->second;
  }
  else
  {
    return {};
  }
}
