#include "RPNtree.hpp"

std::unique_ptr<RPNNode> build_tree(const std::string& formula)
{
	std::stack<std::unique_ptr<RPNNode> > stack;

	for (char c : formula)
	{
		if (isalpha(c))
			stack.push(std::make_unique<VariableNode>(c));
		else if (c == '!')
		{
			if (stack.empty())
				throw std::runtime_error("Invalid formula: Not enough operands");
			std::unique_ptr<RPNNode> operand = std::move(stack.top());
			stack.pop();
			stack.push(std::make_unique<UnaryOperatorNode>(c, std::move(operand)));
		}
		else if (c == '&' || c == '|' || c == '^' || c == '>' || c == '=')
		{
			if (stack.size() < 2)
				throw std::runtime_error("Invalid formula: Not enough operands");
			std::unique_ptr<RPNNode> right = std::move(stack.top());
			stack.pop();
			std::unique_ptr<RPNNode> left = std::move(stack.top());
			stack.pop();
			stack.push(std::make_unique<BinaryOperatorNode>(c, std::move(left), std::move(right)));
		}
		else
			throw std::runtime_error("Invalid formula: Unexpected symbol");
	}
	if (stack.size() != 1)
		throw std::runtime_error("Invalid formula: Too many operands");
	return std::move(stack.top());
}

void	print_node(const RPNNode* node)
{
	if (node)
		node->print();
	std::cout << std::endl;
}

void	print_tree(const RPNNode* node, int indent)
{
    if (node == nullptr) {
        return;
    }

    std::cout << std::string(indent, ' ');
	node->traverse();
    std::cout << std::endl;
    //std::cout << std::string(indent, ' ') << "Node Type: " << typeid(*node).name();
    if (const UnaryOperatorNode* unary_node = dynamic_cast<const UnaryOperatorNode*>(node)) {
        print_tree(unary_node->get_operand(), indent + 2);
        return;
    }

    if (const BinaryOperatorNode* binary_node = dynamic_cast<const BinaryOperatorNode*>(node)) {
        print_tree(binary_node->get_right(), indent + 2);
        print_tree(binary_node->get_left(), indent + 2);
    }
}

void	reverse_traversal(const RPNNode* node)
{
    if (node == nullptr) {
        return;
	}

	node->traverse();
    if (const BinaryOperatorNode* binary_node = dynamic_cast<const BinaryOperatorNode*>(node))
    {
        reverse_traversal(binary_node->get_right());
        reverse_traversal(binary_node->get_left());
    }
    else if (const UnaryOperatorNode* unary_node = dynamic_cast<const UnaryOperatorNode*>(node))
        reverse_traversal(unary_node->get_operand());
}

