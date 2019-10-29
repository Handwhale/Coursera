#pragma once
#include "total_duration.h"
#include "global_stats.h"
#include <istream>
#include <ostream>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <string_view>
using namespace std;

class InvertedIndex
{
public:
  void Add(string &&document);
  list<size_t> Lookup(const string &word) const;

  const string &GetDocument(size_t id) const
  {
    return docs[id];
  }

  int GetDocsCount() const { return docs.size(); }

private:
  map<string, list<size_t>> index;
  vector<string> docs;
};

class SearchServer
{
public:
  SearchServer() = default;
  explicit SearchServer(istream &document_input);
  void UpdateDocumentBase(istream &document_input);
  void AddQueriesStream(istream &query_input, ostream &search_results_output, bool profile = false);

private:
  InvertedIndex index;
};
