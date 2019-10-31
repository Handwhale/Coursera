#pragma once
#include "total_duration.h"
#include "global_stats.h"
#include "synchronized.h"

#include <istream>
#include <ostream>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <string_view>
#include <future>
using namespace std;

class InvertedIndex
{
public:
  struct IndexData
  {
    size_t docId;
    size_t hitcount;
  }; 

  InvertedIndex() = default;
  explicit InvertedIndex(istream &document_input);

  void AddDocument(string &&document);
  void ConstructIndex();
  const vector<IndexData> &Lookup(string_view word) const;

  int GetDocsCount() const { return docs.size(); }

private:
  map<string_view, vector<IndexData>> index;
  vector<string> docs;
};

class SearchServer
{
public:
  SearchServer() = default;
  explicit SearchServer(istream &document_input);
  void UpdateDocumentBase(istream &document_input);
  void AddQueriesStream(istream &query_input, ostream &search_results_output);

private:
  Synchronized<InvertedIndex> index_handler;
  vector<future<void>> async_task_holder;
};
