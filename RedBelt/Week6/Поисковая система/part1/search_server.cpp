#include "search_server.h"
#include "iterator_range.h"
#include "profile.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <vector>
#include <string_view>

vector<string_view> SplitIntoWords(string_view line)
{
  vector<string_view> result;
  size_t first = 0;

  while (first < line.size())
  {
    const auto second = line.find_first_of(' ', first);

    if (first != second)
      result.emplace_back(line.substr(first, second - first));

    if (second == string_view::npos)
      break;

    first = second + 1;
  }

  return result;
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
    new_index.AddDocument(move(current_document));
  }

  new_index.ConstructIndex();

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
    vector<string_view> words;
    {
      // ADD DURATION SPLIT
      ADD_DURATION(stats.split);
      words = SplitIntoWords(current_query);
    }

    {
      // ADD DURATION LOOKUP
      ADD_DURATION(stats.lookup);

      for (string_view &word : words)
      {
        for (const auto &docid : index.Lookup(word))
        {
          docid_count[docid.docId].first = docid.docId;
          docid_count[docid.docId].second += docid.hitcount;
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

void InvertedIndex::AddDocument(string &&document)
{
  docs.push_back(move(document));
}

void InvertedIndex::ConstructIndex()
{
  for (size_t docid = 0; docid < docs.size(); docid++)
    for (string_view word : SplitIntoWords(docs[docid]))
    {
      auto &word_index = index[word];
      if (word_index.empty() || word_index.back().docId != docid)
        word_index.push_back({docid, 1});
      else
        word_index.back().hitcount++;
    }
}

const vector<InvertedIndex::IndexData> &InvertedIndex::Lookup(string_view word) const
{
  static const vector<IndexData> empty_result;
  if (auto it = index.find(word); it != index.end())
  {
    return it->second;
  }
  else
  {
    return empty_result;
  }
}
