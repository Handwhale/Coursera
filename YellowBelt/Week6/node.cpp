#include "node.h"

using namespace std;

template<class T>
bool ValueComparison(const Comparison &cmp, const T &predicate_val, const T &eval_val) {
    switch (cmp) {
        case Comparison::Equal :
            return eval_val == predicate_val;
        case Comparison::NotEqual:
            return eval_val != predicate_val;
        case Comparison::Greater:
            return eval_val > predicate_val;
        case Comparison::GreaterOrEqual:
            return eval_val >= predicate_val;
        case Comparison::Less :
            return eval_val < predicate_val;
        case Comparison::LessOrEqual:
            return eval_val <= predicate_val;
    }
    throw logic_error("Unexpected comparison sign");
}

bool EmptyNode::Evaluate(const Date &date, const std::string &event) {
    return true;
}

DateComparisonNode::DateComparisonNode(const Comparison &cmp, const Date &date) : _cmp(cmp), _date(date) {}

bool DateComparisonNode::Evaluate(const Date &date, const std::string &event) {
    return ValueComparison(_cmp, _date, date);

//    switch (_cmp) {
//        case Comparison::Equal :
//            return date == _date;
//        case Comparison::NotEqual:
//            return date != _date;
//        case Comparison::Greater:
//            return date > _date;
//        case Comparison::GreaterOrEqual:
//            return date >= _date;
//        case Comparison::Less :
//            return date < _date;
//        case Comparison::LessOrEqual:
//            return date <= _date;
//    }
}

EventComparisonNode::EventComparisonNode(const Comparison &cmp, const std::string &event) : _cmp(cmp), _event(event) {}

bool EventComparisonNode::Evaluate(const Date &date, const std::string &event) {
    return ValueComparison(_cmp, _event, event);
}

LogicalOperationNode::LogicalOperationNode(
        const LogicalOperation &logical_operation, std::shared_ptr<Node> left_node, std::shared_ptr<Node> right_node) :
        _log_op(logical_operation), _left_node(left_node), _right_node(right_node) {}

bool LogicalOperationNode::Evaluate(const Date &date, const std::string &event) {
    auto left_result = _left_node->Evaluate(date, event);
    auto right_result = _right_node->Evaluate(date, event);

    if (_log_op == LogicalOperation::And)
        return (left_result && right_result);
    if(_log_op == LogicalOperation::Or)
        return (left_result || right_result);

    throw logic_error("Unexpected logical sign");
}