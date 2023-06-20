#ifndef RPNTREE_HPP
#define RPNTREE_HPP
#include <iostream>
#include <string>
#include <memory>
#include <stack>
#include <vector>

class RPNNode
{
	public:
		virtual			~RPNNode() = default;
		virtual void	print() const = 0;
		virtual void	traverse() const = 0;
};

class VariableNode : public RPNNode
{
	private:
		char			m_variable;

	public:
		explicit		VariableNode(char variable) : m_variable(variable) {}
		char			get_variable() const { return m_variable; }
		void			print() const override { std::cout << m_variable; }
		void			traverse() const override { std::cout << m_variable; }
};

class UnaryOperatorNode : public RPNNode
{
	private:
		char						m_operator;
		std::unique_ptr<RPNNode>	m_operand;

	public:
		UnaryOperatorNode(char op, std::unique_ptr<RPNNode> operand) : m_operator(op), m_operand(std::move(operand)) {}
		char			get_operator() const { return m_operator; }
		const RPNNode*	get_operand() const { return m_operand.get(); }
		void			print() const override { std::cout << m_operator; m_operand->print(); }
		void			traverse() const override { std::cout << m_operator; }
};

class BinaryOperatorNode: public RPNNode
{
	private:
		char						m_operator;
		std::unique_ptr<RPNNode>	m_left;
		std::unique_ptr<RPNNode>	m_right;

	public:
		BinaryOperatorNode(char op, std::unique_ptr<RPNNode> left, std::unique_ptr<RPNNode> right) : m_operator(op), m_left(std::move(left)), m_right(std::move(right)) {}
		char			get_operator() const { return m_operator; }
		const RPNNode*	get_left() const { return m_left.get(); }
		const RPNNode*	get_right() const { return m_right.get(); }
		void			print() const override { m_left->print(); m_right->print(); std::cout << m_operator; }
		void			traverse() const override { std::cout << m_operator; }
		void			swap_child_nodes() { std::swap(m_left, m_right); }
};

std::unique_ptr<RPNNode> build_tree(const std::string& formula);
void	print_node(const RPNNode* node);
void	print_tree(const RPNNode* node);
void	print_tree(const std::string& prefix, const RPNNode* node, bool isLeft);
void	reverse_traversal(const RPNNode* node);

#endif