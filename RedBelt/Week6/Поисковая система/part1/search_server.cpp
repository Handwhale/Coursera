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
    istream &query_input, ostream &docid_count_output, bool profile)
{
  SStats stats = {TotalDuration{"Split into words"},
                  TotalDuration{"Index lookup"},
                  TotalDuration{"Document sort"},
                  TotalDuration{"Result concat"}};

  vector<pair<size_t, size_t>> docid_count(max(index.GetDocsCount(), 5), {0, 0});
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

    {
      // ADD DURATION SORT
      ADD_DURATION(stats.sort);

      partial_sort(docid_count.begin(), docid_count.begin() + 5, docid_count.end(),
                   [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
                     int64_t lhs_docid = lhs.first;
                     auto lhs_hit_count = lhs.second;
                     int64_t rhs_docid = rhs.first;
                     auto rhs_hit_count = rhs.second;
                     return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
                   });
    }

    auto end_it = find_if(docid_count.begin(), Head(docid_count, 5).end(),
                          [](const pair<size_t, size_t> elem) { return elem.second == 0; });

    // ADD DURATION RESULT
    ADD_DURATION(stats.format);
    docid_count_output << current_query << ':';
    for (auto [docid, hitcount] : Head(docid_count, end_it - docid_count.begin()))
    {
      docid_count_output << " {"
                         << "docid: " << docid << ", "
                         << "hitcount: " << hitcount << '}';
    }
    docid_count_output << endl;

    // clean up vector
    docid_count.assign(docid_count.size(), {0, 0});
  }
}

void InvertedIndex::Add(string &&document)
{
  docs.push_back(move(document));

  const size_t docid = docs.size() - 1;
  for (const auto &word : SplitIntoWords(docs.back()))
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
