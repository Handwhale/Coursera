#pragma once

#include "date.h"
#include <string>
#include <memory>

enum Comparison {
    Less,
    LessOrEqual,
    GreaterOrEqual,
    Greater,
    Equal,
    NotEqual
};

enum LogicalOperation {
    And,
    Or
};

class Node {
public:
    virtual bool Evaluate(const Date &date, const std::string &event) = 0;
};

class EmptyNode : public Node{
    bool Evaluate(const Date &date, const std::string &event) override;
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison &cmp, const Date &date);
    bool Evaluate(const Date &date, const std::string &event) override;
private:
    Comparison _cmp;
    Date _date;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison &cmp, const std::string &event);
    bool Evaluate(const Date &date, const std::string &event) override;
private:
    Comparison _cmp;
    std::string _event;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(const LogicalOperation &logical_operation, std::shared_ptr<Node> left_node, std::shared_ptr<Node> right_node);
    bool Evaluate(const Date &date, const std::string &event) override;
private:
    LogicalOperation _log_op;
    std::shared_ptr<Node> _left_node, _right_node;
};