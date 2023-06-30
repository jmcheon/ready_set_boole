#include "RPNtree.hpp"

std::unique_ptr<RPNNode> buildTree(const std::string& formula)
{
	std::stack<std::unique_ptr<RPNNode> > stack;

	for (char c : formula)
	{
		if (c >= 'A' && c <= 'Z')
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

void	printNode(const RPNNode* node)
{
	if (node)
		node->print();
	std::cout << std::endl;
}

void	printTreeLeftview(const std::string& prefix, const RPNNode* node, bool is_left)
{
    if( node != nullptr )
    {
        std::cout << prefix;
        std::cout << (is_left ? "└─" : "├─" );

		node->traverse();
    	std::cout << std::endl;
    	if (const UnaryOperatorNode* unary_node = dynamic_cast<const UnaryOperatorNode*>(node))
        	printTreeLeftview(prefix + (is_left ? "   " : "│  "), unary_node->getOperand(), true);
    	if (const BinaryOperatorNode* binary_node = dynamic_cast<const BinaryOperatorNode*>(node))
		{
        	printTreeLeftview(prefix + (is_left ? "   " : "│  "), binary_node->getRight(), false);
        	printTreeLeftview(prefix + (is_left ? "   " : "│  "), binary_node->getLeft(), true);
    	}
    }
}

void	printTreeRightview(const std::string& prefix, const RPNNode* node, bool is_left)
{
    if( node != nullptr )
    {
        std::cout << prefix;
        std::cout << (is_left ? "├─" : "└─" );

		node->traverse();
    	std::cout << std::endl;
    	if (const UnaryOperatorNode* unary_node = dynamic_cast<const UnaryOperatorNode*>(node))
        	printTreeRightview(prefix + (is_left ? "│  " : "   "), unary_node->getOperand(), false);
    	if (const BinaryOperatorNode* binary_node = dynamic_cast<const BinaryOperatorNode*>(node))
		{
        	printTreeRightview(prefix + (is_left ? "│  " : "   "), binary_node->getLeft(), true);
        	printTreeRightview(prefix + (is_left ? "│  " : "   "), binary_node->getRight(), false);
    	}
    }
}

void	printTree(const RPNNode* node, bool leftview)
{
	if (leftview)
    	printTreeLeftview("", node, true);
	else
    	printTreeRightview("", node, false);
}

void	reverseTraversal(const RPNNode* node)
{
    if (node != nullptr)
	{
		node->traverse();
    	if (const BinaryOperatorNode* binary_node = dynamic_cast<const BinaryOperatorNode*>(node))
    	{
    	    reverseTraversal(binary_node->getRight());
    	    reverseTraversal(binary_node->getLeft());
    	}
    	else if (const UnaryOperatorNode* unary_node = dynamic_cast<const UnaryOperatorNode*>(node))
    	    reverseTraversal(unary_node->getOperand());
		}
}

