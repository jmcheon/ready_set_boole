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
		char			getVariable() const { return m_variable; }
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
		char			getOperator() const { return m_operator; }
		const RPNNode*	getOperand() const { return m_operand.get(); }
		void			print() const override { m_operand->print(); std::cout << m_operator; }
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
		char			getOperator() const { return m_operator; }
		const RPNNode*	getLeft() const { return m_left.get(); }
		const RPNNode*	getRight() const { return m_right.get(); }
		void			print() const override { m_left->print(); m_right->print(); std::cout << m_operator; }
		void			traverse() const override { std::cout << m_operator; }
		void			swapChildNodes() { std::swap(m_left, m_right); }
};

std::unique_ptr<RPNNode> buildTree(const std::string& formula);
void	printNode(const RPNNode* node);
void	printTree(const RPNNode* node, bool leftview=false);
void	printTreeRightview(const std::string& prefix, const RPNNode* node, bool is_left);
void	printTreeLeftview(const std::string& prefix, const RPNNode* node, bool is_left);
void	reverseTraversal(const RPNNode* node);

#endif
