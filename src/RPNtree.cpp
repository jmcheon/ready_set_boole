#include "RPNtree.hpp"

std::unique_ptr<RPNNode> buildTree(const std::string& formula)
{
	std::stack<std::unique_ptr<RPNNode> > stack;
	
	for (char c : formula)
	{
		if (c >= 'A' && c <= 'Z')
		{
			std::unique_ptr<RPNNode> new_node = std::make_unique<RPNNode>(c, nullptr, nullptr);
			stack.push(std::move(new_node));
		}
		else if (c == '!')
		{
			if (stack.empty())
				throw std::runtime_error("Invalid formula: Not enough operands");
			std::unique_ptr<RPNNode> new_node = std::make_unique<RPNNode>(c, nullptr, nullptr);
			new_node->m_left = std::move(stack.top());
			stack.pop();
			stack.push(std::move(new_node));
		}
		else if (c == '&' || c == '|' || c == '^' || c == '>' || c == '=')
		{
			if (stack.size() < 2)
				throw std::runtime_error("Invalid formula: Not enough operands");
			std::unique_ptr<RPNNode> new_node = std::make_unique<RPNNode>(c, nullptr, nullptr);
			new_node->m_right = std::move(stack.top());
			stack.pop();
			new_node->m_left = std::move(stack.top());
			stack.pop();
			stack.push(std::move(new_node));
		}
		else
			throw std::runtime_error("Invalid formula: Unexpected symbol");
	}
	if (stack.size() != 1)
		throw std::runtime_error("Invalid formula: Too many operands");
	return std::move(stack.top());
}

std::string	postorder(std::unique_ptr<RPNNode>& root)
{
	std::string output;

    if (root == nullptr)
        return output;

    output += postorder(root->m_left);
    output += postorder(root->m_right);
    output += root->getValue();
	return output;
}

std::string	inorder(std::unique_ptr<RPNNode>& root)
{
	std::string output;

	if (!root)
		return output;
	
	if (isupper(root->getValue()))
		output += root->getValue();
	output += inorder(root->m_left);
	
	if (!isupper(root->getValue()))
		output += root->getValue();
	output += inorder(root->m_right);
	return output;
}

std::unique_ptr<RPNNode> distribute(std::unique_ptr<RPNNode>& a, std::unique_ptr<RPNNode>& b, std::unique_ptr<RPNNode>& c)
{
    auto new_root = std::make_unique<RPNNode>('&');
    new_root->m_left = std::make_unique<RPNNode>('|', a->clone(), std::move(b));
    new_root->m_right = std::make_unique<RPNNode>('|', a->clone(), std::move(c));
    return new_root;
}

bool isDistributable(const std::unique_ptr<RPNNode>& root)
{
    if (!root)
        return false;
    return (root->getValue() == '|' && ((root->m_left && root->m_left->getValue() == '&') || (root->m_right && root->m_right->getValue() == '&')));
}

std::unique_ptr<RPNNode> applyDistributiveLaw(std::unique_ptr<RPNNode>& root)
{
    if (!root)
        return nullptr;

    root->m_left = applyDistributiveLaw(root->m_left);
    root->m_right = applyDistributiveLaw(root->m_right);

    if (isDistributable(root)) {
        std::unique_ptr<RPNNode> a, b, c;

        if (root->m_left && root->m_left->getValue() == '&') {
			    a = std::move(root->m_right);
			    b = std::move(root->m_left->m_left);
			    c = std::move(root->m_left->m_right);
        } else if (root->m_right && root->m_right->getValue() == '&') {
			    a = std::move(root->m_right);
			    b = std::move(root->m_left->m_left);
			    c = std::move(root->m_left->m_right);
				/*
        } else if (root->m_left && root->m_left->getValue() == '|') {
			    a = std::move(root->m_right);
			    b = std::move(root->m_left->m_left);
			    c = std::move(root->m_left->m_right);
				*/
        } else { // (root->m_right && root->m_right->getValue() == '|')
			    a = std::move(root->m_left);
			    b = std::move(root->m_right->m_left);
			    c = std::move(root->m_right->m_right);
        }

        root = distribute(a, b, c);
        root->m_left = applyDistributiveLaw(root->m_left);
        root->m_right = applyDistributiveLaw(root->m_right);
    }

    return std::move(root);
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
        printTreeLeftview(prefix + (is_left ? "   " : "│  "), node->getRight(), false);
        printTreeLeftview(prefix + (is_left ? "   " : "│  "), node->getLeft(), true);
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
        printTreeRightview(prefix + (is_left ? "│  " : "   "), node->getLeft(), true);
        printTreeRightview(prefix + (is_left ? "│  " : "   "), node->getRight(), false);
    }
}

void	printTree(const RPNNode* node, bool leftview)
{
	if (leftview)
    	printTreeLeftview("", node, true);
	else
    	printTreeRightview("", node, false);
}
